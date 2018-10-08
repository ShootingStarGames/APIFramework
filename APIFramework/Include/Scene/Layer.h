#pragma once

#include "../Game.h"
#include "../Core/Ref.h"

class Layer :
	public Ref

{
private:
	friend class Scene;
private:
	Layer();
	~Layer();
private:
	class Scene* m_pScene;
	string	m_strTag;
	int		m_iZOrder;
	list<class Obj*> m_ObjList;

public:
	void SetScene(class Scene* pScene)
	{
		m_pScene = pScene;
	}
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetZOrder(const int& iZOrder)
	{
		m_iZOrder = iZOrder;
	}
	Scene* GetScene() const
	{
		return m_pScene;
	}
	string GetTag() const
	{
		return m_strTag;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

public:
	void AddObject(class Obj* pObj);

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDc, float fDeltaTime);
};

