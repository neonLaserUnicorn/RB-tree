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
			sf::sleep(sf::seconds(1));
			std::cout << this->data << " left: ";
			this->left->print();
			std::cout << std::endl << this->data << " right: ";
			this->right->print();
		}
	}
};

template<class T>
Leaf<T>* bigRotateRight(Leaf<T>* root);

template<class T>
void rotateRight(Leaf<T>* root);

template<class T>
Leaf<T>* rotateLeft(Leaf<T>* root);

template<class T>
Leaf<T>* organize(Leaf<T>* root)
{
	if (root == nullptr)
		return nullptr;
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
					
				}
				else
				{
					if (parent == grand->left && root==parent->left)//LL-case
					{ 
						std::cout << "\norganizing...\n";
						std::cout << grand->data << ' ' << grand->left->data << '\n';
						parent->right = grand;
						parent->parent = grand->parent;
						grand->parent = parent;
						grand->left = nullptr;
						std::cout << grand->data << ' ' << grand->left << '\n';
						//root->parent = parent;


						//bigRotateRight();

					}
					if (parent == grand->left && root == parent->right)//LR-case
					{ 

					}
					if (parent == grand->right && root == parent->right)//RR-case
					{

					}
					if (parent == grand->right && root == parent->left)//RL-case
					{

					}
				}
				//grand = organize(grand);
			}
		}
	}
	//root->parent = organize(root->parent);
	root->left = organize(root->left);
	root->right = organize(root->right);
	return root;
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
		std::cout << "add: " << root->left->data << std::endl;
		//organize(root->left);
	}
	else
	{
		root->right = add(n_data, root->right);
		if (root->right->parent == nullptr)
			root->right->parent = root;
		std::cout << "add: " << root->right->data << std::endl;
		//organize(root->right);
	}
	//root = organize(root);
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


public:
	Leaf<T>* root;
	BinaryTree();
	void push(T data);
	void print();
	Leaf<T>*& getRoot();
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
	root = organize(root);
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
Leaf<T>*& BinaryTree<T>::getRoot()
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
void rotateRight(Leaf<T>* root)
{
	Leaf<T>* x = root->left;
	Leaf<T>* y = x->right;
	x->right = root;
	root->left = y;
	root->parent = x;
	if (y != nullptr)
		y->parent = root;
	
	//return x;
}

template<class T>
Leaf<T>* bigRotateRight(Leaf<T>* root)
{
	Leaf<T>* new_root = root->left;
	if (new_root->right != nullptr)
	{
		root->left = new_root->right;
		new_root->right->parent = root;
	}
	else
		root->left = nullptr;
	new_root->right = root;
	new_root->parent = root->parent;
	//root->parent = new_root;

	return new_root;
	
}