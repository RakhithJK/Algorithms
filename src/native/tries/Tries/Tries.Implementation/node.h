#pragma once
#include<vector>

namespace tries
{
    template<typename T>
	class node
	{
		private:
			T*					    _value;
			std::vector<node<T>*>	_children;
		public:
			node();
			~node();
	};
}