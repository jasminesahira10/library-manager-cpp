# Object-Oriented Library Manager

A C++ command-line Library Manager built using Object-Oriented Programming concepts.

## Features

- Add books
- List all books
- Search books
- Add members
- List members
- Borrow books
- Return books
- Check book availability
- Track loan records
- Import book records from CSV
- Save and load members using CSV
- Save and load loan records using CSV
- Local file persistence
- Duplicate ID validation
- Invalid input handling
- Malformed CSV row handling

## Technologies Used

- C++
- Object-Oriented Programming
- C++ Standard Library
- CSV file handling
- File I/O
- MinGW-w64 GCC
- Visual Studio Code

## Project Structure

```text
LibraryManager/
│
├── main.cpp
├── Book.h
├── Book.cpp
├── Member.h
├── Member.cpp
├── Loan.h
├── Loan.cpp
├── LibraryManager.h
├── LibraryManager.cpp
├── library_records.csv
├── members.csv
└── loans.csv
## Class Diagram

```text
+----------------------+
|        Book          |
+----------------------+
| - bookId             |
| - title              |
| - author             |
| - category           |
| - year               |
| - available          |
| - borrowerId         |
| - dueDate            |
+----------------------+
| + borrowBook()       |
| + returnBook()       |
| + display()          |
+----------------------+

+----------------------+       +----------------------+
|   LibraryManager     |       |       Member         |
+----------------------+       +----------------------+
| - books              |       | - memberId           |
| - members            |       | - name               |
| - loans              |       | - email              |
+----------------------+       +----------------------+
| + addBook()          |       | + display()          |
| + listBooks()        |       +----------------------+
| + searchBook()       |
| + addMember()        |
| + borrowBook()       |
| + returnBook()       |
| + listLoans()        |
+----------------------+
          |
          v
+----------------------+
|        Loan          |
+----------------------+
| - loanId             |
| - bookId             |
| - memberId           |
| - issueDate          |
| - dueDate            |
| - returned           |
+----------------------+
| + markReturned()     |
| + display()          |
+----------------------+