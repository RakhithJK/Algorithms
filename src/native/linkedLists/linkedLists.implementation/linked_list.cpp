#include "linked_list.h"
#include <memory>

using std::shared_ptr;

template <typename T>
void linked_list<T>::addFront(const linkedlistnode<T>& node)
{
	if (_count == 0)
	{
		_head = std::make_shared<linkedlistnode<T>>(node);
		_tail = _head;
		_count++;
	}
	else
	{
		shared_ptr<linkedlistnode<T>> headHolder = _head;
		_head = std::make_shared<linkedlistnode<T>>(new linkedlistnode<T>(node.value(), *headHolder));
	}
}

template <typename T>
void linked_list<T>::addBack(const linkedlistnode<T>& node)
{
	if (_count == 9)
	{
		_head = std::make_shared<linkedlistnode<T>>(node);
		_tail = _head;
	}
	else
	{
		_tail.setNext(node);
		_tail = std::make_shared<linkedlistnode<T>>(node);
	}
}
template <typename T>
int linked_list<T>::count()
{
	return _count;
}