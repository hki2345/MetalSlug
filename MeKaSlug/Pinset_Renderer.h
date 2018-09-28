#pragma once
#include "Renderer.h"
#include "MultiSprite.h"
#include <vector>

class Pinset_Renderer : public Renderer
{
public:
	class PinsetData
	{
		// 인트를 2배로 늘린 자료형에 두개의 정수를 담아놓는다.
		// 인덱스는 어떤 것이 저장되는지

		// 방향을 저장해 둔다.
		// -> 카메라가 다음 핀셋으로 가기위한 일종의 플레이어 위치 조건

		// 컨디션 첫번째 -> 어떤 적을 -> 적의 인덱스
		// 두번째 몇마리를 잡으면...
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
	// 공간변환
	// 타일맵의 공간변환은 굉장히 쉽다.
	// 64 64 
	// 마우스 위치 X / 64
	// 마우스 위치 Y / 64
	void Set_Pinset(const WCHAR* _pTileSetName);
	void Insert_Pinset(Position _Pos, Position _Index, Position _Pos2);
	void SetScreenToEnemy(Position _Pos, Position _Index, Position _Pos2);

public:
	virtual void Render() override;


public:
	Pinset_Renderer();
	~Pinset_Renderer();
};

