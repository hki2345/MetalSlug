#pragma once
#include "One_Player.h"

// class AniName 
// {
//		std::wstring BodyAni;
//		std::wstring LegAni;
// }

class Player_Leona : public One_Player
{
	bool MoonSlasher;

	virtual void Init_Collision() override {} ;
	virtual void Init_Render() override;
	void Update_Key();

	void Update_Set_AniRender();


public:
	void Init() override;
	void Update() override;
	void MoonUpdate();

public:
	Player_Leona();
	~Player_Leona();
};

