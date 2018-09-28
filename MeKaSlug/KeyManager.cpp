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



// Ŀ�ǵ忡 ����� Ű�� �˸°� ���ȴ��� �˻�
void KeyManager::Command::Get_Key_Check()
{

	for (size_t i = 0; i < m_vector_KeyData.size(); i++)
	{
		// Ű�� ���°� 0�̸� ������ �ʴ´�.
		// �����ð����� �����Ѵٰ� �Ͽ����� �ᱹ �ߵǹǷ� �Ϲ�������
		// �̷��� �Ǵ� �ɷ� �Ǵ�.
		// �ϳ��� ������ ������ ���� ���� �ƴϴ�.
		if (0 != GetAsyncKeyState(m_vector_KeyData[i]))
		{
			// ������ �ִ� �����͸� �ִ´�.
			Insert_PressData(m_vector_KeyData[i]);
		}
		else
		{
			// ���� ���� 0���� ������� ���δ��� -> ������ 0�̴ϱ�
			Insert_EraseData(m_vector_KeyData[i]);
		}
	}
}

// ���� Ű�� ��� ���� 1ȸ �Է��ϴ� ������
// �ٸ� �Ϻ��� Ű�� �����ٰ� �� ������ �˻�
void KeyManager::Command::Press_Check()
{
	// �Ϻ��ѵ� 0�� ���� (�� Ű�� ������) -> ���� �Ϻ��� ���� �ƴ�
	// ������ �� �����ٰ�� �� �� ���� ... �ֳĸ� �Ϻ�Ű�� ����
	// ������ ���̹Ƿ� �ش� Ű�� �ٽ� ������ �ٽ� �ùٸ��� �Է��� �Ǿ��ٰ� �Ǻ��Ǳ⿡
	// �Ϻθ� ���ȴٴ� -1�� ���� ��츦 �� �ø�
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
	// Ʋ���� ��� -> ��� �� ��쿡�� -> �ʱ�ȭ
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

// Command���� �˻� �κ� -> �Է� ������ ������
// ������ Ű���带 �˸°� ���� ���� �˻翡 ����
bool KeyManager::Command::Chain_Check()
{
	// �� �� �� �˻� -> ������ �´��� �˻�.
	// ���� �Ǹ� ���� ������ �շ� ��ų �� �ִ���... -> �ֳ��ϸ� ���۰� �� �� �� ä������ �ϴϱ�
	for (size_t i = 0; i < m_vector_KeyData.size(); i++)
	{
		if (m_vector_KeyData[i] != m_vector_KeyPressData[i])
		{
			return false;
		}
	}

	// Ű�� ������ ���ȴ��� üũ�ϴ� �κ�
	// 0 ���� ���� + 1 �˸°� ������ ��� �˸°� ������ ���̴�.
	if (0 == m_PressCheck || 1 == m_PressCheck)
	{
		// Ű���带 �˸°� ������.
		m_PressCheck = 1;
	}

	// ���ʿ� �˸°� �������� ���߿� ������.
	else
	if (-1 == m_PressCheck)
	{
		return false;
	}

	return true;
}




// �ӽ� �˻� �����Ϳ� �ش� �����͸� �ִ´�. -> 1ȸ��
void KeyManager::Command::Insert_PressData(const int& _Value)
{
	// ��� �ִ� ������ ��ŭ
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// �ش� Ű�� �ϳ��� ������ -> ������ �ִ� ���̴�.
		if (_Value == m_vector_KeyPressData[i])
		{
			return;
		}
	}

	// ������ �ʾ����Ƿ� �����ٰ� �־��ش�.
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// 0�� �� -> �� ���� �־��ش�.
		if (0 == m_vector_KeyPressData[i])
		{
			m_vector_KeyPressData[i] = _Value;
			return;
		}
	}
}

// �ӽ� Ű ���۸� �ʱ�ȭ ��Ų��.
void KeyManager::Command::Insert_EraseData(const int& _Value)
{
	// �������Ƿ� �������� ������ش�.
	for (size_t i = 0; i < m_vector_KeyPressData.size(); i++)
	{
		// ���� �� -> �� ������ ������ش�.
		if (_Value == m_vector_KeyPressData[i])
		{
			m_vector_KeyPressData[i] = 0;
			// ������ �����ʹ� �Ѱ��̴ϱ� ���⼭ ������
			return;
		}
	}
}




// ����� ��� �´��� üũ�Ѵ� -> ���;ȿ� ������ �´��� Ȯ��
bool KeyManager::Command::Command_Check()
{
	Get_Key_Check();
	Press_Check();
	return Chain_Check();
}



void KeyManager::Command::Update()
{
	// �� Ŀ�ǵ��� ���࿩�κ��� �Ǻ��Ѵ�.
	bool Check = Command_Check();

	// Ŀ�ǵ尡 ���� ���
	if (true == Check)
	{
		// ���� �����ӿ��� ������ ����
		if (true == m_UnPress)
		{
			m_UnPress = false;
			m_Up = false;
			m_Down = true;
			m_Press = true;
		}

		// ���� �����ӿ��� ����
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
		// ���� �����ӿ��� ������ ����
		if (true == m_UnPress)
		{
			m_UnPress = true;
			m_Up = false;
			m_Down = false;
			m_Press = false;
		}

		// ���� �����ӿ��� ����
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


// Ű ���� ����� Ŀ�Ǵ����� �ϳ��� ������Ʈ�ϴ� ����
// �̰��� �ھ ������Ʈ ������Ʈ���� ������Ʈ �� ��
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