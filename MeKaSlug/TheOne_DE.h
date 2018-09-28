#pragma once
#include "Begin_DE.h"
#include "TheOne.h"

// 콜리더와 렌더러를 다룬다.
class TheOne_DE : public Begin_DE
{

protected:
	// Mother - TheOne
	TheOne* m_MotherOfTheOne_DE;

	// 비긴이니까 좌표를 가지고 있는 것이다.
	// 그리는 축 -> 그리려는 객체와 그려지는 것의 좌표는 서로 다를 수 있다.
	// 따라서 따로 지정하여야한다.
	Positionf m_Pivot;
	

public:
	bool Death()	override	{ return m_MotherOfTheOne_DE->Death() || Begin_DE::Death(); }
	bool Active()	override	{ return m_MotherOfTheOne_DE->Active() && Begin_DE::Active(); }
	bool Live()		override	{ return m_MotherOfTheOne_DE->Live() && Begin_DE::Live(); }
	bool LiveAndActive() 		{ return (m_MotherOfTheOne_DE->Active() && m_MotherOfTheOne_DE->Live()) &&
										(Begin_DE::Active() && Begin_DE::Live()); }


	// Mother - TheOne
	void		MotherOfTheOne_DE(TheOne* _Value)	{ m_MotherOfTheOne_DE = _Value; }
	TheOne*		MotherOfTheOne_DE()					{ return m_MotherOfTheOne_DE; }
	Positionf&	Pivot()								{ return m_Pivot; }
	void		Pivot(const Positionf& _Value)		{ m_Pivot = _Value; }




public:
	TheOne_DE();
	~TheOne_DE();
};

