#include "avl_tree.h"
#include <regex>
using namespace std;

// constructor
AVLTree::AVLTree() {
  root = nullptr;
}

// destructor
AVLTree::~AVLTree() {
  destroyTree(root);
}

// validate Gator ID (must be 8 digits)
bool AVLTree::isValidGatorID(const string& gatorIDStr) {
  if (gatorIDStr.length() != 8)
    return false;
  for (char c : gatorIDStr) {
    if (!isdigit(c))
      return false;
  }
  return true;
}

// validate names (alphabet and space only)
bool AVLTree::isValidName(const string& name) {
  for (char c : name) {
    if (!isalpha(c) && c != ' ')
      return false;
  }
  return !name.empty();
}

// insert into tree if valid
void AVLTree::insert(const string& gatorIDStr, const string& name) {
  if (isValidGatorID(gatorIDStr) && isValidName(name)) {
    if (!searchHelper(root, gatorIDStr)) {
      root = insertHelper(root, gatorIDStr, name);
      cout << "successful\n";
      return;
    }
  }
  cout << "unsuccessful\n";
}

// remove node based on Gator ID
void AVLTree::remove(const string& gatorIDStr) {
  if (isValidGatorID(gatorIDStr)) {
    if (searchHelper(root, gatorIDStr)) {
      root = removeHelper(root, gatorIDStr);
      cout << "successful\n";
      return;
    }
  }
  cout << "unsuccessful\n";
}

// search for nodes by ID or name
void AVLTree::search(const string& key) {
  if (isValidGatorID(key)) {
    // Search by Gator ID
    Node* result = searchByGatorIDHelper(root, key);
    if (result) {
      cout << result->name << endl;
    } else {
      cout << "unsuccessful\n";
    }
  } else if (isValidName(key)) {
    // Search by Name
    bool found = false;
    searchByNameHelper(root, key, found);
    if (!found)
      cout << "unsuccessful\n";
  } else {
    cout << "unsuccessful\n";
  }
}

// helper for searching by Gator ID
AVLTree::Node* AVLTree::searchByGatorIDHelper(Node* node, const string& gatorIDStr) {
  if (node == nullptr)
    return nullptr;
  if (gatorIDStr < node->gatorID)
    return searchByGatorIDHelper(node->left, gatorIDStr);
  else if (gatorIDStr > node->gatorID)
    return searchByGatorIDHelper(node->right, gatorIDStr);
  else
    return node;
}

// helper for searching by name (pre-order traversal)
void AVLTree::searchByNameHelper(Node* node, const string& name, bool& found) {
  if (node != nullptr) {
    if (node->name == name) {
      cout << node->gatorID << endl;
      found = true;
    }
    searchByNameHelper(node->left, name, found);
    searchByNameHelper(node->right, name, found);
  }
}

// helper for searching by Gator ID (returns true if found)
bool AVLTree::searchHelper(Node* node, const string& gatorIDStr) {
  if (node == nullptr)
    return false;
  if (gatorIDStr < node->gatorID)
    return searchHelper(node->left, gatorIDStr);
  else if (gatorIDStr > node->gatorID)
    return searchHelper(node->right, gatorIDStr);
  else
    return true;
}

// print tree in-order, names only
void AVLTree::printInOrder() {
  bool first = true;
  printInOrderHelper(root, first);
  cout << endl;
}

// helper for in-order print
void AVLTree::printInOrderHelper(Node* node, bool& first) {
  if (node != nullptr) {
    printInOrderHelper(node->left, first);
    if (first) {
      cout << node->name;
      first = false;
    } else {
      cout << ", " << node->name;
    }
    printInOrderHelper(node->right, first);
  }
}

// print tree in preorder, names only
void AVLTree::printPreorder() {
  bool first = true;
  printPreorderHelper(root, first);
  cout << endl;
}

// helper for preorder print
void AVLTree::printPreorderHelper(Node* node, bool& first) {
  if (node != nullptr) {
    if (first) {
      cout << node->name;
      first = false;
    } else {
      cout << ", " << node->name;
    }
    printPreorderHelper(node->left, first);
    printPreorderHelper(node->right, first);
  }
}

// print tree in postorder, names only
void AVLTree::printPostorder() {
  bool first = true;
  printPostorderHelper(root, first);
  cout << endl;
}

// helper for postorder print
void AVLTree::printPostorderHelper(Node* node, bool& first) {
  if (node != nullptr) {
    printPostorderHelper(node->left, first);
    printPostorderHelper(node->right, first);
    if (first) {
      cout << node->name;
      first = false;
    } else {
      cout << ", " << node->name;
    }
  }
}

// print number of levels in the tree
void AVLTree::printLevelCount() {
  if (root == nullptr)
    cout << 0 << endl;
  else
    cout << height(root) << endl;
}

// remove by position in in-order traversal
void AVLTree::removeInorder(int position) {
  int currentIndex = 0;
  string res = inorderHelper(root, position, currentIndex);
  if (res.empty()) {
    cout << "unsuccessful\n";
  }
}

// helper for in-order remove
string AVLTree::inorderHelper(Node* node, int position, int& current) {
  if (node == nullptr)
    return "";
  string res = inorderHelper(node->left, position, current);
  if (!res.empty())
    return res;
  if (current == position) {
    string id = node->gatorID;
    remove(id);
    return id;
  }
  ++current;
  return inorderHelper(node->right, position, current);
}

// get node height
int AVLTree::height(Node* node) {
  if (node == nullptr)
    return 0;
  return node->height;
}

// calculate balance factor
int AVLTree::getBalance(Node* node) {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

// rotate left
AVLTree::Node* AVLTree::rotateLeft(Node* node) {
  Node* rightChild = node->right;
  node->right = rightChild->left;
  rightChild->left = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
  return rightChild;
}

// rotate right
AVLTree::Node* AVLTree::rotateRight(Node* node) {
  Node* leftChild = node->left;
  node->left = leftChild->right;
  leftChild->right = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
  return leftChild;
}

// balance node based on balance factor
AVLTree::Node* AVLTree::balance(Node* node) {
  int bf = getBalance(node);
  if (bf > 1) {
    if (getBalance(node->left) < 0)
      node->left = rotateLeft(node->left);
    return rotateRight(node);
  } else if (bf < -1) {
    if (getBalance(node->right) > 0)
      node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

// helper for inserting into tree
AVLTree::Node* AVLTree::insertHelper(Node* node, const string& gatorIDStr, const string& name) {
  if (node == nullptr)
    return new Node(gatorIDStr, name);
  if (gatorIDStr < node->gatorID)
    node->left = insertHelper(node->left, gatorIDStr, name);
  else if (gatorIDStr > node->gatorID)
    node->right = insertHelper(node->right, gatorIDStr, name);
  else
    return node;
  node->height = max(height(node->left), height(node->right)) + 1;
  return balance(node);
}

// helper for removing node
AVLTree::Node* AVLTree::removeHelper(Node* node, const string& gatorIDStr) {
  if (node == nullptr)
    return node;
  if (gatorIDStr < node->gatorID)
    node->left = removeHelper(node->left, gatorIDStr);
  else if (gatorIDStr > node->gatorID)
    node->right = removeHelper(node->right, gatorIDStr);
  else {
    if (node->left == nullptr || node->right == nullptr) {
      Node* temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        delete node;
        node = nullptr;
      } else {
        *node = *temp;
        delete temp;
      }
    } else {
      Node* temp = minValueNode(node->right);
      node->gatorID = temp->gatorID;
      node->name = temp->name;
      node->right = removeHelper(node->right, temp->gatorID);
    }
  }
  if (node == nullptr)
    return node;
  node->height = max(height(node->left), height(node->right)) + 1;
  return balance(node);
}

// find node with minimum value
AVLTree::Node* AVLTree::minValueNode(Node* node) {
  while (node->left != nullptr)
    node = node->left;
  return node;
}

// recursively delete tree nodes
void AVLTree::destroyTree(Node* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}
