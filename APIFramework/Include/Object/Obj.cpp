#include "Obj.h"
#include "../Scene/Layer.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Collider/Collider.h"

list<Obj*> Obj::m_ObjList;

Obj::Obj()
{
}

Obj::Obj(const Obj & obj)
{
	*this = obj;

	m_ColliderList.clear();

	list<Collider*>::const_iterator iter;
	list<Collider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		Collider* pColl = (*iter)->Clone();

		m_ColliderList.push_back(pColl);
	}

}

Obj::~Obj()
{
	Safe_Release_VecList(m_ColliderList);
}

void Obj::AddObj(Obj * pObj)
{
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

Obj * Obj::FindObject(const string & strTag)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag) 
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return NULL;
}

void Obj::EraseObj(Obj * pObj)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void Obj::EraseObj(const string & strTag)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void Obj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

bool Obj::Init()
{
	return false;
}

void Obj::Input(float fDeltaTime)
{
}

int Obj::Update(float fDeltaTime)
{
	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void Obj::Collision(float fDeltaTime)
{
}

void Obj::Render(HDC hDc, float fDeltaTime)
{
}

Obj * Obj::CreateCloneObj(const string & strPrototypeKey, 
	const string & strTag, class Layer* pLayer)
{
	Obj* pPrototype = Scene::FindPrototype(strPrototypeKey);

	if (!pPrototype)
		return NULL;
	Obj* pObj = pPrototype->Clone();
	
	pObj->SetTag(strTag);

	if (pLayer)
	{
		pLayer->AddObject(pObj);
	}

	AddObj(pObj);

	return pObj;
}
