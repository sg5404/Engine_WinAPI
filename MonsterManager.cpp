#include "MonsterManager.h"
#include "King_Pig.h"

MonsterManager::MonsterManager()
{
	m_InstanceID = 0;
	m_Player = nullptr;
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Init()
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		m_vMonsters[i]->Init();
	}
}

void MonsterManager::Update(float dt)
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		if (m_vMonsters[i]->IsDead())
		{
			m_vMonsters[i]->Release();
			delete m_vMonsters[i];
			m_vMonsters.erase(m_vMonsters.begin() + i);
		}
		else
		{
			m_vMonsters[i]->Update(dt);
		}
	}
}

void MonsterManager::Render(HDC hdc)
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		m_vMonsters[i]->Render(hdc);
	}
}

void MonsterManager::Release()
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		m_vMonsters[i]->Release();
	}
}

void MonsterManager::SetPlayer(Player* player)
{
	m_Player = player;

	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		m_vMonsters[i]->SetPlayer(m_Player);
	}
}

void MonsterManager::RegisterMonster(MONSTER_TYPE type, FPOINT pos)
{
	Monster* monster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::KING_PIG:
		monster = new King_Pig(type, pos, 20.0f);
		break;
	}

	if (monster)
	{
		monster->SetID(m_InstanceID++);
		m_vMonsters.push_back(monster);
	}
}

void MonsterManager::RemoveMonster(int id)
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		if (m_vMonsters[i]->GetID() == id)
		{
			m_vMonsters[i]->SetIsDead(true);
		}
	}
}

void MonsterManager::ClearMonster()
{
	for (size_t i = 0; i < m_vMonsters.size(); ++i)
	{
		m_vMonsters[i]->Release();
		delete m_vMonsters[i];
		m_vMonsters.erase(m_vMonsters.begin() + i);
	}
	m_vMonsters.clear();
}
