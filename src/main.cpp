#include <iostream>
#include <string>
#include <vector>
#include "avl_tree.h"

using namespace std;

// Function to split a string by space without using istringstream
vector<string> splitString(const string& str) {
    vector<string> tokens;
    string token;

    for (char ch : str) {
        if (ch == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);  // Add token to the result if it's non-empty
                token.clear();
            }
        } else {
            token += ch;  // Append character to the current token
        }
    }

    // Add the last token
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to remove double quotes from a string
string removeQuotes(const string& str) {
    if (str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.size() - 2);  // Remove the first and last characters (quotes)
    }
    return str;  // Return the original string if no quotes are found
}

int main() {
    AVLTree tree;
    int numCommands;
    string commandLine;

    // Read the number of commands
    cin >> numCommands;
    cin.ignore();  // Ignore the newline character after the number of commands

    for (int i = 0; i < numCommands; ++i) {
        getline(cin, commandLine);
        vector<string> commandParts = splitString(commandLine);

        if (commandParts[0] == "insert") {
            // Insert command
            string name = removeQuotes(commandParts[1]);  // Remove quotes from the name if present
            string gatorID = commandParts[2];  // Treat Gator ID as a string
            tree.insert(gatorID, name);  // Insert both Gator ID and name
        } else if (commandParts[0] == "remove") {
            // Remove by Gator ID command
            string gatorID = commandParts[1];  // Treat Gator ID as a string
            tree.remove(gatorID);
        } else if (commandParts[0] == "printInorder") {
            // Print In-order command
            tree.printInOrder();
        } else if (commandParts[0] == "removeInorder") {
            // Remove node by in-order position
            int position = stoi(commandParts[1]);  // Position is still an integer
            tree.removeInorder(position);
        } else if (commandParts[0] == "search") {
            string name = removeQuotes(commandParts[1]);
            tree.search(name);  // Search by name
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}
