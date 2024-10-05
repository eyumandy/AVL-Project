#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

class AVLTree {
public:
  AVLTree();  // constructor

  ~AVLTree();  // destructor

  // insert a new node with gatorID and name
  void insert(const string& gatorIDStr, const string& name);

  // remove node by gatorID
  void remove(const string& gatorIDStr);

  // search for a name or ID
  void search(const string& key);

  // print the tree in-order by names
  void printInOrder();

  // print the tree in preorder by names
  void printPreorder();

  // print the tree in postorder by names
  void printPostorder();

  // print the number of levels in the tree
  void printLevelCount();

  // remove a node by its in-order position
  void removeInorder(int position);

private:
  struct Node {
    string gatorID;
    string name;
    int height;
    Node* left;
    Node* right;

    // constructor for node
    Node(const string& gID, const string& n) : gatorID(gID), name(n), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root;  // root of the tree

  // helpers for insert, remove, search
  Node* insertHelper(Node* node, const string& gatorIDStr, const string& name);
  Node* removeHelper(Node* node, const string& gatorIDStr);
  bool searchHelper(Node* node, const string& gatorIDStr);
  void searchByNameHelper(Node* node, const string& name, bool& found);
  Node* searchByGatorIDHelper(Node* node, const string& gatorIDStr);
  void printInOrderHelper(Node* node, bool& isFirst);
  void printPreorderHelper(Node* node, bool& isFirst);
  void printPostorderHelper(Node* node, bool& isFirst);
  string inorderHelper(Node* node, int position, int& current);

  // AVL tree specific functions
  int height(Node* node);
  int getBalance(Node* node);
  Node* rotateLeft(Node* node);
  Node* rotateRight(Node* node);
  Node* balance(Node* node);
  Node* minValueNode(Node* node);

  // cleanup memory
  void destroyTree(Node* node);

  // validation helpers
  bool isValidGatorID(const string& gatorIDStr);
  bool isValidName(const string& name);
};

#endif  // AVL_TREE_H
