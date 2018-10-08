#include "Obj.h"
#include "../Scene/Layer.h"

list<Obj*> Obj::m_ObjList;
unordered_map<string, Obj*> Obj::m_mapPrototype;

Obj::Obj()
{
}

Obj::Obj(const Obj & obj)
{
	*this = obj;
}

Obj::~Obj()
{
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

void Obj::ErasePrototype(const string & strKey)
{
	unordered_map<string, Obj*>::iterator iter = m_mapPrototype.find(strKey);
	if (iter == m_mapPrototype.end())
		return;
	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);
}

void Obj::ErasePrototype()
{
	Safe_Release_Map(m_mapPrototype);
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
	Obj* pPrototype = FindPrototype(strPrototypeKey);

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

Obj * Obj::FindPrototype(const string & strKey)
{
	unordered_map<string, Obj*>::iterator iter = m_mapPrototype.find(strKey);
	if (iter == m_mapPrototype.end())
		return NULL;
	
	return iter->second;
}
