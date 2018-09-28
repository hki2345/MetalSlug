#pragma once
#include "Animator.h"

class Animator;
class FsmWorker
{
private:
	class StateData
	{
	public:
		std::wstring Name;
		std::wstring AniName;

	public:
		StateData(std::wstring& _StateName, std::wstring& _AniName) : Name(_StateName), AniName(_AniName)
		{
		}
	};

private:
	Animator* m_pWork;
	StateData* m_pCurState;

	std::map<std::wstring, StateData> m_MapData;

public:
	StateData* CurState() {
		return m_pCurState;
	}

public:
	void SetAniWork(Animator* _pWork) 
	{
		m_pWork = _pWork;
	}
	Animator* AniWork()
	{
		return m_pWork;
	}

	void CreateState(std::wstring _StateName, std::wstring _AniName);
	void ChangeState(std::wstring _StateName, Positionf _Pivot);
	void ChangeState(std::wstring _StateName);

public:
	FsmWorker();
	FsmWorker(Animator* _pWork);
	~FsmWorker();
};

//class Animator;
//class PlayerFsmWorker
//{
//private:
//
//
//public:
//	FsmWorker(Animator* _pBodyWork, Animator* _pLegWork);
//	~FsmWorker();
//};
//
