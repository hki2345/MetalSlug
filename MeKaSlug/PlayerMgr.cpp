#include "stdafx.h"
#include "PlayerMgr.h"


One_Player* PlayerMgr::m_MainPlayer = nullptr;
PlayerMgr::Play_Character PlayerMgr::m_PlayChar = None_Char;
int PlayerMgr::Saru_Cnt = 0;

PlayerMgr::PlayerMgr()
{
}


PlayerMgr::~PlayerMgr()
{
}

One_Player* PlayerMgr::MainPlayer() {
	return m_MainPlayer;
}

void PlayerMgr::MainPlayer(One_Player* _MainPlayer) {
	m_MainPlayer = _MainPlayer;
}
