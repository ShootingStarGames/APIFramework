#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>

using namespace std;

#include "Macro.h"
#include "resource.h"
#include "Types.h"
#include "Flag.h"

#pragma comment(lib,"msimg32")

// Path Key
#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"

template <typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}