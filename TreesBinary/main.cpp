#include <iostream>

template<class DataType>
class BinaryTree
{
public:
	typedef BinaryTree<DataType> Node;

	DataType mData;
	Node* mParent;
	Node* mLeft;
	Node* mRight;

public:
	BinaryTree()
	{
		mParent = nullptr;
		mLeft = nullptr;
		mRight = nullptr;
	}
	~BinaryTree()
	{
		Destroy();
	}

	void Destroy()
	{
		if (mLeft) delete mLeft;
		mLeft = nullptr;

		if (mRight) delete mRight;
		mRight = nullptr;
	}

	size_t Count()
	{
		size_t c = 1;
		
		if (mLeft) c += mLeft->Count();
		if (mRight) c += mRight->Count();

		return c;
	}
};

int main()
{
	BinaryTree<int>* root = nullptr;
	BinaryTree<int>* itr = nullptr;

	root = new BinaryTree<int>;
	root->mData = 1;

	root->mLeft = new BinaryTree<int>;
	root->mLeft->mData = 2;
	root->mLeft->mParent = root;

	root->mRight = new BinaryTree<int>;
	root->mRight->mData = 3;
	root->mRight->mParent = root;

	itr = root;
	itr = itr->mLeft;
	itr->mLeft = new BinaryTree<int>;
	itr->mLeft->mData = 4;
	itr->mLeft->mParent = itr;

	itr->mRight = new BinaryTree<int>;
	itr->mRight->mData = 5;
	itr->mRight->mParent = itr;

	itr = itr->mParent;

	itr = itr->mRight;
	itr->mLeft = new BinaryTree<int>;
	itr->mLeft->mData = 6;
	itr->mLeft->mParent = itr;

	itr->mRight = new BinaryTree<int>;
	itr->mRight->mData = 7;
	itr->mRight->mParent = itr;

	return 0;
}