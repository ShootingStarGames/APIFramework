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

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}

}

int Scene::Update(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
}

void Scene::Render(HDC hDc, float fDeltaTime)
{
	list<Layer*> ::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hDc, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
}

bool Scene::LayerSort(Layer * pL1, Layer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}
