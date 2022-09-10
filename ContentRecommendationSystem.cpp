#include <bits/stdc++.h>
using namespace std;
 
// A tree node 
class node
{
    public:
    float key;
    vector<string>list;
    node *left, *right;
};
 
/* Helper function that allocates
a new node with the given key and
    NULL left and right pointers. */
node* newNode(float key)
{
    node* Node = new node();
    Node->key = key;
    Node->left = Node->right = NULL;
    return (Node);
}
 
// A utility function to right
// rotate subtree rooted with y

node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
 
// A utility function to left
// rotate subtree rooted with x

node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
// This function brings the key at
// root if key is present in tree.
// If key is not present, then it
// brings the last accessed item at
// root. This function modifies the
// tree and returns the new root
node *splay(node *root, float key)
{
    // Base cases: root is NULL or
    // key is present at root
    if (root == NULL || root->key == key)
        return root;
 
    // Key lies in left subtree
    if (root->key > key)
    {
        // Key is not in tree, we are done
        if (root->left == NULL) return root;
 
        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the
            // key as root of left-left
            root->left->left = splay(root->left->left, key);
 
            // Do first rotation for root,
            // second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            // First recursively bring
            // the key as root of left-right
            root->left->right = splay(root->left->right, key);
 
            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
 
        // Do second rotation for root
        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == NULL) return root;
 
        // Zig-Zag (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);
 
            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of
            // right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
 
        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}
 
// Function to insert a new key k
// in splay tree with given root
node *insert(node *root, float k,string name,unordered_map<string,float>&hashTable)
{
    // Simple Case: If tree is empty
    hashTable[name]=k;
    if (root == NULL) return newNode(k);
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    if (root->key == k)
    {
        root->list.push_back(name);
        return root;
    } 
 
    // Otherwise allocate memory for new node
    node *newnode = newNode(k);
    newnode->list.push_back(name);
 
    // If root's key is greater, make
    // root as right child of newnode
    // and copy the left child of root to newnode
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make
    // root as left child of newnode
    // and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode; // newnode becomes new root
}
node *search(node *root, int key)
{
    return splay(root, key);
}
 
// A utility function to print
// Levelorder traversal of the tree.

void LevelOrder(node *root)
{
    if(!root )return ;
    queue<node*>q;
    q.push(root);
    while(!q.empty())
    {
        int queuesize=q.size();
        for(int i=0;i<queuesize;i++)
        {
            node* front=q.front();
            q.pop();
            cout<<front->key<<" -> ";
            for(auto it:front->list) cout<<"  "<<it;
            if(front->left) q.push(front->left);
            if(front->right) q.push(front->right);

        }
        cout<<endl;

    }
}
void genrepredictor(string name,vector<int>rating,unordered_map<string,float>&hashTable)
{
    int size=rating.size();
    float result;
    int sum=accumulate(rating.begin(),rating.end(),0);
    result=sum/size;
    hashTable[name]=result;
}
vector<int> rating()
{
    int vote;
    vector<int>ViewersChoice;
    for(int i=0;i<100;i++)
    {
        cin>>vote;
        ViewersChoice.push_back(vote);
    }
    return ViewersChoice;
}
/* Driver code*/
int main()
{
    cout<<"Absolute Ratings"<<endl;
    cout<<"Action  : 1"<<"  "<<"Crime   : 2"<<"  "<<" Thriller : 3"<<"  "<<"Mystery : 4"<<"  "<<endl;
    cout<<"Horror  : 5"<<"  "<<"Comedy  : 6"<<"  "<<" Romance  : 7"<<"  "<<"Drama   : 8"<<"  "<<endl;
    cout<<"Fantasy : 9"<<"  "<<"Science : 10"<<"  "<<"Fiction : 11"<<endl;
   unordered_map<string,float>hashTable;
    node *root=new node();
    root->key=7.3;
    root->list.push_back("LaLa Land");
    root->right=NULL;
    root->left=NULL;
    root=insert(root,7.8,"Titanic",hashTable);
    root=insert(root,3.9,"It",hashTable);
    root=insert(root,4.6,"Lights Out",hashTable);
    root=insert(root,4.8,"Conjuring",hashTable);
    root=insert(root,6.1,"BigBang Theory",hashTable);
    root=insert(root,6.4,"Two And Half Men",hashTable);
    root=insert(root,3.8,"Journey to the Center of the earth",hashTable);
    root=insert(root,3.9,"Jumanji",hashTable);
    root=insert(root,10.2,"Gravity",hashTable);
    root=insert(root,10.8,"InterStellar",hashTable);
    root=insert(root,10.7,"Inception",hashTable);
    root=insert(root,11,"Tomorrow's war",hashTable);
    root=insert(root,10.4,"Independence Day",hashTable);
    root=insert(root,8.7,"Her",hashTable);
    root=insert(root,8.6,"Moana",hashTable);
    root=insert(root,1.7,"Mission Impossible",hashTable);
    root=insert(root,1.2,"Batman Begins",hashTable);

    cout<<"Searching operation begins"<<endl;
    string searchname;
    int searchkey;
    cout<<"Enter the movie name to be searched"<<endl;
    cin>>searchname;
    if(hashTable.find(searchname)!=hashTable.end())
    {
        int key=hashTable[searchname];
       root= search(root,key);
        LevelOrder(root);
    }
    else{
        cout<<"No such thing exists"<<endl;
    }
    LevelOrder(root);
    return 0;
}