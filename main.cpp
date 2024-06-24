#include <iostream>
#include <cstdlib>
using namespace std;
class BinarySearchTree
{
private:
    class node
    {
    public:
        node* left;
        node* right;
        node* parent;
        int key;
        string data;
    };
public:
    node* root;
    BinarySearchTree()
    {
        root = NULL;
    }
    bool isEmpty() const { return root == NULL; }
    void INORDER_TREE_WALK(node*);
    void TREE_INSERT(int );
    void PREORDER_TREE_WALK(node* x);
    void POSTORDER_TREE_WALK(node* x);
    node* MAXIMUM(node* x);
    void REMOVEMAX(node* &x);
    node* MINIMUM(node* x);
    node* SUCCESSOR(node* x);
    node* TREEDELETE(int key);
};

void BinarySearchTree::TREE_INSERT(int d)
{
    node* z = new node();
    z->key = d;
    z->left = NULL;
    z->right = NULL;
    node* y = NULL;
    node* x = root;
    node* parent = NULL;
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    parent = y;
    if (y == NULL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
        if (x->left) INORDER_TREE_WALK(x->left);
        cout << " " << x->key << " ";
        if (x->right) INORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::PREORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
        cout<<x->key<<endl;
        PREORDER_TREE_WALK(x->left);
        PREORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::POSTORDER_TREE_WALK(node* x)
{
    if (x != NULL)
    {
        POSTORDER_TREE_WALK(x->left);
        POSTORDER_TREE_WALK(x->right);
        cout<<x->key<<endl;
    }
}

BinarySearchTree::node* BinarySearchTree::MAXIMUM(node* x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

void BinarySearchTree::REMOVEMAX(node* &x) {
    if (x != NULL) {
        node *maxNode = MAXIMUM(x);
        if (maxNode->parent != NULL) {
            if (maxNode->parent->right == maxNode) {
                maxNode->parent->right = maxNode->left;
            } else {
                maxNode->parent->left = maxNode->left;
            }
        } else {
            root = maxNode->left;
        }
        if (maxNode->left != NULL) {
            maxNode->left->parent = maxNode->parent;
        }
        delete maxNode;
    }
    else {
        return;
    }
}

BinarySearchTree::node* BinarySearchTree::MINIMUM(node* x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

BinarySearchTree::node* BinarySearchTree::SUCCESSOR(node* x){
    if (x == NULL)
        return NULL;
    if(x->right!=NULL){
        return MINIMUM(x->right);
    }
    node* successor = NULL;
    node* current = root;
    while (current != NULL)
    {
        if (x->key < current->key)
        {
            successor = current;
            current = current->left;
        }
        else if (x->key > current->key)
        {
            current = current->right;
        }
        else
        {
            break;
        }
    }
    return successor;
}

BinarySearchTree::node* BinarySearchTree::TREEDELETE(int key)
{
    node* current = root;
    node* parent = nullptr;
    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (current == nullptr) {
        cout << "Node with key " << key << " not found." << endl;
        return root;
    }
    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            delete current;
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    }
    else if (current->left == nullptr || current->right == nullptr) {
        node* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    }
    else {
        node* successor = current->right;
        parent = nullptr;
        while (successor->left != nullptr) {
            parent = successor;
            successor = successor->left;
        }
        current->key = successor->key;
        current->data = successor->data;
        if (parent == nullptr) {
            current->right = successor->right;
        } else {
            parent->left = successor->right;
        }
        delete successor;
    }
    return root;
}


int main()
{
    BinarySearchTree bst;
    int choice, key;
    while (true)
    {
        cout << endl << endl;
        cout << " Binary Search Tree Example " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insertion " << endl;
        cout << " 2. In-Order Traversal " << endl;
        cout << " 3. Pre-Order Traversal " << endl;
        cout << " 4. Post-Order Traversal " << endl;
        cout << " 5. Find Maximum " << endl;
        cout << " 6. Remove Maximum " << endl;
        cout << " 7. Find Minimum " << endl;
        cout << " 8. Find Successor " << endl;
        cout << " 9. Delete a node " << endl;
        cout << " 10. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
            case 2:
                cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            case 3:
                cout << endl;
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
            case 4:
                cout << endl;
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
            case 5:
                if (!bst.isEmpty()) {
                    auto maxNode = bst.MAXIMUM(bst.root);
                    cout << " Maximum key: " << maxNode->key << endl;
                } else {
                    cout << " The tree is empty." << endl;
                }
                break;
            case 6:
                bst.REMOVEMAX(bst.root);
                cout << " Maximum node removed." << endl;
                break;
            case 7:
                if (!bst.isEmpty()) {
                    auto minNode = bst.MINIMUM(bst.root);
                    cout << " Minimum key: " << minNode->key << endl;
                } else {
                    cout << " The tree is empty." << endl;
                }
                break;
            case 8:
                cout << " Enter key to find the successor of: ";
                cin >> key;
                {
                    auto current = bst.root;
                    while (current != NULL && current->key != key) {
                        if (key < current->key)
                            current = current->left;
                        else
                            current = current->right;
                    }
                    if (current != NULL) {
                        auto successor = bst.SUCCESSOR(current);
                        if (successor != NULL) {
                            cout << " Successor of " << key << " is " << successor->key << endl;
                        } else {
                            cout << " No successor found for " << key << endl;
                        }
                    } else {
                        cout << " Node with key " << key << " not found." << endl;
                    }
                }
                break;
            case 9:
                cout << " Enter key to delete: ";
                cin >> key;
                {
                    auto deletedNode = bst.TREEDELETE(key);
                }
                break;
            case 10:
                system("pause");
                return 0;
            default:
                cout << "Invalid choice";
        }
    }
}

