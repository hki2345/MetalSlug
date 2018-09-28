#pragma once
#include "TheOne.h"

class Trans_Renderer;
class Collider;
class Boss_Bottom : public TheOne
{
private:
	Trans_Renderer* p_Render;
	Collider* p_Collider;

	float m_Floating_Speed;

public:
	void Start(const size_t& _Value, const size_t& _Size);

public:
	Boss_Bottom();
	~Boss_Bottom();
};

