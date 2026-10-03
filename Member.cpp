#include "Member.h"
#include <iostream>

using namespace std;

Member::Member() {
}

Member::Member(string id, string name, string email)
    : memberId(id),
      name(name),
      email(email) {
}

string Member::getId() const {
    return memberId;
}

string Member::getName() const {
    return name;
}

string Member::getEmail() const {
    return email;
}

void Member::display() const {
    cout << "Member ID: " << memberId << '\n';
    cout << "Name: " << name << '\n';
    cout << "Email: " << email << '\n';
    cout << "-----------------------------\n";
}