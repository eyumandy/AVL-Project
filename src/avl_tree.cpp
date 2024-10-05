#include "avl_tree.h"
#include <regex>
using namespace std;

// init avl tree
AVLTree::AVLTree() : root(nullptr) {}

// clean up memory
AVLTree::~AVLTree() {
  destroyTree(root);
}

// validate gator ID (must be 8 digits)
bool AVLTree::isValidGatorID(const string& gatorIDStr) {
  return gatorIDStr.size() == 8 && all_of(gatorIDStr.begin(), gatorIDStr.end(), ::isdigit);
}

// validate names (alphabet and space only)
bool AVLTree::isValidName(const string& name) {
  regex namePattern("^[A-Za-z ]+$");
  return regex_match(name, namePattern);
}

// insert into tree if valid
void AVLTree::insert(const string& gatorIDStr, const string& name) {
  if (!isValidGatorID(gatorIDStr) || !isValidName(name)) {
    cout << "unsuccessful\n";
    return;
  }
  if (searchHelper(root, gatorIDStr)) {
    cout << "unsuccessful\n";
  } else {
    root = insertHelper(root, gatorIDStr, name);
    cout << "successful\n";
  }
}

// remove node based on gator ID
void AVLTree::remove(const string& gatorIDStr) {
  if (!isValidGatorID(gatorIDStr)) {
    cout << "unsuccessful\n";
    return;
  }
  if (!searchHelper(root, gatorIDStr)) {
    cout << "unsuccessful\n";
  } else {
    root = removeHelper(root, gatorIDStr);
    cout << "successful\n";
  }
}

// search for nodes by name
void AVLTree::search(const string& name) {
  if (!isValidName(name)) {
    cout << "unsuccessful\n";
    return;
  }
  bool found = false;
  searchByNameHelper(root, name, found);
  if (!found) {
    cout << "unsuccessful\n";
  }
}

// search by name helper, recursive
void AVLTree::searchByNameHelper(Node* node, const string& name, bool& found) {
  if (node == nullptr) return;
  if (node->name == name) {
    cout << node->gatorID << endl;
    found = true;
  }
  searchByNameHelper(node->left, name, found);
  searchByNameHelper(node->right, name, found);
}

// helper for searching by gator ID
bool AVLTree::searchHelper(Node* node, const string& gatorIDStr) {
  if (node == nullptr) return false;
  if (gatorIDStr < node->gatorID) return searchHelper(node->left, gatorIDStr);
  if (gatorIDStr > node->gatorID) return searchHelper(node->right, gatorIDStr);
  return true;
}

// print tree in order, names only
void AVLTree::printInOrder() {
  bool isFirst = true;
  printInOrderHelper(root, isFirst);
  cout << endl;
}

// helper for in-order print
void AVLTree::printInOrderHelper(Node* node, bool& isFirst) {
  if (node != nullptr) {
    printInOrderHelper(node->left, isFirst);
    if (!isFirst) cout << ", ";
    cout << node->name;
    isFirst = false;
    printInOrderHelper(node->right, isFirst);
  }
}

// print tree in preorder, names only
void AVLTree::printPreorder() {
  bool isFirst = true;
  printPreorderHelper(root, isFirst);
  cout << endl;
}

// helper for preorder print
void AVLTree::printPreorderHelper(Node* node, bool& isFirst) {
  if (node != nullptr) {
    if (!isFirst) cout << ", ";
    cout << node->name;
    isFirst = false;
    printPreorderHelper(node->left, isFirst);
    printPreorderHelper(node->right, isFirst);
  }
}

// print tree in postorder, names only
void AVLTree::printPostorder() {
  bool isFirst = true;
  printPostorderHelper(root, isFirst);
  cout << endl;
}

// helper for postorder print
void AVLTree::printPostorderHelper(Node* node, bool& isFirst) {
  if (node != nullptr) {
    printPostorderHelper(node->left, isFirst);
    printPostorderHelper(node->right, isFirst);
    if (!isFirst) cout << ", ";
    cout << node->name;
    isFirst = false;
  }
}

// print number of levels in the tree
void AVLTree::printLevelCount() {
  cout << (root == nullptr ? 0 : height(root)) << endl;
}

// remove by position in in-order traversal
void AVLTree::removeInorder(int position) {
  int current = 0;
  string result = inorderHelper(root, position, current);
  cout << (result.empty() ? "unsuccessful\n" : "successful\n");
}

// recursive helper for in-order remove
string AVLTree::inorderHelper(Node* node, int position, int& current) {
  if (node == nullptr) return "";
  string left = inorderHelper(node->left, position, current);
  if (!left.empty()) return left;
  if (current == position) {
    string gatorID = node->gatorID;
    remove(gatorID);
    return gatorID;
  }
  current++;
  return inorderHelper(node->right, position, current);
}

// get node height
int AVLTree::height(Node* node) {
  return node == nullptr ? 0 : node->height;
}

// calculate balance factor
int AVLTree::getBalance(Node* node) {
  return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// rotate left
AVLTree::Node* AVLTree::rotateLeft(Node* node) {
  Node* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  node->height = 1 + max(height(node->left), height(node->right));
  newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
  return newRoot;
}

// rotate right
AVLTree::Node* AVLTree::rotateRight(Node* node) {
  Node* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  node->height = 1 + max(height(node->left), height(node->right));
  newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
  return newRoot;
}

// balance node based on balance factor
AVLTree::Node* AVLTree::balance(Node* node) {
  int balanceFactor = getBalance(node);
  if (balanceFactor > 1) {
    if (getBalance(node->left) < 0) node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balanceFactor < -1) {
    if (getBalance(node->right) > 0) node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

// helper for inserting into tree
AVLTree::Node* AVLTree::insertHelper(Node* node, const string& gatorIDStr, const string& name) {
  if (node == nullptr) return new Node(gatorIDStr, name);
  if (gatorIDStr < node->gatorID) node->left = insertHelper(node->left, gatorIDStr, name);
  else if (gatorIDStr > node->gatorID) node->right = insertHelper(node->right, gatorIDStr, name);
  else return node;
  node->height = 1 + max(height(node->left), height(node->right));
  return balance(node);
}

// helper for removing node
AVLTree::Node* AVLTree::removeHelper(Node* node, const string& gatorIDStr) {
  if (node == nullptr) return node;
  if (gatorIDStr < node->gatorID) node->left = removeHelper(node->left, gatorIDStr);
  else if (gatorIDStr > node->gatorID) node->right = removeHelper(node->right, gatorIDStr);
  else {
    if (node->left == nullptr || node->right == nullptr) {
      Node* temp = node->left ? node->left : node->right;
      if (temp == nullptr) node = nullptr;
      else *node = *temp;
      delete temp;
    } else {
      Node* temp = minValueNode(node->right);
      node->gatorID = temp->gatorID;
      node->name = temp->name;
      node->right = removeHelper(node->right, temp->gatorID);
    }
  }
  if (node == nullptr) return node;
  node->height = 1 + max(height(node->left), height(node->right));
  return balance(node);
}

// find node with minimum value
AVLTree::Node* AVLTree::minValueNode(Node* node) {
  Node* current = node;
  while (current && current->left != nullptr) current = current->left;
  return current;
}

// recursively delete tree nodes
void AVLTree::destroyTree(Node* node) {
  if (node == nullptr) return;
  destroyTree(node->left);
  destroyTree(node->right);
  delete node;
}
