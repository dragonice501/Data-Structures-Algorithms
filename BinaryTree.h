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