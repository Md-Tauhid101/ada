#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Node class for the suffix tree
class SuffixTreeNode {
public:
    map<char, SuffixTreeNode*> children;
    int start;
    int* end;
    
    // Constructor
    SuffixTreeNode(int start, int* end) {
        this->start = start;
        this->end = end;
    }
};

// Suffix Tree class
class SuffixTree {
private:
    string text;
    SuffixTreeNode* root;
    int size;
    
    // Creates a new node for the tree
    SuffixTreeNode* createNode(int start, int* end) {
        return new SuffixTreeNode(start, end);
    }

    // Insert the suffix into the suffix tree
    void insertSuffix(const string& suffix, int suffixStart) {
        SuffixTreeNode* currentNode = root;

        for (char c : suffix) {
            // If the current node doesn't have this character as a child, create a new child
            if (currentNode->children.find(c) == currentNode->children.end()) {
                currentNode->children[c] = createNode(suffixStart, nullptr);  // Leaf node for each suffix
            }

            // Move to the next node (child)
            currentNode = currentNode->children[c];
        }
    }

    // Recursively print the tree in a visually indented way
    void printTree(SuffixTreeNode* node, int level) {
        for (auto& child : node->children) {
            cout << string(level, ' ') << child.first << endl;
            printTree(child.second, level + 2);  // Increase indentation for children
        }
    }

public:
    // Constructor
    SuffixTree(const string& input) {
        text = input;
        size = input.size();
        root = createNode(-1, nullptr);  // Root node with no start or end

        // Insert all suffixes into the suffix tree
        for (int i = 0; i < size; i++) {
            string suffix = text.substr(i);
            insertSuffix(suffix, i);
        }
    }

    // Function to print all the suffixes
    void printSuffixes() {
        cout << "Suffixes:\n";
        for (int i = size - 1; i >= 0; i--) {
            cout << text.substr(i) << endl;
        }
    }

    // Function to display the suffix tree
    void displayTree() {
        cout << "\nSuffix Tree:\n";
        printTree(root, 0);
    }
};

// Main function
int main() {
    string text = "minimize";
    
    // Create the suffix tree
    SuffixTree tree(text);
    
    // Print all suffixes
    tree.printSuffixes();
    
    // Display the tree structure
    tree.displayTree();
    
    return 0;
}
