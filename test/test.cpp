// #include "catch/catch_amalgamated.hpp"
// #include "../src/avl_tree.h"
// #include <sstream>
// #include <map>
// #include <string>
// #include <vector>
// #include <algorithm>

// using namespace std;

// // Test for incorrect command formats
// TEST_CASE("Test incorrect command formats", "[incorrect_commands]") {
//     AVLTree tree;
//     stringstream buffer;
//     streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());  // Redirect cout

//     // Invalid name
//     SECTION("Insert command with invalid name") {
//         tree.insert("45679999", "");  // Empty name
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");

//         tree.insert("45679999", "InvalidName!@#");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Invalid Gator ID
//     SECTION("Insert command with invalid Gator ID") {
//         tree.insert("1234567", "Brandon");  // Less than 8 digits
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");

//         tree.insert("100000000", "Brandon");  // More than 8 digits
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Remove with invalid Gator ID
//     SECTION("Remove command with invalid Gator ID") {
//         tree.remove("1234567");  // Less than 8 digits
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");

//         tree.remove("100000000");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Invalid RemoveInorder positions
//     SECTION("RemoveInorder command with invalid position") {
//         tree.removeInorder(-1);  // Negative in-order position
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");

//         tree.removeInorder(0);  // Zero in-order position
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Search with invalid Gator ID
//     SECTION("Search command with invalid Gator ID") {
//         tree.search("1234567");  // Less than 8 digits
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");

//         tree.search("100000000");  // More than 8 digits
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     cout.rdbuf(oldCoutBuffer);  // Restore original cout buffer
// }

// // Test for edge cases in AVL tree functions
// TEST_CASE("Test edge cases for AVL tree functions", "[edge_cases]") {
//     AVLTree tree;
//     stringstream buffer;
//     streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//     // Duplicate Gator ID
//     SECTION("Insert duplicate Gator ID") {
//         tree.insert("12345678", "Brandon");
//         buffer.str("");  // Clear buffer

//         tree.insert("12345678", "Brandon");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Non-existent Gator ID
//     SECTION("Remove non-existent Gator ID") {
//         tree.insert("12345678", "Brandon");
//         buffer.str("");  // Clear buffer

//         tree.remove("87654321");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Search in an empty tree
//     SECTION("Search in an empty tree") {
//         tree.search("12345678");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Remove from an empty tree
//     SECTION("Remove from an empty tree") {
//         tree.remove("12345678");
//         REQUIRE(buffer.str() == "unsuccessful\n");
//         buffer.str("");
//     }

//     // Print in-order on an empty tree
//     SECTION("Print in-order for an empty tree") {
//         tree.printInOrder();
//         REQUIRE(buffer.str() == "\n");
//         buffer.str("");
//     }

//     cout.rdbuf(oldCoutBuffer);
// }

// // Test all four rotation cases in the AVL Tree
// TEST_CASE("Test AVL tree rotations", "[rotations]") {
//     SECTION("Right-Right (RR) rotation") {
//         AVLTree tree;
//         stringstream buffer;
//         auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//         tree.insert("10000030", "Alice");
//         tree.insert("10000040", "Bob");
//         tree.insert("10000050", "Charlie");

//         buffer.str("");
//         tree.printInOrder();
//         cout.flush();
//         string output = buffer.str();
//         REQUIRE(output == "Alice, Bob, Charlie\n");

//         cout.rdbuf(oldCoutBuffer);
//     }

//     SECTION("Left-Left (LL) rotation") {
//         AVLTree tree;
//         stringstream buffer;
//         auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//         tree.insert("10000050", "Charlie");
//         tree.insert("10000040", "Bob");
//         tree.insert("10000030", "Alice");

//         buffer.str("");
//         tree.printInOrder();
//         cout.flush();
//         string output = buffer.str();
//         REQUIRE(output == "Alice, Bob, Charlie\n");

//         cout.rdbuf(oldCoutBuffer);
//     }

//     SECTION("Right-Left (RL) rotation") {
//         AVLTree tree;
//         stringstream buffer;
//         auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//         tree.insert("10000030", "Alice");
//         tree.insert("10000050", "Charlie");
//         tree.insert("10000040", "Bob");

//         buffer.str("");
//         tree.printInOrder();
//         cout.flush();
//         string output = buffer.str();
//         REQUIRE(output == "Alice, Bob, Charlie\n");

//         cout.rdbuf(oldCoutBuffer);
//     }

//     SECTION("Left-Right (LR) rotation") {
//         AVLTree tree;
//         stringstream buffer;
//         auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//         tree.insert("10000050", "Charlie");
//         tree.insert("10000030", "Alice");
//         tree.insert("10000040", "Bob");

//         buffer.str("");
//         tree.printInOrder();
//         cout.flush();
//         string output = buffer.str();
//         REQUIRE(output == "Alice, Bob, Charlie\n");

//         cout.rdbuf(oldCoutBuffer);
//     }
// }

// // Test for all three deletion cases
// TEST_CASE("Test AVL tree deletion cases", "[deletions]") {
//     AVLTree tree;
//     stringstream buffer;
//     auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//     SECTION("Delete node with no children") {
//         tree.insert("10000030", "Alyssa");
//         tree.insert("10000040", "Bob");
//         tree.insert("10000050", "Charlie");

//         tree.remove("10000040");
//         buffer.str("");
//         cout.flush();

//         tree.printInOrder();
//         string output = buffer.str();
//         REQUIRE(output == "Alyssa, Charlie\n");

//         buffer.str("");
//     }

//     SECTION("Delete node with one child") {
//         tree.insert("10000030", "Alice");
//         tree.insert("10000040", "Bob");
//         tree.insert("10000050", "Charlie");

//         tree.remove("10000040");
//         buffer.str("");
//         cout.flush();

//         tree.printInOrder();
//         string output = buffer.str();
//         REQUIRE(output == "Alice, Charlie\n");

//         buffer.str("");
//     }

//     SECTION("Delete node with two children") {
//         tree.insert("10000030", "Alice");
//         tree.insert("10000020", "Zoe");
//         tree.insert("10000050", "Charlie");
//         tree.insert("10000040", "Bob");
//         tree.insert("10000060", "Dave");

//         tree.remove("10000050");
//         buffer.str("");
//         cout.flush();

//         tree.printInOrder();
//         string output = buffer.str();
//         REQUIRE(output == "Zoe, Alice, Bob, Dave\n");

//         buffer.str("");
//     }

//     cout.rdbuf(oldCoutBuffer);
// }

// // Test insertion of 100 nodes and deletion of 10 nodes
// TEST_CASE("Test insertion of 100 nodes and deletion of 10 nodes", "[bulk_insert_remove]") {
//     vector<string> names = {
//         "Pedro Sanchez", "Finnegan Lawson", "Brooklynn Kline", "Charles Evans", "Chad Frederick",
//         "Christopher Klein", "Isaac Shelton", "Shayna Shields", "Douglas Keith", "Ethan Shepherd",
//         "Shania Lang", "Molly Huerta", "Valerie Shaffer", "Ali Salazar", "Dominique Stokes",
//         "Dakota Elliott", "Eden Espinoza", "Thaddeus Wolf", "Charlize Bentley", "Rylan Dickson",
//         "Allan Larsen", "Hana Shepherd", "Yosef Tucker", "Kade Fernandez", "Johnathan Gibson",
//         "Jabari Norman", "Braden Maddox", "Makhi Horton", "Riya Lester", "Sydnee Wright",
//         "Sariah Chung", "Cannon Hendrix", "Aniya Burns", "Mariela Curtis", "Hamza Abbott",
//         "Karen Hutchinson", "Jaeden Davila", "Ryland Smith", "Logan Owens", "Jonathon Mcconnell",
//         "Jagger Hunter", "Humberto Spears", "Wayne Duarte", "Cassidy Henderson", "Lainey Johnston",
//         "Emmy Ho", "Maleah Moon", "Stephanie Hudson", "Tianna Pennington", "Angel Baker",
//         "Nico Leach", "Carleigh Landry", "Nathaly Meadows", "Tyrese David", "Zaiden Hoffman",
//         "Jermaine Aguilar", "Reynaldo Holden", "Gemma Holmes", "Douglas Bond", "Brock Stanley",
//         "Rene Conley", "Howard Krause", "Krista Young", "Kaiden Acevedo", "Giana Cross",
//         "Erick Lawson", "Dayana Hobbs", "Jaden Morris", "Dylan Hester", "Izabelle Gross",
//         "Russell Benson", "Mckenna Woodward", "Chris Nguyen", "Dayanara Blankenship", "Wilson Sharp",
//         "Braydon Novak", "Camron Hinton", "London Melton", "Clay Salinas", "Erik Oneal",
//         "Gordon Mcconnell", "Madisyn Mccall", "Sterling Henderson", "Lauren Frost", "Martha Archer",
//         "Jose Dean", "Marisol Sharp", "Shyanne Santos", "Bennett Hamilton", "Clarence Haley",
//         "Duncan Jarvis", "Spencer Mann", "Alec Mcmahon", "Anabella Merritt", "Roman Gomez",
//         "Kyler Sampson", "Angeline Parks", "Kiersten Francis", "Karlee Guerra", "Miah Lowe"
//     };

//     map<string, string> gatorIDToName;
//     for (int i = 0; i < 100; ++i) {
//         string gatorID = string("100") + (i < 10 ? "0000" : "000") + to_string(i);
//         gatorIDToName[gatorID] = names[i];
//     }

//     AVLTree tree;
//     stringstream buffer;
//     auto oldCoutBuffer = cout.rdbuf(buffer.rdbuf());

//     for (const auto& entry : gatorIDToName) {
//         tree.insert(entry.first, entry.second);
//     }

//     vector<string> idsToRemove = {
//         "10000005", "10000015", "10000025", "10000035", "10000045",
//         "10000055", "10000065", "10000075", "10000085", "10000095"
//     };
//     for (const auto& id : idsToRemove) {
//         tree.remove(id);
//     }

//     vector<string> expectedNames;
//     for (const auto& entry : gatorIDToName) {
//         if (find(idsToRemove.begin(), idsToRemove.end(), entry.first) == idsToRemove.end()) {
//             expectedNames.push_back(entry.second);
//         }
//     }

//     buffer.str("");
//     tree.printInOrder();
//     cout.flush();
//     string output = buffer.str();

//     if (!output.empty() && output.back() == '\n') {
//         output.pop_back();
//     }

//     vector<string> actualNames;
//     stringstream ss(output);
//     string name;
//     while (getline(ss, name, ',')) {
//         name.erase(name.begin(), find_if(name.begin(), name.end(), [](unsigned char ch) {
//             return !isspace(ch);
//         }));
//         name.erase(find_if(name.rbegin(), name.rend(), [](unsigned char ch) {
//             return !isspace(ch);
//         }).base(), name.end());
//         actualNames.push_back(name);
//     }

//     REQUIRE(actualNames.size() == 90);

//     vector<pair<string, string>> sortedEntries;
//     for (const auto& entry : gatorIDToName) {
//         if (find(idsToRemove.begin(), idsToRemove.end(), entry.first) == idsToRemove.end()) {
//             sortedEntries.emplace_back(entry.first, entry.second);
//         }
//     }
//     sort(sortedEntries.begin(), sortedEntries.end());

//     vector<string> expectedSortedNames;
//     for (const auto& entry : sortedEntries) {
//         expectedSortedNames.push_back(entry.second);
//     }

//     REQUIRE(actualNames == expectedSortedNames);

//     cout.rdbuf(oldCoutBuffer);
// }
