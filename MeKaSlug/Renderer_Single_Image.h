#pragma once
#include "Renderer.h"

class Sprite;
class Renderer_Single_Sprite : public Renderer
{
public:
	// �ش� �������� ��ü���� ���� �� �ִ�.
	friend class TheOne;


	// ��̹����� �׸��� �˰� �־�� ���� �ʰڳ�... -> �� �̹����� �׷�����.
protected:
	Sprite* m_p_Sprite;

public:
	// Resource �޴����� ����� �ش� ������ �̹����� ������ ����Ѵ�.
	virtual bool	Set_Sprite(const WCHAR* _Name, int _Index);
	virtual bool	Set_Sprite(const WCHAR* _Name);
	virtual bool	Set_Sprite(Sprite* _Data);

	virtual void	Set_TransColor(const UINT& _Value);
	virtual void	Render() override = 0 {};

protected:
	Renderer_Single_Sprite();
	~Renderer_Single_Sprite();
};

