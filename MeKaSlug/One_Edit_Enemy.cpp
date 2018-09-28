#include "stdafx.h"
#include "One_Edit_Enemy.h"
#include "Resource.h"

#include "MapData_Creator.h"
#include "Pinset_Renderer.h"
#include "Trans_Renderer.h"

#include "WriteStream.h"
#include "ReadStream.h"
#include <Windows.h>

WCHAR One_Edit_Enemy::m_char_FileName[1024] = { 0 };
std::wstring One_Edit_Enemy::m_map_FileName = L"";
std::wstring One_Edit_Enemy::m_pin_FileName = L"";
int One_Edit_Enemy::m_pin_EnemyNum = 0;

Position One_Edit_Enemy::m_Pinset_Dir = Vector2();
Position One_Edit_Enemy::m_Pinset_Enemy = Vector2();

bool One_Edit_Enemy::m_b_SaveCheck = false;
bool One_Edit_Enemy::m_b_InDialog = false;

One_Edit_Enemy::One_Edit_Enemy() : Enemy_Index(0)
{
}


One_Edit_Enemy::~One_Edit_Enemy()
{
}

void One_Edit_Enemy::Update()
{
	if (KEYMANAGER.KEY_DOWN("Enemy_Save"))
	{
		m_b_SaveCheck = false;


		DialogBox(Core::Inst().GetHInstance(), MAKEINTRESOURCE(IDD_DIALOG1)
				, Core::Inst().GetHWND(), One_Edit_Enemy::FileNameDlgProc);
	
		if (true == m_b_SaveCheck)
		{
			WriteStream MapStream = WriteStream(FILE_PATH_NOT_L(L"Data", m_map_FileName.c_str()));
			WriteStream PinStream = WriteStream(FILE_PATH_NOT_L(L"Data", m_pin_FileName.c_str()));

			// 벡터를 통째로 가져와 세이브 한다
			std::vector<MapData_Creator::EnemyData> NE = m_p_DataMap->GetAllEnemyData();
			std::vector<Pinset_Renderer::PinsetData> PE = m_p_PinsetMap->GetAllPinsetData();


			// -> 파일 적용
			MapStream << NE.size();
			PinStream << PE.size();

			for (size_t i = 0; i < NE.size(); i++)
			{
				MapStream << NE[i];
			}

			for (size_t i = 0; i < PE.size(); i++)
			{
				PinStream << PE[i];
			}
		}
	}

	if (KEYMANAGER.KEY_DOWN("Enemy_Load"))
	{
		m_b_SaveCheck = false;

		DialogBox(Core::Inst().GetHInstance(), MAKEINTRESOURCE(IDD_DIALOG2)
			, Core::Inst().GetHWND(), One_Edit_Enemy::FileNameDlgProc);
		if (true == m_b_SaveCheck)
		{
			// 읽을 경로 확인
			ReadStream MapStream = ReadStream(FILE_PATH_NOT_L(L"Data", m_map_FileName.c_str()));
			ReadStream PinStream = ReadStream(FILE_PATH_NOT_L(L"Data", m_pin_FileName.c_str()));
			
			// 이전 데이터 삭제
			m_p_DataMap->Clear();
			m_p_PinsetMap->Clear();

			size_t map_Size;
			size_t pin_Size;

			MapStream >> map_Size;
			PinStream >> pin_Size;

			MapData_Creator::EnemyData LoadEnemyData;
			Pinset_Renderer::PinsetData LoadPinData;

			for (size_t i = 0; i < map_Size; i++)
			{
				MapStream >> LoadEnemyData;

				m_p_DataMap->Insert_Enemy(LoadEnemyData.m_EPos, (MapData_Creator::Enemy_DataIndex)LoadEnemyData.EnemyIndex);
			}

			for (size_t i = 0; i < pin_Size; i++)
			{
				PinStream >> LoadPinData;

				m_p_PinsetMap->Insert_Pinset(LoadPinData.m_EPos, LoadPinData.m_DPos, LoadPinData.m_Condition);
			}
		}
	}

	if (KEYMANAGER.KEY_DOWN("Enemy_Left"))
	{
		--Enemy_Index;

		if (0 > Enemy_Index)
		{
			Enemy_Index = (int)(m_p_DataMap->Enemy_Index() - 1);
		}

		m_p_EnemyView->Set_Sprite(L"Tileset.bmp", Enemy_Index);
		m_p_EnemyView->Pivot({ 100, 100 });
	}

	if (KEYMANAGER.KEY_DOWN("Enemy_Right"))
	{
		++Enemy_Index;

		if (m_p_DataMap->Enemy_Index() - 1 < Enemy_Index)
		{
			Enemy_Index = 0;
		}

		m_p_EnemyView->Set_Sprite(L"Tileset.bmp", Enemy_Index);
		m_p_EnemyView->Pivot({ 100, 100 });
	}

	if (KEYMANAGER.KEY_DOWN("MouseLB"))
	{
		m_p_DataMap->SetScreenToEnemy(CORE.GetMousePos() + m_MotherOfTheOne->CameraPos(), 
			(MapData_Creator::Enemy_DataIndex)Enemy_Index);
	}


	if (KEYMANAGER.KEY_PRESS("MouseRB"))
	{
		m_p_DataMap->EraseScreenToEnemy(CORE.GetMousePos() + m_MotherOfTheOne->CameraPos());
		m_p_PinsetMap->EraseScreenToPinset(CORE.GetMousePos() + m_MotherOfTheOne->CameraPos());
	}


	// 핀셋을 박는 작업 -> 현재 카메라 위치, 
	if (KEYMANAGER.KEY_DOWN("Pinset"))
	{
		m_b_SaveCheck = false;

		DialogBox(CORE.GetHInstance(), MAKEINTRESOURCE(IDD_DIALOG3)
			, Core::Inst().GetHWND(), One_Edit_Enemy::PinsetDlgProc);

		if (true == m_b_SaveCheck)
		{
			m_p_PinsetMap->SetScreenToEnemy(m_MotherOfTheOne->CameraIntPos(), m_Pinset_Dir, m_Pinset_Enemy);
		}
	}
}

void One_Edit_Enemy::Init()
{
	// 만들기만 해도 랜더할때 
	m_p_EnemyView = Create_Renderer<Trans_Renderer>(600);
	m_p_EnemyView->Set_Sprite(L"Tileset.bmp", 0);
	m_p_EnemyView->Set_TransColor(ORANGE);
	m_p_EnemyView->Pivot({ 100, 100 });
	m_p_EnemyView->CameraMode(false);


	m_p_PinsetMap = Create_Renderer<Pinset_Renderer>(300);
	m_p_PinsetMap->Set_Pinset(L"Pinset.bmp");
	m_p_PinsetMap->PinsetSize({ 30, 30 });
	m_p_PinsetMap->Set_TransColor(RGB(255,0, 255));

	// NewTrans->SettingSprite();

	m_p_DataMap = m_MotherOfTheOne->StateOfOne_Create<MapData_Creator>();
}

void One_Edit_Enemy::DebugUpdate()
{

}


// 정보 대화 상자의 메시지 처리기
// 해당 다이얼로그가 static을 쓰기에 그걸 받는 변수들도 static이어야한다.
INT_PTR CALLBACK One_Edit_Enemy::FileNameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		m_b_InDialog = true;
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// 이녀석이 전역 함수다.
			GetDlgItemTextW(hDlg, IDC_EDIT1, m_char_FileName, 1024);
			m_map_FileName = m_char_FileName;
			m_map_FileName += L".MapData";
			m_pin_FileName = m_char_FileName;
			m_pin_FileName += L".PinData";
			EndDialog(hDlg, LOWORD(wParam));
			m_b_SaveCheck = true;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			m_b_SaveCheck = false;
			m_b_InDialog = false;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		m_b_InDialog = false;
		break;
	}
	return (INT_PTR)FALSE;
}


// 정보 대화 상자의 메시지 처리기
// 해당 다이얼로그가 static을 쓰기에 그걸 받는 변수들도 static이어야한다.
INT_PTR CALLBACK One_Edit_Enemy::PinsetDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		// 일단 버튼 초기화는 처음 으로 해준다.
	case WM_INITDIALOG:
		m_b_InDialog = true;
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO4);
		CheckRadioButton(hDlg, IDC_RADIO5, IDC_RADIO10, IDC_RADIO10);
		
		m_Pinset_Dir = Vector2::Zero;
		m_Pinset_Enemy = Vector2::Zero;

		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// 해당 스트링을 변수로 저장한다.
			GetDlgItemTextW(hDlg, IDC_EDIT1, m_char_FileName, 1024);
			
			// 버튼 체크 - 핀셋 방향 지정
			UINT _Up =IsDlgButtonChecked(hDlg, IDC_RADIO1);
			UINT _Down =IsDlgButtonChecked(hDlg, IDC_RADIO2);
			UINT _Left =IsDlgButtonChecked(hDlg, IDC_RADIO3);
			UINT _Right =IsDlgButtonChecked(hDlg, IDC_RADIO4);
			
			if (1 == _Up) { m_Pinset_Dir = Vector2::Up; }
			else if (1 == _Down) { m_Pinset_Dir = Vector2::Down; }
			else if (1 == _Right) { m_Pinset_Dir = Vector2::Right; }
			else if (1 == _Left) { m_Pinset_Dir = Vector2::Left; }
			else { m_Pinset_Dir = Vector2::Zero; }


			UINT _Walker = IsDlgButtonChecked(hDlg, IDC_RADIO5);
			UINT _Bomb = IsDlgButtonChecked(hDlg, IDC_RADIO6);
			UINT _Cannon = IsDlgButtonChecked(hDlg, IDC_RADIO7);
			UINT _MachineGun = IsDlgButtonChecked(hDlg, IDC_RADIO8);
			UINT _Sarubia = IsDlgButtonChecked(hDlg, IDC_RADIO9);
			UINT _None = IsDlgButtonChecked(hDlg, IDC_RADIO10);
			UINT _Tank = IsDlgButtonChecked(hDlg, IDC_RADIO11);
			UINT _Bradley = IsDlgButtonChecked(hDlg, IDC_RADIO12);
			UINT Heli = IsDlgButtonChecked(hDlg, IDC_RADIO13);


			// 적 체크 - 누구인지와 몇마리 설정
			// 누구인지
			if (1 == _Walker) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Walker; }
			else if (1 == _Bomb) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Bomb; }
			else if (1 == _Cannon) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Cannon; }
			else if (1 == _MachineGun) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::MachineGun; }
			else if (1 == _Sarubia) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::SaruBian; }
			else if (1 == _MachineGun) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::MachineGun; }
			else if (1 == _Tank) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Tank; }
			else if (1 == _Bradley) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Bradley; }
			else if (1 == Heli) { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::Heli; }
			else { m_Pinset_Enemy.X = BaseEnemy::Enemy_DataIndex::None; }

			if (L"" == m_char_FileName)
			{
				m_Pinset_Enemy.Y = 0;
			}

			else
			{
				// 몇마리
				m_Pinset_Enemy.Y = _wtoi(m_char_FileName);
			}



			EndDialog(hDlg, LOWORD(wParam));
			m_b_SaveCheck = true;
			m_b_InDialog = false;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			m_b_SaveCheck = false;
			m_b_InDialog = false;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void One_Edit_Enemy::DataClear()
{
	// 이전 데이터 삭제
	m_p_DataMap->Clear();
	m_p_PinsetMap->Clear();
}