#pragma once
#include "TheOne.h"

class Alpha_Renderer;
class One_BS_Cover : public TheOne
{
private:
	Alpha_Renderer* BSC;

	float AlphaTime;
	float AlphaSpeed;
	int Alpha;

	bool Fade;
	bool FadeCheck;

public:
	// false ¸é ¾Æ¿ô - true ¸é ÀÎ
	bool& fade()		{ return Fade; }
	bool& fade_check()	{ return FadeCheck; }

	void Init_FadeIn(const bool& _End = false);
	void Init_FadeOut();
	void Init();
	void Update();

public:
	One_BS_Cover();
	~One_BS_Cover();
};

