#include "LibraryManager.h"

int main() {
    LibraryManager library;

    library.loadBooksFromCSV("library_records.csv");
    library.loadMembersFromCSV("members.csv");
    library.loadLoansFromCSV("loans.csv");

    library.displayMenu();

    library.saveBooksToCSV("library_records.csv");
    library.saveMembersToCSV("members.csv");
    library.saveLoansToCSV("loans.csv");

    return 0;
}