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
	// �� �ִ� -  ���� ����
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

	// ���� �������� ������ �������� �ƴ϶��
	// �ִϸ��̼� ����
	if (m_v_Acting_Frame != m_v_End_Frame)
	{
		// �ִϸ��̼��� �ӵ��� �����ϴµ�
		// �� ������ ��ŸŸ���� �����Ͽ� �װ��� �ӵ����� Ŭ ���
		// �ð� �ʱ�ȭ �� ���� ���������� �Ѿ��.
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
	// ������ �������̶��
	else
	{
		// ������ ������ 
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
			// ������ �ʱ�ȭ
		}

		// �ƴҰ�� �ƹ��͵� ��������
		m_b_Acting = false;
	}


	Positionf RenderPos = 
		m_p_MotherOfAnimation->MotherOfTheOne_DE()->pos() + 
		m_p_MotherOfAnimation->Pivot();

	if (true == m_p_MotherOfAnimation->CameraMode())
	{
		RenderPos -= m_p_MotherOfAnimation->MotherOfTheOne_DE()->MotherOfTheOne()->CameraPos();
	}

	// ��𼭺���
	TransparentBlt(CORE.GetBHDC(),
		(RenderPos.IntX() - (int)(m_p_MotherOfAnimation->size().X * 0.5f)),
		(RenderPos.IntY() - (int)(m_p_MotherOfAnimation->size().Y * 0.5f)),
		(int)(m_p_MotherOfAnimation->size().X * m_p_MotherOfAnimation->sizeRate()),
		(int)(m_p_MotherOfAnimation->size().Y * m_p_MotherOfAnimation->sizeRate()),
		NewSprite->GetDc(),
		NewSprite->rect().Pos.X, // �̹����� ����� x.
		NewSprite->rect().Pos.Y, // �̹����� ����� y
		NewSprite->rect().Size.X, // ������ x
		NewSprite->rect().Size.Y, // ������ y
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

// ���ǻ� ���� ������ ���� �ּ�ó���� �����ش�.
// �ִϸ����Ͷ� -> �������� �ִϸ��̼��� ��� �׸�
// �ִϸ��̼��� �� ����
void Animator::Set_Animation(
	const WCHAR* _SpriteName, const WCHAR* _AniName,
	size_t _Start, size_t _End, float _Speed /* = 0.1f*/,
	bool _Loop /*= true*/)
{
	Animation* NewAnimation = Find_Animation(_AniName);

	// �ִµ� ����� �׳� �Ͷ߷� ������. ����
	KAssert(nullptr != NewAnimation);
	if (nullptr != NewAnimation)
	{
		return;
	}

	// �����Ͱ� �Ǵ� ��Ƽ��������Ʈ�� �����Ͽ����Ѵ�.����
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

// ������ ������ ��´�. - �̸����� �ڵ�����
void Animator::Set_OneAnimation(const WCHAR* _SpriteName, const WCHAR* _AniName, size_t _End)
{
	Set_Animation(_SpriteName, (_AniName + std::to_wstring(_End)).c_str(), _End, _End);
}


// �ִϸ��̼� ���� ������ ����
void Animator::Fix_Animation(const size_t& _FromFrame, const size_t& _ToFrame)
{
	if (m_Acting_Animation->m_v_Acting_Frame == _ToFrame ||
		(false == m_Acting_Animation->m_b_Reverse && m_Acting_Animation->m_v_Acting_Frame >= _ToFrame) ||
		(true == m_Acting_Animation->m_b_Reverse && m_Acting_Animation->m_v_Acting_Frame <= _ToFrame))
	{
		m_Acting_Animation->m_v_Acting_Frame = _FromFrame;
	}
}

// �������� ������ ������ �����Ƿ� �ٲپ��ִ� �͵� �ʿ�
// Ʈ�� �� ���� ��ȯ - �޽��� ���� �ִϸ��̼��� ���� �� ��ȯ
void  Animator::Change_Animation(const WCHAR* _AniName, bool _Level)
{
	Animation* FindAni = Find_Animation(_AniName);

	KAssert(nullptr == FindAni);
	if (nullptr == FindAni)
	{
		return;
	}

	// ���� ���� �ִϰ� �÷��� ���̸� �ٲ��� �ʴ´�.
	if (m_Acting_Animation == FindAni)
	{
		return;
	}

	m_Acting_Animation = FindAni;

	// ���� ���� �ִϰ� �÷��� ���̸� �ٲ��� �ʴ´�.
	// ���� ��ȯ ���θ� ���´�. -> ���� �ִϰ� ���������� �׸��� ���� ��ȯ �� �������� ���´�.
	// �����ִϰ� Ȱ���� ���̸� �ٲ��� ���Ѵ�.
	if (true == m_Acting_Animation->m_b_Acting && false == _Level)
	{
		return;
	}

	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = true;
}

// ���ϸ��̼� ������ �ʱ�ȭ
void Animator::Reset_Animation()
{
	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = false;
}

// �ִϸ��̼��� ó������ �ٽ� ���� -> �Ѿ� �߻�
void  Animator::Change_ReAnimation()
{
	if (nullptr == m_Acting_Animation)
	{
		return;
	}

	m_Acting_Animation->m_v_Acting_Frame = m_Acting_Animation->m_v_Start_Frame;
	m_Acting_Animation->m_b_Acting = true;
}

// �۵��ϴ� �ִϸ��̼��� �̸�
bool Animator::Acting_Name(const WCHAR* _AniName)
{
	if (nullptr != m_Acting_Animation)
	{
		// ������ 0�� ��ȯ�Ѵ�.
		if (0 == lstrcmpW(m_Acting_Animation->Name(), _AniName))
		{
			return true;
		}
		return false;
	}
	return false;
}



// ���� - �η� ����� ���� ���� ����
void Animator::Render()
{
	if (nullptr != m_Acting_Animation)
	{
		m_Acting_Animation->Render();
	}
}

// ���� �� ���� - ��� ���ϸ����Ϳ� ���� ����
void Animator::Set_TransColor(const UINT& _Data)
{
	std::map<std::wstring, Animation*>::iterator ColorStartIter = m_Map_Animation.begin();
	std::map<std::wstring, Animation*>::iterator ColorEndIter = m_Map_Animation.end();

	for (; ColorStartIter != ColorEndIter; ColorStartIter++)
	{
		ColorStartIter->second->Set_TransColor(_Data);
	}
}