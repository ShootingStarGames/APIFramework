#include "ResourcesManager.h"
#include "Texture.h"

DEFINITION_SINGLE(ResourcesManager)

ResourcesManager::ResourcesManager()
{
}


ResourcesManager::~ResourcesManager()
{
	Safe_Release_Map(m_mapTexture);
}

bool ResourcesManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	return true;
}

Texture * ResourcesManager::LoadTexture(const string & strKey,
	const wchar_t * pFilename, const string & strPathKey)
{
	Texture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new Texture;
	
	if (!pTexture->LoadTexture(m_hInst, strKey, pFilename, strPathKey))
	{
		SAFE_RELEASE(pTexture);
		return NULL;
	}
	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));
	
	return pTexture;
}

Texture * ResourcesManager::FindTexture(const string & strKey)
{
	unordered_map<string, class Texture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	iter->second->AddRef();

	return iter->second;
}
