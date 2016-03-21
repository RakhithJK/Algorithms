#include "linkedlistnode.h"
#include <memory>

using std::shared_ptr;

template<typename T> linkedlistnode<T>::linkedlistnode<T>(T value)
{
	_value = value;
}
template<typename T> linkedlistnode<T>::linkedlistnode<T>(T value, linkedlistnode<T> next) : linkedlistnode<T>(value)
{
	_next = std::make_shared<linkedlistnode<T>>(new linkedlistnode<T>(next.value()));
}

template<typename T> void linkedlistnode<T>::setNext(const linkedlistnode<T>& node)
{
	_next = std::make_shared<linkedlistnode<T>>(new linkedlistnode<T>(node.value()));
}
template<typename T> T linkedlistnode<T>::value()
{
	return *_value;
}
template<typename T> shared_ptr<linkedlistnode<T>> linkedlistnode<T>::next()
{
	return _next;
}