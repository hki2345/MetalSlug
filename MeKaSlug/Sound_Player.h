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
	// 형식상 고정된 음악 - 브금 따위는 이렇게 따로 리소스메니저에서 관리해준다.
	void BGM_Play(const WCHAR* _pKey, const float& _Volume = 1.0f);
	void BGM_Play();
	void BGM_Stop();

public:
	// 플레이 정보를 가져온다.
	// 근데 특이하게 -> 함수에다가 불값을 넣어주어야 그 불값이 수정되는 형태이다.
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

