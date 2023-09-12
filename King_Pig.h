#ifndef KING_PIG_H
#define KING_PIG_H

#include "Monster.h"

// 이미지 갯수
enum KING_PIG_IMAGE
{
	IDLE,
	MOVE,
	ATTACK,
	HIT,
	DEAD,
	KING_PIG_COUNT
};

class King_Pig : public Monster
{
public:
	King_Pig() = default;
	~King_Pig() = default;

public:
	King_Pig(MONSTER_TYPE type, FPOINT pos, float speed = 10.0f);

public:
	// Monster을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	virtual void Move(float dt) override;
	virtual void SetAnimation(MONSTER_STATE state) override;

	virtual void CheckMonsterState() override;
	virtual void CheckCollision() override;

private:
	float m_TraceDistance;

	BImage* m_CurrentImage;
	BImage	m_ImageAnimation[KING_PIG_COUNT];

	BAnimation* m_Ani_Idle;
	BAnimation* m_Ani_Move;
	BAnimation* m_Ani_Attack;
	BAnimation* m_Ani_Hit;
	BAnimation* m_Ani_Dead;
};

#endif // KING_PIG_H

