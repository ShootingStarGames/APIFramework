#pragma once
#include "../Game.h"
#include "../Core/Ref.h"

class Collider	:
	public Ref
{
protected:
	Collider();
	Collider(const Collider& coll);
	virtual ~Collider() = 0;

protected:
	COLLIDER_TYPE	m_eCollType;
	class Obj*		m_pObj;

public:
	COLLIDER_TYPE GetColliderType() const
	{
		return m_eCollType;
	}
	class Obj* GetObj()	const
	{
		return m_pObj;
	}
	void SetObj(class Obj* pObj)
	{
		m_pObj = pObj;
	}
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDc, float fDeltaTime);
	virtual Collider* Clone() = 0;
};

