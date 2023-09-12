#include "GameScene.h"
#include "MonsterManager.h"

GameScene::GameScene()
{
	m_Player = nullptr;
	m_BackGround = nullptr;
	m_PixelCollision = nullptr;
	m_Stage = STAGE1;
}

GameScene::~GameScene()
{	
}

void GameScene::Init()
{
	m_Player = new Player(FPOINT{ 100 , SCREEN_HEIGHT/2 }, OBJSIZE{96, 96}, 100.0f);
	if (m_Player)
		m_Player->Init();

	MonsterManager::GetSingleton()->ClearMonster();
	MonsterManager::GetSingleton()->RegisterMonster(MONSTER_TYPE::KING_PIG, FPOINT{ 600, 300 });
	MonsterManager::GetSingleton()->RegisterMonster(MONSTER_TYPE::KING_PIG, FPOINT{ 1218, 447 });
	MonsterManager::GetSingleton()->Init();
	MonsterManager::GetSingleton()->SetPlayer(m_Player);

	m_BackGround = new BackGround();
	if (m_BackGround)
	{
		m_BackGround->Init();
		m_BackGround->SetStage(m_Stage);
		m_BackGround->SetPlayer(m_Player);
	}

	m_PixelCollision = new PixelCollision();
	if (m_PixelCollision)
	{
		m_PixelCollision->Init();
		m_PixelCollision->SetStage(m_Stage);
		m_PixelCollision->SetPlayer(m_Player);
		m_PixelCollision->SetMonsters(&MonsterManager::GetSingleton()->GetMonsters());
	}

	g_pEngine->m_CameraObject.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH * 2, SCREEN_HEIGHT);
	g_pEngine->m_CameraObject.SetPos(m_Player->GetPos().x, m_Player->GetPos().y);
}

void GameScene::Update(float dt)
{
	
	if (m_Player)
		m_Player->Update(dt);

	MonsterManager::GetSingleton()->Update(dt);

	if (m_BackGround)
		m_BackGround->Update(dt);

	if (m_PixelCollision)
		m_PixelCollision->Update(dt);

	g_pEngine->m_CameraObject.SetPos(m_Player->GetPos().x, m_Player->GetPos().y);
}

void GameScene::Render(HDC hdc, float dt)
{
	int width = SCREEN_WIDTH * 2;
	int height = SCREEN_HEIGHT;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	if (m_BackGround)
		m_BackGround->Render(hMemDC, dt);

	if (m_PixelCollision)
		m_PixelCollision->Render(hMemDC);

	if (m_Player)
		m_Player->Render(hMemDC, dt);

	MonsterManager::GetSingleton()->Render(hMemDC);

	GdiTransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		hMemDC, g_pEngine->m_CameraObject.GetLeft()
		, g_pEngine->m_CameraObject.GetTop()
		, g_pEngine->m_CameraObject.GetWidth()
		, g_pEngine->m_CameraObject.GetHeight(), RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

void GameScene::Release()
{
	if (m_Player)
		m_Player->Release();

	MonsterManager::GetSingleton()->Release();

	if (m_BackGround)
		m_BackGround->Release();

	if (m_PixelCollision)
		m_PixelCollision->Release();

	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_BackGround);
	SAFE_DELETE(m_PixelCollision);
}
