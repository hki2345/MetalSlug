#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
	std::map<std::wstring, Command*>::iterator StartIter = m_map_KeyCommand.begin();
	std::map<std::wstring, Command*>::iterator EndIter = m_map_KeyCommand.end();

	for (; StartIter != EndIter; StartIter++)
	{
		NEW_DELETE(StartIter->second);
	}
}



// 커맨드에 저장된 키가 알맞게 눌렸는지 검사
void KeyManager::Command::Get_Key_Check()
{

	for (size_t i = 0; i < m_vector_KeyData.size(); i++)
	{
		// 키의 상태가 0이면 눌리지 않는다.
		// 수업시간에는 추측한다고 하였으나 결국 잘되므로 암묵적으로
		// 이렇게 되는 걸로 판단.
		// 하나라도 눌리지 않으면 눌린 것이 아니다.
		if (0 != GetAsyncKeyState(m_vector_KeyData[i]))
		{
			// 누르고 있는 데이터를 넣는다.
			Insert_PressData(m_vector_KeyData[i]);
		}
		else
		{
			// 누른 곳을 0으로 만들던지 놔두던지 -> 어차피 0이니까
			Insert_EraseData(m_vector_KeyData[i]);
		}
	}
}

// 연쇄 키의 경우 최초 1회 입력하는 것인지
// 다른 일부의 키를 눌렀다가 뗀 것인지 검사
void KeyManager::Command::Press_Check()
{
	// 완벽한데 0이 있음 (그 키를 때었다) -> 더는 완벽한 것이 아님
	// 하지만 다 떼었다고는 볼 수 없음 ... 왜냐면 일부키가 아직
	// 눌리는 중이므로 해당 키를 다시 누르면 다시 올바르게 입력이 되었다고 판별되기에
	// 일부만 눌렸다는 -1에 대한 경우를 더 늘림
	if (1 == m_PressCheck)
	{
		for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
		{
			if (0 != m_vector_KeyPressData[i])
			{
				continue;
			}
			else
			{
				m_PressCheck = -1;
				return;
			}
		}
	}
	// 틀렸을 경우 -> 모두 뗀 경우에만 -> 초기화
	else
	if(-1 == m_PressCheck)
	{
		for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
		{
			if (0 == m_vector_KeyPressData[i])
			{
				continue;
			}
			else
			{
				return;
			}
		}
		m_PressCheck = 0;
	}
}

// Command최종 검사 부분 -> 입력 순서를 따지고
// 이전에 키보드를 알맞게 누른 것을 검사에 적용
bool KeyManager::Command::Chain_Check()
{
	// 한 번 더 검사 -> 순서가 맞는지 검사.
	// 때가 되면 위에 포문에 합류 시킬 수 있는지... -> 왜냐하면 버퍼가 한 번 다 채워져야 하니까
	for (size_t i = 0; i < m_vector_KeyData.size(); i++)
	{
		if (m_vector_KeyData[i] != m_vector_KeyPressData[i])
		{
			return false;
		}
	}

	// 키가 이전에 눌렸는지 체크하는 부분
	// 0 최초 실행 + 1 알맞게 누르며 계속 알맞게 누르는 중이다.
	if (0 == m_PressCheck || 1 == m_PressCheck)
	{
		// 키보드를 알맞게 눌렀다.
		m_PressCheck = 1;
	}

	// 최초에 알맞게 눌렀으나 도중에 때었다.
	else
	if (-1 == m_PressCheck)
	{
		return false;
	}

	return true;
}




// 임시 검사 데이터에 해당 데이터를 넣는다. -> 1회만
void KeyManager::Command::Insert_PressData(const int& _Value)
{
	// 담고 있는 데이터 만큼
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// 해당 키가 하나라도 있으면 -> 누르고 있는 중이다.
		if (_Value == m_vector_KeyPressData[i])
		{
			return;
		}
	}

	// 누르지 않았으므로 눌렀다고 넣어준다.
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// 0인 곳 -> 빈 곳에 넣어준다.
		if (0 == m_vector_KeyPressData[i])
		{
			m_vector_KeyPressData[i] = _Value;
			return;
		}
	}
}

// 임시 키 버퍼를 초기화 시킨다.
void KeyManager::Command::Insert_EraseData(const int& _Value)
{
	// 눌렀으므로 뗀것으로 만들어준다.
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// 값인 곳 -> 빈 곳으로 만들어준다.
		if (_Value == m_vector_KeyPressData[i])
		{
			m_vector_KeyPressData[i] = 0;
			// 어차피 데이터는 한개이니까 여기서 마무리
			return;
		}
	}
}




// 명령이 모두 맞는지 체크한다 -> 벡터안에 내용이 맞는지 확인
bool KeyManager::Command::Command_Check()
{
	Get_Key_Check();
	Press_Check();
	return Chain_Check();
}



void KeyManager::Command::Update()
{
	// 이 커맨드의 실행여부부터 판별한다.
	bool Check = Command_Check();

	// 커맨드가 눌린 경우
	if (true == Check)
	{
		// 이전 프레임에서 눌리지 않음
		if (true == m_UnPress)
		{
			m_UnPress = false;
			m_Up = false;
			m_Down = true;
			m_Press = true;
		}

		// 이전 프레임에서 눌림
		else
		if (false == m_UnPress)
		{
			m_UnPress = false;
			m_Up = false;
			m_Down = false;
			m_Press = true;
		}
	}
	else
	if (false == Check)
	{
		// 이전 프레임에서 눌리지 않음
		if (true == m_UnPress)
		{
			m_UnPress = true;
			m_Up = false;
			m_Down = false;
			m_Press = false;
		}

		// 이전 프레임에서 눌림
		else
		if (false == m_UnPress)
		{
			m_UnPress = true;
			m_Up = true;
			m_Down = false;
			m_Press = false;
		}
	}
}


// 키 맵의 저장된 커맨더들을 하나씩 업데이트하는 과정
// 이것은 코어나 스테이트 업데이트에서 업데이트 될 것
void KeyManager::Update()
{
	StartIter = m_map_KeyCommand.begin();
	EndIter = m_map_KeyCommand.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if (nullptr != StartIter->second)
		{
			StartIter->second->Update();
		}
	}
}


#pragma region	KEY_STATE

bool KeyManager::IsUp(const WCHAR* _Name)
{
	Command* FC = FindCommand(_Name);
	KAssert(nullptr == FC);
	return FC->IsUp();
}
bool KeyManager::IsUnPress(const WCHAR* _Name)
{
	Command* FC = FindCommand(_Name);
	KAssert(nullptr == FC);
	return FC->IsUnPress();
}
bool KeyManager::IsDown(const WCHAR* _Name)
{
	Command* FC = FindCommand(_Name);
	KAssert(nullptr == FC);
	return FC->IsDown();
}
bool KeyManager::IsPress(const WCHAR* _Name)
{
	Command* FC = FindCommand(_Name);
	KAssert(nullptr == FC);
	return FC->IsPress();
}

#pragma endregion