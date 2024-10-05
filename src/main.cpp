#include <iostream>
#include <string>
#include <vector>
#include "avl_tree.h"

using namespace std;

// split a string by spaces, respecting quoted substrings
vector<string> splitString(const string& str) {
  vector<string> tokens;
  bool inQuotes = false;
  string token;
  
  for (size_t i = 0; i < str.size(); ++i) {
    char ch = str[i];
    if (ch == '"') {
      inQuotes = !inQuotes;
      token += ch;  // include quotes in the token
    } else if (ch == ' ' && !inQuotes) {
      if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
    } else {
      token += ch;
    }
  }
  if (!token.empty()) {
    tokens.push_back(token);
  }
  return tokens;
}

// remove quotes from a string
string removeQuotes(const string& str) {
  if (!str.empty() && str.front() == '"' && str.back() == '"') {
    return str.substr(1, str.length() - 2);
  }
  return str;
}

// function to map command strings to integer codes
int getCommandCode(const string& cmd) {
  if (cmd == "insert") return 1;
  if (cmd == "remove") return 2;
  if (cmd == "search") return 3;
  if (cmd == "printInorder") return 4;
  if (cmd == "printPreorder") return 5;
  if (cmd == "printPostorder") return 6;
  if (cmd == "printLevelCount") return 7;
  if (cmd == "removeInorder") return 8;
  return -1;  // unknown command
}

int main() {
  AVLTree tree;
  int numCommands;
  string line;

  // read number of commands
  if (!(cin >> numCommands)) return 1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int count = 0; count < numCommands; ++count) {
    getline(cin, line);
    vector<string> commandParts = splitString(line);

    if (commandParts.empty()) {
      cout << "unsuccessful" << endl;
      continue;
    }

    const string& cmd = commandParts[0];
    int cmdCode = getCommandCode(cmd);

    switch (cmdCode) {
      case 1: {  // insert
        if (commandParts.size() >= 3) {
            string nameWithQuotes = commandParts[1];
            // check if the name is enclosed in double quotes
            if (nameWithQuotes.front() == '"' && nameWithQuotes.back() == '"') {
            string name = removeQuotes(nameWithQuotes);
            string gatorID = commandParts[2];
            tree.insert(gatorID, name);
            } else {
            cout << "unsuccessful" << endl;  // name not enclosed in quotes
            }
        } else {
            cout << "unsuccessful" << endl;
        }
        break;
        }
      case 2: {  // remove
        if (commandParts.size() >= 2) {
          tree.remove(commandParts[1]);
        } else {
          cout << "unsuccessful" << endl;
        }
        break;
      }
      case 3: {  // search
        if (commandParts.size() >= 2) {
          string searchTerm = commandParts[1];
          if (searchTerm.front() == '"' && searchTerm.back() == '"') {
            // Search by name
            string name = removeQuotes(searchTerm);
            tree.search(name);
          } else {
            // Search by Gator ID
            string gatorID = searchTerm;
            tree.search(gatorID);
          }
        } else {
          cout << "unsuccessful" << endl;
        }
        break;
      }
      case 4: {  // printInorder
        tree.printInOrder();
        break;
      }
      case 5: {  // printPreorder
        tree.printPreorder();
        break;
      }
      case 6: {  // printPostorder
        tree.printPostorder();
        break;
      }
      case 7: {  // printLevelCount
        tree.printLevelCount();
        break;
      }
      case 8: {  // removeInorder
        if (commandParts.size() >= 2) {
          int position = stoi(commandParts[1]);
          tree.removeInorder(position);
        } else {
          cout << "unsuccessful" << endl;
        }
        break;
      }
      default: {
        cout << "unsuccessful" << endl;
        break;
      }
    }
  }

  return 0;
}
