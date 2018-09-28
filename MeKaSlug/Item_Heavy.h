#pragma once
#include "One_Item.h"
class Item_Heavy : public One_Item
{
private:
	Gun_Status Gun_Type;

public:
	void Init() override;
	void Update() override;

public:
	Item_Heavy();
	~Item_Heavy();
};

