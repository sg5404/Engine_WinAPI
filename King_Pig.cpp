#include "King_Pig.h"

King_Pig::King_Pig(MONSTER_TYPE type, FPOINT pos, float speed)
	: Monster(type, pos, speed)
{
	m_IsOnGround = false;
	m_CanMoveLeft = false;
	m_CanMoveRight = false;
	m_TraceDistance = 200.0f;
	m_State = MONSTER_STATE_NONE;

	m_CurrentImage = nullptr;

	m_Ani_Idle = nullptr;
	m_Ani_Move = nullptr;
	m_Ani_Attack = nullptr;
	m_Ani_Hit = nullptr;
	m_Ani_Dead = nullptr;
}

void King_Pig::Init()
{
	m_ImageAnimation[KING_PIG_IMAGE::IDLE].Load(TEXT("Data/Monster/King_Pig_Idle_212.bmp"));
	m_ImageAnimation[KING_PIG_IMAGE::MOVE].Load(TEXT("Data/Monster/King_Pig_Run_26.bmp"));
	m_ImageAnimation[KING_PIG_IMAGE::ATTACK].Load(TEXT("Data/Monster/King_Pig_Attack_25.bmp"));
	m_ImageAnimation[KING_PIG_IMAGE::HIT].Load(TEXT("Data/Monster/King_Pig_Hit_22.bmp"));
	m_ImageAnimation[KING_PIG_IMAGE::DEAD].Load(TEXT("Data/Monster/King_Pig_Dead_24.bmp"));

	m_Ani_Idle = new BAnimation;
	int width = m_ImageAnimation[KING_PIG_IMAGE::IDLE].GetBitmapInfo().bmWidth;
	int height = m_ImageAnimation[KING_PIG_IMAGE::IDLE].GetBitmapInfo().bmHeight;
	m_Ani_Idle->Init(width, height, width / 12, height / 2);
	m_Ani_Idle->SetFPS(10);

	m_Ani_Move = new BAnimation;
	width = m_ImageAnimation[KING_PIG_IMAGE::MOVE].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[KING_PIG_IMAGE::MOVE].GetBitmapInfo().bmHeight;
	m_Ani_Move->Init(width, height, width / 6, height / 2);
	m_Ani_Move->SetFPS(10);

	m_Ani_Attack = new BAnimation;
	width = m_ImageAnimation[KING_PIG_IMAGE::ATTACK].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[KING_PIG_IMAGE::ATTACK].GetBitmapInfo().bmHeight;
	m_Ani_Attack->Init(width, height, width / 5, height / 2);
	m_Ani_Attack->SetFPS(10);

	m_Ani_Hit = new BAnimation;
	width = m_ImageAnimation[KING_PIG_IMAGE::HIT].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[KING_PIG_IMAGE::HIT].GetBitmapInfo().bmHeight;
	m_Ani_Hit->Init(width, height, width / 2, height / 2);
	m_Ani_Hit->SetFPS(10);

	m_Ani_Dead = new BAnimation;
	width = m_ImageAnimation[KING_PIG_IMAGE::DEAD].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[KING_PIG_IMAGE::DEAD].GetBitmapInfo().bmHeight;
	m_Ani_Dead->Init(width, height, width / 4, height / 2);
	m_Ani_Dead->SetFPS(10);

	// 시작 애니 셋팅
	SetAnimation(MONSTER_STATE::LEFT_IDLE);
}

void King_Pig::Update(float dt)
{
	CheckMonsterState();
	Move(dt);

	switch (m_State)
	{
	case RIGHT_IDLE:
	case LEFT_IDLE:
		if (m_Ani_Idle)
			m_Ani_Idle->FrameUpdate(dt);
		break;
	case RIGHT_MOVE:
	case LEFT_MOVE:
		if (m_Ani_Move)
			m_Ani_Move->FrameUpdate(dt);
		break;
	case RIGHT_ATTACK:
	case LEFT_ATTACK:
		if (m_Ani_Attack)
			m_Ani_Attack->FrameUpdate(dt);
		break;
	case RIGHT_HIT:
	case LEFT_HIT:
		if (m_Ani_Hit)
			m_Ani_Hit->FrameUpdate(dt);
		break;
	case RIGHT_DEAD:
	case LEFT_DEAD:
		if (m_Ani_Dead)
			m_Ani_Dead->FrameUpdate(dt);
		break;
	default:
		break;
	}
}

void King_Pig::Render(HDC hdc)
{
	switch (m_State)
	{
	case RIGHT_IDLE:
	case LEFT_IDLE:
		if (m_CurrentImage)
			m_CurrentImage->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Idle);
		break;
	case RIGHT_MOVE:
	case LEFT_MOVE:
		if (m_CurrentImage)
			m_CurrentImage->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Move);
		break;
	case RIGHT_ATTACK:
	case LEFT_ATTACK:
		if (m_CurrentImage)
			m_CurrentImage->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Attack);
		break;
	case RIGHT_HIT:
	case LEFT_HIT:
		if (m_CurrentImage)
			m_CurrentImage->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Hit);
		break;
	case RIGHT_DEAD:
	case LEFT_DEAD:
		if (m_CurrentImage)
			m_CurrentImage->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Dead);
		break;
	default:
		break;
	}

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, m_Pos.x, m_Pos.y, m_Pos.x + m_Size.width, m_Pos.y + m_Size.height);
}

void King_Pig::Release()
{
	m_ImageAnimation[KING_PIG_IMAGE::IDLE].Release();
	m_ImageAnimation[KING_PIG_IMAGE::MOVE].Release();
	m_ImageAnimation[KING_PIG_IMAGE::ATTACK].Release();
	m_ImageAnimation[KING_PIG_IMAGE::HIT].Release();
	m_ImageAnimation[KING_PIG_IMAGE::DEAD].Release();

	SAFE_DELETE(m_Ani_Idle);
	SAFE_DELETE(m_Ani_Move);
	SAFE_DELETE(m_Ani_Attack);
	SAFE_DELETE(m_Ani_Hit);
	SAFE_DELETE(m_Ani_Dead);
}

void King_Pig::Move(float dt)
{
	if (m_State == MONSTER_STATE::LEFT_MOVE && m_CanMoveLeft)
	{
		m_Pos.x -= m_Speed * dt;
	}
	if (m_State == MONSTER_STATE::RIGHT_MOVE && m_CanMoveRight)
	{
		m_Pos.x += m_Speed * dt;
	}

	if (!m_IsOnGround)
	{
		m_Pos.y += m_Gravity * dt;
	}
}

void King_Pig::SetAnimation(MONSTER_STATE state)
{
	if (m_State == state)
		return;

	m_Ani_Idle->Stop();
	m_Ani_Move->Stop();
	m_Ani_Attack->Stop();
	m_Ani_Hit->Stop();
	m_Ani_Dead->Stop();

	m_StateBefore = m_State;
	m_State = state;

	switch (m_State)
	{
	case RIGHT_IDLE:
		m_Ani_Idle->SetPlayFrame(0, 11, false, true);
		m_Ani_Idle->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::IDLE];
		m_Size.width = m_Ani_Idle->GetFrameWidth();
		m_Size.height = m_Ani_Idle->GetFrameHeight();
		break;
	case LEFT_IDLE:
		m_Ani_Idle->SetPlayFrame(12, 23, true, true);
		m_Ani_Idle->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::IDLE];
		m_Size.width = m_Ani_Idle->GetFrameWidth();
		m_Size.height = m_Ani_Idle->GetFrameHeight();
		break;
	case RIGHT_MOVE:
		m_Ani_Move->SetPlayFrame(0, 5, false, true);
		m_Ani_Move->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::MOVE];
		m_Size.width = m_Ani_Move->GetFrameWidth();
		m_Size.height = m_Ani_Move->GetFrameHeight();
		break;
	case LEFT_MOVE:
		m_Ani_Move->SetPlayFrame(6, 11, true, true);
		m_Ani_Move->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::MOVE];
		m_Size.width = m_Ani_Move->GetFrameWidth();
		m_Size.height = m_Ani_Move->GetFrameHeight();
		break;
	case RIGHT_ATTACK:
		m_Ani_Attack->SetPlayFrame(0, 4, false, false);
		m_Ani_Attack->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::ATTACK];
		m_Size.width = m_Ani_Attack->GetFrameWidth();
		m_Size.height = m_Ani_Attack->GetFrameHeight();
		break;
	case LEFT_ATTACK:
		m_Ani_Attack->SetPlayFrame(5, 9, true, false);
		m_Ani_Attack->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::ATTACK];
		m_Size.width = m_Ani_Attack->GetFrameWidth();
		m_Size.height = m_Ani_Attack->GetFrameHeight();
		break;
	case RIGHT_HIT:
		m_Ani_Hit->SetPlayFrame(0, 1, false, false);
		m_Ani_Hit->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::HIT];
		m_Size.width = m_Ani_Hit->GetFrameWidth();
		m_Size.height = m_Ani_Hit->GetFrameHeight();
		break;
	case LEFT_HIT:
		m_Ani_Hit->SetPlayFrame(2, 3, true, false);
		m_Ani_Hit->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::HIT];
		m_Size.width = m_Ani_Hit->GetFrameWidth();
		m_Size.height = m_Ani_Hit->GetFrameHeight();
		break;
	case RIGHT_DEAD:
		m_Ani_Dead->SetPlayFrame(0, 3, false, false);
		m_Ani_Dead->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::DEAD];
		m_Size.width = m_Ani_Dead->GetFrameWidth();
		m_Size.height = m_Ani_Dead->GetFrameHeight();
		break;
	case LEFT_DEAD:
		m_Ani_Dead->SetPlayFrame(4, 7, true, false);
		m_Ani_Dead->Start();
		m_CurrentImage = &m_ImageAnimation[KING_PIG_IMAGE::DEAD];
		m_Size.width = m_Ani_Dead->GetFrameWidth();
		m_Size.height = m_Ani_Dead->GetFrameHeight();
		break;
	default:
		break;
	}
}

void King_Pig::CheckMonsterState()
{
	if (m_Player == nullptr)
		return;

	if (Distance(m_Pos, m_Player->GetPos()) <= m_TraceDistance)
	{
		if (m_Player->GetPos().x < m_Pos.x)
		{
			SetAnimation(MONSTER_STATE::LEFT_MOVE);
		}
		else
		{
			SetAnimation(MONSTER_STATE::RIGHT_MOVE);
		}
	}
	else
	{
		if (IsLeft())
		{
			SetAnimation(MONSTER_STATE::LEFT_IDLE);
		}
		else
		{
			SetAnimation(MONSTER_STATE::RIGHT_IDLE);
		}
	}
}

void King_Pig::CheckCollision()
{
}
