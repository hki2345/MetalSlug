#pragma once
#include <map>
#include "BaseState.h"

// ������ ���� �߿��ϴ� -> �ھ� ����� �߰��Ǿ� �� ������ ��?
// ������Ʈ�� ����� �������� �����޴����� �� ������Ʈ�� �˾ƾ� �ϱ� ������
#include "RenderManager.h"
#include "ColliderManager.h"

// �������� ����� ���
#include "MatrixInfo.h"

// �ھ �̱������� ����� ����!

#define MAX_LOADSTRING 100

class Core
{
private:
	// ���� ����:
	HINSTANCE	kHInstance;                                // ���� �ν��Ͻ��Դϴ�.
	HWND		kHwnd;
	HDC			kHdc;

	// ������������ �� HDC
	HDC			kBHdc;

	// �� ���� �� static���� �Ͽ��� �ϴ°�?
	// CALLBACK �� �������� ���̱� �����̱⿡ static���� ¥�� �Ѵ�.
	static	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
			ATOM                MyRegisterClass();
			BOOL                InitInstance();

	WCHAR szTitle[MAX_LOADSTRING]		= L"asdf";           // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING] = L"rrr";            // �⺻ â Ŭ���� �̸��Դϴ�.


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
	// �� ������ �����ұ�? 
	// �������� GameState*�� ����� ���´�.
	std::map<std::wstring, BaseState*> m_map_AllState;
	BaseState* m_p_ActingState;
	Size m_WinSize;
	

	// ���콺 ��ǥ �ޱ�
	Position MousePos;


private:
	// ����� �����ϴ� �۾�
	template<typename T>
	void SetUpState(std::wstring _Name, bool _create = true)
	{
		if (m_map_AllState.end() != m_map_AllState.find(_Name))
		{
			return;
		}

		BaseState* NewState = new T();
		m_map_AllState.insert(std::map<std::wstring, BaseState*>::value_type(_Name, NewState));


		// ���� �� ����� �̸��� �ο��� ���̴�.
		NewState->Name(_Name.c_str());

		// �ο��� �̸����� ���� �ʿ� Ű�� �߰��Ѵ�.
		// ������ ���� �޴����� ������Ʈ ���־�� �Ʒ����� AllSetup��������
		// ��ü�� ������ ��� �� �� �ְڴ�.
		// �浹�޴����� ��.��.��
		RENDERMANAGER.Insert_State(NewState->Name());
		COLLIDERMANAGER.Insert_State(NewState->Name());

		if (true == _create)
		{
			// �̰������� AllSetup���� ���� ��� ��ü���� ������ ��ϵǾ�� �Ѵ�.
			NewState->Init();
		}
	}


	

	// �ھ �����Ŵ
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

	// ���� Ȱ������ ��� �ٲٱ� - ������ ������ (wstring ��)
	void ActingStateChanger(std::wstring _Name);


private:
	Core();
	Core(const Core& _other);
	~Core();
};

