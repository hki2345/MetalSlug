#include "stdafx.h"
#include "Trans_Renderer.h"
#include "Sprite.h"
#include "Core.h"


// 라이브러리를 추가하는 전처리 문이다.
#pragma comment(lib, "msimg32.lib")

Trans_Renderer::Trans_Renderer() : m_v_SizeRate(1.0f)
{
}


Trans_Renderer::~Trans_Renderer()
{
}

bool Trans_Renderer::Set_Sprite(const WCHAR* _Name)
{
	// 부모의 함수를 실행한다. -> 상속구조에선 보통 이렇게 한다고 한다.
	// 그리고 이 함수는 당연히 오버라이딩 된 것이겠다.
	 Renderer_Single_Sprite::Set_Sprite(_Name);
	
	// 이미지의 크기를 일단 받아놓는다. - 정식 사이즈
	m_Size = { m_p_Sprite->Width(), m_p_Sprite->Height() };
	m_Rect = { Vector2::Zero, {m_Size.X, m_Size.Y} };

	return true;
}

// 타일을 구분하기 위한 인덱스를 따로 받을 수 있게 한다.
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
		m_p_Sprite->rect().Pos.X, // 이미지의 어느점 x.
		m_p_Sprite->rect().Pos.Y, // 이미지의 어느점 y
		m_p_Sprite->rect().Size.X, // 어디까지 x
		m_p_Sprite->rect().Size.Y, // 어디까지 y
		(m_p_Sprite->Set_TransColor()));
}