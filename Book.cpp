#include "Book.h"
#include <iostream>

using namespace std;

Book::Book()
    : year(0), available(true) {
}

Book::Book(string id, string title, string author,
           string category, int year)
    : bookId(id),
      title(title),
      author(author),
      category(category),
      year(year),
      available(true) {
}

string Book::getId() const {
    return bookId;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getCategory() const {
    return category;
}

int Book::getYear() const {
    return year;
}

bool Book::isAvailable() const {
    return available;
}

string Book::getBorrowerId() const {
    return borrowerId;
}

string Book::getDueDate() const {
    return dueDate;
}

void Book::borrowBook(string memberId, string date) {
    if (!available) {
        return;
    }

    available = false;
    borrowerId = memberId;
    dueDate = date;
}

void Book::returnBook() {
    available = true;
    borrowerId = "";
    dueDate = "";
}

void Book::display() const {
    cout << "Book ID: " << bookId << '\n';
    cout << "Title: " << title << '\n';
    cout << "Author: " << author << '\n';
    cout << "Category: " << category << '\n';
    cout << "Year: " << year << '\n';

    cout << "Status: "
         << (available ? "Available" : "Borrowed") << '\n';

    if (!available) {
        cout << "Borrower ID: " << borrowerId << '\n';
        cout << "Due Date: " << dueDate << '\n';
    }

    cout << "-----------------------------\n";
}