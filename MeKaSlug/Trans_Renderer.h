#pragma once
#include "Renderer_Single_Image.h"
class Trans_Renderer :	public Renderer_Single_Sprite
{
public:
	friend class TheOne;

	// 이 클래스에서는 이미지의 크기를 조절할 수 있기에 그 정보를 담아두는 변수
	// 그 이미지를 온전하게 나타내기 위한(함수) 변수를 마련해 놓는다.
private:
	Size m_Size;
	Rect m_Rect;
	float m_v_SizeRate;

public:
	void rect(Rect _Value) { m_Rect = _Value; }
	void size(Size _Value) { m_Size = _Value; }
	void size(float _Value) { m_v_SizeRate = _Value; }
	Size size() { return m_Size; }

public:
	bool BaseSettingSprite(const WCHAR* _ImageKey);
	bool BaseSettingSprite(const WCHAR* _ImageKey, size_t _Index);

public:
	Sprite*		Get_Sprte() { return m_p_Sprite; }
	bool		Set_Sprite(const WCHAR* _Name) override;
	bool		Set_Sprite(const WCHAR* _Name, int _Index);
	bool		Set_Sprite(Sprite* _Data) override;
	void		Render() override;

public:
	Trans_Renderer();
	~Trans_Renderer();
};

