#pragma once
#include <assert.h>

// ���̸� ����� ����Ϸ��� �̷���
#define _USE_MATH_DEFINES
#include <cmath>


// ���ǹ� ó�� ���̰� �ϱ� ���ؼ� ;�� ������. -> Ȥ�� �׳� ������ �� ����.
#define KAssert(Condition) assert(!(Condition))
#define NEW_DELETE(P) if (nullptr != P) { delete P; P = nullptr; }


#define KEYMANAGER KeyManager::Inst()


#define TIMEMANAGER TimeManager::Inst()
#define DELTATIME TIMEMANAGER.DeltaTime()


#define PATHMANAGER PathManager::Inst()


#define RESOURCEMANAGER ResourceManager::Inst()
#define RENDERMANAGER RenderManager::Inst()
#define COLLIDERMANAGER ColliderManager::Inst()
#define MATHMANAGER MathManager::Inst()

#define KEY_UNPRESS(VALUE)	KEYMANAGER.IsUnPress(L##VALUE)
#define KEY_UP(VALUE)		KEYMANAGER.IsUp(L##VALUE)
#define KEY_DOWN(VALUE)		KEYMANAGER.IsDown(L##VALUE)
#define KEY_PRESS(VALUE)	KEYMANAGER.IsPress(L##VALUE)

#define CORE Core::Inst()
#define CAMERA_SPD 300


#define TEXT_OUT(PX, PY, NAME) TextOutW(CORE.GetBHDC(), PX, PY, NAME, lstrlenW(NAME))
#define RadianToDegree (180 / M_PI)
#define DegreeToRadian (M_PI / 180)


// notL�� Edit_Enemy���� ������ �а� ���� ���� �� writestream ���� L�� �Ⱦ��� ���� -> write�Լ�
#define FILE_PATH_NOT_L(_FOLDER, _FILE) PATHMANAGER.CreateFilePath( _FOLDER, _FILE ).c_str()
#define FILE_PATH(FOLDER, FILE) PATHMANAGER.CreateFilePath( L##FOLDER, L##FILE ).c_str()

#define BGM_LOOP if (false == p_Sound_Player->Is_BGMPlay()) { p_Sound_Player->BGM_Play(); }

#define ORANGE RGB(255, 105, 0)
#define VIOLET RGB(255, 0, 255)