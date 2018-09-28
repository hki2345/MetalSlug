#include "stdafx.h"
#include "Bit_Renderer.h"
#include "Sprite.h"

Bit_Renderer::Bit_Renderer()
{
}


Bit_Renderer::~Bit_Renderer()
{
}


void Bit_Renderer::Render()
{
	Positionf RenderPos = MotherOfTheOne_DE()->pos() + Pivot();

	if (true == CameraMode())
	{
		RenderPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	BitBlt 
	(
		CORE.GetBHDC(),
		RenderPos.IntX() - (int)(m_p_Sprite->Width() * 0.5f),
		RenderPos.IntY() - (int)(m_p_Sprite->Height() * 0.5f),
		m_p_Sprite->Width(),
		m_p_Sprite->Height(),
		m_p_Sprite->GetDc(),
		0,
		0,
		SRCCOPY // 고속복사 ㄷㄷ
	);
}


Size Bit_Renderer::size()
{
	return { m_p_Sprite->Width(), m_p_Sprite->Height() };
}

void Bit_Renderer::size(Size _Value)
{
	m_p_Sprite->Width(_Value.X);
	m_p_Sprite->Height(_Value.Y);
}