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
	// ���ҽ����� �ش� �̸��� �̹����� ã�� �� �� �̹��� �����͸� �Ѱ� �޴´�.
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
	// ��Ƽ��������Ʈ���� �ε����� �־� ���ϴ� Ÿ���� �����Ѵ�.
	MultiSprite* FindSprite = RESOURCEMANAGER.Find_Res_MultiSprite(_Name);

	KAssert(nullptr == FindSprite);

	if (nullptr == FindSprite)
	{
		return false;
	}


	// �� ��°�� ��Ƽ��������Ʈ�� ������
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