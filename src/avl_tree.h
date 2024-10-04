#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

class AVLTree {
public:
    // Constructor
    AVLTree();

    // Destructor
    ~AVLTree();

    // Insert a node into the tree with a Gator ID and name
    void insert(const std::string& gatorIDStr, const std::string& name);

    // Remove a node from the tree using Gator ID
    void remove(const std::string& gatorIDStr);

    // Search for a student by name and print the associated Gator ID(s)
    void search(const std::string& name);

    // Print the tree in-order
    void printInOrder();

    // Remove node by in-order position
    void removeInorder(int position);

private:
    struct Node {
        std::string gatorID;  // Gator ID stored as a string to keep leading zeroes
        std::string name;
        int height;
        Node* left;
        Node* right;

        Node(const std::string& gID, const std::string& n) : gatorID(gID), name(n), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    Node* insertHelper(Node* node, const std::string& gatorIDStr, const std::string& name);
    Node* removeHelper(Node* node, const std::string& gatorIDStr);
    bool searchHelper(Node* node, const std::string& gatorIDStr);
    void searchByNameHelper(Node* node, const std::string& name, bool& found);
    void printInOrderHelper(Node* node, bool& isFirst);
    std::string inorderHelper(Node* node, int position, int& current);

    // AVL-specific helpers
    int height(Node* node);
    int getBalance(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);
    Node* minValueNode(Node* node);

    // Destructor helper
    void destroyTree(Node* node);

    // Helper function to validate Gator ID
    bool isValidGatorID(const std::string& gatorIDStr);

    // Helper function to validate names
    bool isValidName(const std::string& name);
};

#endif  // AVL_TREE_H
