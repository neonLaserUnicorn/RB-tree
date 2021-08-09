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
			std::cout << this->data << ' ' << this << "\t Parent: " << this->parent << std::endl;
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
Leaf<T>* bigRotateLeft(Leaf<T>* root);

template<class T>
Leaf<T>* rotateRight(Leaf<T>* root);

template<class T>
Leaf<T>* rotateLeft(Leaf<T>* root);

template<class T>
void organize(Leaf<T>* root)
{
	if (root == nullptr)
		return ;
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
					organize(grand);
					
				}
				else
				{
					if (parent == grand->left && root==parent->left)//LL-case
					{ 
						parent = bigRotateRight(parent);
					}
					if (parent == grand->left && root == parent->right)//LR-case
					{ 
						parent = rotateRight(parent);
						parent = bigRotateRight(parent);
					}
					if (parent == grand->right && root == parent->right)//RR-case
					{
						parent = bigRotateLeft(parent);
					}
					if (parent == grand->right && root == parent->left)//RL-case
					{
						parent = rotateLeft(parent);
						parent = bigRotateLeft(parent);
					}
					//organize(parent);
				}
			}
		}
	}
	//root->left = organize(root->left);
	//root->right = organize(root->right);
	//return root;
}

template<class T>
void add(T n_data, Leaf<T>*& root)
{
	if (root == nullptr)
	{
		root = new Leaf<T>(n_data);
	}
	/*else if (n_data < root->data)
	{
		root->left = add(n_data, root->left);
		if (root->left->parent == nullptr)
			root->left->parent = root;
		std::cout << "add: " << root->left->data << " in " << root->left << std::endl;
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
	return(root)*/
	else
	{
		Leaf<T>* cur = root;
		Leaf<T>* prev = cur;

		while (cur != nullptr)
		{
			prev = cur;
			if (n_data < cur->data)
				cur = cur->left;
			else
				cur = cur->right;
		}
		cur = new Leaf<T>(n_data);
		if (n_data < prev->data)
			prev->left = cur;
		else
			prev->right = cur;
		cur->parent = prev;
		organize(cur);
	}

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
};

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<class T>
void BinaryTree<T>::push(T data)
{
	add(data, root);
	while (root->parent != nullptr)
		root = root->parent;
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
	Leaf<T>* old_parent = root;
	Leaf<T>* grand = root->parent;
	Leaf<T>* new_parent = root->left;
	new_parent->right = old_parent;
	grand->right = new_parent;
	new_parent->parent = grand;
	old_parent->parent = new_parent;
	old_parent->left = nullptr;

	return new_parent;
}

template<class T>
Leaf<T>* rotateRight(Leaf<T>* root)
{
	Leaf<T>* old_parent = root;
	Leaf<T>* grand = root->parent;
	Leaf<T>* new_parent = root->right;
	new_parent->left = old_parent;
	grand->left = new_parent;
	new_parent->parent = grand;
	old_parent->parent = new_parent;
	old_parent->right = nullptr;

	return new_parent;
	
}

template<class T>
Leaf<T>* bigRotateRight(Leaf<T>* root)
{
	Leaf<T>* new_root = root;
	Leaf<T>* old_root = root->parent;
	old_root->left = new_root->right;
	new_root->right = old_root;
	new_root->parent = old_root->parent;
	if (new_root->parent != nullptr)
		new_root->parent->left = new_root;
	old_root->parent = new_root;
	old_root->cl = RED;
	new_root->cl = BLACK;

	return new_root;
}

template<class T>
Leaf<T>* bigRotateLeft(Leaf<T>* root)
{
	Leaf<T>* new_root = root;
	Leaf<T>* old_root = root->parent;
	old_root->right = new_root->left;
	new_root->left = old_root;
	new_root->parent = old_root->parent;
	if (new_root->parent != nullptr)
	{
		new_root->parent->right = new_root;
		new_root->parent->cl = RED;
	}
	old_root->parent = new_root;
	old_root->cl = RED;
	new_root->cl = BLACK;

	return new_root;
}