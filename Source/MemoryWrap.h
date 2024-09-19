#ifndef TSREFLECTION_MEMORYWRAP_H
#define TSREFLECTION_MEMORYWRAP_H


#include <memory>


namespace UniquePtr::Utils
{
template <class T>
using TDeleterFuncPtr = void (*)(T*);

template <class T, TDeleterFuncPtr<T> FuncPtr>
struct TDeleter
{
	void operator()(T* ptr)
	{
		FuncPtr(ptr);
	}
};

template <class T>
void TDefaultDeleter(T* t)
{
	delete t;
}
} // namespace UniquePtr::Utils


// UniquePtr with deleter function
// TUniquePtr<int*, [](int* Ptr){ delete Ptr; }> Obj;
template <class T, UniquePtr::Utils::TDeleterFuncPtr<T> FuncPtr = UniquePtr::Utils::TDefaultDeleter<T>>
using TUniquePtr = std::unique_ptr<T, UniquePtr::Utils::TDeleter<T, FuncPtr>>;


#endif // TSREFLECTION_MEMORYWRAP_H