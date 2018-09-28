#pragma once
#include "Begin.h"

class Begin_DE : public Begin
{
private:
	bool			IsLive;
	bool			IsActive;

public:
	// 생명데이터를 주고 받음
	virtual bool			Live()				{ return IsLive; }
	virtual void			Live(bool _Value)	{ IsLive = _Value; }

	virtual bool			Active()			{ return IsActive; }
	virtual void			Active(bool _Value) { IsActive = _Value; }
	
	virtual bool			Death()				{ return !IsLive; }
	virtual void			Death(bool _Value)	{ IsLive = !(_Value); }

protected:
	Begin_DE() : IsLive(true), IsActive(true) {};
	virtual ~Begin_DE() {};
};

