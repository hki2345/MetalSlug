#pragma once
#include "Begin.h"

#include "RenderManager.h"
#include "ColliderManager.h"

// �� ��鿡 ����ִ� ������Ʈ���� ����Ʈ�� ����Ǿ�� �ϴ°�?
// ���� reserve�� �� ������ ������?
// �׳� ������ �ִ� ���̰� ��� ������ ������ �ֱ� ������
// ������ ������ ���Ű� �Ǵ� ���� �ƴ� �׷����� �ʴ� ���� ���̴�.
// � Ʋ�� ������� ���� �ʿ� ����(�޸� ���� ���) �˲� ä��� �ʱ�ȭ �ֽ�ȭ �ð�ȭ�� �ؾ��Ѵ�.
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
	// �������������� Ư����
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
	// �߷� ���� - �浹ü �̹���
	const	WCHAR*	m_Wchar_Map;

	// ������ ���� Ȯ��
public:
	void		acting_map(const WCHAR* _Value) { m_Wchar_Map = _Value; }
	void		acting_map(WCHAR* _Value)		{ m_Wchar_Map = _Value; }
	const WCHAR* acting_map()					{ return m_Wchar_Map; }
	bool		Is_Create()						{ return m_Create; }

public:
	// �� ��� ���� ���� �� �־�� �Ѵ�. -> ���ø�
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

// �ڽĵ鸸�� ������ �� �� �ִ�.
// -> �ڽĵ� :: ���������� ������Ʈ ��� ����
protected:
	BaseState();
	~BaseState();

protected:
	virtual void Setting_Key() {};
	virtual void Setting_Image() {};
	virtual void Setting_Collider() {};

	// ���⼭ �ֽ�ȭ �ϴ� ���� ��� ��ü������ ����Ǵ� �͵�
	// Ű�� �ð��� �ɼ� �ְڴ�.
	virtual void StateUpdate() {};
	virtual void Value_DebugRender() {};
	virtual void Obj_DebugRender() ;

	// ��� �͵��� �� ���� �����Ǿ�� �Ѵ�.
	virtual void All_SetUp() = 0 {};

	// �ٲ�� ���� �ѹ� �����Ѵ�.
	virtual void StateStart();

	void Init();
	// ��� �ʱ�ȭ �ֽ�ȭ �浹 �ð�ȭ�� �� ��鿡�� �����Ѵ�.
	virtual void Update();
	virtual void Collision();
	void Release();

	// �������� �浹ó��
	void Insert_Renderer(Renderer* _Renderer);
	void Insert_Collider(const WCHAR* _GroupName, Collider* _Collider);



	/********************** ���� *******************/
public:
	Sound_Player* p_Sound_Player;



	/********************** �ɼ� *******************/
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

