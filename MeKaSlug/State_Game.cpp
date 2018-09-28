#include "stdafx.h"
#include "State_Game.h"

#include "ResourceManager.h"

#include "Player_Leona.h"
#include "Enemy_Walker.h"
#include "Item_Heavy.h"

#include "Core.h"

State_Game::State_Game()
{
}


State_Game::~State_Game()
{
}


void State_Game::StateUpdate()
{
	if (KEYMANAGER.KEY_DOWN("Debug"))
	{
		CORE.ActingStateChanger(L"Title");
	}
	if (KEYMANAGER.KEY_DOWN("Leona"))
	{
		CORE.ActingStateChanger(L"Leona");
	}
	if (KEYMANAGER.KEY_DOWN("Eri"))
	{
		CORE.ActingStateChanger(L"Eri");
	}
	if (KEYMANAGER.KEY_DOWN("MapEdit"))
	{
		CORE.ActingStateChanger(L"EnemyEdit");
	}

	if (KEYMANAGER.KEY_DOWN("Stage1"))
	{
		CORE.ActingStateChanger(L"Stage01Deb");
	}
	if (KEYMANAGER.KEY_DOWN("Stage2"))
	{
		CORE.ActingStateChanger(L"Stage02Deb");
	}
	if (KEYMANAGER.KEY_DOWN("Stage3"))
	{
		CORE.ActingStateChanger(L"Stage03Deb");
	}
	if (KEYMANAGER.KEY_DOWN("StageBoss"))
	{
		CORE.ActingStateChanger(L"StageBossDeb");
	}
	
	if (KEYMANAGER.KEY_DOWN("Value_Debug"))
	{
		CORE.Value_Debug_Switch();
	}
	if (KEYMANAGER.KEY_DOWN("Obj_Debug"))
	{
		CORE.Obj_Debug_Switch();
	}

	if (KEYMANAGER.KEY_PRESS("CamerUp"))
	{
		MoveCamera(Vector2f::Up * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerDown"))
	{
		MoveCamera(Vector2f::Down * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerLeft"))
	{
		MoveCamera(Vector2f::Left * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerRight"))
	{
		MoveCamera(Vector2f::Right * CAMERA_SPD * DELTATIME);
	}
}


void State_Game::Setting_Key()
{
	// 자세한 내용은 KeyCommand 메모장에
	KEYMANAGER.SetUp_Command(L"Move_Up", VK_UP);
	KEYMANAGER.SetUp_Command(L"Move_Down", VK_DOWN);
	KEYMANAGER.SetUp_Command(L"Move_Left", VK_LEFT);
	KEYMANAGER.SetUp_Command(L"Move_Right", VK_RIGHT);
	KEYMANAGER.SetUp_Command(L"Fire", 'A');
	KEYMANAGER.SetUp_Command(L"Jump", 'S');
	KEYMANAGER.SetUp_Command(L"Bomb", 'D');

	KEYMANAGER.SetUp_Command(L"CamerUp", 'I');
	KEYMANAGER.SetUp_Command(L"CamerLeft", 'J');
	KEYMANAGER.SetUp_Command(L"CamerRight", 'L');
	KEYMANAGER.SetUp_Command(L"CamerDown", 'K');

	KEYMANAGER.SetUp_Command(L"Special", 'E');
	KEYMANAGER.SetUp_Command(L"Kick", 'Q');
	KEYMANAGER.SetUp_Command(L"MoonSlasher", VK_UP, 'Q', 'E');
	KEYMANAGER.SetUp_Command(L"Changer", VK_TAB);


	KEYMANAGER.SetUp_Command(L"Die_Sword", 'Z');
	KEYMANAGER.SetUp_Command(L"Die_Shut", 'X');
	KEYMANAGER.SetUp_Command(L"Die_Fire", 'C');
	KEYMANAGER.SetUp_Command(L"Die_Air", 'V');





	KEYMANAGER.SetUp_Command(L"Leona", 'N');
	KEYMANAGER.SetUp_Command(L"Eri", 'R');
	KEYMANAGER.SetUp_Command(L"MapEdit", 'M');

	KEYMANAGER.SetUp_Command(L"Value_Debug", 'B');
	KEYMANAGER.SetUp_Command(L"Obj_Debug", 'B');
	KEYMANAGER.SetUp_Command(L"Collider", 'C');


	KEYMANAGER.SetUp_Command(L"Fever", 'F');

	KEYMANAGER.SetUp_Command(L"Stage1", '1');
	KEYMANAGER.SetUp_Command(L"Stage2", '2');
	KEYMANAGER.SetUp_Command(L"Stage3", '3');
	KEYMANAGER.SetUp_Command(L"StageBoss", '4');
}

void State_Game::Setting_Image()
{
	PATHMANAGER.CreateGamePath(L"Leona", L"Image\\Leona");
	PATHMANAGER.CreateGamePath(L"Eri", L"Image\\Eri");
	PATHMANAGER.CreateGamePath(L"Bullet", L"Image\\Bullet");
	PATHMANAGER.CreateGamePath(L"Map", L"Image\\Map");
	PATHMANAGER.CreateGamePath(L"Items", L"Image\\Items");
	PATHMANAGER.CreateGamePath(L"Weapon", L"Image\\Weapon");
	PATHMANAGER.CreateGamePath(L"Enemy", L"Image\\Enemy");
	PATHMANAGER.CreateGamePath(L"Effect", L"Image\\Effect");
	PATHMANAGER.CreateGamePath(L"Boss", L"Image\\Boss");

	/******************************** Leona **************************************/


	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_Gun_Body_Right.bmp").c_str(), { 4, 24 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_Gun_Body_Left.bmp").c_str(), { 4, 24 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_NoGun_Body_Right.bmp").c_str(), { 4, 28});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_NoGun_Body_Left.bmp").c_str(), { 4, 28});
	
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_Leg_Right.bmp").c_str(), { 4,9});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_Leg_Left.bmp").c_str(), { 4,9 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_All_Body_Right.bmp").c_str(), { 4,28 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_All_Body_Left.bmp").c_str(), { 4,28 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_All_Body_Action_Right.bmp").c_str(), { 4,36 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_All_Body_Action_Left.bmp").c_str(), { 4,36 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Leona", L"Leona_Respawn.bmp").c_str(), { 7,1 });

	/******************************** Eri **************************************/


	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_Gun_Body_Right.bmp").c_str(), { 4, 24 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_Gun_Body_Left.bmp").c_str(), { 4, 24 });
																			  
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_NoGun_Body_Right.bmp").c_str(), { 4, 28 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_NoGun_Body_Left.bmp").c_str(), { 4, 28 });
																			  
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_Leg_Right.bmp").c_str(), { 4,9 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_Leg_Left.bmp").c_str(), { 4,9 });
																			  
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_All_Body_Right.bmp").c_str(), { 4,28 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_All_Body_Left.bmp").c_str(), { 4,28 });
																			  
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_All_Body_Action_Right.bmp").c_str(), { 4,30 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_All_Body_Action_Left.bmp").c_str(), { 4,30 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Eri", L"Eri_Respawn.bmp").c_str(), { 7,1 });


	/******************************** Enemy **************************************/

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Enemy_Edit.bmp").c_str(), { 12,26 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Enemy_Edit2.bmp").c_str(), { 6, 22 });

	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Shoot.bmp").c_str(), { 6,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Idle.bmp").c_str(), { 2,1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Reload.bmp").c_str(), { 7,1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Move.bmp").c_str(), { 6,1 });;
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Damage.bmp").c_str(), { 7,1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"SaruBia\\Saru_Wrecked.bmp").c_str(), { 4,1 });


	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\R_Ma_Idle.bmp").c_str(), { 4,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\R_Ma_Move.bmp").c_str(), { 6,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\R_Ma_Fire.bmp").c_str(), { 10,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\R_Ma_Reload.bmp").c_str(), { 6,3 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\L_Ma_Idle.bmp").c_str(), { 4,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\L_Ma_Move.bmp").c_str(), { 6,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\L_Ma_Fire.bmp").c_str(), { 10,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\L_Ma_Reload.bmp").c_str(), { 6,3 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"MachineGun\\Ma_Turning.bmp").c_str(), { 5,2 });



	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Bradley_Edit.bmp").c_str(), { 6, 8});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Middle_To_Raise.bmp").c_str(), { 5,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Raise_Shoot.bmp").c_str(), { 4,2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Side_Shoot.bmp").c_str(), { 4,2 });;
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Raise_Idle.bmp").c_str(), { 2,1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Enemy", L"Bradley\\Side_Idle.bmp").c_str(), { 2,1 });


	/******************************** Items ****************************************/
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Items", L"Gun_Bomb.bmp").c_str(), { 6,12 });

	/******************************** Map ****************************************/
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage1_Front.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage1_PlayGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage1_Collider.bmp").c_str());


	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage2_PlayGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage2_Collider.bmp").c_str());


	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage3_PlayGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Stage3_Collider.bmp").c_str());


	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"StageBoss_PlayGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"StageBoss_Collider.bmp").c_str());


	/******************************** Weapon ****************************************/
	// 가로 세로 순으로 자르는 것이다.
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Bullet", L"HeavyMachine.bmp"),
	{ 16 , 4 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L( L"Bullet", L"Bullet_Basic.bmp"),
	{ 1 , 3 });

	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"WeaponEffect.bmp"),{ 12 , 12 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Bomb_Cannon_Bullet.bmp"),{ 5 , 8 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Enemy_Bullet.bmp"), { 2, 1});


	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Sarubia_Bullet.bmp"), { 5 , 10 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Sarubia_Fire_Effect.bmp"), { 8 , 2 });

	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Tank_Bullet.bmp"), { 5 , 3 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Tank_Effect.bmp"), { 7 , 2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Weapon", L"Bradley_Bullet_Effect.bmp"), { 10 , 6 });


	/******************************** Effect ****************************************/
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Small.bmp").c_str(), { 7 , 4 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Medium.bmp").c_str(), { 7 , 4 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Big.bmp").c_str(), { 7 , 4 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Huge.bmp").c_str(), { 5 , 5 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Bomb.bmp").c_str(), { 7 , 4 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Effect", L"Effect_Bullet.bmp").c_str(), { 5 , 1 });


	/******************************** Boss ****************************************/
	// 가로 세로 순으로 자르는 것이다.
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"Boss_Bottom_Effect.bmp"), { 5 , 2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"Boss_Rocket.bmp"), { 4 , 1 });

	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom0.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom1.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom2.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom3.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom4.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"Bottom5.bmp"));
	RESOURCEMANAGER.Load_Res_Sprite(FILE_PATH_NOT_L(L"Boss", L"StageBoss_Front.bmp"));

	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"Enemy_Boss.bmp"), { 4 , 5 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"MagmaCannon.bmp"), { 5 , 1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"MagmaEffect.bmp"), { 6 , 2 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"MedicineCannon.bmp"), { 10 , 3 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"Water_Effect.bmp"), { 5 , 5 });
	RESOURCEMANAGER.Load_Res_MultiSprite(FILE_PATH_NOT_L(L"Boss", L"Wave_Effect.bmp"), { 2 , 12 });

	/******************************** Sound ****************************************/
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Effect_Eri_Die.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Effect_Leona_Die.mp3"));

	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die1.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die2.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die3.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die4.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die5.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Enemy_Die6.mp3"));


	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Sword1.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Sword2.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Cannon_Shut.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Basic_Shut.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Heavy_Shut.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Bullet_Act.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Bomb_Act.mp3"));

	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "MachineWrecked.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "MoonSlasher.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Boss_Wrecked.mp3"));


	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Boss_Medicine.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Boss_Magma.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Boss_Wave.mp3"));


	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "H.mp3"));
}

void State_Game::Setting_Collider()
{
	COLLIDERMANAGER.Link(Name(), L"Weapon", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
}

void State_Game::All_SetUp()
{
	Setting_Key();
	Setting_Image();
	Setting_Collider();
}






void State_Game::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);

	swprintf_s(Str, L"Mouse Pos: %d, %d", CORE.GetMousePos().X, CORE.GetMousePos().Y);
	TEXT_OUT(100, 40, Str);


	swprintf_s(Str, L"G - InGame | N - Leona Debug | R - Eri Debug");
	TEXT_OUT(250, 250, Str);

	swprintf_s(Str, L"M - MapEdit | B - Debug Value");
	TEXT_OUT(300, 275, Str);
}