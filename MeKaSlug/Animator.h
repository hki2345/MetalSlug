#pragma once
#include "Renderer.h"

class MultiSprite;
class Animator : public Renderer
{
private:
	class Animation : public Begin_DE
	{
	public:
		friend Animator;

	private:
		// Animator
		Animator* m_p_MotherOfAnimation;
		MultiSprite* m_p_SpriteData;

		size_t m_v_Acting_Frame;
		size_t m_v_Start_Frame;
		size_t m_v_End_Frame;
		Sizef  m_Size;

		float	m_v_Speed;
		float	m_v_ActingTime;
		bool	m_b_Loop;
		bool	m_b_Reverse;
		bool	m_b_Acting;

	public:
		// 생성 하는데 부모, 데이터, 시작점, 끝점, 속력, 루프 여부를
		// 받는다.
		Animation(Animator* _Mother, MultiSprite* _SpriteData,
			size_t _Start, size_t _End,
			float _Speed, bool _Loop);

		// 그것을 렌더해준다.
		void Render();
		void Set_TransColor(const UINT& _Value);
	};

private:
	std::map<std::wstring, Animation*> m_Map_Animation;
	Animation* m_Acting_Animation;
	Sizef m_Size;
	float m_v_SizeRate;

public:
	inline Animation*	CurAni()							{ return m_Acting_Animation; }
	inline const WCHAR* CurAniName()						{ return m_Acting_Animation->Name(); }
	inline const size_t CurAniFrame()						{ return m_Acting_Animation->m_v_Acting_Frame; }
	void				CurAniFrame(const size_t& _frame)	{ m_Acting_Animation->m_v_Acting_Frame = _frame; }
	inline void			size(Size _Size)					{ m_Size = _Size; }
	inline Sizef&		size()								{ return m_Size; }
	void				sizeRate(float _Value)				{ m_v_SizeRate = _Value; }
	float&				sizeRate()							{ return m_v_SizeRate; }
	void				Set_TransColor(const UINT& _Value);
	void				speed(const float& _Value)			{ m_Acting_Animation->m_v_Speed = _Value; }
	float&				speed()								{ return m_Acting_Animation->m_v_Speed; }

	bool				IsActing()
	{
		if (nullptr == m_Acting_Animation) 
		{
			bool t = false;
			return t;
		}
		
		return m_Acting_Animation->m_b_Acting;
	}


	bool Start_Animation() { return  m_Acting_Animation->m_v_Acting_Frame == m_Acting_Animation->m_v_Start_Frame; }

public:
	Animation* Find_Animation(const WCHAR* _DataName);


	// 애니메이션을 만들어라
	// 어떤 애니메이션을 실행하여라
	void Set_Animation(const WCHAR* _SpriteName, const WCHAR* _AniName, size_t _Start, size_t _End, float _Speed = 0.1f, bool _bLoop = true);
	void Set_OneAnimation(const WCHAR* _SpriteName, const WCHAR* _AniName, size_t _End);

	void Reset_Animation();
	void Change_ReAnimation();
	void Change_Animation(const WCHAR* _AniName, bool _Level = false);
	void Fix_Animation(const size_t& _FromFrame, const size_t& _ToFrame);
	bool Acting_Name(const WCHAR* _AniName);

public:
	virtual void Render() override;


public:
	Animator();
	~Animator();
};

