#pragma once
#include <map>
#include "BaseState.h"

// 랜더가 은근 중요하다 -> 코어 헤더에 추가되야 할 정도로 왜?
// 스테이트를 만드는 과정에서 렌더메니저가 그 스테이트를 알아야 하기 때문에
#include "RenderManager.h"
#include "ColliderManager.h"

// 윈도우의 사이즈를 담당
#include "MatrixInfo.h"

// 코어를 싱글톤으로 만들어 보자!

#define MAX_LOADSTRING 100

class Core
{
private:
	// 전역 변수:
	HINSTANCE	kHInstance;                                // 현재 인스턴스입니다.
	HWND		kHwnd;
	HDC			kHdc;

	// 랜더과정에서 찍어낼 HDC
	HDC			kBHdc;

	// 이 것은 왜 static으로 하여야 하는가?
	// CALLBACK 이 전역으로 쓰이기 때문이기에 static으로 짜야 한다.
	static	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
			ATOM                MyRegisterClass();
			BOOL                InitInstance();

	WCHAR szTitle[MAX_LOADSTRING]		= L"asdf";           // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING] = L"rrr";            // 기본 창 클래스 이름입니다.


	static bool CoreProgress;

	// Debug Bool
	bool Value_Debegger;
	bool Obj_Debegger;

public:
	bool& Get_Value_Debeg()
	{
		return Value_Debegger;
	}

	void Value_Debug_Switch()
	{
		if (true == Value_Debegger)
		{
			Value_Debegger = false;
		}
		else
		{
			Value_Debegger = true;
		}
	}
	void Obj_Debug_Switch()
	{
		if (true == Obj_Debegger)
		{
			Obj_Debegger = false;
		}
		else
		{
			Obj_Debegger = true;
		}
	}


private:
	// 왜 맵으로 관리할까? 
	// 여러개의 GameState*를 만들어 놓는다.
	std::map<std::wstring, BaseState*> m_map_AllState;
	BaseState* m_p_ActingState;
	Size m_WinSize;
	

	// 마우스 좌표 받기
	Position MousePos;


private:
	// 장면을 설정하는 작업
	template<typename T>
	void SetUpState(std::wstring _Name, bool _create = true)
	{
		if (m_map_AllState.end() != m_map_AllState.find(_Name))
		{
			return;
		}

		BaseState* NewState = new T();
		m_map_AllState.insert(std::map<std::wstring, BaseState*>::value_type(_Name, NewState));


		// 나는 이 장면의 이름을 부여할 것이다.
		NewState->Name(_Name.c_str());

		// 부여된 이름으로 렌더 맵에 키를 추가한다.
		// 구조상 랜더 메니저에 스테이트 가있어야 아래에서 AllSetup과정에서
		// 객체의 랜더를 등록 할 수 있겠다.
		// 충돌메니저도 똑.같.다
		RENDERMANAGER.Insert_State(NewState->Name());
		COLLIDERMANAGER.Insert_State(NewState->Name());

		if (true == _create)
		{
			// 이과정에서 AllSetup으로 인해 모든 객체들이 랜더에 등록되어야 한다.
			NewState->Init();
		}
	}


	

	// 코어를 진행시킴
	void ActingCore();
	void CloseCore();


public:
	HDC&				GetHDC()			{ return kHdc; }
	HDC&				GetBHDC()			{ return kBHdc; }
	HWND&				GetHWND()			{ return kHwnd; }
	HINSTANCE&			GetHInstance()		{ return kHInstance; }

	// Window Size
	Size				GetSize()			{ return m_WinSize; }
	Position&			GetMousePos()		{ return MousePos; }
	int					CoreLauncher(_In_ HINSTANCE hInstance);
	static Core&		Inst();

	// 현재 활동중인 장면 바꾸기 - 그인자 값으로 (wstring 값)
	void ActingStateChanger(std::wstring _Name);


private:
	Core();
	Core(const Core& _other);
	~Core();
};

