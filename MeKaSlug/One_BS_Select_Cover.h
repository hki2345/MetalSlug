#pragma once
#include "TheOne.h"
class One_BS_Select_Cover :
	public TheOne
{
private:
	TheOne* m_Target;
	Positionf m_TargetPos;
	float m_Speed;

public:
	void Start(TheOne* _Target);
	void Update() override;


public:
	One_BS_Select_Cover();
	~One_BS_Select_Cover();
};

