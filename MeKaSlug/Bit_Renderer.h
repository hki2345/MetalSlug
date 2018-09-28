#pragma once
#include "Renderer_Single_Image.h"



class Bit_Renderer : public Renderer_Single_Sprite
{
public:
	friend class TheOne;

public:
	void Render() override;
	Size size();
	void size(Size _Value);

public:
	Bit_Renderer();
	~Bit_Renderer();
};

