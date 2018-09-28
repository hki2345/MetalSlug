#pragma once

// hpp - CPP ���� ��� ����?
#include <fmod.hpp>

class Sound
{
public:
	friend class ResourceManager;
	friend class Sound_Player;

private:
	FMOD::Sound* m_pSound;

private:
	bool Load(FMOD::System* _System, const WCHAR* _pFilePath);

public:
	Sound();
	~Sound();
};

