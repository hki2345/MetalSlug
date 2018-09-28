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
		// static�� ������ -> ���� static ���� -> ������ ����� �����ʹ� ����������
		// �� ������ ��� �������� �ش� ������ ������ �� ����.
		static KeyManager OnlyKeyManager = KeyManager();
		return OnlyKeyManager;
	}

private:
	class Command
	{
	private:
		// Ŀ�ǵ� ���� ��� �׸�
		std::vector<int> m_vector_KeyData;

		//  �ԷµǴ� ������ ���������� �˻��ϱ� ���� �ӽ������� �Ҵ��ϴ� ����.
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
		// �����͸� �ϳ��� ����ִ� �ܰ� -> ���? �ʿ� ����Ǵ� ���� Ű �迭�� ����ȴ�.
		// �� Ű �迭�� �ϳ��� ����. -> �� Ű ���� int�� ����.
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

	// Ű���� Ŀ�ǵ� �迭�� ��� �ִ� Ű������ �ϳ� �ʿ��ϴ� -> �� -> �̸����� �������´�.
private:
	std::map<std::wstring, Command*> m_map_KeyCommand;


	// �� ���͵� - �ߺ��ؼ� �����̱� ������ ����� ���´�.
	std::map<std::wstring, Command*>::iterator FindIter;
	std::map<std::wstring, Command*>::iterator StartIter;
	std::map<std::wstring, Command*>::iterator EndIter;

	// �ӽ� ����� -> Ŀ�ǵ带 �����ϱ� ���� �ѹ� ���⿡ ��ŵд�.
	Command* m_p_Command;

public:
	// �������� ���ڸ� �޴� ���ø�
	template<typename ... Rest>
	void SetUp_Command(const WCHAR* _Name, Rest ... _Arg)
	{
		// �ٷ� �����ϱ� ���� �� �ȿ� �̹� �����ϴ������� �˻� -> ������ �Ͷ߸���.
		m_p_Command = FindCommand(_Name);
		KAssert(nullptr != m_p_Command);
		
		// ������ ���� ������ ���� ���̴�.
		if (nullptr != m_p_Command)
		{ return; }

		// sizeof...(_Arg) -> ���ڰ��� ũ�⸦ ��ȯ�Ѵ�.
		m_p_Command = new Command(sizeof...(_Arg));
		Push_Command_Data(_Arg...);
		m_map_KeyCommand.insert(std::map<std::wstring, Command*>::value_type(_Name, m_p_Command));
	}

private:
	// ���ڰ��� �ϳ��� ���� �����̴�.
	template<typename T, typename ... Rest>
	void Push_Command_Data(const T& _Key, Rest ... _Arg)
	{
		m_p_Command->List_KeyDataPush(_Key);
		Push_Command_Data(_Arg...);
	}
	// �����Լ��� ��
	void Push_Command_Data() {};


	// ����� ã�� ���� -> ����Ű Ȥ�� ���� Ű
	Command* FindCommand(const WCHAR* _Name)
	{
		FindIter = m_map_KeyCommand.find(_Name);

		if (m_map_KeyCommand.end() == FindIter)
		{ return nullptr; }

		return FindIter->second;
	}

private:
	// ��� �ùٸ� ����Ű Ŀ�ǵ尡 ���ȴ����� �˻��Ѵ�.
	void Update();


public:
	// �ش� Ű�� ���ȴ��� ��·������ �ľ�
	bool IsUnPress(const WCHAR* _Name);
	bool IsUp(const WCHAR* _Name);
	bool IsDown(const WCHAR* _Name);
	bool IsPress(const WCHAR* _Name);

private:
	KeyManager();
	KeyManager(const KeyManager& _other) {};
	~KeyManager();
};

