#ifndef MONSTER_H
#define MONSTER_H

#include "Player.h"

enum MONSTER_TYPE
{
	KING_PIG,
	MONSTER_COUNT
};

enum MONSTER_STATE
{
	MONSTER_STATE_NONE = -1,

	RIGHT_IDLE = 0,
	LEFT_IDLE,

	RIGHT_MOVE,
	LEFT_MOVE,

	RIGHT_ATTACK,
	LEFT_ATTACK,

	RIGHT_HIT,
	LEFT_HIT,

	RIGHT_DEAD,
	LEFT_DEAD,

	MONSTER_STATE_COUNT
};


class Monster
{
public:
	Monster() = default;
	virtual ~Monster() = default;

public:
	Monster(MONSTER_TYPE type, FPOINT pos, float speed = 10.0f)
		: m_Type(type), m_Pos(pos), m_Speed(speed), m_Scale(1.0f), m_Gravity(10), m_IsDead(false) {}

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

public:
	virtual void Move(float dt) = 0;
	virtual void SetAnimation(MONSTER_STATE state) = 0;
	virtual void CheckMonsterState() = 0;
	virtual void CheckCollision() = 0;

protected:
	virtual bool IsCollision(RECT* rc1, RECT* rc2)
	{
		bool bCollision = false;
		RECT temp;
		if (IntersectRect(&temp, rc1, rc2))
		{
			bCollision = true;
		}
		return bCollision;
	}

	virtual float Distance(FPOINT pos1, FPOINT pos2)
	{
		float x = pos2.x - pos1.x;
		float y = pos2.y - pos1.y;

		return sqrtf(x * x + y * y);
	}

public:
	void SetID(int id) { m_ID = id; }
	UINT GetID() { return m_ID; }

	void SetPos(FPOINT pos) { m_Pos = pos; }
	FPOINT GetPos() { return m_Pos; }

	void SetCenter(FPOINT center) { m_Center = center; }
	FPOINT GetCenter() { return m_Center; }

	void SetSize(OBJSIZE size) { m_Size = size; }
	OBJSIZE GetSize() { return m_Size; }

	void SetScale(float scale) { m_Scale = scale; }
	float GetScale() { return m_Scale; }

	void SetSpeed(float speed) { m_Speed = speed; }
	float GetSpeed() { return m_Speed; }

	void SetGravity(int gravity) { m_Gravity = gravity; }
	int GetGravity() { return m_Gravity; }

	void SetIsDead(bool isDead) { m_IsDead = isDead; }
	bool IsDead() { return m_IsDead; }

	void SetIsOnGround(bool isOnGround) { m_IsOnGround = isOnGround; }
	bool IsOnGround() { return m_IsOnGround; }

	void SetCanMoveLeft(bool canMoveLeft) { m_CanMoveLeft = canMoveLeft; }
	bool IsCanMoveLeft() { return m_CanMoveLeft; }

	void SetCanMoveRight(bool canMoveRight) { m_CanMoveRight = canMoveRight; }
	bool IsCanMoveRight() { return m_CanMoveRight; }

	bool IsLeft() { return m_State % 2 == 1 ? true : false; }

	void SetHp(int hp) { m_Hp = hp; }
	int GetHp() { return m_Hp; }

	void SetMaxHp(int hp) { m_MaxHp = hp; }
	int GetMaxHp() { return m_MaxHp; }

	void SetType(MONSTER_TYPE type) { m_Type = type; }
	MONSTER_TYPE GetType() { return m_Type; }

	void SetState(MONSTER_STATE state) { m_State = state; }
	MONSTER_STATE GetState() { return m_State; }

	void SetPlayer(Player* player) { m_Player = player; }

protected:
	UINT			m_ID;
	FPOINT			m_Pos;
	FPOINT			m_Center;
	OBJSIZE			m_Size;
	float			m_Scale;
	float			m_Speed;
	int				m_Gravity;

	bool			m_IsDead;
	bool			m_IsOnGround;
	bool			m_CanMoveLeft;
	bool			m_CanMoveRight;

	int				m_Hp;
	int				m_MaxHp;
	MONSTER_TYPE	m_Type;
	MONSTER_STATE	m_State;
	MONSTER_STATE	m_StateBefore;

	Player*			m_Player;
};

#endif // MONSTER_H