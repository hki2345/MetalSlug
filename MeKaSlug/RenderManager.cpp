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
	// ã�´�.
	RendingIter = m_map_RendererList.find(_StateName);
	std::map<int, std::list<Renderer*>> NewStateRenderList = std::map<int, std::list<Renderer*>>();

	// ������ -> �ִ´�.
	if (RendingIter == m_map_RendererList.end())
	{
		// �ϴ� Ű�� ����� ���´�? ����
		m_map_RendererList.insert
		(std::map<std::wstring, std::map<int, std::list<Renderer*>>>::value_type(_StateName, NewStateRenderList));
	}
}

// ���� ������Ʈ �̸��� �ϳ� �� �޾ƾ� �Ѵ� ��.��;;
// ���� ���� Ŀ����. ��.��;; �� ���ϳ��� ������ ���ε� �������⼭ �� �̸��� ���Ѵ�...
void RenderManager::Insert_Renderer(Renderer* _Renderer, const WCHAR* _Name)
{
	std::map<std::wstring, std::map<int, std::list<Renderer*>>>::iterator FindState =
		m_map_RendererList.find(_Name);


	// ���� ���� �ִ� ����
	std::map<int, std::list<Renderer*>>::iterator FindOrderIter
		= FindState->second.find(_Renderer->Order());

	// ���� ���� �������� �������� ����
	if (FindOrderIter == FindState->second.end())
	{
		// �׷� ���� ����� �־��
		std::list<Renderer*> List = std::list<Renderer*>();
		List.push_back(_Renderer);
		FindState->second.insert(std::map<int, std::list<Renderer*>>::value_type(_Renderer->Order(), List));
		return;
	}

	// ������ ���� ������ ���� ���ݲ� �ڿ��� ������ ���� ����Ʈ�ϱ�
	FindOrderIter->second.push_back(_Renderer);
}

// �� �۾��� �ھ�� Change�Ҷ� ���� �̷�������Ѵ�.,
// �ƴϸ� ������Ʈ���� �ݵ�� �� ��ü�۾��� �̷�����߰ڴ�.
void RenderManager::Change_Rending_State(const WCHAR* _Name)
{
	// ã�´� -> ���� �� �� �ʿ� ���� ����ڵ常 �ĳ��� �ƹ� �͵� ���ص� �ȴ�.
	// ���ʹ� �� �͸� �����ѵ� �� ���� �ϴ� ���̴�.
	RendingIter = m_map_RendererList.find(_Name);

	if (RendingIter == m_map_RendererList.end())
	{
		KAssert(true);
	}
}



// ���� -> ���� ����� ������Ʈ �̸����� ���� ã�� �� �� ������Ʈ ������
// ������ �����ϵ��� �ϰڴ�
void RenderManager::Render()
{
	// change�� �ٲ� ���͸� ���⼭ ���� �Ŵ�
	// ����Ű�⸸ �ص� �ȴٴ� ���� �̷� �� -> ����Ű�� �͸� �����Ѵ�.
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


// ������Ʈ ��ȯ �ܰ迡�� �� �Լ��� ������ ������ �����,.
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
			// �θ�ü�� �׾��� ��� ������ �������Ѵ�.
			if ((*RendererStartIter)->Death())
			{
				RendererStartIter = LayerStartIter->second.erase(RendererStartIter);
			}
			// for���� ++�� ���ܽ�Ų��.
			else
			{
				RendererStartIter++;
			}
		}
	}
}