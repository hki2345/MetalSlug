#include "stdafx.h"
#include "MultiSprite.h"


MultiSprite::MultiSprite(size_t _Size)
{
	m_vec_Sprite.reserve(_Size);
}


MultiSprite::~MultiSprite()
{
	for (size_t i = 0; i < m_vec_Sprite.size(); i++)
	{
		NEW_DELETE(m_vec_Sprite[i]);
	}

	m_vec_Sprite.clear();
}


void MultiSprite::Set_TransColor(const UINT& _Data)
{
	for (size_t i = 0; i < m_vec_Sprite.size(); i++)
	{
		m_vec_Sprite[i]->Set_TransColor(_Data);
	}
}