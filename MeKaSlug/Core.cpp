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
	// ���� static ���� �ϳ��� ���� �� �ְ�
	static Core NewCore;
	return NewCore;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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



	// �������� ��Ÿ���� �ٲٴ� �۾�
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

	// ���⼭ GetDc�� ���������. -> �ٵ� ������ RenderManager�� GetDC�� ȣ����
	// Image�� ����� ���̸� �翬 Nullptr�� ������.
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
		
		// ���� �ھ �̱����̶� ���ʿ� ���� �ʴ´� ����;;;�ФѤ�;;�����Ʒ��Ӥ��ð����v
		// ���� ��� static���� �����ָ� �ǰ����� �ϱ� �ȴ�!
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
	
	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance())
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(kHInstance, MAKEINTRESOURCE(IDC_MEKASLUG));

	MSG msg;

	// ���ҽ��޴����� ���� - ���� ������Ʈ���� ������Ʈ�� ����� �������� �� �޴����� �����ȴ�.
	// ���� �� ���������� GetDc�� ���� ���̴�.
	// ������ �ʱ�ȭ-ȭ�鿡 ���� �̹��� �ʱ�ȭ�� �и��Ǿ���Ѵ�.
	kBHdc = RESOURCEMANAGER.Inst().Init();

	while (CoreProgress)
	{
		// �ȸ޽����� ��ȯ �ڿ�	�޽����� ���̸� �ƿ� ���������� ����
		// �޽��� ��ĸ��� ��� ����ϴ� ����� �ƴϴ�.
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

	// ���� ��ȯ
	m_p_ActingState = Iter->second;
	RENDERMANAGER.Change_Rending_State(Iter->second->Name());
	COLLIDERMANAGER.Change_ColliderIter(Iter->second->Name());
	m_p_ActingState->StateStart();
}


void Core::ActingCore()
{
	// ���콺 ��ǥ �޾ƿ���
	POINT MousePoint = { 0,0 };

	// ���콺�� ��ǥ�� ȭ�� �������� �����´�.
	GetCursorPos(&MousePoint);
	// �� ��ǥ�� ����ڰ� ���� �� �ֵ��� �����Ѵ�.
	ScreenToClient(kHwnd, &MousePoint);

	// �� ��ǥ�� �޴´�.
	MousePos.X = MousePoint.x;
	MousePos.Y = MousePoint.y;

	KEYMANAGER.Update();
	TIMEMANAGER.Update();

	KAssert(nullptr == m_p_ActingState);


	m_p_ActingState->Update();
	m_p_ActingState->StateUpdate();
	m_p_ActingState->Collision();

	RESOURCEMANAGER.Update_Sound();
	// ������Ʈ ����-> ������Ʈ�� �����޴����� ��� �ִ°��� �ƴ�
	// �����Ŵ��� ���� ���� �и��Ǿ� ����Ǵ� �̷��� �������� ������ �����ؾ��Ѵ�.
	RENDERMANAGER.Render();

	if (true == Value_Debegger)
	{
		m_p_ActingState->Value_DebugRender();
	}
	if (true == Obj_Debegger)
	{
		m_p_ActingState->Obj_DebugRender();
	}


	// ������۸� -> ȭ��ũ�⸸ŭ�� ��ƼĿ�� ���� ������ ����.
	BitBlt(kHdc, 0, 0, m_WinSize.X, m_WinSize.Y, kBHdc, 0, 0, SRCCOPY);

	// ȭ�� �ѹ� û���ϴ� �ڵ�
	Rectangle(kBHdc, 0, 0, m_WinSize.X, m_WinSize.Y);
	m_p_ActingState->Release();
}

void Core::CloseCore()
{
	// ��� �������� ����ִ� ������ �� ������ ����Ʈ �Ͽ��ش�.
	std::map<std::wstring, BaseState*>::iterator StartIter = m_map_AllState.begin();
	std::map<std::wstring, BaseState*>::iterator EndIter = m_map_AllState.end();
	for (; StartIter != EndIter; StartIter++)
	{
		NEW_DELETE(StartIter->second)
	}
	m_map_AllState.clear();
}