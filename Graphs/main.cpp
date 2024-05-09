#include <iostream>

#include "../Array.h"
#include "../DLinkedList.h"
#include "../Queue.h"

template<class NodeType, class ArcType>
class GraphArc;

template<class NodeType, class ArcType>
class GraphNode
{
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	NodeType mData;
	DLinkedList<Arc> mArcList;
	bool mMarked;

	void AddArc(Node* node, ArcType weight)
	{
		Arc a;
		a.mNode = node;
		a.mWeight = weight;
		mArcList.Append(a);
	}

	Arc* GetArc(Node* node)
	{
		DListIterator<Arc> itr = mArcList.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (itr.Item().mNode == node) return &(itr.Item());
		}

		return nullptr;
	}

	bool RemoveArc(Arc* arc)
	{
		DListIterator<Arc> itr = mArcList.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (itr.Item().mNode == node)
			{
				mArcList.Remove(itr);
				return true;
			}

			return false;
		}
	}
};

template<class NodeType, class ArcType>
class GraphArc
{
public:
	GraphNode<NodeType, ArcType>* mNode;
	ArcType mWeight;
};

template<class NodeType, class ArcType>
class Graph
{
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	Array<Node*> mNodes;
	size_t mCount;

public:
	Graph(size_t size) : mNodes(size)
	{
		for (size_t i = 0; i < size; i++)
		{
			mNodes[i] = 0;
		}

		mCount = 0;
	}
	~Graph()
	{
		for (size_t i = 0; i < mNodes.Size(); i++)
		{
			if (mNodes[i]) delete mNodes[i];
		}
	}

	bool AddNode(NodeType data, size_t index)
	{
		if (mNodes[index]) return false;

		mNodes[index] = new Node;
		mNodes[index]->mData = data;
		mNodes[index]->mMarked = false;
		mCount++;

		return true;
	}
	void RemoveNode(size_t index)
	{
		if (mNodes[index] == nullptr) return false;

		Arc* arc;
		for (size_t node = 0; node < mNodes.Size(); node++)
		{
			if (mNodes[node])
			{
				arc = mNodes[node]->GetArc(mNodes[index]);

				if (arc) RemoveArc(node, index);
			}
		}

		delete mNodes[index];
		mNodes[index] = nullptr;
		mCount--;
	}
	bool AddArc(size_t from, size_t to, ArcType weight)
	{
		if (mNodes[from] == nullptr || mNodes[to] == nullptr) return false;
		if (mNodes[from]->GetArc(mNodes[to])) return false;

		mNodes[from]->AddArc(mNodes[to], weight);

		return true;
	}
	bool RemoveArc(size_t from, size_t to)
	{
		if (mNodes[from] == nullptr || mNodes[to] == nullptr) return false;

		mNodes[from]->RemoveArc(mNodes[to]);

		return true;
	}
	Arc* GetArc(size_t from, size_t to)
	{
		if (mNodes[from] == nullptr || mNodes[to] == nullptr) return nullptr;

		return mNodes[from]->GetArc(mNodes[to]);
	}
	void ClearMarks()
	{
		for (size_t i = 0; i < mNodes.Size(); i++)
		{
			if (mNodes[i]) mNodes[i]->mMarked = false;
		}
	}

	void DepthFirst(Node* node, void(*process)(Node*))
	{
		if (!node) return;

		process(node);
		node->mMarked = true;

		DListIterator<Arc> itr = node->mArcList.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (!itr.Item().mNode->mMarked)
			{
				DepthFirst(itr.Item().mNode, process);
			}
		}
	}
	void BreathFirst(Node* node, void(*process)(Node*))
	{
		if (!node) return;

		LQueue<Node*> queue;
		DListIterator<Arc> itr;

		queue.Enqueue(node);
		node->mMarked = true;

		while (queue.Count != 0)
		{
			process(queue.Front());
			itr = queue.Front()->mArcList.GetIterator();
			for (itr.Start(); itr.Valid(); itr.Forth())
			{
				if (!itr.Item().mNode->marked)
				{
					itr.Item().mNode->marked = true;
					queue.Enqueue(itr.Item().mNode);
				}
			}

			queue.Dequeue();
		}
	}
};

int main()
{


	return 0;
}