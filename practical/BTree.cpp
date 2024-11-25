#include <iostream>
#include <vector>

class BTreeNode
{
public:
    std::vector<int> keys;             // Keys in the node
    std::vector<BTreeNode *> children; // Children pointers
    bool isLeaf;                       // True if node is a leaf
    int degree;                        // Minimum degree (defines the range for the number of keys)

    BTreeNode(int degree, bool isLeaf);
    void traverse();                      // Traverse the subtree rooted at this node
    BTreeNode *search(int k);             // Search for a key in the subtree
    void insertNonFull(int k);            // Insert key when node is not full
    void splitChild(int i, BTreeNode *y); // Split child y of this node
};

// Constructor
BTreeNode::BTreeNode(int degree, bool isLeaf)
{
    this->degree = degree;
    this->isLeaf = isLeaf;
}

// Function to traverse all keys in the subtree rooted at this node
void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < keys.size(); i++)
    {
        if (!isLeaf)
        {
            children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    if (!isLeaf)
    {
        children[i]->traverse();
    }
}

// Function to search for a key in the subtree rooted at this node
BTreeNode *BTreeNode::search(int k)
{
    int i = 0;
    while (i < keys.size() && k > keys[i])
    {
        i++;
    }
    if (i < keys.size() && keys[i] == k)
    {
        return this;
    }
    if (isLeaf)
    {
        return nullptr;
    }
    return children[i]->search(k);
}

// Function to insert a new key in the subtree rooted at this node
void BTreeNode::insertNonFull(int k)
{
    int i = keys.size() - 1;
    if (isLeaf)
    {
        keys.insert(keys.end(), k);
        while (i >= 0 && keys[i] > k)
        {

            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
        {
            i--;
        }
        if (children[i + 1]->keys.size() == 2 * degree - 1)
        {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k)
            {
                i++;
            }
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Function to split the child y of this node
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->degree, y->isLeaf);
    z->keys.resize(degree - 1);

    for (int j = 0; j < degree - 1; j++)
    {
        z->keys[j] = y->keys[j + degree];
    }

    if (!y->isLeaf)
    {
        z->children.resize(degree);
        for (int j = 0; j < degree; j++)
        {
            z->children[j] = y->children[j + degree];
        }
    }

    y->keys.resize(degree - 1);
    children.insert(children.begin() + i + 1, z);

    keys.insert(keys.begin() + i, y->keys[degree - 1]);
}

class BTree
{
private:
    BTreeNode *root;
    int degree;

public:
    BTree(int degree);
    void traverse();
    BTreeNode *search(int k);
    void insert(int k);
};

// Constructor
BTree::BTree(int degree)
{
    root = nullptr;
    this->degree = degree;
}

// Traverse the BTree
void BTree::traverse()
{
    if (root != nullptr)
    {
        root->traverse();
    }
    std::cout << std::endl;
}

// Search for a key in the BTree
BTreeNode *BTree::search(int k)
{
    return root == nullptr ? nullptr : root->search(k);
}

// Insert a key into the BTree
void BTree::insert(int k)
{
    if (root == nullptr)
    {
        root = new BTreeNode(degree, true);
        root->keys.push_back(k);
    }
    else
    {
        if (root->keys.size() == 2 * degree - 1)
        {
            BTreeNode *s = new BTreeNode(degree, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
            {
                i++;
            }
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}
int main()
{
    int degree;
    std::cout << "Enter the degree of the BTree: ";
    std::cin >> degree;

    BTree tree(degree);

    int choice, key;
    do
    {
        std::cout << "\n1. Insert\n2. Search\n3. Traverse\n4. Exit\nEnter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter key to insert: ";
            std::cin >> key;
            tree.insert(key);
            break;
        case 2:
            std::cout << "Enter key to search: ";
            std::cin >> key;
            if (tree.search(key))
            {
                std::cout << "Key " << key << " found in the tree.\n";
            }
            else
            {
                std::cout << "Key " << key << " not found.\n";
            }
            break;
        case 3:
            std::cout << "BTree traversal: ";
            tree.traverse();
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
