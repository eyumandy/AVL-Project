#include "avl_tree.h"
#include <regex>  // For regex validation of names

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Helper function to validate Gator ID
bool AVLTree::isValidGatorID(const std::string& gatorIDStr) {
    // Check if the string represents exactly 8 digits
    if (gatorIDStr.size() != 8 || !std::all_of(gatorIDStr.begin(), gatorIDStr.end(), ::isdigit)) {
        return false;
    }
    return true;
}

// Helper function to validate names (only alphabetic characters and spaces allowed)
bool AVLTree::isValidName(const std::string& name) {
    // Use regex to validate that the name contains only alphabetic characters and spaces
    std::regex namePattern("^[A-Za-z ]+$");
    return std::regex_match(name, namePattern);
}

// Insert a node into the tree
void AVLTree::insert(const std::string& gatorIDStr, const std::string& name) {
    if (!isValidGatorID(gatorIDStr) || !isValidName(name)) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    if (searchHelper(root, gatorIDStr)) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        root = insertHelper(root, gatorIDStr, name);
        std::cout << "successful" << std::endl;
    }
}

// Remove a node from the tree
void AVLTree::remove(const std::string& gatorIDStr) {
    if (!isValidGatorID(gatorIDStr)) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    if (!searchHelper(root, gatorIDStr)) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        root = removeHelper(root, gatorIDStr);
        std::cout << "successful" << std::endl;
    }
}

// Search by name and print Gator IDs
void AVLTree::search(const std::string& name) {
    if (!isValidName(name)) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    bool found = false;
    searchByNameHelper(root, name, found);
    if (!found) {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Helper function for searching by name
void AVLTree::searchByNameHelper(Node* node, const std::string& name, bool& found) {
    if (node == nullptr) return;

    if (node->name == name) {
        std::cout << node->gatorID << std::endl;
        found = true;
    }

    searchByNameHelper(node->left, name, found);
    searchByNameHelper(node->right, name, found);
}

// Search Helper function (recursive search in the tree by Gator ID)
bool AVLTree::searchHelper(Node* node, const std::string& gatorIDStr) {
    if (node == nullptr) {
        return false;
    }
    if (gatorIDStr < node->gatorID) {
        return searchHelper(node->left, gatorIDStr);
    } else if (gatorIDStr > node->gatorID) {
        return searchHelper(node->right, gatorIDStr);
    } else {
        return true;  // Found the node
    }
}

// Print In-Order (prints names instead of Gator IDs)
void AVLTree::printInOrder() {
    bool isFirst = true;  // Track whether it's the first element to avoid a leading comma
    printInOrderHelper(root, isFirst);
    std::cout << std::endl;
}

void AVLTree::printInOrderHelper(Node* node, bool& isFirst) {
    if (node != nullptr) {
        printInOrderHelper(node->left, isFirst);
        if (!isFirst) {
            std::cout << ", ";  // Print a comma before all elements except the first
        }
        std::cout << node->name;  // Print the name
        isFirst = false;  // Set to false after the first element is printed
        printInOrderHelper(node->right, isFirst);
    }
}

// Remove by in-order position
void AVLTree::removeInorder(int position) {
    int current = 0;
    std::string result = inorderHelper(root, position, current);
    if (result.empty()) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        std::cout << "successful" << std::endl;
    }
}

std::string AVLTree::inorderHelper(Node* node, int position, int& current) {
    if (node == nullptr) {
        return "";  // Invalid case
    }

    // Traverse the left subtree
    std::string left = inorderHelper(node->left, position, current);
    if (!left.empty()) return left;

    // Current node is the one we're looking for
    if (current == position) {
        std::string gatorID = node->gatorID;
        remove(gatorID);  // Remove the node
        return gatorID;
    }
    current++;

    // Traverse the right subtree
    return inorderHelper(node->right, position, current);
}

// AVL Tree Balancing Helpers
int AVLTree::height(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int AVLTree::getBalance(Node* node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = 1 + std::max(height(node->left), height(node->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = 1 + std::max(height(node->left), height(node->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    int balanceFactor = getBalance(node);

    // Left heavy
    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);  
        }
        return rotateRight(node); 
    }

    // Right heavy
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node); 
    }
    // Already balanced
    return node;  
}

AVLTree::Node* AVLTree::insertHelper(Node* node, const std::string& gatorIDStr, const std::string& name) {
    if (node == nullptr)
        return new Node(gatorIDStr, name);

    if (gatorIDStr < node->gatorID)
        node->left = insertHelper(node->left, gatorIDStr, name);
    else if (gatorIDStr > node->gatorID)
        node->right = insertHelper(node->right, gatorIDStr, name);
    else
        return node;  // Duplicate Gator IDs not allowed

    // Update height of the ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Balance the node
    return balance(node);
}

AVLTree::Node* AVLTree::removeHelper(Node* node, const std::string& gatorIDStr) {
    if (node == nullptr)
        return node;

    if (gatorIDStr < node->gatorID) {
        node->left = removeHelper(node->left, gatorIDStr);
    } else if (gatorIDStr > node->gatorID) {
        node->right = removeHelper(node->right, gatorIDStr);
    } else {
        // Node to be deleted found
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->gatorID = temp->gatorID;
            node->name = temp->name;
            node->right = removeHelper(node->right, temp->gatorID);
        }
    }

    if (node == nullptr)
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    return balance(node);
}

AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void AVLTree::destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
