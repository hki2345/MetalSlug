#pragma once
#include "One_Player.h"
#include "BaseEnemy.h"

class PlayerMgr
{
public:
	enum Play_Character
	{
		None_Char = 0,
		Eri,
		Leona
	};

public:
	PlayerMgr& Inst()
	{
		static PlayerMgr newPlayerMgr;
		return newPlayerMgr;
	}

private:
	static int Saru_Cnt;

	static One_Player* m_MainPlayer;
	static Play_Character m_PlayChar;

public:
	static int  SaruCnt(){ return Saru_Cnt; }
	static void DestroyEnemyCnt() { Saru_Cnt++; }
	static void ResetEnemyCnt() { Saru_Cnt = 0; }
	static One_Player* MainPlayer();
	static void MainPlayer(One_Player* _MainPlayer);

	static void				character(const Play_Character& _Value) { m_PlayChar = _Value; }
	static Play_Character&	character() { return m_PlayChar; }

public:
	PlayerMgr();
	~PlayerMgr();
};