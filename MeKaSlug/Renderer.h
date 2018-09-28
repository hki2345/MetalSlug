#pragma once
#include "TheOne_DE.h"
#include "RenderManager.h"

class Image;
class Renderer : public TheOne_DE
{
public:
	friend class TheOne;
	friend class RenderManager;

private:	
	// 그리는 순서
	int m_Order;
	// 다른 곳에 공개는 하지 않는다 -> 선택한 곳만 공개
	// 단 자식들은 알아야한다 물론 -> 순수가상이기 때문에 가능
	virtual void Render() = 0;
	bool m_b_Camera;

public:
	void CameraMode(bool _Value)			{ m_b_Camera = _Value; }
	bool CameraMode()						{ return m_b_Camera; }

public:
	int& Order()			{ return m_Order; }
	void Order(int _Value)	{ m_Order = _Value; }

public:
	Renderer();
	~Renderer();
};

