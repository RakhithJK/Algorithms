#pragma once
#include "node.h"

namespace tries
{
	template<typename T>
	class tree
	{
		private:
			node<T> * _root;
		public:
			tree();
			~tree();
	};
}