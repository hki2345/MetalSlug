#include "stdafx.h"
#include "Core.h"
#include "Resource.h"


#include "State_Game.h"
#include "State_Enemy_Edit.h"
#include "State_Enemy_Edit.h"

#include "State_Debug_S1.h"
#include "State_Debug_S2.h"
#include "State_Debug_S3.h"
#include "State_Debug_SB.h"

#include "State_LeonaDeb.h"
#include "State_EriDeb.h"

#include "State_Title.h"
#include "State_Military_System.h"
#include "State_Barracks.h"
#include "State_Stage01.h"
#include "State_Stage02.h"
#include "State_Stage03.h"
#include "State_Boss.h"
#include "State_End.h"




#include "KeyManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"

bool Core::CoreProgress = true;

Core::Core() : m_WinSize({800, 600}), kHInstance(nullptr), 
kHdc(nullptr), kBHdc(nullptr), m_p_ActingState(nullptr),
MousePos(Vector2::Zero), Value_Debegger(true), Obj_Debegger(true)
{	
}


Core::~Core()
{
}



Core& Core::Inst()
{
	// 지역 static 으로 하나만 만들 수 있게
	static Core NewCore;
	return NewCore;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = kHInstance;
	wcex.hIcon = LoadIcon(kHInstance, MAKEINTRESOURCE(IDC_MEKASLUG));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}



BOOL Core::InitInstance()
{
	kHwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_WinSize.X, m_WinSize.Y, nullptr, nullptr, kHInstance, nullptr);



	// 윈도우의 스타일을 바꾸는 작업
	RECT Rc = { 0, 0, m_WinSize.X, m_WinSize.Y };
	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(kHwnd, nullptr, 0, 0, Rc.right - Rc.left, Rc.bottom - Rc.top,
		SWP_NOMOVE | SWP_NOZORDER);

	if (!kHwnd)
	{
		return FALSE;
	}

	ShowWindow(kHwnd, SW_SHOWDEFAULT);
	UpdateWindow(kHwnd);

	// 여기서 GetDc가 만들어진다. -> 근데 이전에 RenderManager에 GetDC를 호출해
	// Image를 만드는 식이면 당연 Nullptr로 터진다.
	kHdc = GetDC(kHwnd);
	return TRUE;
}


LRESULT CALLBACK Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		// 나는 코어가 싱글톤이라 애초에 되지 않는다 ㅋㅋ;;;ㅠㅡㅠ;;ㅁㄴ아러ㅣㅏㅓ컾ㅊ퉣
		// 물론 모두 static으로 붙혀주면 되겠지만 하기 싫다!
		// ActingCore();
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		CoreProgress = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}




int Core::CoreLauncher(_In_ HINSTANCE hInstance)
{
	kHInstance = hInstance;

	MyRegisterClass();

	RENDERMANAGER;
	RESOURCEMANAGER.Set_Sound();

	COLLIDERMANAGER;
	SetUpState<State_Title>(L"Title");
	SetUpState<State_Military_System>(L"Military_System");
	SetUpState<State_Barracks>(L"Barracks");
	SetUpState<State_Game>(L"Game");
	SetUpState<State_LeonaDeb>(L"Leona");
	SetUpState<State_EriDeb>(L"Eri");
	SetUpState<State_Enemy_Edit>(L"EnemyEdit");


	SetUpState<State_Debug_S1>(L"Stage01Deb");
	SetUpState<State_Debug_S2>(L"Stage02Deb");
	SetUpState<State_Debug_S3>(L"Stage03Deb");
	SetUpState<State_Debug_SB>(L"StageBossDeb");

	SetUpState<State_Stage01>(L"Stage01");
	SetUpState<State_Stage02>(L"Stage02");
	SetUpState<State_Stage03>(L"Stage03");
	SetUpState<State_Boss>(L"StageBoss");
	SetUpState<State_End>(L"StageEnd");

	ActingStateChanger(L"Title");
	
	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance())
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(kHInstance, MAKEINTRESOURCE(IDC_MEKASLUG));

	MSG msg;

	// 리소스메니저의 생성 - 실은 스테이트에서 오브젝트를 만드는 과정에서 이 메니저가 생성된다.
	// 따라서 그 시점에서는 GetDc는 없을 것이다.
	// 생성과 초기화-화면에 찍을 이미지 초기화는 분리되어야한다.
	kBHdc = RESOURCEMANAGER.Inst().Init();

	while (CoreProgress)
	{
		// 픽메시지로 전환 뒤에	메시지가 쌓이면 아예 지워버리게 하자
		// 메시지 방식마저 계속 대기하는 방식이 아니다.
		// 
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ActingCore();
		}
	}

	CloseCore();
	
	return (int)msg.wParam;
}




void Core::ActingStateChanger(std::wstring _Name)
{
	std::map<std::wstring, BaseState*>::iterator Iter = m_map_AllState.find(_Name);

	KAssert(Iter == m_map_AllState.end());
	if (Iter == m_map_AllState.end()){ return; }

	// 현재 전환
	m_p_ActingState = Iter->second;
	RENDERMANAGER.Change_Rending_State(Iter->second->Name());
	COLLIDERMANAGER.Change_ColliderIter(Iter->second->Name());
	m_p_ActingState->StateStart();
}


void Core::ActingCore()
{
	// 마우스 좌표 받아오기
	POINT MousePoint = { 0,0 };

	// 마우스의 좌표를 화면 기준으로 가져온다.
	GetCursorPos(&MousePoint);
	// 그 좌표를 사용자가 읽을 수 있도록 보정한다.
	ScreenToClient(kHwnd, &MousePoint);

	// 그 좌표를 받는다.
	MousePos.X = MousePoint.x;
	MousePos.Y = MousePoint.y;

	KEYMANAGER.Update();
	TIMEMANAGER.Update();

	KAssert(nullptr == m_p_ActingState);


	m_p_ActingState->Update();
	m_p_ActingState->StateUpdate();
	m_p_ActingState->Collision();

	RESOURCEMANAGER.Update_Sound();
	// 스테이트 랜더-> 스테이트가 랜더메니저를 들고 있는것이 아닌
	// 랜더매니저 내에 맵이 분리되어 실행되니 이렇게 전역으로 랜더를 실행해야한다.
	RENDERMANAGER.Render();

	if (true == Value_Debegger)
	{
		m_p_ActingState->Value_DebugRender();
	}
	if (true == Obj_Debegger)
	{
		m_p_ActingState->Obj_DebugRender();
	}


	// 더블버퍼링 -> 화면크기만큼의 스티커를 이제 완전히 찍어낸다.
	BitBlt(kHdc, 0, 0, m_WinSize.X, m_WinSize.Y, kBHdc, 0, 0, SRCCOPY);

	// 화면 한번 청소하는 코드
	Rectangle(kBHdc, 0, 0, m_WinSize.X, m_WinSize.Y);
	m_p_ActingState->Release();
}

void Core::CloseCore()
{
	// 모든 힙영역에 들어있는 포인터 및 값들을 딜리트 하여준다.
	std::map<std::wstring, BaseState*>::iterator StartIter = m_map_AllState.begin();
	std::map<std::wstring, BaseState*>::iterator EndIter = m_map_AllState.end();
	for (; StartIter != EndIter; StartIter++)
	{
		NEW_DELETE(StartIter->second)
	}
	m_map_AllState.clear();
}