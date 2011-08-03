#ifndef TGRefCounter_h__
#define TGRefCounter_h__
//-----------------------------------------------------------------------------
#define uint32_t uint 
//-----------------------------------------------------------------------------
#include "windows.h"
//-----------------------------------------------------------------------------

/** Используется как базовый класс для объектов с подсчетом ссылок
*/
class TGReferenceCounter
{
public:
	//! Конструктор. Устанавливает счетчик ссылок в ноль
	TGReferenceCounter();
	//! Деструктор. Убирает объект из монитора уничтожаемых объектов
	virtual ~TGReferenceCounter(void);
	//! Увеличение счетчика ссылок. Атомарное.
	void AddRef();
	//! Уменьшение счетчика ссылок. Атомарное. При достижении нуля объект самоуничтожается
	virtual void DelRef();
	//! Зарегистрировать объект в мониторе уничтожаемых объектов.
	void PushDestroyMonitor();
	//! Получение объекта-счетчика. Для объектов QT это не основной объект, а внешний подсчет ссылок
	virtual TGReferenceCounter* GetReferenceCounter();
	//! Получить значение счетчика ссылок
	long GetReferenceCount() const;
protected:
#ifdef _DEBUG
	bool CanBeDestructed;
#endif
private:
	long ReferenceCount;		//!< Количество ссылок
	bool UseMonitor;			//!< Используется монитор уничтожаемых объектов
};

template <typename T>
class TGRefCountPtr
{
public:
	//! Конструктор
	TGRefCountPtr(T* object = NULL)
		: Object(object ? (T*)((TGReferenceCounter*)object)->GetReferenceCounter() : NULL)
	{
		AddRef();
	}
	//! Конструтор копирования
	TGRefCountPtr(const TGRefCountPtr& left)
	{
		this->Object = left.Object;
		AddRef();
	}
	//SN_TODO(Конструктор копирования и оператор присваивания на T*);
	//! Оператор присваивания
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
	//! Деструктор
	virtual ~TGRefCountPtr(void)
	{
		DelRef();
	}
	//! Увеличение счетчика ссылок
	void AddRef() const
	{
		if (Object)
			((TGReferenceCounter*)Object)->AddRef();
	}
	//! Уменьшение счетчика ссылок
	void DelRef() const
	{
		if (Object)
			((TGReferenceCounter*)Object)->DelRef();
	}
	//! Очистка указателя и уменьшение счетчика ссылок
	void Reset()
	{
		DelRef();
		Object = NULL;
	}
	//! Переопределенный оператор разыменовывания указателя
	T* operator->()	const
	{
		return Object;
	}
	//! Переопределенный оператор разыменовывания указателя
	const T* GetData() const
	{
		return Object;
	}
	T* GetData()
	{
		return Object;
	}
	//! Оператор преобразования типа
	template<typename A>
	operator TGRefCountPtr<A>() const
	{
		return check_cast<A*>(Object);
	}
	//! Переопределенный оператор преобразования типа в T*
	operator T*() const
	{
		return Object;
	}
	bool operator < (const TGRefCountPtr& left) const
	{
		return Object < left.Object;
	}

private:
	T* Object;	//!< Объект, на который указывает указатель
};

//-----------------------------------------------------------------------------
#define TG_REFC_PTR(T)	\
class T;			\
	typedef TGRefCountPtr<T> P##T;\
	typedef const TGRefCountPtr<T> PC##T;
//-----------------------------------------------------------------------------

#endif // TGRefCounter_h__