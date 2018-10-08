#include "Scene.h"
#include "Layer.h"


Scene::Scene()
{
	Layer* pLayer = CreateLayer("Default");
	pLayer = CreateLayer("UI", INT_MAX);
}


Scene::~Scene()
{
	Safe_Release_VecList(m_LayerList);
}

Layer * Scene::CreateLayer(const string& strTag,
	int iZOrder)
{
	Layer* pLayer = new Layer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 0)
		m_LayerList.sort(Scene::LayerSort);

	return pLayer;
}

Layer* Scene::FindLayer(const string & strTag)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
			return *iter;
	}

	return NULL;
}

bool Scene::Init()
{
	return true;
}

void Scene::Input(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(fDeltaTime);
	}

}

int Scene::Update(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(fDeltaTime);
	}
	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(fDeltaTime);
	}
	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(fDeltaTime);
	}
}

void Scene::Render(HDC hDc, float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDc, fDeltaTime);
	}
}

bool Scene::LayerSort(Layer * pL1, Layer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}
