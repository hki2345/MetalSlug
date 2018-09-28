#pragma once
#include "Begin_DE.h"
#include "TheOne.h"

// �ݸ����� �������� �ٷ��.
class TheOne_DE : public Begin_DE
{

protected:
	// Mother - TheOne
	TheOne* m_MotherOfTheOne_DE;

	// ����̴ϱ� ��ǥ�� ������ �ִ� ���̴�.
	// �׸��� �� -> �׸����� ��ü�� �׷����� ���� ��ǥ�� ���� �ٸ� �� �ִ�.
	// ���� ���� �����Ͽ����Ѵ�.
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

