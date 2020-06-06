#include <iostream>
#include <conio.h>
#include <stack>
#include <queue>
#include <map>
#include <stdlib>  // qsort()
using namespace std;

typedef struct treeNode
{
	int value;
	struct treeNode* Lchild;
	struct treeNode* Rchild;
}node;

node* BuildTree(int* Arr, int no);
void CreateBST(node** bst, int no);
void Traverse(node* rt);
void Inorder(node* rt);
void Preorder(node* rt);
void Postorder(node* rt);
void LevelTraversal(node* rt);
void LevelWiseTraversal(node* rt);
void PrintSumAtEachLevel(node* rt);
void FindTotalLeaveNodes(node* rt);
void printPath(node* root, int path[], int pathlen);
void print(int path[], int pathlen);
void verticalSum(node* rt);
void verticalLine(int base, int hd, node* rt, vector<int>& sum);
bool FindPathSum(node* rt, int sum);
node* DeleteNode(node* rt, int val);


int main()
{
	
	int no;
	node* rt = NULL;
	int Arr[6] = {7,5,10,3,6,8};
	rt = BuildTree(Arr, 0);
	Traverse(rt);
	cout << endl;
	cout <<"Inorder : ";
	Inorder(rt);
	cout << endl;
	cout <<"Preorder : ";
	Preorder(rt);
	cout << endl;
	cout <<"Postorder :";
	Postorder(rt);
	cout << endl;
	LevelTraversal(rt);
	LevelWiseTraversal(rt);
	PrintSumAtEachLevel(rt);
	FindTotalLeaveNodes(rt);
	//print vertical path
	int path[10];
	printPath(rt, path, 0);
	cout << endl;

	// Print vertical sum
	verticalSum(rt);
	cout << endl;

	// sum of vertical path found in tree
	int sum = 0;
	cout<<"Sum Found or not ? : "<< FindPathSum(rt, sum);
	cout << endl;

	//Delete node from Tree
	node* temp = DeleteNode(rt,7);
	Inorder(rt);
	_getch();
	return 1;
}

node* BuildTree(int* Arr, int no)
{
	node* temp = NULL;
	int i = 0;
	if ( no < 6)
	{
		temp = (node*)malloc(sizeof(node));
		temp->Lchild = BuildTree(Arr,2*no+1);
		temp->value = Arr[no];
		temp->Rchild = BuildTree(Arr, 2 * no + 2);
	}

	return temp;
}

void CreateBST(node** bst, int no)
{
	if (*bst == NULL)
	{
		*bst = (node*)malloc(sizeof(node));
		(*bst)->value = no;
		(*bst)->Lchild = NULL;
		(*bst)->Rchild = NULL;
		return;
	}
	else
	{
		if ((*bst)->value > no )
			CreateBST(&((*bst)->Lchild), no);
		else
			CreateBST(&((*bst)->Rchild), no);
	}
}
//Inorder - Recursive method
void Inorder(node* root)
{
	node* temp = root;
	if (root == NULL)
		return;

	Traverse(root->Lchild);
	cout << root->value;
	Traverse(root->Rchild);
	
}

void Inorder(node* root)
{
	stack<node*> s;
	node* curr = root;
	while (curr != NULL || !s.empty())
	{
		if (curr != NULL)
		{
			s.push(curr);
			curr = curr->Lchild;
		}
		else if (curr == NULL && !s.empty())
		{
			node* temp = s.top();
			s.pop();
			cout << temp->value;
			curr = temp->Rchild;
		}
		else if (curr == NULL && s.empty())
		{
			break;
		}
	}
}

void Preorder(node* root)
{
	stack<node*> s;
	node* curr = root;
	s.push(root);

	while (!s.empty())
	{
		node* temp = s.top();
		s.pop();
		cout << temp->value;
		if(temp->Rchild != NULL)
			s.push(temp->Rchild);
		if (temp->Lchild != NULL)
			s.push(temp->Lchild);
	}
}

void Postorder(node* rt)
{
	stack<node*> s;
	
	node* troot = rt;
	do
	{
		while (troot != NULL)
		{
			if(troot->Rchild !=NULL)
				s.push(troot->Rchild);
			s.push(troot);
			troot = troot->Lchild;
		}

		troot = s.top();
		s.pop();

		if (troot->Rchild != NULL && !s.empty() && s.top() == troot->Rchild)
		{
			s.pop();
			s.push(troot);
			troot = troot->Rchild;
		}
		else
		{
			cout << troot->value;
			troot = NULL;
		}
	} while (!s.empty());
}

//Tree Traversal
//Size of Tree(no. of node in tree)?
//Find element in tree ?
//Find max / min element in tree ?
//Time complexity : O(n)
void LevelTraversal(node* rt)
{
	queue<node*> q;
	node* temp = rt;
	int sum = 0;
	while (temp != NULL)
	{
		cout << temp->value;
		//if(temp->Lchild != NULL)
			q.push(temp->Lchild);
		//if (temp->Rchild != NULL)
			q.push(temp->Rchild);

		if (!q.empty())
		{
			temp = q.front();
			q.pop();
			sum += 1;
		}
	}
	cout << endl;
	cout << "Total number of Nodes : " << sum<<endl;
}

//Marker at a level ? / Level Traversal ?
//http ://www.geeksforgeeks.org/given-binary-tree-print-nodes-two-given-level-numbers/
//Time complexity : O(n)
void LevelWiseTraversal(node* rt)
{
	if (rt == NULL)
		return;

	queue<node*> q;
	q.push(rt);

	while (1)
	{
		int nodecount = q.size();
		if (nodecount == 0)
			break;

		while (nodecount > 0)
		{
			node* temp = q.front();
			cout << temp->value;
			q.pop();

			if (temp->Lchild != NULL)
				q.push(temp->Lchild);
			if (temp->Rchild != NULL)
				q.push(temp->Rchild);

			nodecount--;
		}
		cout << endl;
	}
}

//Print sum of nodes at each level.
//Print '\n' at each level.
//Heilght of tree ?
//Find the deepest node in the tree ?----------------------------
//Hint-Check in last level, you will gwt deepest node in the tree 
//---------------------------------------------------------------
//Time Complexity : O(n)
void PrintSumAtEachLevel(node* rt)
{
	if (rt == NULL)
		return;

	queue<node*> q;
	q.push(rt);
	int levelcount = 0;
	while (1)
	{
		int nodecount = q.size();
		if (node count == 0)
			break;
		int sum = 0;
		
		while (nodecount > 0)
		{
			node* temp = q.front();
			q.pop();
			sum += temp->value;

			if (temp->Lchild)
				q.push(temp->Lchild);

			if (temp->Rchild)
				q.push(temp->Rchild);

			nodecount--;
			
		}
		levelcount++;
		cout << levelcount << " : " << sum<<"\t";
	}
	cout << endl;
	cout <<"Height of the Tree : "<< levelcount<<endl;
}

//Find number of leave nodes
//Find number of full nodes in tree ?
void FindTotalLeaveNodes(node* rt)
{
	if (rt == NULL)
		return;
	queue<node*> q;
	q.push(rt);
	int total = 0;
	cout << endl;
	while (!q.empty())
	{
		node* temp = q.front();
		q.pop();
		if (temp->Lchild == NULL && temp->Rchild == NULL)
		{
			cout << temp->value <<"\t";
			total += 1;
		}

		if (temp->Lchild)
			q.push(temp->Lchild);
		if (temp->Rchild)
			q.push(temp->Rchild);
	}

}

//Print all root leave paths.
void printPath(node* root, int path[], int pathlen)
{
	path[pathlen] = root->value;
	pathlen++;

	if (root->Lchild == NULL && root->Rchild == NULL )
	{
		cout << endl;
		print(path, pathlen);
		return;
	}
	//path[pathlen] = root->value;
	else
	{
		if (root->Lchild != NULL)
			printPath(root->Lchild, path, pathlen);
		if (root->Rchild != NULL)
			printPath(root->Rchild, path, pathlen);
	}
}
 
void print(int path[], int pathlen)
{
	int i = 0;
	while (i < pathless)
		cout << path[i++];
	cout << endl;
}

//Vertical sum of given binary tree :
void verticalSum(node* rt)
{
	if (!rt) return;

	int l = 0, r = 0;
	node* temp = rt;

	while (temp->Child)
	{
		--l;
		temp = temp->Lchild;
	} 
	temp = rt;
	while (temp->Rchild)
	{
		++r;
		temp = temp->Rchild;
	}
	int i;
	
	for (i = l; i <= r; i++)
	{
		vector<int> sum;
		cout << endl << i - l + 1;
		verticalLine(0, i, rt,sum);
		if (sum.size() > 0)
		{
			int i = 0;
			int s = 0;
			while (i < sum.size())
			{
				s += sum[i++];
			}
			cout << s;
		}
		
	}
}

void verticalLine(int base, int hd, node* rt, vector<int>& sum)
{
	
	if (!rt) return;
	
	int r;
	verticalLine(base - 1, hd, rt->Lchild,sum);
	if (base == hd)
	{
		//cout << rt->value<<" ";
		sum.push_back(rt->value);
	}
	
	verticalLine(base + 1, hd, rt->Rchild,sum);

}

bool FindPathSum(node* rt, int sum)
{
	//int sum = 0;
	if (rt != NULL)
	{
		sum = sum + rt->value;
		if (rt->Lchild == NULL && rt->Rchild == NULL)
		{
			if (sum == 6)
				return true;
			sum = 0;
		}

		FindPathSum(rt->Lchild, sum);
		FindPathSum(rt->Rchild, sum);
	}
 
	return false;
}

node* DeleteNode(node* rt, int val)
{
	if (rt==NULL) return rt;
	
	if (rt->value > val)
		rt->Lchild = DeleteNode(rt->Lchild, val);
	else if (rt->value < val)
		rt->Rchild = DeleteNode(rt->Rchild, val);
	else
	{
		if (!rt->Lchild && !rt->Rchild)
		{
			rt = NULL;
			return rt;
		}
		//One child 
        	else if(root->right == NULL)
        	{
           	 Node* temp = root;
           	 root= root->left;
           	 delete temp;
        	}
        	else if(root->left == NULL)
        	{
           	 Node* temp = root;
           	 root= root->right;
           	 delete temp;
        	}
		
		node* temp = rt->Rchild;
		while (temp->Lchild)
		{
			tempParent = temp;
			temp = temp->Lchild;
		}
			
		rt->value = temp->value;
			
		rt->Rchild = DeleteNode(tempParent, temp->value);		
	}
	return rt;
}

/*
Least common ancestor? - O(n)
	http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
int FindLCA(node* rt, int n1, int n2)
{
	if(!rt) return;
	
	vector<int> path1, path2;
	
	if( !FindPath(rt,path1,n1) || !FindPath(rt,path2,n2))
		return -1;
		
	int i;
	for(i=0; i<path1.size() && i<path2.size(); i++)
	{
		if(path1[i] != path2[i])
			break;
	}
	return path1[i-1];
}

bool FindPath(node* rt, vector<int> path, int n)
{
	if(!rt) return;
	path.push_back(rt->value);
	
	if(rt->value == n)
		return true;
	
	if(rt->left && FindPath(rt->left,path,n) ||
	   rt->right && FindPath(rt->right,path,n))
		return true;
	
	path.pop_back();
	return false;
}
*/

/*
Find all the ancestor of the node?
	http://www.geeksforgeeks.org/print-ancestors-of-a-given-node-in-binary-tree/
	http://www.geeksforgeeks.org/print-ancestors-of-a-given-binary-tree-node-without-recursion/
Check if two nodes are cousins in a Binary Tree
	http://www.geeksforgeeks.org/check-two-nodes-cousins-binary-tree/
bool isCousin(node* rt, node* n1, node* n2)
	{
		if(!rt) return 0;
		
		if(level(rt,n1,1) == level(rt,n2,1) && !isSubling(rt,n1,n2))
			return true;
		return false;
	}

//Level, compare with node value
int getLevel_1(node* rt, int n, int l)
{
	if(rt == NULL)
		return l;
	if(rt->data == n)
		return l;
	
	getLevel_1(rt->left, n, l+1);
	getLevel_1(rt->right, n, l+1);
}
	
int level(node* rt, node* n, int lev)
	{
		if(!rt) return 0;
		if(rt == n) return lev;
		
		int l = level(rt->left,n,lev+1);
		if(l != 0) retun l;
		
		return level(rt->right,n,lev+1);
	}
	
bool isSubling(node* rt, node*n1, node* n2)
{
	if(!rt) return false;
	
	if((rt->left == n1 && rt->right == n2) ||
		(rt->left == n2 && rt->right == n1) ||
		isSibling(rt->left, n1,n2) ||
		isSibling(rt->right,n1,n2))
		return true;
	else
		return false;
}	
*/

/*
Vertical sum of given binary tree:
verticalSum(node* rt)
{
	if(!rt) return;
	
	int l=0, r=0;
	node* temp = rt;
	
	while(temp->left)
		{
			--l;
			temp = temp->left;
		}
	temp = rt;
	while(temp->right)
		{
			++r;
			temp = temp->right;
		}
	int i;
	for(i=l; i<=r; i++)
	{
		cout<<i-l+1<<;
		verticalLine(0,i,rt);
	}
}	

verticalLine(int base, int hd, node* rt)
{
	if(!rt) return;
	
	verticalLine(base-1, hd, rt->left);
	if(base==hd) cout<<rt->value;
	verticalLine(base+1, hd, rt->right);
}
*/

/*
Create mirror tree:
/* Change a tree so that the roles of the  left and  
    right pointers are swapped at every node. 
  
 So the tree... 
       4 
      / \ 
     2   5 
    / \ 
   1   3 
  
 is changed to... 
       4 
      / \ 
     5   2 
        / \ 
       3   1 

void mirror(struct Node* node)  
{ 
  if (node==NULL)  
    return;   
  else 
  { 
    struct Node* temp; 
      
    /* do the subtrees */
    mirror(node->left); 
    mirror(node->right); 
  
    /* swap the pointers in this node */
    temp        = node->left; 
    node->left  = node->right; 
    node->right = temp; 
  } 
}
*/

/*
Clone of tree
node  *clone( root ) : 
   if (root == NULL ) : return root;
 
   //create new node and make it a copy of node pointed by root
   node *temp = (node *)malloc(sizeof(node)) ;
   temp->data = root-> data;    //copying data
   temp->left = clone(root -> left);    //cloning left child
   temp->right = clone(root -> right);  //cloning right child
   return temp;

*/



/*
int height(struct node* node)
{
   // base case tree is empty
   if(node == NULL)
       return 0;
 
   //If tree is not empty then height = 1 + max of left 
   //height and right heights   
   return 1 + max(height(node->left), height(node->right));
}
*/

//AVL TREE
How to handle duplicates in binary search tree
https://www.quora.com/Does-a-binary-search-tree-allow-a-duplicate-vertex

// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 
  
// An AVL tree node 
struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
  
// A utility function to get maximum of two integers 
int max(int a, int b); 
  
// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+h1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree roted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int key) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->  = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
       /* return the (unchanged) node pointer */
    return node; 
} 
  
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 
  
/* Drier program to test above function*/
int main() 
{ 
  struct Node *root = NULL; 
  
  /* Constructing tree given in the above figure */
  root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25); 
  
  /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
  */
  
  printf("Preorder traversal of the constructed AVL"
         " tree is \n"); 
  preOrder(root); 
  
  return 0; 
} 

//B- TREE
//RED BLACK TREE


//Huffman coding
Huffman tree


