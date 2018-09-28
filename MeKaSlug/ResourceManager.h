#pragma once
#include <map>
#include <string>
#include "MultiSprite.h"
#include "Sound.h"
#include <fmod.hpp>

// 사운드 자료는 스택으로 관리한다 -> 빼고 다시 넣는식
#include <stack>
#include <list>


// 해당 라이브러리 파일은 실행파일(exe) 잇는데 놓는다.
#ifdef X32
#pragma comment(lib, "fmod_vc")
#else
#pragma comment(lib, "fmod64_vc")
#endif

// COLORREF에서 RGB 추출 0 , 255, 255, 255 식으로 8비트씩 저장되었고 BGR순으로 저장
// 앞에 0은 사용되지 않으며, 이를 형변환해 사용
//#define GetRValue(rgb) ((BYTE)(rgb))
//#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb) ((BYTE)((rgb) >> 16))

class ResourceManager
{
	// 상호 프렌드
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
	// 이미지는 리소스 메니저에서 관리
	// 그 이미지들을 어디에 찍을 건지 -> HDC에 찍어 한번에 찍는다.
private:
	std::map<std::wstring, Image*> m_MapImage;
	Image* m_ImageOfMapImage;

	// 해당 경로의 이미지를 로드한다.
public:
	HDC& Init();

	Image* Load_Res_Image(const WCHAR* _Path);
	Image* Load_Res_Image(const WCHAR* _Path, const WCHAR* _Name);
	Image* Find_Res_Image(const WCHAR* _Name);
	COLORREF Get_PixelColor(const WCHAR* _Name, Position _pos);

	/****************************** Sprite ********************************/

	// 스프라이트도 리소스 메니저에서 관리
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
	// 사운드 장치에게 권한을 허락받기 위한 객체
	// Fmod가 없으면 아되겠징
	FMOD::System* SoundSystem;
	std::map<std::wstring, Sound*> m_Map_Sound;

	// 풀방식 - 스텍에 넣었다 플레이어를 하나씩 꺼내 쓴다.
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
