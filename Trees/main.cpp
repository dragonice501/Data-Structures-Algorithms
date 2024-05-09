#include <iostream>

template<class DataType>
class DListNode
{
public:
	DataType mData;
	DListNode<DataType>* mNext = nullptr;
	DListNode<DataType>* mPrevious = nullptr;

public:
	void InsertAfter(DataType data)
	{
		DListNode<DataType>* newNode = new DListNode<DataType>;

		newNode->mData = data;
		if (mNext)
		{
			newNode->mNext = mNext;
			mNext->mPrevious = newNode;
		}
		newNode->mPrevious = this;

		mNext = newNode;
	}
};

template<class DataType>
class DListIterator;

template<class DataType>
class DLinkedList
{
public:
	DListNode<DataType>* mHead = nullptr;
	DListNode<DataType>* mTail = nullptr;
	size_t mCount;

public:
	DLinkedList()
	{
		mHead = nullptr;
		mTail = nullptr;
		mCount = 0;
	}
	~DLinkedList()
	{
		DListNode<DataType>* itr = mHead;
		DListNode<DataType>* temp;
		while (itr)
		{
			temp = itr->mNext;

			delete itr;

			itr = temp;
		}
	}

	DListIterator<DataType> GetIterator()
	{
		return DListIterator<DataType>(this, mHead);
	}

	void Prepend(DataType data)
	{
		DListNode<DataType>* newNode = new DListNode<DataType>;
		newNode->mData = data;
		newNode->mNext = mHead;

		mHead = newNode;

		if (!mTail)
		{
			mTail = mHead;
		}

		mCount++;
	}
	void Append(DataType data)
	{
		if (!mHead)
		{
			mHead = mTail = new DListNode<DataType>;
			mHead->mData = data;
		}
		else
		{
			mTail->InsertAfter(data);
			mTail = mTail->mNext;
		}

		mCount++;
	}
	void RemoveHead()
	{
		DListNode<DataType>* node = nullptr;
		if (mHead)
		{
			node = mHead->mNext;

			delete mHead;

			mHead = node;

			if (mHead == nullptr) mTail = nullptr;
			mCount--;
		}
	}
	void RemoveTail()
	{
		DListNode<DataType>* node = mHead;
		if (mHead)
		{
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				while (node->mNext != mTail)
				{
					node = node->mNext;
				}

				mTail = node;
				delete node->mNext;
				node->mNext = nullptr;
			}

			mCount--;
		}
	}
	void Remove(DListIterator<DataType>& itr)
	{
		DListNode<DataType>* node = mHead;

		if (itr.mList != this) return;

		if (!itr.mNode) return;

		if (itr.mNode == mHead)
		{
			itr.Forth();
			RemoveHead();
		}
		else
		{
			while (node->mNext != itr.mNode)
			{
				node = node->mNext;
			}

			itr.Forth();
			if (node->mNext == mTail)
			{
				mTail = node;
			}

			delete node->mNext;

			node->mNext = itr.mNode;
		}

		mCount--;
	}
	void Insert(DListIterator<DataType>& itr, DataType data)
	{
		if (itr.mList != this) return;

		if (itr.mNode)
		{
			itr.mNode->InsertAfter(data);

			if (itr.mNode == mTail) mTail = itr.mNode->mNext;

			mCount++;
		}
		else
		{
			Append(data);
		}
	}
};

template<class DataType>
class DListIterator
{
public:
	DListNode<DataType>* mNode = nullptr;
	DLinkedList<DataType>* mList = nullptr;

public:
	DListIterator(DLinkedList<DataType>* list = nullptr, DListNode<DataType>* node = nullptr)
	{
		mList = list;
		mNode = node;
	}

	bool Valid()
	{
		return mNode != nullptr;
	}
	DataType& Item()
	{
		return mNode->mData;
	}

	void Start()
	{
		if (mList)
		{
			mNode = mList->mHead;
		}
	}
	void End()
	{
		if (mList)
		{
			mNode = mList->mTail;
		}
	}
	void Forth()
	{
		if (mNode)
		{
			mNode = mNode->mNext;
		}
	}
	void Back()
	{
		if (mNode)
		{
			mNode = mNode->mPrevious;
		}
	}
};

template<class DataType>
class Tree
{
public:
	typedef Tree<DataType> Node;

	DataType mData;
	Node* mParent;
	DLinkedList<Node*> mChildren;

public:
	Tree()
	{
		mParent = nullptr;
	}
	~Tree()
	{
		Destroy();
	}

	void Destroy()
	{
		DListIterator<Node*> itr = mChildren.GetIterator();
		Node* node = nullptr;
		itr.Start();
		while (itr.Valid())
		{
			node = itr.Item();
			mChildren.Remove(itr);
			delete node;
		}
	}

	size_t Count()
	{
		size_t c = 1;
		DListIterator<Node*> itr = mChildren.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			c += itr.Item()->Count();
		}

		return c;
	}
};

template<class DataType>
class TreeIterator
{
public:
	typedef Tree<DataType> Node;
	Node* mNode;
	DListIterator<Node*> mChildItr;

public:
	TreeIterator(Node* pNode = nullptr)
	{
		this = pNode;
	}

	void operator= (Node* node)
	{
		mNode = node;
		ResetIterator();
	}

	void ResetIterator()
	{
		if (mNode)
		{
			mChildItr = mNode->mChildren.GetIterator();
		}
		else
		{
			mChildItr.mList = nullptr;
			mChildItr.mNode = nullptr;
		}
	}

	void Root()
	{
		while (mNode->mParent)
		{
			mNode = mNode->mParent;
		}
	}
	void Up()
	{
		if (mNode)
		{
			mNode = mNode->mParent;
		}
		ResetIterator();
	}
	void Down()
	{
		if (mChildItr.Valid())
		{
			mNode = mChildItr.Item();
			ResetIterator();
		}
	}
	void ChildForth()
	{
		mChildItr.Forth();
	}
	void ChildBack()
	{
		mChildItr.Back();
	}
	void ChildStart()
	{
		mChildItr.Start();
	}
	void ChildEnd()
	{
		mChildItr.End();
	}
};

template<class DataType>
void Process(Tree<DataType>* tree)
{

}

template<class DataType>
void Preorder(Tree<DataType>* node, void(*process)(Tree<DataType>*))
{
	Process(node);
	DListIterator<Tree<DataType>*> itr = node->mChildren.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		Preorder(itr.Item(), Process);
	}
}

int main()
{


	return 0;
}