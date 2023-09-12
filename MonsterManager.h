#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include "Singleton.h"
#include "Monster.h"

class MonsterManager : public Singleton<MonsterManager>
{
public:
	MonsterManager();
	~MonsterManager();

public:
	void Init();
	void Update(float dt);
	void Render(HDC hdc);
	void Release();

public:
	void SetPlayer(Player* player);

public:
	void RegisterMonster(MONSTER_TYPE type, FPOINT pos);
	void RemoveMonster(int id);
	void ClearMonster();

	vector<Monster*>& GetMonsters() { return m_vMonsters; }

private:
	int m_InstanceID;
	Player* m_Player;
	vector<Monster*> m_vMonsters;
};

#endif // MONSTERMANAGER_H