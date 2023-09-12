#include "Player.h"

Player::Player()
	: Obj(FPOINT{ 100, SCREEN_HEIGHT / 2 }, OBJSIZE{96, 96}, 1.0f)
{
	m_ImagePlayer = nullptr;
	m_ImageEffect = nullptr;
	m_State = PLAYER_STATE::NONE;
	m_Speed = 10.0f;
	m_SpeedY = 6.0f;
	m_Angle = PI / 2;
	m_Gravity = 0;
	m_IsOnGround = false;
	m_CanMoveLeft = false;
	m_CanMoveRight = false;
	memset(&m_InputState, 0, sizeof(TInputState));
}

Player::Player(FPOINT pos, OBJSIZE size, float speed)
	: Obj(pos, size, 1.0f)
	, m_Speed(speed)
{
	m_ImagePlayer = nullptr;
	m_ImageEffect = nullptr;
	m_State = PLAYER_STATE::NONE;
	m_SpeedY = 6.0f;
	m_Angle = PI / 2;
	m_Gravity = 0;
	m_IsOnGround = false;
	m_CanMoveLeft = false;
	m_CanMoveRight = false;
	memset(&m_InputState, 0, sizeof(TInputState));
}

Player::~Player()
{
}

void Player::Init()
{
	m_ImageAnimation[(UINT)PLAYER_IMAGE::IDLE].Load(TEXT("Data/Player/Owlet_Monster_Idle_24.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE].Load(TEXT("Data/Player/Owlet_Monster_Walk_26.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK].Load(TEXT("Data/Player/Owlet_Monster_Attack2_26.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::THROW].Load(TEXT("Data/Player/Owlet_Monster_Throw_24.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::HURT].Load(TEXT("Data/Player/Owlet_Monster_Hurt_24.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP].Load(TEXT("Data/Player/Owlet_Monster_Jump_28.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::DEAD].Load(TEXT("Data/Player/Owlet_Monster_Death_28.bmp"));

	m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT].Load(TEXT("Data/Player/Walk_Run_Push_Dust_26.bmp"));
	m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT].Load(TEXT("Data/Player/Owlet_Monster_effect_24.bmp"));

	m_Ani_Idle = new BAnimation;
	int width = m_ImageAnimation[(UINT)PLAYER_IMAGE::IDLE].GetBitmapInfo().bmWidth;
	int height = m_ImageAnimation[(UINT)PLAYER_IMAGE::IDLE].GetBitmapInfo().bmHeight;
	m_Ani_Idle->Init(width, height, width / 4, height / 2);
	m_Ani_Idle->SetFPS(10);

	m_Ani_Move = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE].GetBitmapInfo().bmHeight;
	m_Ani_Move->Init(width, height, width / 6, height / 2);
	m_Ani_Move->SetFPS(10);

	m_Ani_Attack = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK].GetBitmapInfo().bmHeight;
	m_Ani_Attack->Init(width, height, width / 6, height / 2);
	m_Ani_Attack->SetFPS(10);

	m_Ani_Throw = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::THROW].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::THROW].GetBitmapInfo().bmHeight;
	m_Ani_Throw->Init(width, height, width / 4, height / 2);
	m_Ani_Throw->SetFPS(10);

	m_Ani_Hurt = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::HURT].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::HURT].GetBitmapInfo().bmHeight;
	m_Ani_Hurt->Init(width, height, width / 4, height / 2);
	m_Ani_Hurt->SetFPS(10);

	m_Ani_Jump = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP].GetBitmapInfo().bmHeight;
	m_Ani_Jump->Init(width, height, width / 8, height / 2);
	m_Ani_Jump->SetFPS(10);

	m_Ani_Dead = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::DEAD].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::DEAD].GetBitmapInfo().bmHeight;
	m_Ani_Dead->Init(width, height, width / 8, height / 2);
	m_Ani_Dead->SetFPS(10);

	m_Ani_MoveEffect = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT].GetBitmapInfo().bmHeight;
	m_Ani_MoveEffect->Init(width, height, width / 6, height / 2);
	m_Ani_MoveEffect->SetFPS(10);

	m_Ani_AttackEffect = new BAnimation;
	width = m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT].GetBitmapInfo().bmWidth;
	height = m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT].GetBitmapInfo().bmHeight;
	m_Ani_AttackEffect->Init(width, height, width / 4, height / 2);
	m_Ani_AttackEffect->SetFPS(10);

	// 시작 애니
	SetAnimation(PLAYER_STATE::RIGHT_IDLE);

	m_StateBefore = PLAYER_STATE::RIGHT_IDLE;
}

void Player::Update(float dt)
{
	if (!g_pEngine)
		return;

	g_pEngine->m_InputObject.KeyCheck(VK_LEFT, m_InputState.dwKeyLEFT);
	g_pEngine->m_InputObject.KeyCheck(VK_RIGHT, m_InputState.dwKeyRIGHT);
	g_pEngine->m_InputObject.KeyCheck(VK_SPACE, m_InputState.dwKeySpace);
	g_pEngine->m_InputObject.KeyCheck('A', m_InputState.dwKeyA);

	if (m_InputState.dwKeyLEFT == KEY_PUSH)
	{
		if( !IsJumping() && !IsFalling() && !IsAttacking())
			SetAnimation(PLAYER_STATE::LEFT_MOVE);
	}

	if (m_InputState.dwKeyLEFT == KEY_DOWN)
	{
		m_StateBefore = PLAYER_STATE::LEFT_MOVE;

		if (IsJumping())
		{
			m_Angle = PI / 5 * 3;
			SetAnimation(PLAYER_STATE::LEFT_JUMP);
		}
		if (IsFalling())
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
		}

		if (m_State == PLAYER_STATE::LEFT_MOVE && m_Ani_Move->IsPlay() && m_CanMoveLeft)
		{
			m_Pos.x -= m_Speed * dt;
		}
	}

	if (m_InputState.dwKeyLEFT == KEY_UP)
	{
		m_StateBefore = PLAYER_STATE::LEFT_IDLE;

		if (m_IsOnGround)
		{
			SetAnimation(PLAYER_STATE::LEFT_IDLE);
		}
		else if (!(IsFalling() || IsJumping() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
			m_Angle = PI / 5 * 3;
			m_Gravity = m_SpeedY + 0.2f;
		}
	}

	if (m_InputState.dwKeyRIGHT == KEY_PUSH)
	{
		if (!IsJumping() && !IsFalling() && !IsAttacking())
			SetAnimation(PLAYER_STATE::RIGHT_MOVE);
	}

	if (m_InputState.dwKeyRIGHT == KEY_DOWN)
	{
		m_StateBefore = PLAYER_STATE::RIGHT_MOVE;

		if (IsJumping())
		{
			m_Angle = PI / 5 * 2;
			SetAnimation(PLAYER_STATE::RIGHT_JUMP);
		}
		if (IsFalling())
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
		}

		if (m_State == PLAYER_STATE::RIGHT_MOVE && m_Ani_Move->IsPlay() && m_CanMoveRight)
		{
			m_Pos.x += m_Speed * dt;
		}
	}

	if (m_InputState.dwKeyRIGHT == KEY_UP)
	{
		m_StateBefore = PLAYER_STATE::RIGHT_IDLE;

		if (m_IsOnGround)
		{
			SetAnimation(PLAYER_STATE::RIGHT_IDLE);
		}
		else if (!(IsFalling() || IsJumping() || IsAttacking()))
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
			m_Angle = PI / 5 * 2;
			m_Gravity = m_SpeedY + 0.2f;
		}
	}


	if (m_InputState.dwKeyA == KEY_PUSH)
	{
		if (!IsAttacking())
		{
			if (IsLeft())
			{
				SetAnimation(PLAYER_STATE::LEFT_ATTACK);
			}
			else
			{
				SetAnimation(PLAYER_STATE::RIGHT_ATTACK);
			}
		}
	}

	if (m_InputState.dwKeySpace == KEY_PUSH)
	{
		if (IsLeft() && !IsJumping() && !IsFalling() && GetIsOnGround())
		{
			m_StateBefore = m_State;
			SetAnimation(PLAYER_STATE::LEFT_JUMP);
			m_Gravity = 0;
			m_IsOnGround = false;
			m_Angle = PI / 2;
		}
		if (!IsLeft() && !IsJumping() && !IsFalling() && GetIsOnGround())
		{
			m_StateBefore = m_State;
			SetAnimation(PLAYER_STATE::RIGHT_JUMP);
			m_Gravity = 0;
			m_IsOnGround = false;
			m_Angle = PI / 2;
		}
	}

	if ((IsJumping() || IsFalling()) && !GetIsOnGround())
	{
		m_Pos.x += cosf(m_Angle) * m_SpeedY;
		m_Pos.y += -sinf(m_Angle) * m_SpeedY + m_Gravity;
		m_Gravity += 0.15f;
	}


	if (!(IsJumping() || IsFalling()) && !GetIsOnGround())
	{
		m_Pos.y += 3;
	}


	switch (m_State)
	{
	case PLAYER_STATE::RIGHT_IDLE:
	case PLAYER_STATE::LEFT_IDLE:
		m_Ani_Idle->FrameUpdate(dt);
		break;
	case PLAYER_STATE::RIGHT_MOVE:
	case PLAYER_STATE::LEFT_MOVE:
		m_Ani_Move->FrameUpdate(dt);
		m_Ani_MoveEffect->FrameUpdate(dt);
		break;
	case PLAYER_STATE::RIGHT_ATTACK:
	case PLAYER_STATE::LEFT_ATTACK:
		m_Ani_Attack->FrameUpdate(dt);
		m_Ani_AttackEffect->FrameUpdate(dt);

		if (!m_Ani_Attack->IsPlay())
		{
			SetAnimation(m_StateBefore);
		}
		break;
	case PLAYER_STATE::RIGHT_THROW:
	case PLAYER_STATE::LEFT_THROW:
		m_Ani_Throw->FrameUpdate(dt);
		break;
	case PLAYER_STATE::RIGHT_HURT:
	case PLAYER_STATE::LEFT_HURT:
		m_Ani_Hurt->FrameUpdate(dt);
		break;
	case PLAYER_STATE::RIGHT_JUMP:
		m_Ani_Jump->FrameUpdate(dt);
		if (m_Gravity > m_SpeedY)
		{
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
		}
		break;
	case PLAYER_STATE::LEFT_JUMP:
		m_Ani_Jump->FrameUpdate(dt);
		if (m_Gravity > m_SpeedY)
		{
			SetAnimation(PLAYER_STATE::LEFT_FALL);
		}
		break;
	case PLAYER_STATE::RIGHT_FALL:
	case PLAYER_STATE::LEFT_FALL:
		m_Ani_Jump->FrameUpdate(dt);

		if (m_IsOnGround)
		{
			SetAnimation(m_StateBefore);
		}
		break;
	case PLAYER_STATE::RIGHT_DEAD:
	case PLAYER_STATE::LEFT_DEAD:
		m_Ani_Dead->FrameUpdate(dt);
		break;
	default:
		break;
	}
}

void Player::Render(HDC hdc, float dt)
{
	if (m_ImagePlayer == nullptr)
		return;

	switch (m_State)
	{
	case PLAYER_STATE::RIGHT_IDLE:
	case PLAYER_STATE::LEFT_IDLE:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Idle);
		break;
	case PLAYER_STATE::RIGHT_MOVE:
	case PLAYER_STATE::LEFT_MOVE:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Move);
		m_ImageEffect->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_MoveEffect);
		break;
	case PLAYER_STATE::RIGHT_ATTACK:
	case PLAYER_STATE::LEFT_ATTACK:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Attack);
		m_ImageEffect->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_AttackEffect);
		break;
	case PLAYER_STATE::RIGHT_THROW:
	case PLAYER_STATE::LEFT_THROW:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Throw);
		break;
	case PLAYER_STATE::RIGHT_HURT:
	case PLAYER_STATE::LEFT_HURT:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Hurt);
		break;
	case PLAYER_STATE::RIGHT_JUMP:
	case PLAYER_STATE::LEFT_JUMP:
	case PLAYER_STATE::RIGHT_FALL:
	case PLAYER_STATE::LEFT_FALL:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Jump);
		break;
	case PLAYER_STATE::RIGHT_DEAD:
	case PLAYER_STATE::LEFT_DEAD:
		m_ImagePlayer->DrawAniRender(hdc, m_Pos.x, m_Pos.y, m_Ani_Dead);
		break;
	default:
		break;
	}

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, m_Pos.x, m_Pos.y, m_Pos.x + m_Size.width, m_Pos.y + m_Size.height);
}

void Player::Release()
{
}

void Player::SetAnimation(PLAYER_STATE state)
{
	if (m_State == state)
		return;

	m_Ani_Idle->Stop();
	m_Ani_Move->Stop();
	m_Ani_Attack->Stop();
	m_Ani_Throw->Stop();
	m_Ani_Hurt->Stop();
	m_Ani_Jump->Stop();
	m_Ani_Dead->Stop();
	m_Ani_MoveEffect->Stop();
	m_Ani_AttackEffect->Stop();

	m_State = state;

	switch (state)
	{
	case PLAYER_STATE::RIGHT_IDLE:
		m_Ani_Idle->SetPlayFrame(0, 3, false, true);
		m_Ani_Idle->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::IDLE];
		break;
	case PLAYER_STATE::LEFT_IDLE:
		m_Ani_Idle->SetPlayFrame(4, 7, true, true);
		m_Ani_Idle->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::IDLE];
		break;
	case PLAYER_STATE::RIGHT_MOVE:
		m_Ani_Move->SetPlayFrame(0, 5, false, true);
		m_Ani_Move->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE];

		m_Ani_MoveEffect->SetPlayFrame(0, 5, false, true);
		m_Ani_MoveEffect->Start();
		m_ImageEffect = &m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT];
		break;
	case PLAYER_STATE::LEFT_MOVE:
		m_Ani_Move->SetPlayFrame(6, 11, true, true);
		m_Ani_Move->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE];

		m_Ani_MoveEffect->SetPlayFrame(6, 11, true, true);
		m_Ani_MoveEffect->Start();
		m_ImageEffect = &m_ImageAnimation[(UINT)PLAYER_IMAGE::MOVE_EFFECT];
		break;
	case PLAYER_STATE::RIGHT_ATTACK:
		m_Ani_Attack->SetPlayFrame(0, 5, false, false);
		m_Ani_Attack->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK];

		m_Ani_AttackEffect->SetPlayFrame(0, 3, false, false);
		m_Ani_AttackEffect->Start();
		m_ImageEffect = &m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT];
		break;
	case PLAYER_STATE::LEFT_ATTACK:
		m_Ani_Attack->SetPlayFrame(6, 11, true, false);
		m_Ani_Attack->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK];

		m_Ani_AttackEffect->SetPlayFrame(4, 7, true, false);
		m_Ani_AttackEffect->Start();
		m_ImageEffect = &m_ImageAnimation[(UINT)PLAYER_IMAGE::ATTACK_EFFECT];
		break;
	case PLAYER_STATE::RIGHT_THROW:
		m_Ani_Throw->SetPlayFrame(0, 3, false, false);
		m_Ani_Throw->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::THROW];
		break;
	case PLAYER_STATE::LEFT_THROW:
		m_Ani_Throw->SetPlayFrame(4, 7, true, false);
		m_Ani_Throw->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::THROW];
		break;
	case PLAYER_STATE::RIGHT_HURT:
		m_Ani_Hurt->SetPlayFrame(0, 3, false, false);
		m_Ani_Hurt->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::HURT];
		break;
	case PLAYER_STATE::LEFT_HURT:
		m_Ani_Hurt->SetPlayFrame(4, 7, true, false);
		m_Ani_Hurt->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::HURT];
		break;
	case PLAYER_STATE::RIGHT_JUMP:
		m_Ani_Jump->SetPlayFrame(3, 3, false, false);
		m_Ani_Jump->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::LEFT_JUMP:
		m_Ani_Jump->SetPlayFrame(12, 12, true, false);
		m_Ani_Jump->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::RIGHT_FALL:
		m_Ani_Jump->SetPlayFrame(5, 5, false, false);
		m_Ani_Jump->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::LEFT_FALL:
		m_Ani_Jump->SetPlayFrame(10, 10, true, false);
		m_Ani_Jump->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::JUMP];
		break;
	case PLAYER_STATE::RIGHT_DEAD:
		m_Ani_Dead->SetPlayFrame(0, 7, false, false);
		m_Ani_Dead->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::DEAD];
		break;
	case PLAYER_STATE::LEFT_DEAD:
		m_Ani_Dead->SetPlayFrame(8, 15, true, false);
		m_Ani_Dead->Start();
		m_ImagePlayer = &m_ImageAnimation[(UINT)PLAYER_IMAGE::DEAD];
		break;
	default:
		break;
	}
}
