#include "stdafx.h"
#include "ResourceManager.h"

#include "MultiSprite.h"
#include "Sound_Player.h"

#include "Core.h"

ResourceManager::ResourceManager() : BGMPlayer(nullptr)
{
}


ResourceManager::~ResourceManager()
{
	/***** Sound ******/

	// 스텍 지우는 방식
	while (false == m_Stack_Sleep_Player.empty())
	{
		delete m_Stack_Sleep_Player.top();
		m_Stack_Sleep_Player.pop();
	}


	// 나머진 역시  for문 돌린다.ㅇ
	std::list<Sound_Player*>::iterator PlayerStartIter = m_List_Active_Player.begin();
	std::list<Sound_Player*>::iterator PlayerEndIter = m_List_Active_Player.end();

	for (; PlayerStartIter != PlayerEndIter; PlayerStartIter++)
	{
		delete (*PlayerStartIter);
	}

	m_List_Active_Player.clear();


	std::map<std::wstring, Sound*>::iterator SoundStartIter = m_Map_Sound.begin();
	std::map<std::wstring, Sound*>::iterator SoundEndIter = m_Map_Sound.end();

	for (; SoundStartIter != SoundEndIter; SoundStartIter++)
	{
		delete SoundStartIter->second;
	}

	m_Map_Sound.clear();


	/***** Back Buffer ******/

	if (nullptr != m_ImageOfMapImage)
	{
		delete m_ImageOfMapImage;
		m_ImageOfMapImage = nullptr;
	}


	/***** Multi Sprite Erase ******/

	std::map<std::wstring, MultiSprite*>::iterator StartMultiSpriteIter = m_Map_MultiSprite.begin();
	std::map<std::wstring, MultiSprite*>::iterator EndMultiSpriteIter = m_Map_MultiSprite.end();

	for (; StartMultiSpriteIter != EndMultiSpriteIter; StartMultiSpriteIter++)
	{
		delete StartMultiSpriteIter->second;
	}

	m_Map_MultiSprite.clear();

	/***** Sprite ******/

	std::map<std::wstring, Sprite*>::iterator StartSpriteIter = m_Map_Sprite.begin();
	std::map<std::wstring, Sprite*>::iterator EndSpriteIter = m_Map_Sprite.end();

	for (; StartSpriteIter != EndSpriteIter; StartSpriteIter++)
	{
		delete StartSpriteIter->second;
	}

	m_Map_Sprite.clear();

	/***** Image ******/

	std::map<std::wstring, Image*>::iterator StartImageIter = m_MapImage.begin();
	std::map<std::wstring, Image*>::iterator EndImageIter = m_MapImage.end();

	for (; StartImageIter != EndImageIter; StartImageIter++)
	{
		// 굳이 null로 만들 필요도 없다.
		delete StartImageIter->second;
	}

	// 여기서 비워버릴 거니깤ㅋㅋ
	m_MapImage.clear();

	NEW_DELETE(m_ImageOfMapImage);
}

HDC& ResourceManager::Init()
{
	m_ImageOfMapImage = new Image();
	return m_ImageOfMapImage->Create_Image(CORE.GetSize());
}

/*********************** Image ************************/
// 실은 편의상 하나만 넣어주어도 불러올수 있게끔 하는 것이다.
// 내가 편하라고ㅇㅇ
Image* ResourceManager::Load_Res_Image(const WCHAR* _Path)
{
	// 앞에 부분만 짤라내서 파일명을 그대로 키로 사용하는 녀석
	// c:\\Player.Bmp
	std::wstring Path = _Path;
	size_t Count = Path.find_last_of('\\');
	Path.replace(0, Count + 1, L"");

	return Load_Res_Image(_Path, Path.c_str());
}

Image* ResourceManager::Load_Res_Image(const WCHAR* _Path, const WCHAR* _Name)
{
	// _waccess -> w char로 된 패스에 자료가 있는지 확인-> 6번이 자료가 있는지만 확인하는 것이다.
	// 요부분 msdn 뒤져서 자세히 하장
	KAssert(0 != _waccess(_Path, 6));

	Image* p_Image = Find_Res_Image(_Path);

	if (nullptr != p_Image)
	{
		return p_Image;
	}

	p_Image = new Image();
	p_Image->Name(_Name);

	// 실질적인 함수가 이루어지면서 -> 검사까지 한다.
	// 만약 여기서 이미지가 제대로 로드되지 못한 채 
	// 펄스를 반환하게 되면 프로젝트가 터지게 되겠다.
	if (false == p_Image->Load(_Path))
	{
		KAssert(true);

		// 실제는 이렇게 널로 해주어야 한다.
		delete p_Image;
		p_Image = nullptr;
		return nullptr;
	}

	m_MapImage.insert(std::map<std::wstring, Image*>::value_type(p_Image->Name(), p_Image));

	return p_Image;
}

Image* ResourceManager::Find_Res_Image(const WCHAR* _Name)
{
	std::map < std::wstring, Image*>::iterator FindIter = m_MapImage.find(_Name);

	if (m_MapImage.end() == FindIter)
	{
		// 여기선 터뜨리면 안된다. 없으면 당연히 엔드까지 가는게 맞고
		// 없을 경우에는 이미지 리소스가 없으니 불러오는 것이 맞다.
		return nullptr;
	}

	return FindIter->second;
}

// 검사하고 싶은 이미지를 찾고 검사하는 함수
COLORREF ResourceManager::Get_PixelColor(const WCHAR* _Name, Position _Pos)
{
	Image* pFindImage = Find_Res_Image(_Name);
	KAssert(nullptr == pFindImage);
	if (nullptr == pFindImage)
	{
		return 0;
	}

	return pFindImage->Get_PixelColor(_Pos);
}


/******************************  Sprite ************************************/

Sprite* ResourceManager::Find_Res_Sprite(const WCHAR* _Name)
{
	std::map < std::wstring, Sprite*>::iterator FindIter = m_Map_Sprite.find(_Name);

	if (m_Map_Sprite.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path)
{
	// 앞에 부분만 짤라내서 파일명을 그대로 키로 사용하는 녀석
	// c:\\Player.Bmp
	std::wstring Name = _Path;
	size_t Count = Name.find_last_of('\\');
	Name.replace(0, Count + 1, L"");

	return Load_Res_Sprite(_Path, Name.c_str());
}
Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path, const Rect& _Rect)
{
	// 앞에 부분만 짤라내서 파일명을 그대로 키로 사용하는 녀석
	// c:\\Player.Bmp
	std::wstring Name = _Path;
	size_t Count = Name.find_last_of('\\');
	Name.replace(0, Count + 1, L"");

	return Load_Res_Sprite(_Path, Name.c_str(), _Rect);
}

// 경로와 해당 이미지의 이름을 찾아 리소스메니저가 관리할 수 있도록 넣는다.
Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path, const WCHAR* _Name)
{
	Sprite* FindSprite = Find_Res_Sprite(_Name);

	if (nullptr != FindSprite)
	{
		return FindSprite;
	}

	Image* p_Img = Load_Res_Image(_Path);

	// 없다는 뜻이므로 폭파
	KAssert(nullptr == p_Img);

	if (nullptr == p_Img)
	{
		return nullptr;
	}

	Sprite* NewSprite = new Sprite(p_Img, { { 0,0 }, p_Img->size() });

	m_Map_Sprite.insert(std::map<std::wstring, Sprite*>::value_type(_Name, NewSprite));

	return NewSprite;
}


Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path, const WCHAR* _Name, const Rect& _Rect)
{
	Sprite* NewSprite = Load_Res_Sprite(_Path, _Name);

	// 실은 크기를 지정하는 것이라 두번 지정하는 것이지만 편의상 이렇게 하는 것이다.
	// 함수 한 번 더 타고 들어가는 것
	NewSprite->rect(_Rect);
	return NewSprite;
}


/****************************** Multi Sprite ********************************/

MultiSprite* ResourceManager::Find_Res_MultiSprite(const WCHAR* _Name)
{
	std::map < std::wstring, MultiSprite*>::iterator FindIter = m_Map_MultiSprite.find(_Name);

	if (m_Map_MultiSprite.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}



MultiSprite* ResourceManager::Load_Res_MultiSprite(const WCHAR* _Path, const Size& _Rect)
{
	// 앞에 부분만 짤라내서 파일명을 그대로 키로 사용하는 녀석
	// c:\\Player.Bmp
	std::wstring Name = _Path;
	size_t Count = Name.find_last_of('\\');
	Name.replace(0, Count + 1, L"");

	return Load_Res_MultiSprite(_Path, Name.c_str(), _Rect);
}

MultiSprite* ResourceManager::Load_Res_MultiSprite(const WCHAR* _Path, const WCHAR* _Name, const Size& _Size)
{
	MultiSprite* FindMultiSprite = Find_Res_MultiSprite(_Name);

	if (nullptr != FindMultiSprite)
	{
		return FindMultiSprite;
	}

	Image* p_Img = Load_Res_Image(_Path);

	// 없다는 뜻이므로 폭파
	KAssert(nullptr == p_Img);

	if (nullptr == p_Img)
	{
		return nullptr;
	}
	// 사이즈를 음수로 넣으면 폭파
	if (0 >= _Size.X || 0 >= _Size.Y)
	{
		KAssert(true);
		return nullptr;
	}


	// 멀티 스프라이트
	// 스프라이트가 여러개이므로 그 곱 만큼 스프라이트를 만든다는 말이다.
	// -> 백터를 리절브 하는 과정
	MultiSprite* NewMultiSprite = new MultiSprite(_Size.X * _Size.Y);

	Rect Rectangle;

	int SpriteSizeX = p_Img->Width() / _Size.X;
	int SpriteSizeY = p_Img->Height() / _Size.Y;

	// 해당 이미지를 자동으로 나누는 과정 - 이덕분에 리소스작업이 수월해졌다.
	Rectangle.Size.X = SpriteSizeX;
	Rectangle.Size.Y = SpriteSizeY;

	// 벡터에 차곡차곡 넣는다.
	// 넣은뒤 자르는 위치를 한 칸씩 이동-> 이미지가 크기만큼  잘 잘린다.
	// 애초에 나눈 다음에 for문을 돌리는 것이기 때문ㅇ
	for (int i = 0; i < _Size.Y; i++)
	{
		for (int i = 0; i < _Size.X; i++)
		{
			Sprite* NewSprite = new Sprite(p_Img, Rectangle);
			NewMultiSprite->Insert_Sprite(NewSprite);
			Rectangle.Pos.X += SpriteSizeX;
		}

		// 이동하는 것이다.
		Rectangle.Pos.X = 0;
		Rectangle.Pos.Y += SpriteSizeY;
	}

	m_Map_MultiSprite.insert(std::map<std::wstring, MultiSprite*>::value_type(_Name, NewMultiSprite));

	return NewMultiSprite;
}




/****************************** Sound ********************************/

void ResourceManager::Set_Sound()
{
	// 플레이어 하나를 빌려온다. - 권한획득
	FMOD::System_Create(&SoundSystem);

	KAssert(nullptr == SoundSystem);

	if (nullptr == SoundSystem)
	{
		return;
	}

	FMOD_RESULT FR = SoundSystem->init(32, FMOD_DEFAULT, nullptr);

	KAssert(FMOD_OK != FR);

	if (FMOD_OK != FR)
	{
		return;
	}

	for (size_t i = 0; i < 32; i++)
	{
		m_Stack_Sleep_Player.push(new Sound_Player());
	}
}

// 여타 다른 스프라이트랑 마찬가지로 찾는 과정 ㅇㅇ
// 없다고 터드리는 건 아니다 단지 찾는 거니까 - 최초로 찾을 땐 당연히 없으니까.
Sound* ResourceManager::Find_Sound(const WCHAR* _pName)
{
	std::map<std::wstring, Sound*>::iterator FindIter = m_Map_Sound.find(_pName);

	if (FindIter == m_Map_Sound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

// 편의 오버로딩
bool ResourceManager::Load_Sound(const WCHAR* _pPath)
{
	std::wstring Key = _pPath;
	size_t CutSize = Key.find_last_of('\\');
	Key.replace(0, CutSize + 1, L"");

	return Load_Sound(_pPath, Key.c_str());
}

// 실제 실행 함수
bool ResourceManager::Load_Sound(const WCHAR* _pPath, const WCHAR* _pKey)
{
	Sound* NewSound = Find_Sound(_pKey);

	// 빵빵!!!
	KAssert(nullptr != NewSound);
	if (nullptr != NewSound) { return false; }

	NewSound = new Sound();

	// Fmod 에서 반환값을 트루로 하는데
	// 당연히 잘 로드 됐으면 트루다.
	if (false == NewSound->Load(SoundSystem, _pPath))
	{
		KAssert(true);
		delete NewSound;
		return false;
	}

	// 맵에 등록
	m_Map_Sound.insert(std::map<std::wstring, Sound*>::value_type(_pKey, NewSound));
	return true;
}

void ResourceManager::Play_Sound(const WCHAR* _pKey, const float& _Volume /*= 1.0f*/)
{
	if (true == m_Stack_Sleep_Player.empty())
	{
		return;
	}

	Sound* pPlaySound = Find_Sound(_pKey);

	KAssert(nullptr == pPlaySound);
	if (nullptr == pPlaySound) { return; }


	// 하나 꺼내 등록한다 -> 현재 진행되는 곳에 물론
	// 해당 사운드를 플레이 한 후에 넣는 것이다.
	Sound_Player* NewPlayer = m_Stack_Sleep_Player.top();

	NewPlayer->Sound_Play(SoundSystem, pPlaySound, _Volume);
	m_List_Active_Player.push_back(NewPlayer);
	m_Stack_Sleep_Player.pop();

	return;
}

// 자는 플레이어 하나를 빼온다 -> 이유는 얘가 바로 BGM이기 때문 -> 상시 재생
Sound_Player* ResourceManager::Rental_SoundPlayer()
{
	if (nullptr != BGMPlayer)
	{
		return BGMPlayer;
	}

	// 브금은 하나만 이ㅆ어야 한다.
	BGMPlayer = m_Stack_Sleep_Player.top();
	BGMPlayer->Rental();
	m_List_Active_Player.push_back(BGMPlayer);
	m_Stack_Sleep_Player.pop();
	return BGMPlayer;
}


// 현재 재생 중 + 하나 빼온 것이면 플레이 하도록 한다.-> 브금
void ResourceManager::Update_Sound() {

	std::list<Sound_Player*>::iterator PlayerStartIter = m_List_Active_Player.begin();
	std::list<Sound_Player*>::iterator PlayerEndIter = m_List_Active_Player.end();

	for (; PlayerStartIter != PlayerEndIter;)
	{
		if (false == (*PlayerStartIter)->Is_Play()
			&& false == (*PlayerStartIter)->Is_Rental())
		{
			m_Stack_Sleep_Player.push(*PlayerStartIter);
			PlayerStartIter = m_List_Active_Player.erase(PlayerStartIter);
		}
		else {
			++PlayerStartIter;
		}
	}
}