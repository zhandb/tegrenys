#ifndef TGRefCounter_h__
#define TGRefCounter_h__
//-----------------------------------------------------------------------------
#define uint32_t uint 
//-----------------------------------------------------------------------------
#include "windows.h"
//-----------------------------------------------------------------------------

/** ������������ ��� ������� ����� ��� �������� � ��������� ������
*/
class TGReferenceCounter
{
public:
	//! �����������. ������������� ������� ������ � ����
	TGReferenceCounter();
	//! ����������. ������� ������ �� �������� ������������ ��������
	virtual ~TGReferenceCounter(void);
	//! ���������� �������� ������. ���������.
	void AddRef();
	//! ���������� �������� ������. ���������. ��� ���������� ���� ������ ����������������
	virtual void DelRef();
	//! ���������������� ������ � �������� ������������ ��������.
	void PushDestroyMonitor();
	//! ��������� �������-��������. ��� �������� QT ��� �� �������� ������, � ������� ������� ������
	virtual TGReferenceCounter* GetReferenceCounter();
	//! �������� �������� �������� ������
	long GetReferenceCount() const;
protected:
#ifdef _DEBUG
	bool CanBeDestructed;
#endif
private:
	long ReferenceCount;		//!< ���������� ������
	bool UseMonitor;			//!< ������������ ������� ������������ ��������
};

template <typename T>
class TGRefCountPtr
{
public:
	//! �����������
	TGRefCountPtr(T* object = NULL)
		: Object(object ? (T*)((TGReferenceCounter*)object)->GetReferenceCounter() : NULL)
	{
		AddRef();
	}
	//! ���������� �����������
	TGRefCountPtr(const TGRefCountPtr& left)
	{
		this->Object = left.Object;
		AddRef();
	}
	//SN_TODO(����������� ����������� � �������� ������������ �� T*);
	//! �������� ������������
	TGRefCountPtr& operator=(const TGRefCountPtr& left)
	{
		if (this->Object != left.Object)
		{
			DelRef();
			this->Object = left.Object;
			AddRef();
		}
		return *this;
	}
	//! ����������
	virtual ~TGRefCountPtr(void)
	{
		DelRef();
	}
	//! ���������� �������� ������
	void AddRef() const
	{
		if (Object)
			((TGReferenceCounter*)Object)->AddRef();
	}
	//! ���������� �������� ������
	void DelRef() const
	{
		if (Object)
			((TGReferenceCounter*)Object)->DelRef();
	}
	//! ������� ��������� � ���������� �������� ������
	void Reset()
	{
		DelRef();
		Object = NULL;
	}
	//! ���������������� �������� ��������������� ���������
	T* operator->()	const
	{
		return Object;
	}
	//! ���������������� �������� ��������������� ���������
	const T* GetData() const
	{
		return Object;
	}
	T* GetData()
	{
		return Object;
	}
	//! �������� �������������� ����
	template<typename A>
	operator TGRefCountPtr<A>() const
	{
		return check_cast<A*>(Object);
	}
	//! ���������������� �������� �������������� ���� � T*
	operator T*() const
	{
		return Object;
	}
	bool operator < (const TGRefCountPtr& left) const
	{
		return Object < left.Object;
	}

private:
	T* Object;	//!< ������, �� ������� ��������� ���������
};

//-----------------------------------------------------------------------------
#define TG_REFC_PTR(T)	\
class T;			\
	typedef TGRefCountPtr<T> P##T;\
	typedef const TGRefCountPtr<T> PC##T;
//-----------------------------------------------------------------------------

#endif // TGRefCounter_h__