#pragma once
#include "../Core/Core.h"

class SceneManager
{
private:
	class Scene*	m_pScene;
	class Scene*	m_pNextScene;

public:
	class Scene* GetScene() const
	{
		return m_pScene;
	}
public :
	bool Init();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDc,float fDeltaTime);

public:
	template <typename T>
	T* CreateScene(SCENE_CREATE sc)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	};
	DECLARE_SINGLE(SceneManager)

};