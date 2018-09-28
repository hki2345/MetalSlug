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
	// ù��° �� -> ������Ʈ�� ����
	// �ι�° �� -> ������ ������ ���� -> ����
	// ����° ����Ʈ -> �� ���� ����Ʈ��
	std::map<std::wstring, std::map<int, std::list<Renderer*>>> m_map_RendererList;

	// ���� ������Ʈ ����
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
	// ���⼭ �����Ŵ����� �� �ȿ� �մ� ��� ���������� �����ϴ� ���
	void Render();
	// �θ� �� ������ ��ü�� ����� ���(�Ѿ� ���� ��) ������ �ϸ� �� �ǹǷ� ����Ʈ���� �����ؾ��Ѵ�.
	void Release();
};

