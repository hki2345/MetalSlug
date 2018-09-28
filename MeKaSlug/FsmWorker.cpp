#include "stdafx.h"
#include "FsmWorker.h"
#include "Animator.h"


FsmWorker::FsmWorker() : m_pWork(nullptr)
{

}

FsmWorker::FsmWorker(Animator* _pWork) : m_pWork(_pWork)
{
}

FsmWorker::~FsmWorker()
{
}


void FsmWorker::CreateState(std::wstring _StateName, std::wstring _AniName)
{
	std::map<std::wstring, StateData>::iterator Iter = m_MapData.find(_StateName);
	KAssert(Iter != m_MapData.end());
	m_MapData.insert(std::map<std::wstring, StateData>::value_type(_StateName, StateData(_StateName, _AniName)));
}

void FsmWorker::ChangeState(std::wstring _StateName)
{
	m_pWork->Reset_Animation();
	std::map<std::wstring, StateData>::iterator Iter = m_MapData.find(_StateName);
	KAssert(Iter == m_MapData.end());

	m_pCurState = &Iter->second;
	m_pWork->Change_Animation(Iter->second.AniName.c_str());
	m_pWork->Pivot(Vector2f::Zero);
}

void FsmWorker::ChangeState(std::wstring _StateName, Positionf _Pivot)
{
	ChangeState(_StateName);
	m_pWork->Pivot(_Pivot);
}