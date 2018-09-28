#pragma once
#include "Renderer.h"

class Sprite;
class Renderer_Single_Sprite : public Renderer
{
public:
	// 해당 랜더러는 객체마다 만들 수 있다.
	friend class TheOne;


	// 어떤이미지를 그릴지 알고 있어야 하지 않겠냐... -> 즉 이미지만 그려본다.
protected:
	Sprite* m_p_Sprite;

public:
	// Resource 메니저에 저장된 해당 네임의 이미지를 가져와 출력한다.
	virtual bool	Set_Sprite(const WCHAR* _Name, int _Index);
	virtual bool	Set_Sprite(const WCHAR* _Name);
	virtual bool	Set_Sprite(Sprite* _Data);

	virtual void	Set_TransColor(const UINT& _Value);
	virtual void	Render() override = 0 {};

protected:
	Renderer_Single_Sprite();
	~Renderer_Single_Sprite();
};

