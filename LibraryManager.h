#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include "Book.h"
#include "Member.h"
#include "Loan.h"

#include <vector>
#include <string>

using namespace std;

class LibraryManager {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;

public:
    void addBook();
    void listBooks() const;
    void searchBook() const;

    void addMember();
    void listMembers() const;

    void borrowBook();
    void returnBook();
    void listLoans() const;

    bool loadBooksFromCSV(const string& filename);
    bool saveBooksToCSV(const string& filename) const;

    bool loadMembersFromCSV(const string& filename);
    bool saveMembersToCSV(const string& filename) const;

    bool loadLoansFromCSV(const string& filename);
    bool saveLoansToCSV(const string& filename) const;

    void displayMenu();
};

#endif