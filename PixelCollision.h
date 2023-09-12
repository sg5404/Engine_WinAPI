#ifndef PIXELCOLLISION_H
#define PIXELCOLLISION_H

#include "BBasisStd.h"
#include "Player.h"
#include "Monster.h"

class PixelCollision
{
public:
	PixelCollision();
	~PixelCollision();

public:
	void Init();
	void Update(float dt);
	void Render(HDC hdc);
	void Release();

public:
	void SetStage(STAGE stage);

	void SetPlayer(Player* player) { m_Player = player;  }
	void PlayerPixelCollision();

	void SetMonsters(vector<Monster*>* monsters) { m_Monsters = monsters; }
	void MonstersPixelCollision();

private:
	STAGE m_Stage;
	HDC m_CurruntMemDC;
	HBITMAP m_OldBitmap;
	Player* m_Player;
	vector<Monster*>* m_Monsters;

	BImage* m_CurrentPixel;
	BImage	m_ImagePixel[STAGE_COUNT];
};

#endif // PIXELCOLLISION_H