#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"
#include "BBasisSys.h"

enum class PLAYER_IMAGE
{
	IDLE,
	MOVE,
	ATTACK,
	THROW,
	HURT,
	JUMP,
	DEAD,
	MOVE_EFFECT,
	ATTACK_EFFECT,
	COUNT
};

enum class PLAYER_STATE
{
	NONE = -1,

	// IDLE
	RIGHT_IDLE = 0,
	LEFT_IDLE,

	// MOVE
	RIGHT_MOVE,
	LEFT_MOVE,

	// ATTACK
	RIGHT_ATTACK,
	LEFT_ATTACK,

	// THROW
	RIGHT_THROW,
	LEFT_THROW,

	// HURT
	RIGHT_HURT,
	LEFT_HURT,

	// JUMP
	RIGHT_JUMP,
	LEFT_JUMP,

	// FALL
	RIGHT_FALL,
	LEFT_FALL,

	// DEAD
	RIGHT_DEAD,
	LEFT_DEAD
};

class Player : public Obj
{
public:
	Player();
	Player(FPOINT pos, OBJSIZE size, float speed);
	~Player();

public:
	void Init() override;
	void Update(float dt) override;
	void Render(HDC hdc, float dt) override;
	void Release() override;

public:
	void SetAnimation(PLAYER_STATE state);

	bool IsLeft() { return (UINT)m_State % 2 == 1 ? true : false; }

	bool IsAttacking() 
	{
		if (m_State == PLAYER_STATE::LEFT_ATTACK || m_State == PLAYER_STATE::RIGHT_ATTACK)
			return true;
		return false;
	}

	bool IsJumping()
	{
		if (m_State == PLAYER_STATE::LEFT_JUMP || m_State == PLAYER_STATE::RIGHT_JUMP)
			return true;
		return false;
	}

	bool IsFalling()
	{
		if (m_State == PLAYER_STATE::LEFT_FALL || m_State == PLAYER_STATE::RIGHT_FALL)
			return true;
		return false;
	}

	bool IsMovingRight()
	{
		if ( m_State == PLAYER_STATE::RIGHT_MOVE ||
		   ((m_State == PLAYER_STATE::RIGHT_JUMP || m_State == PLAYER_STATE::RIGHT_FALL) && m_Angle != (float)PI/2))
			return true;
		return false;
	}

	bool IsMovingLeft()
	{
		if (m_State == PLAYER_STATE::LEFT_MOVE ||
		   ((m_State == PLAYER_STATE::LEFT_JUMP || m_State == PLAYER_STATE::LEFT_FALL) && m_Angle != (float)PI / 2))
			return true;
		return false;
	}



	FPOINT GetPos() { return m_Pos; }
	OBJSIZE GetSize() { return m_Size; }

	void SetIsOnGround(bool isonground) { m_IsOnGround = isonground; }
	bool GetIsOnGround() { return m_IsOnGround; }

	void SetCanMoveLeft(bool moveleft) { m_CanMoveLeft = moveleft; }
	bool GetCanMoveLeft() { return m_CanMoveLeft; }

	void SetCanMoveRight(bool moveright) { m_CanMoveRight = moveright; }
	bool GetCanMoveRight() { return m_CanMoveRight; }

private:
	float			m_Speed;
	float			m_SpeedY;
	float			m_Angle;
	float			m_Gravity;
	float			m_Hp;
	float			m_MaxHp;
	bool			m_IsOnGround;
	bool			m_CanMoveLeft;
	bool			m_CanMoveRight;
	PLAYER_STATE	m_State;
	PLAYER_STATE	m_StateBefore;

private:
	TInputState		m_InputState;

	BImage* m_ImagePlayer;
	BImage* m_ImageEffect;
	BImage	m_ImageAnimation[(UINT)PLAYER_IMAGE::COUNT];

	BAnimation* m_Ani_Idle;
	BAnimation* m_Ani_Move;
	BAnimation* m_Ani_Attack;
	BAnimation* m_Ani_Throw;
	BAnimation* m_Ani_Hurt;
	BAnimation* m_Ani_Jump;
	BAnimation* m_Ani_Dead;

	BAnimation* m_Ani_MoveEffect;
	BAnimation* m_Ani_AttackEffect;
};

#endif // PLAYER_H

