#include "stdafx.h"
#include "Renderer.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::Insert_State(const WCHAR* _StateName)
{
	// 찾는다.
	RendingIter = m_map_RendererList.find(_StateName);
	std::map<int, std::list<Renderer*>> NewStateRenderList = std::map<int, std::list<Renderer*>>();

	// 없으면 -> 넣는다.
	if (RendingIter == m_map_RendererList.end())
	{
		// 일단 키만 만들어 놓는다? ㅇㅇ
		m_map_RendererList.insert
		(std::map<std::wstring, std::map<int, std::list<Renderer*>>>::value_type(_StateName, NewStateRenderList));
	}
}

// 나는 스테이트 이름을 하나 더 받아야 한다 ㅡ.ㅡ;;
// 왠지 일이 커진다. ㅡ.ㅡ;; 난 맵하나를 더했을 뿐인데 여기저기서 이 이름을 원한다...
void RenderManager::Insert_Renderer(Renderer* _Renderer, const WCHAR* _Name)
{
	std::map<std::wstring, std::map<int, std::list<Renderer*>>>::iterator FindState =
		m_map_RendererList.find(_Name);


	// 같은 층에 넣는 과정
	std::map<int, std::list<Renderer*>>::iterator FindOrderIter
		= FindState->second.find(_Renderer->Order());

	// 같은 층에 넣으려는 랜더러가 없다
	if (FindOrderIter == FindState->second.end())
	{
		// 그럼 새로 만들어 넣어라
		std::list<Renderer*> List = std::list<Renderer*>();
		List.push_back(_Renderer);
		FindState->second.insert(std::map<int, std::list<Renderer*>>::value_type(_Renderer->Order(), List));
		return;
	}

	// 있으면 굳이 만들지 말고 지금꺼 뒤에다 넣으삼 ㅇㅇ 리스트니까
	FindOrderIter->second.push_back(_Renderer);
}

// 이 작업이 코어에서 Change할때 같이 이루어져야한다.,
// 아니면 스테이트에서 반드시 이 교체작업이 이루어져야겠다.
void RenderManager::Change_Rending_State(const WCHAR* _Name)
{
	// 찾는다 -> 굳이 뭐 할 필요 없이 방어코드만 쳐놓고 아무 것도 안해도 된다.
	// 이터는 그 것만 가리켜도 제 할을 하는 것이다.
	RendingIter = m_map_RendererList.find(_Name);

	if (RendingIter == m_map_RendererList.end())
	{
		KAssert(true);
	}
}



// 나는 -> 현재 저장된 스테이트 이름으로 먼저 찾은 후 그 스테이트 에서만
// 렌더를 실행하도록 하겠당
void RenderManager::Render()
{
	// change로 바꾼 이터를 여기서 쓰는 거다
	// 가리키기만 해도 된다는 것이 이런 것 -> 가리키는 것만 랜더한다.
	LayerStartIter = RendingIter->second.begin();
	LayerEndIter = RendingIter->second.end();

	for (; LayerStartIter != LayerEndIter; LayerStartIter++)
	{
		RendererStartIter = LayerStartIter->second.begin();
		RendererEndIter = LayerStartIter->second.end();

		for (; RendererStartIter != RendererEndIter; RendererStartIter++)
		{
			(*RendererStartIter)->Render();
		}
	}
}


// 스테이트 전환 단계에서 이 함수를 실행해 렌더를 지운다,.
void RenderManager::Release()
{
	LayerStartIter = RendingIter->second.begin();
	LayerEndIter = RendingIter->second.end();

	for (; LayerStartIter != LayerEndIter; LayerStartIter++)
	{
		RendererStartIter = LayerStartIter->second.begin();
		RendererEndIter = LayerStartIter->second.end();

		for (; RendererStartIter != RendererEndIter;)
		{
			// 부모객체가 죽었을 경우 랜더도 빠져야한다.
			if ((*RendererStartIter)->Death())
			{
				RendererStartIter = LayerStartIter->second.erase(RendererStartIter);
			}
			// for에서 ++를 제외시킨다.
			else
			{
				RendererStartIter++;
			}
		}
	}
}