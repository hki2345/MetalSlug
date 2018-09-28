#pragma once
#include "One_Player.h"
class Player_Eri : public One_Player
{
private:
	virtual void Init_Collision() override {};
	virtual void Init_Render() override;

	void Update_Bomb() override;
	void Update_Key();
	void Update_Set_AniRender();


public:
	void Init() override;
	void Update() override;
public:
	Player_Eri();
	~Player_Eri();
};

