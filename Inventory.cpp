#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
    head = nullptr; // Initialize the head pointer to null
    bookCount = 0; // Initialize book count to zero
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
    Node* currNode = head;
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        delete currNode->data;
        delete currNode;
        currNode = nextNode;
    }
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null data pointer.\n";
        return;
    }

    Node* newNode = new Node(bookPtr);
    bookCount++; // Increment the book count

    if (head == nullptr || head->data->getTitle() > bookPtr->getTitle()) {
        newNode->next = head;
        head = newNode;
        std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
        return;
    }
    
    Node* currNode = head;

    while (currNode->next != nullptr && currNode->next->data->getTitle() < bookPtr->getTitle()) {
        currNode = currNode->next;
    }

    newNode->next = currNode->next;
    currNode->next = newNode;

    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";


    // if (bookPtr == nullptr) {
    //     std::cout << "Error: Cannot add null book pointer.\n";
    //     return;
    // }

    // // Find the correct position to insert (alphabetical order by title)
    // auto insertPos = std::upper_bound(books.begin(), books.end(), bookPtr,
    //     [](const Book* a, const Book* b) {
    //         return a->getTitle() < b->getTitle();
    //     });

    // books.insert(insertPos, bookPtr);
    // std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";

}

// Display all books in the inventory
void Inventory::displayAll() const {
    Node* currNode = head;
    if (currNode == nullptr) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    int bookCount = 0;
    while (currNode != nullptr) {
        std::cout << "Book #" << (++bookCount) << ":\n";
        currNode->data->displayInfo();
        currNode = currNode->next;
    }
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    Node* currNode = head;
    Node* prevNode = nullptr;

    while (currNode != nullptr) {
        if (currNode->data->getTitle() == title) {
            if (prevNode == nullptr) {
                head = currNode->next; // Remove head
            } else {
                prevNode->next = currNode->next; // Bypass the current node
            }
            std::cout << "Book '" << title << "' removed from inventory.\n";
            delete currNode->data; // Free the memory
            delete currNode; // Free the node
            bookCount--; // Decrement the data count
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    std::cout << "Book '" << title << "' not found in inventory.\n";
}

// Get the number of books
size_t Inventory::getBookCount() const {
    return bookCount;
}

// Search for a book by title
Book* Inventory::findBook(const std::string& title) const {
    Node* currNode = head;
    while (currNode != nullptr) {
        if (currNode->data->getTitle() == title) {
            return currNode->data;
        }
        currNode = currNode->next;
    }
    
    return nullptr; // Book not found
    // auto it = std::find_if(books.begin(), books.end(),
    //     [&title](const Book* data) {
    //         return data->getTitle() == title;
    //     });
    
    // return (it != books.end()) ? *it : nullptr;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
    return head == nullptr;
}