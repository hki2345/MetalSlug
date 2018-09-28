#pragma once
#include "TheOne.h"

class MapData_Creator;
class Pinset_Renderer;
class Trans_Renderer;
class One_Edit_Enemy : public TheOne
{
private:
	Trans_Renderer* m_p_EnemyView;
	Pinset_Renderer* m_p_PinsetMap;
	MapData_Creator* m_p_DataMap;
	int Enemy_Index;

	// �ݹ��� ���鼭 ���̾�α׸� ��� ���̱� ������  static���� �Ѵ�.
	static WCHAR m_char_FileName[1024];
	static std::wstring m_map_FileName;
	static std::wstring m_pin_FileName;

	// ���ʹ� �����ϴ� ���� ������ -> X, ����� -> Y
	static int m_pin_EnemyNum;
	static Position m_Pinset_Dir;
	static Position m_Pinset_Enemy;

	static bool m_b_SaveCheck;

public:
	static bool m_b_InDialog;


	// static std::wstring FileName;

public:
	void DataClear();

	virtual void Update() override;
	virtual void Init() override;
	virtual void DebugUpdate() override;

	static INT_PTR CALLBACK FileNameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK PinsetDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	One_Edit_Enemy();
	~One_Edit_Enemy();
};

