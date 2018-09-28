#pragma once
#include"TheOne.h"

class Trans_Renderer;
class MS_Arrow_Side : public TheOne
{
private:
	TheOne* TargetUI; 
	Trans_Renderer* ArrowRIght;
	Trans_Renderer* ArrowLeft;

	float Speed;
	bool In;

public:
	void Update() override;
	void Init() override;
	inline void SetTarget(TheOne* _Target) 
	{ 
		TargetUI = _Target; 
		m_Pos = TargetUI->pos();
	}

public:
	MS_Arrow_Side();
	~MS_Arrow_Side();
};

