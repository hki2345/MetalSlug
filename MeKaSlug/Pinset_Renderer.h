#pragma once
#include "Renderer.h"
#include "MultiSprite.h"
#include <vector>

class Pinset_Renderer : public Renderer
{
public:
	class PinsetData
	{
		// ��Ʈ�� 2��� �ø� �ڷ����� �ΰ��� ������ ��Ƴ��´�.
		// �ε����� � ���� ����Ǵ���

		// ������ ������ �д�.
		// -> ī�޶� ���� �ɼ����� �������� ������ �÷��̾� ��ġ ����

		// ����� ù��° -> � ���� -> ���� �ε���
		// �ι�° ����� ������...
	public:
		__int64 m_EPos;
		__int64 m_DPos;
		__int64 m_Condition;

		PinsetData() : m_EPos(0), m_DPos(0), m_Condition(0)
		{}
		PinsetData(__int64 _Pos, __int64 _Dir, __int64 _Con)  : m_EPos(_Pos), m_DPos(_Dir), m_Condition(_Con)
		{}
	};
private:
	bool m_IsRender;
	Sprite* p_Sprite;
	int m_Erase_Size;

	std::list<PinsetData> m_PinsetMap;
	std::list<PinsetData>::iterator m_FindIter;
	std::list<PinsetData>::iterator m_StartIter;
	std::list<PinsetData>::iterator m_EndIter;

	Size m_Size;

public:
	void PinsetSize(Size _Size)
	{
		m_Size = _Size;
	}

	Size& PinsetSize()
	{
		return m_Size;
	}

	void Set_TransColor(const UINT& _Data)
	{
	 	p_Sprite->Set_TransColor(_Data);
	}

	void Clear();
	std::vector<PinsetData> GetAllPinsetData();
	void EraseScreenToPinset(Position _Pos);


public:
	// ������ȯ
	// Ÿ�ϸ��� ������ȯ�� ������ ����.
	// 64 64 
	// ���콺 ��ġ X / 64
	// ���콺 ��ġ Y / 64
	void Set_Pinset(const WCHAR* _pTileSetName);
	void Insert_Pinset(Position _Pos, Position _Index, Position _Pos2);
	void SetScreenToEnemy(Position _Pos, Position _Index, Position _Pos2);

public:
	virtual void Render() override;


public:
	Pinset_Renderer();
	~Pinset_Renderer();
};

