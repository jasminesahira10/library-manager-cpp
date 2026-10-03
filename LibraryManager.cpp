#include "LibraryManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// -------------------- BOOKS --------------------

void LibraryManager::addBook() {
    string id, title, author, category;
    int year;

    cout << "Enter Book ID: ";
    cin >> id;

    for (const Book& book : books) {
        if (book.getId() == id) {
            cout << "Error: Book ID already exists.\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Year: ";
    cin >> year;

    if (cin.fail() || year <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid year.\n";
        return;
    }

    books.push_back(Book(id, title, author, category, year));

    cout << "Book added successfully.\n";
}

void LibraryManager::listBooks() const {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    for (const Book& book : books) {
        book.display();
    }
}

void LibraryManager::searchBook() const {
    string keyword;

    cin.ignore();

    cout << "Enter Book ID or Title: ";
    getline(cin, keyword);

    bool found = false;

    for (const Book& book : books) {
        if (book.getId() == keyword ||
            book.getTitle() == keyword) {
            book.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }
}

// -------------------- MEMBERS --------------------

void LibraryManager::addMember() {
    string id, name, email;

    cout << "Enter Member ID: ";
    cin >> id;

    for (const Member& member : members) {
        if (member.getId() == id) {
            cout << "Error: Member ID already exists.\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Email: ";
    getline(cin, email);

    if (name.empty() || email.empty()) {
        cout << "Error: Name and email cannot be empty.\n";
        return;
    }

    members.push_back(Member(id, name, email));

    cout << "Member added successfully.\n";
}

void LibraryManager::listMembers() const {
    if (members.empty()) {
        cout << "No members available.\n";
        return;
    }

    for (const Member& member : members) {
        member.display();
    }
}

// -------------------- BORROW / RETURN --------------------

void LibraryManager::borrowBook() {
    string bookId, memberId, dueDate;

    cout << "Enter Book ID: ";
    cin >> bookId;

    for (Book& book : books) {
        if (book.getId() == bookId) {

            if (!book.isAvailable()) {
                cout << "Error: Book is already borrowed.\n";
                return;
            }

            cout << "Enter Member ID: ";
            cin >> memberId;

            bool memberFound = false;

            for (const Member& member : members) {
                if (member.getId() == memberId) {
                    memberFound = true;
                    break;
                }
            }

            if (!memberFound) {
                cout << "Error: Member not found.\n";
                return;
            }

            cout << "Enter Due Date (YYYY-MM-DD): ";
            cin >> dueDate;

            if (dueDate.empty()) {
                cout << "Error: Due date cannot be empty.\n";
                return;
            }

            book.borrowBook(memberId, dueDate);

            string loanId = "L" + to_string(loans.size() + 1);

            loans.push_back(
                Loan(loanId, bookId, memberId, "Today", dueDate)
            );

            cout << "Book borrowed successfully.\n";
            return;
        }
    }

    cout << "Error: Book not found.\n";
}

void LibraryManager::returnBook() {
    string bookId;

    cout << "Enter Book ID: ";
    cin >> bookId;

    for (Book& book : books) {
        if (book.getId() == bookId) {

            if (book.isAvailable()) {
                cout << "Error: Book is already available.\n";
                return;
            }

            book.returnBook();

            for (Loan& loan : loans) {
                if (loan.getBookId() == bookId &&
                    !loan.isReturned()) {
                    loan.markReturned();
                    break;
                }
            }

            cout << "Book returned successfully.\n";
            return;
        }
    }

    cout << "Error: Book not found.\n";
}

void LibraryManager::listLoans() const {
    if (loans.empty()) {
        cout << "No loan records available.\n";
        return;
    }

    for (const Loan& loan : loans) {
        loan.display();
    }
}

// -------------------- BOOK CSV --------------------

bool LibraryManager::loadBooksFromCSV(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << '\n';
        return false;
    }

    books.clear();

    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string id;
        string title;
        string author;
        string category;
        string yearText;
        string status;
        string borrowerId;
        string dueDate;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, yearText, ',');
        getline(ss, status, ',');
        getline(ss, borrowerId, ',');
        getline(ss, dueDate, ',');

        if (id.empty() || title.empty() ||
            author.empty() || category.empty() ||
            yearText.empty()) {
            cout << "Warning: Skipping malformed book row.\n";
            continue;
        }

        try {
            int year = stoi(yearText);

            if (year <= 0) {
                throw invalid_argument("Invalid year");
            }

            Book book(id, title, author, category, year);

            if (status == "Borrowed" &&
                !borrowerId.empty() &&
                !dueDate.empty()) {
                book.borrowBook(borrowerId, dueDate);
            }

            books.push_back(book);
        }
        catch (...) {
            cout << "Warning: Skipping malformed book row.\n";
        }
    }

    file.close();

    cout << "Books loaded successfully.\n";
    return true;
}

bool LibraryManager::saveBooksToCSV(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not save " << filename << '\n';
        return false;
    }

    file << "book_id,title,author,category,year,status,borrower_id,due_date\n";

    for (const Book& book : books) {
        file << book.getId() << ","
             << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getCategory() << ","
             << book.getYear() << ","
             << (book.isAvailable() ? "Available" : "Borrowed") << ","
             << book.getBorrowerId() << ","
             << book.getDueDate() << '\n';
    }

    file.close();

    return true;
}

// -------------------- MEMBER CSV --------------------

bool LibraryManager::loadMembersFromCSV(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    members.clear();

    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string email;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');

        if (!id.empty() &&
            !name.empty() &&
            !email.empty()) {

            members.push_back(Member(id, name, email));
        }
    }

    file.close();

    return true;
}

bool LibraryManager::saveMembersToCSV(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not save " << filename << '\n';
        return false;
    }

    file << "member_id,name,email\n";

    for (const Member& member : members) {
        file << member.getId() << ","
             << member.getName() << ","
             << member.getEmail() << '\n';
    }

    file.close();

    return true;
}

// -------------------- LOAN CSV --------------------

bool LibraryManager::loadLoansFromCSV(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    loans.clear();

    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string loanId;
        string bookId;
        string memberId;
        string issueDate;
        string dueDate;
        string status;

        getline(ss, loanId, ',');
        getline(ss, bookId, ',');
        getline(ss, memberId, ',');
        getline(ss, issueDate, ',');
        getline(ss, dueDate, ',');
        getline(ss, status, ',');

        if (loanId.empty() ||
            bookId.empty() ||
            memberId.empty()) {
            continue;
        }

        Loan loan(
            loanId,
            bookId,
            memberId,
            issueDate,
            dueDate
        );

        if (status == "Returned") {
            loan.markReturned();
        }

        loans.push_back(loan);
    }

    file.close();

    return true;
}

bool LibraryManager::saveLoansToCSV(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not save " << filename << '\n';
        return false;
    }

    file << "loan_id,book_id,member_id,issue_date,due_date,status\n";

    for (const Loan& loan : loans) {
        file << loan.getLoanId() << ","
             << loan.getBookId() << ","
             << loan.getMemberId() << ","
             << loan.getIssueDate() << ","
             << loan.getDueDate() << ","
             << (loan.isReturned() ? "Returned" : "Active")
             << '\n';
    }

    file.close();

    return true;
}

// -------------------- MENU --------------------

void LibraryManager::displayMenu() {
    int choice;

    do {
        cout << "\n========== LIBRARY MANAGER ==========\n";
        cout << "1. Add Book\n";
        cout << "2. List Books\n";
        cout << "3. Search Book\n";
        cout << "4. Add Member\n";
        cout << "5. List Members\n";
        cout << "6. Borrow Book\n";
        cout << "7. Return Book\n";
        cout << "8. List Loans\n";
        cout << "9. Save Data\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

        case 1:
            addBook();
            break;

        case 2:
            listBooks();
            break;

        case 3:
            listBooks();
            searchBook();
            break;

        case 4:
            addMember();
            break;

        case 5:
            listMembers();
            break;

        case 6:
            borrowBook();
            break;

        case 7:
            returnBook();
            break;

        case 8:
            listLoans();
            break;

        case 9:
            saveBooksToCSV("library_records.csv");
            saveMembersToCSV("members.csv");
            saveLoansToCSV("loans.csv");
            cout << "Data saved successfully.\n";
            break;

        case 0:
            cout << "Exiting Library Manager...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}