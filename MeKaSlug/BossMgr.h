#pragma once
#include "Enemy_Boss.h"


class BossMgr
{

public:
	BossMgr& Inst()
	{
		static BossMgr newPlayerMgr;
		return newPlayerMgr;
	}

private:
	static Enemy_Boss* m_MainPlayer;

public:
	static Enemy_Boss* MainBoss();
	static void MainBoss(Enemy_Boss* _MainPlayer);
public:
	BossMgr();
	~BossMgr();
};

