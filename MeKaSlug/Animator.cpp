#include "stdafx.h"

#include "Animator.h"

#include "MultiSprite.h"

#include "ResourceManager.h"

/*************************************** Animation *************************************/
Animator::Animation::Animation(
	Animator* _Mother, MultiSprite* _SpriteData,
	size_t _Start, size_t _End,
	float _Speed, bool _Loop) : 
	m_p_MotherOfAnimation(_Mother), m_p_SpriteData(_SpriteData),
	m_v_Start_Frame(_Start), m_v_End_Frame(_End),
	m_v_Speed(_Speed), m_b_Loop(_Loop),
	m_v_ActingTime(.0f), m_b_Reverse(false)
{
	// 역 애니 -  좌측 방향
	if (m_v_Start_Frame > m_v_End_Frame)
	{
		m_b_Reverse = true;
	}
}

void Animator::Animation::Set_TransColor(const UINT& _Value)
{
	m_p_SpriteData->Set_TransColor(_Value);
}

void Animator::Animation::Render()
{
	Sprite* NewSprite = m_p_SpriteData->Get_Sprite(m_v_Acting_Frame);

	// 현재 프레임이 마지막 프레임이 아니라면
	// 애니메이션 구현
	if (m_v_Acting_Frame != m_v_End_Frame)
	{
		// 애니메이션은 속도로 제어하는데
		// 매 프레임 델타타임을 측정하여 그것이 속도보다 클 경우
		// 시간 초기화 및 다음 프레임으로 넘어간다.
		m_v_ActingTime += DELTATIME;
		if (m_v_Speed <= m_v_ActingTime)
		{
			if (false == m_b_Reverse)
			{
				++m_v_Acting_Frame;
			}
			else if (true == m_b_Reverse)
			{
				--m_v_Acting_Frame;
			}
			m_v_ActingTime = 0.0f;
		}
	}
	// 마지막 프레임이라면
	else
	{
		// 루프를 돌면은 
		if (true == m_b_Loop)
		{
			/*if (m_v_Speed <= m_v_ActingTime)
			{
				++m_v_Acting_Frame;
				m_v_ActingTime = 0.0f;
			}*/
			if (false == m_b_Reverse)
			{
				if (m_v_End_Frame <= m_v_Acting_Frame)
				{
					m_v_Acting_Frame = m_v_Start_Frame;
				}
			}
			else if (true == m_b_Reverse)
			{
				if (m_v_End_Frame >= m_v_Acting_Frame)
				{
					m_v_Acting_Frame = m_v_Start_Frame;
				}
			}
			// 프레임 초기화
		}

		// 아닐경우 아무것도 하지않음
		m_b_Acting = false;
	}


	Positionf RenderPos = 
		m_p_MotherOfAnimation->MotherOfTheOne_DE()->pos() + 
		m_p_MotherOfAnimation->Pivot();

	if (true == m_p_MotherOfAnimation->CameraMode())
	{
		RenderPos -= m_p_MotherOfAnimation->MotherOfTheOne_DE()->MotherOfTheOne()->CameraPos();
	}

	// 어디서부터
	TransparentBlt(CORE.GetBHDC(),
		(RenderPos.IntX() - (int)(m_p_MotherOfAnimation->size().X * 0.5f)),
		(RenderPos.IntY() - (int)(m_p_MotherOfAnimation->size().Y * 0.5f)),
		(int)(m_p_MotherOfAnimation->size().X * m_p_MotherOfAnimation->sizeRate()),
		(int)(m_p_MotherOfAnimation->size().Y * m_p_MotherOfAnimation->sizeRate()),
		NewSprite->GetDc(),
		NewSprite->rect().Pos.X, // 이미지의 어느점 x.
		NewSprite->rect().Pos.Y, // 이미지의 어느점 y
		NewSprite->rect().Size.X, // 어디까지 x
		NewSprite->rect().Size.Y, // 어디까지 y
		NewSprite->Get_Img()->Set_TransColor());
}


/*************************************** Animatior *************************************/
Animator::Animator() :m_Size({0,0}), m_v_SizeRate(1.0f), m_Acting_Animation(nullptr)
{
}


Animator::~Animator()
{
	std::map<std::wstring, Animation*>::iterator DeleteStartIter = m_Map_Animation.begin();
	std::map<std::wstring, Animation*>::iterator DeleteEndIter = m_Map_Animation.end();

	for (; DeleteStartIter != DeleteEndIter; DeleteStartIter++)
	{
		NEW_DELETE(DeleteStartIter->second);
	}

	m_Map_Animation.clear();
}



Animator::Animation* Animator::Find_Animation(const WCHAR* _DataName)
{
	std::map<std::wstring, Animation*>::iterator FindIter = m_Map_Animation.find(_DataName);

	if (m_Map_Animation.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

// 예의상 생략 인자의 값은 주석처리로 보여준다.
// 애니메이터란 -> 여러개의 애니메이션을 담는 그릇
// 애니메이션이 한 동작
void Animator::Set_Animation(
	const WCHAR* _SpriteName, const WCHAR* _AniName,
	size_t _Start, size_t _End, float _Speed /* = 0.1f*/,
	bool _Loop /*= true*/)
{
	Animation* NewAnimation = Find_Animation(_AniName);

	// 있는데 만들면 그냥 터뜨려 버린다. ㅇㅇ
	KAssert(nullptr != NewAnimation);
	if (nullptr != NewAnimation)
	{
		return;
	}

	// 데이터가 되는 멀티스프라이트는 존재하여야한다.ㅇㅇ
	MultiSprite* NewMultiSprite = RESOURCEMANAGER.Find_Res_MultiSprite(_SpriteName);
	KAssert(nullptr == NewMultiSprite);

	if(nullptr == NewMultiSprite)
	{
		return;
	}

	NewAnimation = new Animation(this, NewMultiSprite, _Start, _End, _Speed, _Loop);
	m_Size = NewMultiSprite->size();
	NewAnimation->Name(_AniName);
	m_Map_Animation.insert(std::map<std::wstring, Animation*>::value_type(_AniName, NewAnimation));
}

// 한장의 사진을 담는다. - 이름까지 자동생성
void Animator::Set_OneAnimation(const WCHAR* _SpriteName, const WCHAR* _AniName, size_t _End)
{
	Set_Animation(_SpriteName, (_AniName + std::to_wstring(_End)).c_str(), _End, _End);
}


// 애니메이션 지정 프레임 고정
void Animator::Fix_Animation(const size_t& _FromFrame, const size_t& _ToFrame)
{
	if (m_Acting_Animation->m_v_Acting_Frame == _ToFrame ||
		(false == m_Acting_Animation->m_b_Reverse && m_Acting_Animation->m_v_Acting_Frame >= _ToFrame) ||
		(true == m_Acting_Animation->m_b_Reverse && m_Acting_Animation->m_v_Acting_Frame <= _ToFrame))
	{
		m_Acting_Animation->m_v_Acting_Frame = _FromFrame;
	}
}

// 여러개의 동작을 가지고 있으므로 바꾸어주는 것도 필요
// 트루 시 강제 변환 - 펄스시 현재 애니메이션이 끝난 후 변환
void  Animator::Change_Animation(const WCHAR* _AniName, bool _Level)
{
	Animation* FindAni = Find_Animation(_AniName);

	KAssert(nullptr == FindAni);
	if (nullptr == FindAni)
	{
		return;
	}

	// 현재 같은 애니가 플레이 중이면 바꾸지 않는다.
	if (m_Acting_Animation == FindAni)
	{
		return;
	}

	m_Acting_Animation = FindAni;

	// 현재 같은 애니가 플레이 중이면 바꾸지 않는다.
	// 강제 변환 여부를 묻는다. -> 이전 애니가 진행중인지 그리고 강제 변환 할 것인지를 묻는다.
	// 같은애니가 활서와 중이면 바꾸지 못한다.
	if (true == m_Acting_Animation->m_b_Acting && false == _Level)
	{
		return;
	}

	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = true;
}

// 에니메이션 프레임 초기화
void Animator::Reset_Animation()
{
	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = false;
}

// 애니메이션을 처음부터 다시 실행 -> 총알 발사
void  Animator::Change_ReAnimation()
{
	if (nullptr == m_Acting_Animation)
	{
		return;
	}

	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = true;
}

// 작동하는 애니메이션의 이름
bool Animator::Acting_Name(const WCHAR* _AniName)
{
	if (nullptr != m_Acting_Animation)
	{
		// 같으면 0을 반환한다.
		if (0 == lstrcmpW(m_Acting_Animation->Name(), _AniName))
		{
			return true;
		}
		return false;
	}
	return false;
}



// 랜더 - 널로 만들면 실행 안함 ㅇㅇ
void Animator::Render()
{
	if (nullptr != m_Acting_Animation)
	{
		m_Acting_Animation->Render();
	}
}

// 빼는 색 설정 - 모든 에니메이터에 같게 적용
void Animator::Set_TransColor(const UINT& _Data)
{
	std::map<std::wstring, Animation*>::iterator ColorStartIter = m_Map_Animation.begin();
	std::map<std::wstring, Animation*>::iterator ColorEndIter = m_Map_Animation.end();

	for (; ColorStartIter != ColorEndIter; ColorStartIter++)
	{
		ColorStartIter->second->Set_TransColor(_Data);
	}
}