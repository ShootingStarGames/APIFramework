#include "Collider.h"



Collider::Collider()
{
}

Collider::Collider(const Collider & coll)
{
	*this = coll;
}


Collider::~Collider()
{
}

bool Collider::Init()
{
	return false;
}

void Collider::Input(float fDeltaTime)
{
}

int Collider::Update(float fDeltaTime)
{
	return 0;
}

int Collider::LateUpdate(float fDeltaTime)
{
	return 0;
}

void Collider::Collision(float fDeltaTime)
{
}

void Collider::Render(HDC hDc, float fDeltaTime)
{
}

Collider * Collider::Clone()
{
	return nullptr;
}
