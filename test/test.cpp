#include "catch/catch_amalgamated.hpp"
#include "../src/avl_tree.h"
#include <sstream>  // For capturing console output

// Test for incorrect command formats
TEST_CASE("Test incorrect command formats", "[incorrect_commands]") {
    AVLTree tree;
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());  // Redirect cout

    // Test Case 1: Insert with invalid name (empty or special characters)
    SECTION("Insert command with invalid name") {
        tree.insert("45679999", "");  // Empty name
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");  // Clear the buffer

        tree.insert("45679999", "InvalidName!@#");  // Name with special characters
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");
    }

    // Test Case 2: Insert with invalid Gator ID
    SECTION("Insert command with invalid Gator ID") {
        tree.insert("1234567", "Brandon");  // Less than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");

        tree.insert("100000000", "Brandon");  // More than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");
    }

    // Test Case 3: Remove with invalid Gator ID (too short or long)
    SECTION("Remove command with invalid Gator ID") {
        tree.remove("1234567");  // Gator ID less than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");

        tree.remove("100000000");  // Gator ID more than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");
    }

    // Test Case 4: RemoveInorder with invalid position
    SECTION("RemoveInorder command with invalid position") {
        tree.removeInorder(-1);  // Negative in-order position
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");

        tree.removeInorder(0);  // Zero in-order position
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");
    }

    // Test Case 5: Search with invalid Gator ID
    SECTION("Search command with invalid Gator ID") {
        tree.search("1234567");  // Gator ID with less than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");

        tree.search("100000000");  // Gator ID with more than 8 digits
        REQUIRE(buffer.str() == "unsuccessful\n");
        buffer.str("");
    }

    std::cout.rdbuf(oldCoutBuffer);  // Restore original cout buffer
}

// Test for edge cases in AVL tree functions
TEST_CASE("Test edge cases for AVL tree functions", "[edge_cases]") {
    AVLTree tree;
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());  // Redirect cout

    // Test Case 1: Inserting a duplicate Gator ID
    SECTION("Insert duplicate Gator ID") {
        tree.insert("12345678", "Brandon");  // Insert the first time
        buffer.str("");  // Clear the buffer

        tree.insert("12345678", "Brandon");  // Insert a duplicate
        REQUIRE(buffer.str() == "unsuccessful\n");  // Duplicate insertion should fail
        buffer.str("");  // Clear the buffer
    }

    // Test Case 2: Removing a non-existent Gator ID
    SECTION("Remove non-existent Gator ID") {
        tree.insert("12345678", "Brandon");  // Insert a valid Gator ID
        buffer.str("");  // Clear the buffer

        tree.remove("87654321");  // Try to remove a Gator ID that doesn't exist
        REQUIRE(buffer.str() == "unsuccessful\n");  // Removing non-existent Gator ID should fail
        buffer.str("");  // Clear the buffer
    }

    // Test Case 3: Searching for a Gator ID in an empty tree
    SECTION("Search in an empty tree") {
        tree.search("12345678");  // Try to search when the tree is empty
        REQUIRE(buffer.str() == "unsuccessful\n");  // Searching in an empty tree should fail
        buffer.str("");  // Clear the buffer
    }

    // Test Case 4: Removing from an empty tree
    SECTION("Remove from an empty tree") {
        tree.remove("12345678");  // Try to remove a node from an empty tree
        REQUIRE(buffer.str() == "unsuccessful\n");  // Removing from an empty tree should fail
        buffer.str("");  // Clear the buffer
    }

    // Test Case 5: Print in-order on an empty tree
    SECTION("Print in-order for an empty tree") {
        tree.printInOrder();  // Print in-order for an empty tree
        REQUIRE(buffer.str() == "\n");  // Should only print a new line for an empty tree
        buffer.str("");  // Clear the buffer
    }

    std::cout.rdbuf(oldCoutBuffer);
}

// Test all four rotation cases in the AVL Tree
TEST_CASE("Test AVL tree rotations", "[rotations]") {
    AVLTree tree;
    std::stringstream buffer;
    auto oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());  // Redirect std::cout to the buffer

    SECTION("Right-Right (RR) rotation") {
        tree.insert("30", "Node30");
        tree.insert("40", "Node40");
        tree.insert("50", "Node50");  // This will trigger a RR rotation

        buffer.str("");  // Clear the buffer
        tree.printInOrder();
        std::cout.flush();  // Ensure all output is flushed to buffer
        std::string output = buffer.str();
        REQUIRE(output == "Node30, Node40, Node50\n");  // RR rotation result
    }

    SECTION("Left-Left (LL) rotation") {
        tree.insert("50", "Node50");
        tree.insert("40", "Node40");
        tree.insert("30", "Node30");  // This will trigger a LL rotation

        buffer.str("");  // Clear the buffer
        tree.printInOrder();
        std::cout.flush();  // Ensure all output is flushed to buffer
        std::string output = buffer.str();
        REQUIRE(output == "Node30, Node40, Node50\n");  // LL rotation result
    }

    SECTION("Right-Left (RL) rotation") {
        tree.insert("30", "Node30");
        tree.insert("50", "Node50");
        tree.insert("40", "Node40");  // This will trigger a RL rotation

        buffer.str("");  // Clear the buffer
        tree.printInOrder();
        std::cout.flush();  // Ensure all output is flushed to buffer
        std::string output = buffer.str();
        REQUIRE(output == "Node30, Node40, Node50\n");  // RL rotation result
    }

    SECTION("Left-Right (LR) rotation") {
        tree.insert("50", "Node50");
        tree.insert("30", "Node30");
        tree.insert("40", "Node40");  // This will trigger a LR rotation

        buffer.str("");  // Clear the buffer
        tree.printInOrder();
        std::cout.flush();  // Ensure all output is flushed to buffer
        std::string output = buffer.str();
        REQUIRE(output == "Node30, Node40, Node50\n");  // LR rotation result
    }

    std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer
}
