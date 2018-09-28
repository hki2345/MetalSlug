#include "stdafx.h"
#include "Alpha_Renderer.h"
#include "Sprite.h"
#include "Core.h"


// ���� ���� ���̺귯��
#pragma comment(lib, "msimg32.lib")


Alpha_Renderer::Alpha_Renderer() : m_v_SizeRate(1.0f)
{
}


Alpha_Renderer::~Alpha_Renderer()
{
}


bool Alpha_Renderer::Set_Sprite(const WCHAR* _Name)
{
	// �θ��� �Լ��� �����Ѵ�. -> ��ӱ������� ���� �̷��� �Ѵٰ� �Ѵ�.
	// �׸��� �� �Լ��� �翬�� �������̵� �� ���̰ڴ�.
	Renderer_Single_Sprite::Set_Sprite(_Name);

	// �̹����� ũ�⸦ �ϴ� �޾Ƴ��´�. - ���� ������
	m_Size = { m_p_Sprite->Width(), m_p_Sprite->Height() };
	m_Rect = { Vector2::Zero,{ m_Size.X, m_Size.Y } };

	return true;
}

// Ÿ���� �����ϱ� ���� �ε����� ���� ���� �� �ְ� �Ѵ�.
bool Alpha_Renderer::Set_Sprite(const WCHAR* _Name, int _Index)
{
	Renderer_Single_Sprite::Set_Sprite(_Name, _Index);
	m_Size = { m_p_Sprite->Width(), m_p_Sprite->Height() };
	return true;
}


bool Alpha_Renderer::Set_Sprite(Sprite* _Data)
{
	Renderer_Single_Sprite::Set_Sprite(_Data);
	m_Size = { _Data->Width(), _Data->Height() };
	return true;
}


void Alpha_Renderer::Render()
{
	Positionf RenderPos = m_MotherOfTheOne_DE->pos() + Pivot();

	if (true == CameraMode())
	{
		RenderPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	AlphaBlend(CORE.GetBHDC(),
		(RenderPos.IntX() - (int)(m_Size.X * 0.5f)),
		(RenderPos.IntY() - (int)(m_Size.Y * 0.5f)),
		(int)(m_Size.X * m_v_SizeRate),
		(int)(m_Size.Y * m_v_SizeRate),
		m_p_Sprite->GetDc(),
		m_p_Sprite->rect().Pos.X, // �̹����� ����� x.
		m_p_Sprite->rect().Pos.Y, // �̹����� ����� y
		m_p_Sprite->rect().Size.X, // ������ x
		m_p_Sprite->rect().Size.Y, // ������ y
		m_BF);
}