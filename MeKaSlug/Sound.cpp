#include "stdafx.h"
#include "Sound.h"

#include <atlstr.h>

Sound::Sound()
{
}


Sound::~Sound()
{
}

bool Sound::Load(FMOD::System* _System, const WCHAR* _pFilePath)
{
	// UTF8 인코딩 -> WCHAR 을 Wstring 으로 볌ㄴ환 -> atlstr.h 필요
	std::wstring WStr = _pFilePath;
	std::string Str = CW2A(_pFilePath, CP_UTF8);

	// 항상 당른 라이브러리 사용시 반환값이 무엇인지 확인 화라
	// Fmod_Ok -> 0 값
	// 그리고 왠만하면 0 + nullptr을 집어넣는 것이 현명하다 한다.

	// 현재 불러오는 과정 - 사운드를 체크하는 권한을 획득한다.
	// 경로, 이펙트, 사운드 특이사항, 사운드

	//if (FMOD_OK != _System->createSound("D:\\Class\\5.1 - AssortRock\\\Work\MekaSlug\\MeKaSlug_0330_02\\bin\\Sound", FMOD_DEFAULT, nullptr, &m_pSound))
	if (FMOD_OK != _System->createSound(Str.c_str(), FMOD_DEFAULT, nullptr, &m_pSound))
	{
		KAssert(true);
		return false;
	}

	KAssert(nullptr == m_pSound);

	if (nullptr == m_pSound)
	{
		return false;
	}

	return true;
}