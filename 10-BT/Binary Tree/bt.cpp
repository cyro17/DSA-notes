#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class node
{
public:
	int val;
	node *left;
	node *right;

	node(int d = 0)
	{
		this->val = d;
		this->left = nullptr;
		this->right = nullptr;
	}
};

node *new_node(int data)
{
	node *temp = new node(data);
	return temp;
}

node *create(int *arr, int i, int n)
{
	node *root;
	if (i < n)
	{
		root = new_node(arr[i]);
		root->left = create(arr, 2 * i + 1, n);
		root->right = create(arr, 2 * i + 2, n);
	}
	return root;
}

void bfs(node *root)
{
	queue<node *> q;
	q.push(root);
	q.push(nullptr);

	while (!q.empty())
	{
		node *temp = q.front();
		q.pop();

		if (temp == nullptr)
		{
			cout << endl;
			if (!q.empty())
				q.push(nullptr);
		}
		else
		{
			cout << temp->val << " ";
			if (temp->left)
			{
				q.push(temp->left);
			}
			if (temp->right)
			{
				q.push(temp->right);
			}
		}
	}
}

void inorder(node *root)
{
	if (root != nullptr)
	{
		inorder(root->left);
		cout << root->val << " ";
		inorder(root->right);
	}
}

vector<int> inorderTraversal(node *root)
{
	vector<int> res;
	stack<node *> s;

	while (root || s.empty() != false)
	{
		while (root)
		{
			s.push(root);
			root = root->left;
		}

		root = s.top();
		s.pop();
		res.push_back(root->val);
		root = root->right;
	}

	return res;
}

void postOrderTraversal(node *root)
{
	node *temp = new node;
	node *curr = root;
	vector<int> res;
	stack<node *> s;

	while (curr != nullptr || !s.empty())
	{
		if (curr != nullptr)
		{
			s.push(curr);
			curr = curr->left;
		}
		else
		{
			temp = s.top()->right;
			if (temp == nullptr)
			{
				temp = s.top();
				s.pop();
				cout << temp->val << " ";

				while (!s.empty() && temp == s.top()->right)
				{
					temp = s.top();
					s.pop();
					cout << temp->val << " ";
				}
			}
			else
				curr = temp;
		}
	}
}

void disp(vector<int> v)
{
	for (auto i : v)
		cout << i << " ";
}

int main()
{
	node *root = nullptr;
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	root = create(arr, 0, 7);

	cout << "postorder traversal" << endl;
	// cout << inorder(root) << endl;
	postOrderTraversal(root);
	return 0;
}