#pragma once

enum COLOR
{
	RED, 
	BLACK,
};

template<class T>
struct Leaf
{
	T data;
	COLOR cl;
	Leaf* left;
	Leaf* right;
	Leaf* parent;
	Leaf(T d) 
		:data(d), left(nullptr), right(nullptr), parent(nullptr),cl(RED)
	{	}
	void print()
	{
		if (this != nullptr)
		{
			std::cout << this->data << ' ' << this << std::endl;
			this->left->print();
			this->right->print();
		}
	}
};

template<class T>
Leaf<T>* rotateRight(Leaf<T>* root);

template<class T>
Leaf<T>* rotateLeft(Leaf<T>* root);

template<class T>
void organize(Leaf<T>* root)
{
	Leaf<T>* parent = root->parent;
	if (!(parent!=nullptr && parent->cl == BLACK))
	{
		if (parent == nullptr)
			root->cl = BLACK;
		else
		{
			Leaf<T>* grand = parent->parent;
			if (grand != nullptr)
			{
				Leaf<T>* uncle = nullptr;
				if (parent == grand->left)
					uncle = grand->right;
				else
					uncle = grand->left;
				if (uncle != nullptr && uncle->cl == RED)
				{
					parent->cl = BLACK;
					uncle->cl = BLACK;
					grand->cl = RED;
					std::cout << "\n****Changed****\n";
					organize(grand);
				}
				else 
				{
					if (root == parent->right && parent == grand->left)
					{
						
						//parent = rotateLeft(root);
					}
				}
			}
		}
	}
	/*if(root->left != nullptr)
		organize(root->left);
	if(root->right != nullptr)
		organize(root->right);*/
	
}

template<class T>
Leaf<T>* add(T n_data, Leaf<T>* root)
{
	if (root == nullptr)
	{
		root = new Leaf<T>(n_data);
	}
	else if (n_data < root->data)
	{
		root->left = add(n_data, root->left);
		if (root->left->parent == nullptr)
			root->left->parent = root;
		organize(root->left);
	}
	else
	{
		root->right = add(n_data, root->right);
		if (root->right->parent == nullptr)
			root->right->parent = root;
		organize(root->right);
	}
	return(root);
}

template<class T>
Leaf<T>* find(T n_data, Leaf<T>* root)
{
	Leaf<T>* ret = nullptr;
	if (root != nullptr)
	{
		if (n_data < root->data)
			ret = find(n_data, root->left);
		if (n_data > root->data)
			ret = find(n_data, root->right);
		if (n_data == root->data)
		{
			ret = root;
		}	
	}
	return ret;

}

template<class T>
class BinaryTree
{
private:

	Leaf<T>* root;

public:
	BinaryTree();
	void push(T data);
	void print();
	Leaf<T>* getRoot();
	T getData();
	Leaf<T>* operator[](T key)
	{
		Leaf* cur = root;
		while (cur != nullptr)
		{
			if (key < cur->data)
				cur = cur->left;
			else if (key > cur->data)
				cur = cur->right;
			else
				break;
		}
		return cur;
	}
	//Leaf* 
};

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<class T>
void BinaryTree<T>::push(T data)
{
	root = add(data, root);
}

template<class T>
void BinaryTree<T>::print()
{
	root->print();
}

template<class T>
T BinaryTree<T>::getData()
{
	return root->data;
}

template<class T>
Leaf<T>* BinaryTree<T>::getRoot()
{
	return root;
}

template<class T>
Leaf<T>* rotateLeft(Leaf<T>* root)
{
	std::cout << "\n root is " << root << ": " << root->data;
	Leaf<T>* x = root->right;
	std::cout << "\n x is " << x << ": ";
	if (x != nullptr)
		std::cout << x->data;
	Leaf<T>* y = x->left;
	std::cout << "\n y is " << y << ": ";
	if (y != nullptr)
		std::cout << y->data;
	x->left = root;
	root->right = y;
	root->parent = x;
	if (y != nullptr)
		y->parent = root;
	return x;
}

template<class T>
Leaf<T>* rotateRight(Leaf<T>* root)
{
	Leaf<T>* x = root->left;
	Leaf<T>* y = x->right;
	x->right = root;
	root->left = y;
	root->parent = x;
	if (y != nullptr)
		y->parent = root;
	return x;
}