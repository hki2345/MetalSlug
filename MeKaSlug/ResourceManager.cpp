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

	// ���� ����� ���
	while (false == m_Stack_Sleep_Player.empty())
	{
		delete m_Stack_Sleep_Player.top();
		m_Stack_Sleep_Player.pop();
	}


	// ������ ����  for�� ������.��
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
		// ���� null�� ���� �ʿ䵵 ����.
		delete StartImageIter->second;
	}

	// ���⼭ ������� �Ŵσ�����
	m_MapImage.clear();

	NEW_DELETE(m_ImageOfMapImage);
}

HDC& ResourceManager::Init()
{
	m_ImageOfMapImage = new Image();
	return m_ImageOfMapImage->Create_Image(CORE.GetSize());
}

/*********************** Image ************************/
// ���� ���ǻ� �ϳ��� �־��־ �ҷ��ü� �ְԲ� �ϴ� ���̴�.
// ���� ���϶����
Image* ResourceManager::Load_Res_Image(const WCHAR* _Path)
{
	// �տ� �κи� ©�󳻼� ���ϸ��� �״�� Ű�� ����ϴ� �༮
	// c:\\Player.Bmp
	std::wstring Path = _Path;
	size_t Count = Path.find_last_of('\\');
	Path.replace(0, Count + 1, L"");

	return Load_Res_Image(_Path, Path.c_str());
}

Image* ResourceManager::Load_Res_Image(const WCHAR* _Path, const WCHAR* _Name)
{
	// _waccess -> w char�� �� �н��� �ڷᰡ �ִ��� Ȯ��-> 6���� �ڷᰡ �ִ����� Ȯ���ϴ� ���̴�.
	// ��κ� msdn ������ �ڼ��� ����
	KAssert(0 != _waccess(_Path, 6));

	Image* p_Image = Find_Res_Image(_Path);

	if (nullptr != p_Image)
	{
		return p_Image;
	}

	p_Image = new Image();
	p_Image->Name(_Name);

	// �������� �Լ��� �̷�����鼭 -> �˻���� �Ѵ�.
	// ���� ���⼭ �̹����� ����� �ε���� ���� ä 
	// �޽��� ��ȯ�ϰ� �Ǹ� ������Ʈ�� ������ �ǰڴ�.
	if (false == p_Image->Load(_Path))
	{
		KAssert(true);

		// ������ �̷��� �η� ���־�� �Ѵ�.
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
		// ���⼱ �Ͷ߸��� �ȵȴ�. ������ �翬�� ������� ���°� �°�
		// ���� ��쿡�� �̹��� ���ҽ��� ������ �ҷ����� ���� �´�.
		return nullptr;
	}

	return FindIter->second;
}

// �˻��ϰ� ���� �̹����� ã�� �˻��ϴ� �Լ�
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
	// �տ� �κи� ©�󳻼� ���ϸ��� �״�� Ű�� ����ϴ� �༮
	// c:\\Player.Bmp
	std::wstring Name = _Path;
	size_t Count = Name.find_last_of('\\');
	Name.replace(0, Count + 1, L"");

	return Load_Res_Sprite(_Path, Name.c_str());
}
Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path, const Rect& _Rect)
{
	// �տ� �κи� ©�󳻼� ���ϸ��� �״�� Ű�� ����ϴ� �༮
	// c:\\Player.Bmp
	std::wstring Name = _Path;
	size_t Count = Name.find_last_of('\\');
	Name.replace(0, Count + 1, L"");

	return Load_Res_Sprite(_Path, Name.c_str(), _Rect);
}

// ��ο� �ش� �̹����� �̸��� ã�� ���ҽ��޴����� ������ �� �ֵ��� �ִ´�.
Sprite* ResourceManager::Load_Res_Sprite(const WCHAR* _Path, const WCHAR* _Name)
{
	Sprite* FindSprite = Find_Res_Sprite(_Name);

	if (nullptr != FindSprite)
	{
		return FindSprite;
	}

	Image* p_Img = Load_Res_Image(_Path);

	// ���ٴ� ���̹Ƿ� ����
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

	// ���� ũ�⸦ �����ϴ� ���̶� �ι� �����ϴ� �������� ���ǻ� �̷��� �ϴ� ���̴�.
	// �Լ� �� �� �� Ÿ�� ���� ��
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
	// �տ� �κи� ©�󳻼� ���ϸ��� �״�� Ű�� ����ϴ� �༮
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

	// ���ٴ� ���̹Ƿ� ����
	KAssert(nullptr == p_Img);

	if (nullptr == p_Img)
	{
		return nullptr;
	}
	// ����� ������ ������ ����
	if (0 >= _Size.X || 0 >= _Size.Y)
	{
		KAssert(true);
		return nullptr;
	}


	// ��Ƽ ��������Ʈ
	// ��������Ʈ�� �������̹Ƿ� �� �� ��ŭ ��������Ʈ�� ����ٴ� ���̴�.
	// -> ���͸� ������ �ϴ� ����
	MultiSprite* NewMultiSprite = new MultiSprite(_Size.X * _Size.Y);

	Rect Rectangle;

	int SpriteSizeX = p_Img->Width() / _Size.X;
	int SpriteSizeY = p_Img->Height() / _Size.Y;

	// �ش� �̹����� �ڵ����� ������ ���� - �̴��п� ���ҽ��۾��� ����������.
	Rectangle.Size.X = SpriteSizeX;
	Rectangle.Size.Y = SpriteSizeY;

	// ���Ϳ� �������� �ִ´�.
	// ������ �ڸ��� ��ġ�� �� ĭ�� �̵�-> �̹����� ũ�⸸ŭ  �� �߸���.
	// ���ʿ� ���� ������ for���� ������ ���̱� ������
	for (int i = 0; i < _Size.Y; i++)
	{
		for (int i = 0; i < _Size.X; i++)
		{
			Sprite* NewSprite = new Sprite(p_Img, Rectangle);
			NewMultiSprite->Insert_Sprite(NewSprite);
			Rectangle.Pos.X += SpriteSizeX;
		}

		// �̵��ϴ� ���̴�.
		Rectangle.Pos.X = 0;
		Rectangle.Pos.Y += SpriteSizeY;
	}

	m_Map_MultiSprite.insert(std::map<std::wstring, MultiSprite*>::value_type(_Name, NewMultiSprite));

	return NewMultiSprite;
}




/****************************** Sound ********************************/

void ResourceManager::Set_Sound()
{
	// �÷��̾� �ϳ��� �����´�. - ����ȹ��
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

// ��Ÿ �ٸ� ��������Ʈ�� ���������� ã�� ���� ����
// ���ٰ� �͵帮�� �� �ƴϴ� ���� ã�� �Ŵϱ� - ���ʷ� ã�� �� �翬�� �����ϱ�.
Sound* ResourceManager::Find_Sound(const WCHAR* _pName)
{
	std::map<std::wstring, Sound*>::iterator FindIter = m_Map_Sound.find(_pName);

	if (FindIter == m_Map_Sound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

// ���� �����ε�
bool ResourceManager::Load_Sound(const WCHAR* _pPath)
{
	std::wstring Key = _pPath;
	size_t CutSize = Key.find_last_of('\\');
	Key.replace(0, CutSize + 1, L"");

	return Load_Sound(_pPath, Key.c_str());
}

// ���� ���� �Լ�
bool ResourceManager::Load_Sound(const WCHAR* _pPath, const WCHAR* _pKey)
{
	Sound* NewSound = Find_Sound(_pKey);

	// ����!!!
	KAssert(nullptr != NewSound);
	if (nullptr != NewSound) { return false; }

	NewSound = new Sound();

	// Fmod ���� ��ȯ���� Ʈ��� �ϴµ�
	// �翬�� �� �ε� ������ Ʈ���.
	if (false == NewSound->Load(SoundSystem, _pPath))
	{
		KAssert(true);
		delete NewSound;
		return false;
	}

	// �ʿ� ���
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


	// �ϳ� ���� ����Ѵ� -> ���� ����Ǵ� ���� ����
	// �ش� ���带 �÷��� �� �Ŀ� �ִ� ���̴�.
	Sound_Player* NewPlayer = m_Stack_Sleep_Player.top();

	NewPlayer->Sound_Play(SoundSystem, pPlaySound, _Volume);
	m_List_Active_Player.push_back(NewPlayer);
	m_Stack_Sleep_Player.pop();

	return;
}

// �ڴ� �÷��̾� �ϳ��� ���´� -> ������ �갡 �ٷ� BGM�̱� ���� -> ��� ���
Sound_Player* ResourceManager::Rental_SoundPlayer()
{
	if (nullptr != BGMPlayer)
	{
		return BGMPlayer;
	}

	// ����� �ϳ��� �̤���� �Ѵ�.
	BGMPlayer = m_Stack_Sleep_Player.top();
	BGMPlayer->Rental();
	m_List_Active_Player.push_back(BGMPlayer);
	m_Stack_Sleep_Player.pop();
	return BGMPlayer;
}


// ���� ��� �� + �ϳ� ���� ���̸� �÷��� �ϵ��� �Ѵ�.-> ���
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