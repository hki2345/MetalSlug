#include "stdafx.h"
#include "Item_Heavy.h"

#include "ResourceManager.h"
#include "MultiSprite.h"
#include "Trans_Renderer.h"
#include "Collider.h"

Item_Heavy::Item_Heavy()
{
	m_Pos = { 300, 100 };
	Name(L"HeavyMachine");
}


Item_Heavy::~Item_Heavy()
{
}


void Item_Heavy::Init()
{
	float Ani_Time = .05f;

	Trans_Renderer* p_RenderItem = Create_Renderer<Trans_Renderer>(5);
	MultiSprite* p_MultiData = RESOURCEMANAGER.Find_Res_MultiSprite(L"Gun_Bomb.bmp");

	p_RenderItem->Set_Sprite(p_MultiData->Get_Sprite(0));
	p_RenderItem->Set_TransColor(RGB(255, 105, 0));

	p_Collider = Create_Collider(L"Item", { 30,30 });
	p_Collider->size({ 30,30 });
	p_Collider->type(Collider::TYPE::RECT);
}

void Item_Heavy::Update()
{
	TheOne::Update_Bottom();
	TheOne::Update_Gravity();
}