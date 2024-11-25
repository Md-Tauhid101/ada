#include <iostream>
#include <map>
#include <string>
using namespace std;

// Node structure for Suffix Tree
struct SuffixTreeNode {
    map<char, SuffixTreeNode*> children; // Maps each character to its child node
    int start; // Starting index of the edge label
    int* end;  // Ending index of the edge label
    SuffixTreeNode* suffixLink; // Suffix link for fast traversal

    // Constructor
    SuffixTreeNode(int start, int* end) {
        this->start = start;
        this->end = end;
        this->suffixLink = nullptr;
    }
};

class SuffixTree {
    string text; // Input string
    SuffixTreeNode* root; // Root of the tree
    int remainingSuffixCount; // Number of suffixes to be added
    int* end; // Global end for leaf nodes
    int activeLength; // Length of the currently active edge
    int activeEdge; // Index of the current active edge
    SuffixTreeNode* activeNode; // Currently active node
    int leafEnd; // End index for all leaf nodes
    int size; // Size of the input string

    // Utility to create a new node
    SuffixTreeNode* newNode(int start, int* end) {
        return new SuffixTreeNode(start, end);
    }

    // Function to walk down the tree
    bool walkDown(SuffixTreeNode* currentNode) {
        int edgeLength = *(currentNode->end) - currentNode->start + 1;
        if (activeLength >= edgeLength) {
            activeEdge += edgeLength;
            activeLength -= edgeLength;
            activeNode = currentNode;
            return true;
        }
        return false;
    }

    // Extension function for each phase
    void extendSuffixTree(int pos) {
        leafEnd = pos; // Update the leaf end
        remainingSuffixCount++; // Increment the count of remaining suffixes
        SuffixTreeNode* lastNewNode = nullptr;

        // Loop until all suffixes are added
        while (remainingSuffixCount > 0) {
            if (activeLength == 0) activeEdge = pos; // Set active edge if no active length

            // Check if there's an edge starting with the current character
            if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
                // Create a new leaf node
                activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

                // Add a suffix link if a new internal node was created in the previous iteration
                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            } else {
                // There is an edge starting with the activeEdge character
                SuffixTreeNode* next = activeNode->children[text[activeEdge]];

                if (walkDown(next)) continue; // If active length > edge length, move to the next node

                // Check if the next character on the edge matches the current character
                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }
                    activeLength++;
                    break;
                }

                // Split the edge and create a new internal node
                int* splitEnd = new int(next->start + activeLength - 1);
                SuffixTreeNode* split = newNode(next->start, splitEnd);
                activeNode->children[text[activeEdge]] = split;

                // Create a new leaf node for the new character
                split->children[text[pos]] = newNode(pos, &leafEnd);

                // Update the existing child
                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            // Decrement the remainingSuffixCount
            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

public:
    // Constructor
    SuffixTree(string text) {
        this->text = text;
        size = text.size();
        root = newNode(-1, new int(-1));
        end = new int(-1);
        activeNode = root;
        activeLength = 0;
        activeEdge = -1;
        leafEnd = -1;
        remainingSuffixCount = 0;

        // Build the suffix tree
        for (int i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
    }

    // Function to print the suffix tree
    void printTree(SuffixTreeNode* node, int height) {
        if (node == nullptr) return;

        for (auto& child : node->children) {
            int start = child.second->start;
            int end = *(child.second->end);
            cout << text.substr(start, end - start + 1) << " at depth " << height << endl;
            printTree(child.second, height + 1);
        }
    }

    // Wrapper to print the tree
    void printTree() {
        printTree(root, 0);
    }
};

int main() {
    string text = "banana$"; // Input string with a terminator
    SuffixTree tree(text);

    // Print the suffix tree
    tree.printTree();
    return 0;
}
