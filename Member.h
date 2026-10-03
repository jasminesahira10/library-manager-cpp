#ifndef MEMBER_H
#define MEMBER_H

#include <string>

using namespace std;

class Member {
private:
    string memberId;
    string name;
    string email;

public:
    Member();

    Member(string id, string name, string email);

    string getId() const;
    string getName() const;
    string getEmail() const;

    void display() const;
};

#endif