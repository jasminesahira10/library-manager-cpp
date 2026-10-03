#ifndef LOAN_H
#define LOAN_H

#include <string>

using namespace std;

class Loan {
private:
    string loanId;
    string bookId;
    string memberId;
    string issueDate;
    string dueDate;
    bool returned;

public:
    Loan();

    Loan(string loanId, string bookId, string memberId,
         string issueDate, string dueDate);

    string getLoanId() const;
    string getBookId() const;
    string getMemberId() const;
    string getIssueDate() const;
    string getDueDate() const;

    bool isReturned() const;

    void markReturned();

    void display() const;
};

#endif