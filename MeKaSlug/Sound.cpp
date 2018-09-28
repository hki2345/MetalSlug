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
	// UTF8 ���ڵ� -> WCHAR �� Wstring ���� �٤�ȯ -> atlstr.h �ʿ�
	std::wstring WStr = _pFilePath;
	std::string Str = CW2A(_pFilePath, CP_UTF8);

	// �׻� �縥 ���̺귯�� ���� ��ȯ���� �������� Ȯ�� ȭ��
	// Fmod_Ok -> 0 ��
	// �׸��� �ظ��ϸ� 0 + nullptr�� ����ִ� ���� �����ϴ� �Ѵ�.

	// ���� �ҷ����� ���� - ���带 üũ�ϴ� ������ ȹ���Ѵ�.
	// ���, ����Ʈ, ���� Ư�̻���, ����

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