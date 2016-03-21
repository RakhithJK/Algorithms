#include<memory>
#include "linkedlistnode.h"

using std::shared_ptr;

template<typename T> class linked_list
{
public:
	void addFront(const linkedlistnode<T>& node);
	void addBack(const linkedlistnode<T>& node);
	int count();
private:
	shared_ptr<T> _head  = nullptr;
	shared_ptr<T> _tail  = nullptr;
	int			  _count = 0;
};