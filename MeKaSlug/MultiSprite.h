#pragma once
#include "Sprite.h"

class MultiSprite : public Begin
{
private:
	std::vector<Sprite*> m_vec_Sprite;
	size_t Sprite_Index;

public:
	void Set_TransColor(const UINT& _Data);

	size_t Get_MultiSpriteCount() { return m_vec_Sprite.size(); }

	Sprite* Get_Sprite(const size_t& _Index)
	{
		KAssert(m_vec_Sprite.size() <= _Index);
		Sprite_Index = _Index;
		return m_vec_Sprite[_Index];
	}

	size_t Get_Index() const
	{
		return Sprite_Index;
	}

	void Insert_Sprite(Sprite* _Data)
	{
		m_vec_Sprite.push_back(_Data);
	}

	Sizef size() { return m_vec_Sprite[0]->size(); }

public:
	MultiSprite(size_t _Size);
	~MultiSprite();
};

