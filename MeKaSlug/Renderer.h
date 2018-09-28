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
	// �׸��� ����
	int m_Order;
	// �ٸ� ���� ������ ���� �ʴ´� -> ������ ���� ����
	// �� �ڽĵ��� �˾ƾ��Ѵ� ���� -> ���������̱� ������ ����
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

