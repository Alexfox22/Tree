#include<iostream> 
#include<fstream>
#include <cstdlib> 
#include <conio.h>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <typeinfo>

using namespace std;

template <typename T>
struct Node {
	T key;
	shared_ptr<Node> left_ptr;
	shared_ptr<Node> right_ptr;
	void print()
	{
		cout << key << " ";
	}
};

template <typename T>
class Tree
{
protected:
	shared_ptr<Node<T>> root_ptr;
public:
	Tree()
	{
		root_ptr = nullptr;
	}

	virtual void Add(const Node<T>& node) = 0;

	virtual ~Tree() {}
};

template <typename T>
class Binary_tree : public Tree<T>
{
	using Tree<T>::root_ptr;

public:

	void Add(const Node<T>& node)
	{
		shared_ptr<Node<T>> new_ptr = make_shared<Node<T>>(node);
		new_ptr->left_ptr = nullptr;
		new_ptr->right_ptr = nullptr;
		if (root_ptr == nullptr)		//add root
		{
			root_ptr = new_ptr;
		}
		else
		{
			shared_ptr<Node<T>> cur_ptr = root_ptr;
			while ((cur_ptr->left_ptr != new_ptr) && (cur_ptr->right_ptr != new_ptr))		//while point isn't added
			{
				if (new_ptr->key < cur_ptr->key)		//if new point key less than existed point key, then go to the left
				{
					if (cur_ptr->left_ptr != nullptr)		
					{
						cur_ptr = cur_ptr->left_ptr;
						continue;
					}
					else
					{
						cur_ptr->left_ptr = new_ptr;
						break;
					}
				}
				if (new_ptr->key > cur_ptr->key)		//or go to the right
				{
					if (cur_ptr->right_ptr != nullptr)
					{
						cur_ptr = cur_ptr->right_ptr;
						continue;
					}
					else
					{
						cur_ptr->right_ptr = new_ptr;
						break;
					}
				}
				else break;			//if we met equal key point
			}
		}
	}

	void Breadth_first_search()
	{
		queue<shared_ptr<Node<T>>> q;
		shared_ptr<Node<T>> cur_ptr;
		q.push(root_ptr);
		while (!q.empty())
		{
			cur_ptr = q.front();
			q.pop();
			if (cur_ptr->left_ptr != nullptr)
			{
				q.push(cur_ptr->left_ptr);
			}
			if (cur_ptr->right_ptr != nullptr)
			{
				q.push(cur_ptr->right_ptr);
			}
			(*cur_ptr).print();
		}
	}

	void Depth_first_search()
	{
		stack<shared_ptr<Node<T>>> s;
		shared_ptr<Node<T>> cur_ptr;
		s.push(root_ptr);
		while (!s.empty())
		{
			cur_ptr = s.top();
			s.pop();
			if (cur_ptr->right_ptr != nullptr)
			{
				s.push(cur_ptr->right_ptr);
			}
			if (cur_ptr->left_ptr != nullptr)
			{
				s.push(cur_ptr->left_ptr);
			}
			(*cur_ptr).print();
		}
	}
};

int main()
{
	Binary_tree<int> tree;

	cout << "- Input tree or 0 to finish" << endl;
	int menu;
	cin >> menu;
	while (menu != 0)
	{
		Node<int> point;
		point.key = menu;
		tree.Add(point);
		cin >> menu;
	}

	cout << "1. Breadth_first_search" << endl << "2. Depth_first_search" << endl;
	cin >> menu;
	switch (menu)
	{
	case 1:
		tree.Breadth_first_search();
		cout << endl;
		break;
	case 2:
		tree.Depth_first_search();
		cout << endl;
		break;
	}
	system("pause");
	return 0;
}