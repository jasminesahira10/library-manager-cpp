#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string bookId;
    string title;
    string author;
    string category;
    int year;
    bool available;
    string borrowerId;
    string dueDate;

public:
    Book();

    Book(string id, string title, string author,
         string category, int year);

    string getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    int getYear() const;

    bool isAvailable() const;

    string getBorrowerId() const;
    string getDueDate() const;

    void borrowBook(string memberId, string date);
    void returnBook();

    void display() const;
};

#endif