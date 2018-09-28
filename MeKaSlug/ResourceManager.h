#pragma once
#include <map>
#include <string>
#include "MultiSprite.h"
#include "Sound.h"
#include <fmod.hpp>

// ���� �ڷ�� �������� �����Ѵ� -> ���� �ٽ� �ִ½�
#include <stack>
#include <list>


// �ش� ���̺귯�� ������ ��������(exe) �մµ� ���´�.
#ifdef X32
#pragma comment(lib, "fmod_vc")
#else
#pragma comment(lib, "fmod64_vc")
#endif

// COLORREF���� RGB ���� 0 , 255, 255, 255 ������ 8��Ʈ�� ����Ǿ��� BGR������ ����
// �տ� 0�� ������ ������, �̸� ����ȯ�� ���
//#define GetRValue(rgb) ((BYTE)(rgb))
//#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb) ((BYTE)((rgb) >> 16))

class ResourceManager
{
	// ��ȣ ������
public:
	friend Sound_Player;
	friend Core;

public:
	static ResourceManager& Inst()
	{
		static ResourceManager NewResourceMgr = ResourceManager();
		return NewResourceMgr;
	}

private:
	ResourceManager();
	~ResourceManager();

	/****************************** Image ********************************/
	// �̹����� ���ҽ� �޴������� ����
	// �� �̹������� ��� ���� ���� -> HDC�� ��� �ѹ��� ��´�.
private:
	std::map<std::wstring, Image*> m_MapImage;
	Image* m_ImageOfMapImage;

	// �ش� ����� �̹����� �ε��Ѵ�.
public:
	HDC& Init();

	Image* Load_Res_Image(const WCHAR* _Path);
	Image* Load_Res_Image(const WCHAR* _Path, const WCHAR* _Name);
	Image* Find_Res_Image(const WCHAR* _Name);
	COLORREF Get_PixelColor(const WCHAR* _Name, Position _pos);

	/****************************** Sprite ********************************/

	// ��������Ʈ�� ���ҽ� �޴������� ����
private:
	std::map<std::wstring, Sprite*> m_Map_Sprite;

public:
	Sprite* Find_Res_Sprite(const WCHAR* _Name);
	Sprite* Load_Res_Sprite(const WCHAR* _Path);
	Sprite* Load_Res_Sprite(const WCHAR* _Path, const Rect& _Rect);
	Sprite* Load_Res_Sprite(const WCHAR* _Path, const WCHAR* _Name);
	Sprite* Load_Res_Sprite(const WCHAR* _Path, const WCHAR* _Name, const Rect& _Rect);


	/****************************** Multi Sprite ********************************/

private:
	std::map<std::wstring, MultiSprite*> m_Map_MultiSprite;

public:
	MultiSprite* Find_Res_MultiSprite(const WCHAR* _Name);
	MultiSprite* Load_Res_MultiSprite(const WCHAR* _Path, const Size& _Rect);
	MultiSprite* Load_Res_MultiSprite(const WCHAR* _Path, const WCHAR* _Name, const Size& _Size);

	/****************************** Sound ********************************/


private:
	// ���� ��ġ���� ������ ����ޱ� ���� ��ü
	// Fmod�� ������ �Ƶǰ�¡
	FMOD::System* SoundSystem;
	std::map<std::wstring, Sound*> m_Map_Sound;

	// Ǯ��� - ���ؿ� �־��� �÷��̾ �ϳ��� ���� ����.
	std::stack<Sound_Player*> m_Stack_Sleep_Player;
	std::list<Sound_Player*> m_List_Active_Player; 

	Sound_Player* BGMPlayer;
private:
	void	Set_Sound();
	void	Update_Sound();
	Sound*	Find_Sound(const WCHAR* _pName);

public:
	void			Play_Sound(const WCHAR* _pKey, const float& _Volume = 1.0f);
	Sound_Player*	Rental_SoundPlayer();

public:
	bool Load_Sound(const WCHAR* _pPath);
	bool Load_Sound(const WCHAR* _pPath, const WCHAR* _pKey);

};
