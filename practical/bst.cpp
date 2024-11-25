#include <iostream>
using namespace std;

// Define a Node structure
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Define a Binary Search Tree class
class BinarySearchTree {
private:
    TreeNode* root;

    // Helper function to insert a node recursively
    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Helper function to search a value recursively
    bool search(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (node->value == value) {
            return true;
        }
        if (value < node->value) {
            return search(node->left, value);
        }
        return search(node->right, value);
    }

    // Helper function for in-order traversal
    void inOrder(TreeNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a value into the BST
    void insert(int value) {
        root = insert(root, value);
    }

    // Search for a value in the BST
    bool search(int value) {
        return search(root, value);
    }

    // Print the BST in in-order traversal
    void inOrderTraversal() {
        inOrder(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;
    int choice, value;

    do {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Display (In-order Traversal)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            bst.insert(value);
            cout << "Value inserted.\n";
            break;
        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (bst.search(value)) {
                cout << "Value " << value << " found in the tree.\n";
            } else {
                cout << "Value " << value << " not found.\n";
            }
            break;
        case 3:
            cout << "In-order traversal of the tree: ";
            bst.inOrderTraversal();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
