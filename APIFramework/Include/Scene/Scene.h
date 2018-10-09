#pragma once
#include "../Game.h"

class Scene
{
protected:
	friend class SceneManager;

protected:
	Scene();
	virtual	~Scene() = 0;

private:
	static unordered_map<string, class Obj*> m_mapPrototype;

public:
	static void ErasePrototype(const string& strKey);
	static void ErasePrototype();
protected:
	list<class Layer*> m_LayerList;

public:
	class Layer* CreateLayer(const string& strTag,
		int iZOrder = 0);
	class Layer* FindLayer(const string& strTag);

public:
	virtual bool Init();
	virtual	void Input(float fDeltaTime);
	virtual	int Update(float fDeltaTime);
	virtual	int LateUpdate(float fDeltaTime);
	virtual	void Collision(float fDeltaTime);
	virtual	void Render(HDC hDc, float fDeltaTime);

public:
	static bool LayerSort(class Layer* pL1, class Layer* pL2);

public:
	template <typename T>
	static  T* CreatePrototype(const string& strTag)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);
		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}
		pObj->AddRef();

		m_mapPrototype.insert(make_pair(strTag, pObj));

		return pObj;
	}

	static Obj* FindPrototype(const string& strKey);
};

