#pragma once
#include "Renderer_Single_Image.h"
class Trans_Renderer :	public Renderer_Single_Sprite
{
public:
	friend class TheOne;

	// �� Ŭ���������� �̹����� ũ�⸦ ������ �� �ֱ⿡ �� ������ ��Ƶδ� ����
	// �� �̹����� �����ϰ� ��Ÿ���� ����(�Լ�) ������ ������ ���´�.
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

