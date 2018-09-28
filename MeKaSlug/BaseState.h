#pragma once
#include "Begin.h"

#include "RenderManager.h"
#include "ColliderManager.h"

// 왜 장면에 들어있는 오브젝트들은 리스트로 저장되어야 하는가?
// 굳이 reserve를 할 이유가 있을까?
// 그냥 넣으면 넣는 것이고 모두 생명을 가지고 있기 때문에
// 생명이 없으면 제거가 되는 것이 아닌 그려지지 않는 것일 뿐이다.
// 어떤 틀의 빈공간을 만들 필요 없이(메모리 낭비 없어도) 꽉꽉 채우고 초기화 최신화 시각화를 해야한다.
#include <list>

class TheOne;
class One_Player;
class Sound_Player;
class Pinset_FixData;
class One_Data_Loader;

class Trans_Renderer;
class One_Stage_SCover;
class One_Stage_CCover;
class One_MultiFont;
class One_NumberFont;
class State_Boss;
class State_Debug_SB;
class BaseState : public Begin
{
public:
	// 보스스테이지는 특수함
	friend class State_Boss;
	friend class State_Debug_SB;
	friend class TheOne;
	friend class Core;

private:
	std::list<TheOne*> m_list_StateOfOne;
	std::list<TheOne*>::iterator m_Start_Iter;
	std::list<TheOne*>::iterator m_End_Iter;

	bool		m_Create;
	Positionf	m_pos_Camera;

protected:
	// 중력 관련 - 충돌체 이미지
	const	WCHAR*	m_Wchar_Map;

	// 생성된 것을 확인
public:
	void		acting_map(const WCHAR* _Value) { m_Wchar_Map = _Value; }
	void		acting_map(WCHAR* _Value)		{ m_Wchar_Map = _Value; }
	const WCHAR* acting_map()					{ return m_Wchar_Map; }
	bool		Is_Create()						{ return m_Create; }

public:
	// 그 모든 것을 만들 수 있어야 한다. -> 템플릿
	template<typename T>
	T* StateOfOne_Create()
	{
		T* newOne = new T();
		newOne->MotherOfTheOne(this);

		newOne->Init();
		m_list_StateOfOne.push_back(newOne);
		return newOne;
	}


	Positionf&	CameraPos()						{ return m_pos_Camera; }
	Position	CameraIntPos()					{ return Vector2({m_pos_Camera.X, m_pos_Camera.Y}); }
	void		CameraPos(Positionf _Pos)		{ m_pos_Camera = _Pos; }
	void		MoveCamera(Positionf _Pos)		{ m_pos_Camera += _Pos; }
	void		ToMoveCamera(Positionf _Pos);

// 자식들만이 생성을 할 수 있다.
// -> 자식들 :: 여러가지의 스테이트 장면 역할
protected:
	BaseState();
	~BaseState();

protected:
	virtual void Setting_Key() {};
	virtual void Setting_Image() {};
	virtual void Setting_Collider() {};

	// 여기서 최신화 하는 것은 장면 전체적으로 적용되는 것들
	// 키나 시간이 될수 있겠다.
	virtual void StateUpdate() {};
	virtual void Value_DebugRender() {};
	virtual void Obj_DebugRender() ;

	// 모든 것들은 한 번만 생성되어야 한다.
	virtual void All_SetUp() = 0 {};

	// 바뀌고 나서 한번 실행한다.
	virtual void StateStart();

	void Init();
	// 모든 초기화 최신화 충돌 시각화는 한 장면에서 관리한다.
	virtual void Update();
	virtual void Collision();
	void Release();

	// 랜더링과 충돌처리
	void Insert_Renderer(Renderer* _Renderer);
	void Insert_Collider(const WCHAR* _GroupName, Collider* _Collider);



	/********************** 사운드 *******************/
public:
	Sound_Player* p_Sound_Player;



	/********************** 핀셋 *******************/
protected:
	float m_Time;
	float m_State_Time;

protected:
	bool m_State_Over;
	One_Player* m_p_Player;
	One_Data_Loader* m_p_Load;
	
private:
	std::list<Pinset_FixData*> m_ListData;

	std::list<Pinset_FixData*>::iterator DataFindIter;
	std::list<Pinset_FixData*>::iterator DataStartIter;
	std::list<Pinset_FixData*>::iterator DataEndIter;

	int m_CameraSpdX;
	int m_CameraSpdY;
	int m_Camera_space_size;
	Dirf m_CameraDir;

	Pinset_FixData* m_CurPinset;
	Pinset_FixData* SearchPinset();
	void Change_CurPinset();

protected:
	void Init_Camera(const WCHAR* _Path);
	void Update_Camera();



	/********************** UI *******************/
private:
	One_Stage_SCover*	m_SCover;
	One_Stage_CCover*	m_CCover;
	
	One_MultiFont* m_Multi_Life;
	One_MultiFont* m_Multi_Armo;

	One_NumberFont* m_NumMulti_Armo;
	One_NumberFont* m_NumMulti_Bomb;
	One_NumberFont* m_NumMulti_Score;

	Trans_Renderer* m_Armo_Bomb;

protected:
	void Init_UI(const Positionf& _StartPos, const WCHAR* _BGM, const WCHAR* _SND);
	void Update_UI(const WCHAR* _NextStage);

};

