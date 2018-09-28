#pragma once
#include <map>
#include <vector>
#include "KMacro.h"

class KeyManager
{
public:
	friend class Core;

public:
	static KeyManager& Inst()
	{
		// static인 이유는 -> 지역 static 변수 -> 지역을 벗어나도 데이터는 남아잇지만
		// 그 지역을 벗어난 곳에서는 해당 변수에 접근할 수 없다.
		static KeyManager OnlyKeyManager = KeyManager();
		return OnlyKeyManager;
	}

private:
	class Command
	{
	private:
		// 커맨드 정보 담는 그릇
		std::vector<int> m_vector_KeyData;

		//  입력되는 순서를 순차적으로 검사하기 위해 임시적으로 할당하는 공간.
		std::vector<int> m_vector_KeyPressData;

		bool m_UnPress;
		bool m_Up;
		bool m_Down;
		bool m_Press;

	public:
		bool IsUnPress()		{ return m_UnPress; }
		bool IsUp()				{ return m_Up; }
		bool IsDown()			{ return m_Down; }
		bool IsPress()			{ return m_Press; }

	public:
		// 데이터를 하나씩 집어넣는 단계 -> 어디에? 맵에 저장되는 것은 키 배열이 저장된다.
		// 즉 키 배열이 하나씩 들어간다. -> 그 키 값은 int로 들어간다.
		void List_KeyDataPush(const int& _Value) 
		{
			m_vector_KeyData.push_back(_Value); m_vector_KeyPressData.push_back(0);
		}
		void Update();

	private:
		int m_PressCheck;

		void Get_Key_Check();
		void Press_Check();
		bool Chain_Check();
		bool Command_Check();
		void Insert_PressData(const int& _Value);
		void Insert_EraseData(const int& _Value);

	public:
		Command(size_t _Count) : m_UnPress(true), m_Up(false), m_Down(false), m_Press(false),
			m_PressCheck(false)
		{ m_vector_KeyData.reserve(_Count); m_vector_KeyPressData.reserve(_Count); }
		~Command() {}
	};

	// 키들의 커맨드 배열을 담고 있는 키집합이 하나 필요하다 -> 맵 -> 이름으로 구분짓는다.
private:
	std::map<std::wstring, Command*> m_map_KeyCommand;


	// 그 이터들 - 중복해서 쓸것이기 때문에 만들어 놓는다.
	std::map<std::wstring, Command*>::iterator FindIter;
	std::map<std::wstring, Command*>::iterator StartIter;
	std::map<std::wstring, Command*>::iterator EndIter;

	// 임시 저장소 -> 커맨드를 저장하기 전에 한번 여기에 모셔둔다.
	Command* m_p_Command;

public:
	// 여러개의 인자를 받는 탬플릿
	template<typename ... Rest>
	void SetUp_Command(const WCHAR* _Name, Rest ... _Arg)
	{
		// 바로 생산하기 전에 맵 안에 이미 존재하는지부터 검사 -> 있으면 터뜨린다.
		m_p_Command = FindCommand(_Name);
		KAssert(nullptr != m_p_Command);
		
		// 이전에 터져 들어오진 않을 것이다.
		if (nullptr != m_p_Command)
		{ return; }

		// sizeof...(_Arg) -> 인자값의 크기를 반환한다.
		m_p_Command = new Command(sizeof...(_Arg));
		Push_Command_Data(_Arg...);
		m_map_KeyCommand.insert(std::map<std::wstring, Command*>::value_type(_Name, m_p_Command));
	}

private:
	// 인자값을 하나씩 빼는 과정이다.
	template<typename T, typename ... Rest>
	void Push_Command_Data(const T& _Key, Rest ... _Arg)
	{
		m_p_Command->List_KeyDataPush(_Key);
		Push_Command_Data(_Arg...);
	}
	// 제귀함수의 끝
	void Push_Command_Data() {};


	// 명령을 찾는 과정 -> 단축키 혹은 단일 키
	Command* FindCommand(const WCHAR* _Name)
	{
		FindIter = m_map_KeyCommand.find(_Name);

		if (m_map_KeyCommand.end() == FindIter)
		{ return nullptr; }

		return FindIter->second;
	}

private:
	// 얘는 올바른 단축키 커맨드가 눌렸는지를 검사한다.
	void Update();


public:
	// 해당 키가 눌렸는지 어쨌는지를 파악
	bool IsUnPress(const WCHAR* _Name);
	bool IsUp(const WCHAR* _Name);
	bool IsDown(const WCHAR* _Name);
	bool IsPress(const WCHAR* _Name);

private:
	KeyManager();
	KeyManager(const KeyManager& _other) {};
	~KeyManager();
};

