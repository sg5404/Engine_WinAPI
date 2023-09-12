#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "BackGround.h"
#include "PixelCollision.h"

class GameScene : public CScene
{
public:
	GameScene();
	virtual ~GameScene();

public:
	void	Init();
	void	Update(float dt);
	void	Render(HDC hdc, float dt);
	void	Release();

private:
	STAGE	m_Stage;
	Player* m_Player;
	BackGround* m_BackGround;
	PixelCollision* m_PixelCollision;
};
#endif // GAMESCENE_H
