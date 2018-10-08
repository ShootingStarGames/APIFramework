#include "Layer.h"
#include "../Object/Obj.h"


Layer::Layer()	:
	m_iZOrder(0),
	m_strTag(""),
	m_pScene(NULL)
{
}


Layer::~Layer()
{
	Safe_Release_VecList(m_ObjList);
}

void Layer::AddObject(Obj * pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();

	m_ObjList.push_back(pObj);
}

void Layer::Input(float fDeltaTime)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(fDeltaTime);
	}
}

int Layer::Update(float fDeltaTime)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(fDeltaTime);
	}
	return 0;
}

int Layer::LateUpdate(float fDeltaTime)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void Layer::Collision(float fDeltaTime)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(fDeltaTime);
	}
}

void Layer::Render(HDC hDc, float fDeltaTime)
{
	list<Obj*> ::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDc, fDeltaTime);
	}
}
