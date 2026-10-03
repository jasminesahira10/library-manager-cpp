#include "Loan.h"
#include <iostream>

using namespace std;

Loan::Loan()
    : returned(false) {
}

Loan::Loan(string loanId, string bookId, string memberId,
           string issueDate, string dueDate)
    : loanId(loanId),
      bookId(bookId),
      memberId(memberId),
      issueDate(issueDate),
      dueDate(dueDate),
      returned(false) {
}

string Loan::getLoanId() const {
    return loanId;
}

string Loan::getBookId() const {
    return bookId;
}

string Loan::getMemberId() const {
    return memberId;
}

string Loan::getIssueDate() const {
    return issueDate;
}

string Loan::getDueDate() const {
    return dueDate;
}

bool Loan::isReturned() const {
    return returned;
}

void Loan::markReturned() {
    returned = true;
}

void Loan::display() const {
    cout << "Loan ID: " << loanId << '\n';
    cout << "Book ID: " << bookId << '\n';
    cout << "Member ID: " << memberId << '\n';
    cout << "Issue Date: " << issueDate << '\n';
    cout << "Due Date: " << dueDate << '\n';

    cout << "Status: "
         << (returned ? "Returned" : "Active") << '\n';

    cout << "-----------------------------\n";
}