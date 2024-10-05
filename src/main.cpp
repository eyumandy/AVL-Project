#include <iostream>
#include <string>
#include <vector>
#include "avl_tree.h"

using namespace std;

// split a string by spaces
vector<string> splitString(const string& str) {
  vector<string> tokens;
  string token;
  for (char ch : str) {
    if (ch == ' ') {
      if (!token.empty()) {
        tokens.push_back(token);  // store the token
        token.clear();
      }
    } else {
      token += ch;
    }
  }
  if (!token.empty()) tokens.push_back(token);  // add last token
  return tokens;
}

// remove quotes from a string
string removeQuotes(const string& str) {
  if (str.front() == '"' && str.back() == '"') {
    return str.substr(1, str.size() - 2);  // remove first and last characters (quotes)
  }
  return str;
}

int main() {
  AVLTree tree;
  int numCommands;
  string commandLine;

  // get number of commands
  cin >> numCommands;
  cin.ignore();  // handle newline

  for (int i = 0; i < numCommands; ++i) {
    getline(cin, commandLine);
    vector<string> commandParts = splitString(commandLine);

    // check the command type
    if (commandParts[0] == "insert") {
      string name = removeQuotes(commandParts[1]);
      string gatorID = commandParts[2];  // handle gatorID as string
      tree.insert(gatorID, name);  // call insert
    } else if (commandParts[0] == "remove") {
      string gatorID = commandParts[1];
      tree.remove(gatorID);
    } else if (commandParts[0] == "printInorder") {
      tree.printInOrder();
    } else if (commandParts[0] == "printPreorder") {
      tree.printPreorder();  // new command to print preorder
    } else if (commandParts[0] == "printPostorder") {
      tree.printPostorder();  // new command to print postorder
    } else if (commandParts[0] == "printLevelCount") {
      tree.printLevelCount();  // new command to print level count
    } else if (commandParts[0] == "removeInorder") {
      int position = stoi(commandParts[1]);  // convert position to int
      tree.removeInorder(position);
    } else if (commandParts[0] == "search") {
      string name = removeQuotes(commandParts[1]);
      tree.search(name);
    } else {
      cout << "unsuccessful" << endl;  // unknown command
    }
  }

  return 0;
}
