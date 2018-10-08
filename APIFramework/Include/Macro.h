#pragma once

#define SAFE_DELETE(p)			if(p)	{delete p; p=NULL;}
#define SAFE_DELETEARRAY(p)		if(p)	{delete[] p; p=NULL;}
#define SAFE_RELEASE(p)			if(p)	{p->Release(); p = NULL;}
#define DECLARE_SINGLE(Type)	\
	private:\
		static Type* m_pInst;	\
	public:\
		static Type* GetInst()	\
	{\
		if(!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
	private:\
		Type();\
		~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL;
#define GET_SINGLE(Type)		Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::DestroyInst()

#define GETRESOLUTION	Core::GetInst()->GetResolution()