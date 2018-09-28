#pragma once
#include <map>
#include <list>
#include <string>

class RenderManager
{
public:
	friend class BaseState;
	friend class Renderer;

public:
	static RenderManager& Inst()
	{
		static RenderManager NewRenderMgr = RenderManager();
		return NewRenderMgr;
	}

private:
	RenderManager();
	~RenderManager();

private:
	// 첫번째 맵 -> 스테이트로 나눔
	// 두번째 맵 -> 랜더러 층으로 나눔 -> 순서
	// 세번째 리스트 -> 그 층의 리스트들
	std::map<std::wstring, std::map<int, std::list<Renderer*>>> m_map_RendererList;

	// 지정 스테이트 이터
	std::map<std::wstring, std::map<int, std::list<Renderer*>>>::iterator RendingIter;
	std::map<int, std::list<Renderer*>>::iterator LayerStartIter;
	std::map<int, std::list<Renderer*>>::iterator LayerEndIter;

	std::list<Renderer*>::iterator RendererStartIter;
	std::list<Renderer*>::iterator RendererEndIter;


private:
	void Insert_Renderer(Renderer* _Renderer, const WCHAR* _Name);



public:
	void Insert_State(const WCHAR* _Name);
	void Change_Rending_State(const WCHAR* _Name);

public:
	// 여기서 랜더매니저가 맵 안에 잇는 모든 랜더러들을 랜더하는 방식
	void Render();
	// 부모 즉 생성한 객체가 사라질 경우(총알 같은 것) 랜더를 하면 안 되므로 리스트에서 제거해야한다.
	void Release();
};

