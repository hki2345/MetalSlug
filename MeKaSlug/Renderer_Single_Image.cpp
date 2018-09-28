#include "stdafx.h"
#include "Renderer_Single_Image.h"
#include "ResourceManager.h"

#include "Sprite.h"

#include "Core.h"

Renderer_Single_Sprite::Renderer_Single_Sprite() : m_p_Sprite(nullptr)
{
}


Renderer_Single_Sprite::~Renderer_Single_Sprite()
{
}

bool Renderer_Single_Sprite::Set_Sprite(const WCHAR* _Name)
{
	// 리소스에서 해당 이름의 이미지를 찾은 뒤 그 이미지 포인터를 넘겨 받는다.
	m_p_Sprite = RESOURCEMANAGER.Find_Res_Sprite(_Name);

	KAssert(nullptr == m_p_Sprite);

	if (nullptr == m_p_Sprite)
	{
		return false;
	}

	return true;
}

bool Renderer_Single_Sprite::Set_Sprite(const WCHAR* _Name, int _Index)
{
	// 멀티스프라이트에서 인덱스를 넣어 원하는 타일을 구분한다.
	MultiSprite* FindSprite = RESOURCEMANAGER.Find_Res_MultiSprite(_Name);

	KAssert(nullptr == FindSprite);

	if (nullptr == FindSprite)
	{
		return false;
	}


	// 몇 번째의 멀티스프라이트를 받을지
	m_p_Sprite = FindSprite->Get_Sprite(_Index);

	return true;
}



bool Renderer_Single_Sprite::Set_Sprite(Sprite* _Data)
{
	m_p_Sprite = _Data;
	return true;
}

void Renderer_Single_Sprite::Set_TransColor(const UINT& _Value)
{
	m_p_Sprite->Set_TransColor(_Value);
}