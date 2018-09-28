#include "stdafx.h"
#include "Sound_Player.h"
#include "Sound.h"
#include "ResourceManager.h"


Sound_Player::Sound_Player()
{
}


Sound_Player::~Sound_Player()
{
}


void Sound_Player::Sound_Play(FMOD::System* _pSystem, Sound* _pSound, const float& _Volume)
{
	FMOD_RESULT FR = _pSystem->playSound(_pSound->m_pSound, nullptr, false, &m_pChannel);
	m_pChannel->setVolume(_Volume);

	// �� �̰ɷ� ���̷�Ʈ�� ���¸� �޴´ٰ� �մϴ�
	// m_pChannel->setCallback()

	if (FMOD_OK != FR)
	{
		KAssert(true);
	}
}

void Sound_Player::BGM_Play(const WCHAR* _pKey, const float& _Volume)
{
	_p_BGM_Snd = RESOURCEMANAGER.Find_Sound(_pKey);

	// ����ڵ� == �����ڵ�
	KAssert(nullptr == _p_BGM_Snd);
	
	if (true == Is_BGMPlay()) { BGM_Stop(); }
	FMOD_RESULT FR = RESOURCEMANAGER.SoundSystem->playSound(_p_BGM_Snd->m_pSound, nullptr, false, &m_p_BGMCh);
	m_p_BGMCh->setVolume(_Volume);

	if (FMOD_OK != FR)
	{
		KAssert(true);
	}
}

// �ڵ� ���� ��
void Sound_Player::BGM_Play()
{
	FMOD_RESULT FR = RESOURCEMANAGER.SoundSystem->playSound(_p_BGM_Snd->m_pSound, nullptr, false, &m_p_BGMCh);

	if (FMOD_OK != FR)
	{
		KAssert(true);
	}
}

void Sound_Player::BGM_Stop()
{
	// ����ڵ� == �����ڵ�
	KAssert(nullptr == m_p_BGMCh);
	m_p_BGMCh->stop();
}