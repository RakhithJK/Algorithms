#include<memory>

using std::shared_ptr;

template <typename T> class linkedlistnode
{
public:
	T value();
	shared_ptr<linkedlistnode<T>> next();
	void setNext(const linkedlistnode<T>& node);
	linkedlistnode(T value);
	linkedlistnode(T value, linkedlistnode<T> next);
private:
	shared_ptr<T> _value;
	shared_ptr<linkedlistnode<T>> _next;
};