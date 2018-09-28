#include "stdafx.h"
#include "Trans_Renderer.h"
#include "Sprite.h"
#include "Core.h"


// ���̺귯���� �߰��ϴ� ��ó�� ���̴�.
#pragma comment(lib, "msimg32.lib")

Trans_Renderer::Trans_Renderer() : m_v_SizeRate(1.0f)
{
}


Trans_Renderer::~Trans_Renderer()
{
}

bool Trans_Renderer::Set_Sprite(const WCHAR* _Name)
{
	// �θ��� �Լ��� �����Ѵ�. -> ��ӱ������� ���� �̷��� �Ѵٰ� �Ѵ�.
	// �׸��� �� �Լ��� �翬�� �������̵� �� ���̰ڴ�.
	 Renderer_Single_Sprite::Set_Sprite(_Name);
	
	// �̹����� ũ�⸦ �ϴ� �޾Ƴ��´�. - ���� ������
	m_Size = { m_p_Sprite->Width(), m_p_Sprite->Height() };
	m_Rect = { Vector2::Zero, {m_Size.X, m_Size.Y} };

	return true;
}

// Ÿ���� �����ϱ� ���� �ε����� ���� ���� �� �ְ� �Ѵ�.
bool Trans_Renderer::Set_Sprite(const WCHAR* _Name, int _Index)
{
	Renderer_Single_Sprite::Set_Sprite(_Name, _Index);
	m_Size = { m_p_Sprite->Width(), m_p_Sprite->Height() };
	return true;
}


bool Trans_Renderer::Set_Sprite(Sprite* _Data)
{
	Renderer_Single_Sprite::Set_Sprite(_Data);
	m_Size = { _Data->Width(), _Data->Height() };
	return true;
}

bool Trans_Renderer::BaseSettingSprite(const WCHAR* _ImageKey) 
{
	Renderer_Single_Sprite::Set_Sprite(_ImageKey);
	return true;
}

bool Trans_Renderer::BaseSettingSprite(const WCHAR* _ImageKey, size_t _Index)
{
	Renderer_Single_Sprite::Set_Sprite(_ImageKey, _Index);
	return true;
}


void Trans_Renderer::Render()
{
	Positionf RenderPos = m_MotherOfTheOne_DE->pos() + Pivot();

	if (true == CameraMode())
	{
		RenderPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	TransparentBlt(CORE.GetBHDC(),
		(RenderPos.IntX() - (int)(m_Size.X * 0.5f)),
		(RenderPos.IntY() - (int)(m_Size.Y * 0.5f)),
		(int)(m_Size.X * m_v_SizeRate),
		(int)(m_Size.Y * m_v_SizeRate),
		m_p_Sprite->GetDc(),
		m_p_Sprite->rect().Pos.X, // �̹����� ����� x.
		m_p_Sprite->rect().Pos.Y, // �̹����� ����� y
		m_p_Sprite->rect().Size.X, // ������ x
		m_p_Sprite->rect().Size.Y, // ������ y
		(m_p_Sprite->Set_TransColor()));
}