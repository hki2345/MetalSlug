#pragma once

#include <fmod.hpp>

class Sound;
class Sound_Player
{
public:
	friend class ResourceManager;
	
	Sound* _p_BGM_Snd;

	FMOD::Channel* m_pChannel;
	FMOD::Channel* m_p_BGMCh;
	bool m_b_Rental;

private:
	void Rental() {
		m_b_Rental = true;
	}

private:
	void Sound_Play(FMOD::System* _pSystem, Sound* _pSound, const float& _Volume = 1.0f);

public:
	// ���Ļ� ������ ���� - ��� ������ �̷��� ���� ���ҽ��޴������� �������ش�.
	void BGM_Play(const WCHAR* _pKey, const float& _Volume = 1.0f);
	void BGM_Play();
	void BGM_Stop();

public:
	// �÷��� ������ �����´�.
	// �ٵ� Ư���ϰ� -> �Լ����ٰ� �Ұ��� �־��־�� �� �Ұ��� �����Ǵ� �����̴�.
	bool Is_Play()
	{
		bool IsPlayer = false;
		m_pChannel->isPlaying(&IsPlayer);
		return IsPlayer;
	}
	bool Is_BGMPlay()
	{
		bool IsPlayer = false;
		m_p_BGMCh->isPlaying(&IsPlayer);
		return IsPlayer;
	}

	bool Is_Rental()
	{
		return m_b_Rental;
	}

	// void Stop();

public:
	Sound_Player();
	~Sound_Player();
};

