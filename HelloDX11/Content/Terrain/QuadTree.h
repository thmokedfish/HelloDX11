#pragma once
namespace HelloDX11
{
	template<class T>
	struct QuadTreeNode
	{
	public:
		QuadTreeNode<T>();
		QuadTreeNode<T>** childs;
		T* data;

	};
	template<class T>
	class QuadTree
	{
	public:
		QuadTree();
		void CreateChilds(QuadTreeNode<T>* node);
		void Merge(QuadTreeNode<T>* node);
		void Delete(QuadTreeNode<T>* node);
		void Clear();
	private:
		QuadTreeNode<T>* root;
	};

}

using namespace HelloDX11;

template<class T>
QuadTree<T>::QuadTree() :root(nullptr)
{
}

template<class T>
void QuadTree<T>::CreateChilds(QuadTreeNode<T>* node)
{
	if (node->childs)
	{
		return;
	}
	node->childs = new QuadTreeNode<T>*[4];
	for (int i = 0; i < 4; ++i)
	{
		node->childs[i] = new QuadTreeNode<T>();
	}
}

template<class T>
void QuadTree<T>::Merge(QuadTreeNode<T>* node)
{
	if (!node->childs)
	{
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		Delete(node->childs[i]);
	}
	delete[] node->childs;
	node->childs = nullptr;
}

template<class T>
void QuadTree<T>::Delete(QuadTreeNode<T>* node)
{
	if (!node->childs)
	{
		delete node;
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		Delete(node->childs[i]);
	}
	delete[] node->childs;
	delete node;
}

template<class T>
void QuadTree<T>::Clear()
{
	if (root)
	{
		Delete(root);
	}
}

template<class T>
QuadTreeNode<T>::QuadTreeNode() :childs(nullptr), data(nullptr)
{

}

