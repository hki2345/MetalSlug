#pragma once
#include "TheOne.h"

class Trans_Renderer;
class One_Stage_CCover : public TheOne
{
private:
	bool	m_CoverActing;
	float m_Time;
	float Obj_Time;

	Trans_Renderer* Cover;
	float Speed;

public:
	bool& Cover_Acting() { return m_CoverActing; }
	void Start(const Positionf& _Value);
	void Close(const Positionf& _Value);
	void Update()override;

public:
	One_Stage_CCover();
	~One_Stage_CCover();
};

