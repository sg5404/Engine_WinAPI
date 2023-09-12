#ifndef OBJ_H
#define OBJ_H

#include "BBasisStd.h"

class Obj
{
public:
	Obj() = default;
	virtual ~Obj() = default;

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc, float dt) = 0;
	virtual void Release() = 0;

protected:
	Obj(FPOINT pos, OBJSIZE size) : m_Pos(pos), m_Size(size), m_fScale(1.0f) {}
	Obj(FPOINT pos, OBJSIZE size, float scale)
		: m_Pos(pos), m_Size(size), m_fScale(scale) {}

	FPOINT		m_Pos;
	OBJSIZE		m_Size;
	float		m_fScale;
};

#endif // OBJ_H