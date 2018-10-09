#pragma once
#include "../Game.h"
#include "../Core/Ref.h"
class Texture	:
	public Ref
{
private:
	friend class ResourcesManager;
private:
	Texture();
	~Texture();

public:
	bool LoadTexture(HINSTANCE hInst,const string& strKey,
		const wchar_t* pFilename, const string& strPathKey = TEXTURE_PATH);
};

