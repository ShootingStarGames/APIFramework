#pragma once

#include "../Game.h"

class ResourcesManager
{
private:
	unordered_map<string, class Texture*> m_mapTexture;
	HINSTANCE	m_hInst;
public:
	bool Init(HINSTANCE hInst);
	class Texture* LoadTexture(const string& strKey,
		const wchar_t* pFilename, const string& strPathKey = TEXTURE_PATH);
	class Texture* FindTexture(const string& strKey);
	DECLARE_SINGLE(ResourcesManager)
};

