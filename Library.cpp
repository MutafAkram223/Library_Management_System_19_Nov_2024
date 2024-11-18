#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

// ------------------ Prototypes
int mainHeader();
char adminMenu();
int clearScreen();
int addStudent();
int viewAllStudents();
int addStudentIntoArray(string username, float balance);
int addUser(string name, string pass, string role);
int viewStudentBalances();
int addBook();
int editBook();
int deleteBook(); // Added prototype for deleteBook function
int viewBooksStatus();
int viewBalance(string username);
int depositBalance(string username);
int issueBook(string username);
char studentMenu();
int findStudentIndex(string username);
int findBookIndex(string id);
int findUserIndex(string name);

// ------------------ Constants
const int MAX_RECORDS = 100;
const int MAX_BOOKS = 100;

// ------------------ Data Structures
string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;

string student_name[MAX_RECORDS]; // Stores student usernames
float student_balance[MAX_RECORDS];
string student_issuedBook[MAX_RECORDS];
int studentCount = 0;

string bookID[MAX_BOOKS];
string bookName[MAX_BOOKS];
string bookAuthor[MAX_BOOKS]; // Added array to store author names
string bookStatus[MAX_BOOKS]; // "Available" or "Issued"
int bookCount = 0;

// Main function
int main() {
    addUser("admin", "123", "ADMIN");

    while (true) {
        system("cls"); // Clear screen at the start of the main loop
        mainHeader();
        cout << "1- Admin" << endl;
        cout << "2- Student" << endl;
        cout << "3- Exit" << endl;
        cout << "Choose Your Option: ";
        char mainOption;
        cin >> mainOption;

        if (mainOption == '1') { // Admin
            system("cls"); // Clear screen before admin login
            mainHeader();
            string loginUsername, loginPassword;
            cout << "Enter admin username: ";
            cin >> loginUsername;
            cout << "Enter password: ";
            cin >> loginPassword;

            int userIndex = findUserIndex(loginUsername);
            if (userIndex != -1 && passwordsA[userIndex] == loginPassword && rolesA[userIndex] == "ADMIN") {
                char option = ' ';
                while (true) {
                    system("cls"); // Clear screen before showing admin menu
                    mainHeader();
                    option = adminMenu();
                    if (option == '1') { // Add Admin
                        system("cls"); // Clear screen before adding admin
                        cout << "Enter admin username: ";
                        string newUsername;
                        cin >> newUsername;

                        // Check if admin already exists
                        int userIndex = findUserIndex(newUsername);
                        if (userIndex != -1) {
                            cout << "Admin of same name already exists." << endl;
                        } else {
                            cout << "Enter password: ";
                            string pass;
                            cin >> pass;

                            addUser(newUsername, pass, "ADMIN");
                            cout << "Admin added successfully!" << endl;
                        }
                        clearScreen();

                    } else if (option == '2') { // Add Student
                        system("cls"); // Clear screen before adding student
                        addStudent();

                    } else if (option == '3') { // Add Books
                        system("cls"); // Clear screen before adding books
                        addBook();

                    } else if (option == '4') { // Edit Books
                        system("cls"); // Clear screen before editing books
                        editBook();

                    } else if (option == '5') { // Delete Books
                        system("cls"); // Clear screen before deleting books
                        deleteBook();

                    } else if (option == '6') { // View Books Status
                        system("cls"); // Clear screen before viewing books status
                        viewBooksStatus();
                        clearScreen();

                    } else if (option == '7') { // View Student Balance
                        system("cls"); // Clear screen before viewing student balances
                        viewStudentBalances();
                        clearScreen();

                    } else if (option == '8') { // Logout
                        break;

                    } else {
                        cout << "You chose an invalid option." << endl;
                        clearScreen();
                    }
                } // end of admin while loop
            } else {
                cout << "Invalid admin credentials." << endl;
                clearScreen();
            }
        } else if (mainOption == '2') { // Student
            system("cls"); // Clear screen before student login
            string loginUsername, loginPassword;
            cout << "Enter student username: ";
            cin >> loginUsername;
            cout << "Enter password: ";
            cin >> loginPassword;

            int userIndex = findUserIndex(loginUsername);
            if (userIndex != -1 && passwordsA[userIndex] == loginPassword && rolesA[userIndex] == "STUDENT") {
                // Set 'username' to the logged-in student's username
                string username = loginUsername;

                char studentOption = ' ';
                while (true) {
                    system("cls"); // Clear screen before showing student menu
                    studentOption = studentMenu();
                    if (studentOption == '1') { // View Balance
                        system("cls"); // Clear screen before viewing balance
                        viewBalance(username);
                        clearScreen();

                    } else if (studentOption == '2') { // Deposit Balance
                        system("cls"); // Clear screen before depositing balance
                        depositBalance(username);
                        clearScreen();

                    } else if (studentOption == '3') { // Issue Book
                        system("cls"); // Clear screen before issuing book
                        issueBook(username);
                        clearScreen();

                    } else if (studentOption == '4') { // Logout
                        break;

                    } else {
                        cout << "Wrong selection! Try again." << endl;
                        clearScreen();
                    }
                } // end of student menu while loop
            } else {
                cout << "Invalid student credentials." << endl;
                clearScreen();
            }
        } else if (mainOption == '3') { // Exit
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid option. Please choose again." << endl;
            clearScreen();
        }
    }

    return 0;
} // end of main function

// Function definitions
int mainHeader() {
    cout << "----------------------------------------------" << endl;
    cout << "---          Library Management System     ---" << endl;
    cout << "----------------------------------------------" << endl;
    return 0;
}

char adminMenu() {
    mainHeader();
    cout << "Admin Main Menu > " << endl;
    cout << "1- Add Admin " << endl;
    cout << "2- Add Student" << endl;
    cout << "3- Add Books" << endl;
    cout << "4- Edit Books" << endl;
    cout << "5- Delete Books" << endl;
    cout << "6- View Books Status" << endl;
    cout << "7- View Student Balance" << endl;
    cout << "8- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

char studentMenu() {
    mainHeader();
    cout << "Student Main Menu > " << endl;
    cout << "1- View Balance " << endl;
    cout << "2- Deposit Balance " << endl;
    cout << "3- Issue Book " << endl;
    cout << "4- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

int clearScreen() {
    cout << "Press any key to continue..." << endl;
    getch();
    system("cls");
    return 1;
}

int addUser(string name, string pass, string role) {
    if (userCount >= MAX_RECORDS) {
        cout << "Cannot add more users. Maximum capacity reached." << endl;
        return 0;
    }
    // Check if user already exists
    if (findUserIndex(name) != -1) {
        cout << "User already exists." << endl;
        return 0;
    }

    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;
    return 1;
}

int findUserIndex(string name) {
    for (int i = 0; i < userCount; i++) {
        if (usernameA[i] == name) {
            return i;
        }
    }
    return -1;
}

int addStudent() {
    string username;
    cout << "Enter student username: ";
    cin >> username;

    // Check if student already exists
    int userIndex = findUserIndex(username);
    if (userIndex != -1) {
        cout << "Student of same name already exists." << endl;
        clearScreen();
        return 0;
    }

    cout << "Enter student password: ";
    string pass;
    cin >> pass;

    cout << "Enter initial balance: ";
    float balance;
    cin >> balance;

    if (!addStudentIntoArray(username, balance)) {
        cout << "Failed to add student into array." << endl;
        return 0;
    }
    if (!addUser(username, pass, "STUDENT")) {
        cout << "Failed to add user." << endl;
        return 0;
    }

    cout << "Student added successfully!" << endl;
    clearScreen();
    return 1;
}

int addStudentIntoArray(string username, float balance) {
    if (studentCount >= MAX_RECORDS) {
        cout << "Cannot add more students. Maximum capacity reached." << endl;
        return 0;
    }
    student_name[studentCount] = username; // Store username instead of name
    student_balance[studentCount] = balance;
    student_issuedBook[studentCount] = "";
    studentCount++;
    return 1;
}

int viewStudentBalances() {
    cout << "Username\tBalance" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << student_name[i] << "\t\t" << student_balance[i] << endl;
    }
    return 1;
}

int addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Cannot add more books. Maximum capacity reached." << endl;
        return 0;
    }
    cout << "Enter Book ID: ";
    string id;
    cin >> id;
    cin.get(); // Consume the newline character left by cin

    // Check if book ID already exists
    if (findBookIndex(id) != -1) {
        cout << "Book with this ID already exists." << endl;
        clearScreen();
        return 0;
    }

    cout << "Enter Book Name: ";
    string name;
    getline(cin, name);

    cout << "Enter Author Name: ";
    string author;
    getline(cin, author);

    bookID[bookCount] = id;
    bookName[bookCount] = name;
    bookAuthor[bookCount] = author; // Store author name
    bookStatus[bookCount] = "Available";
    bookCount++;

    cout << "Book added successfully!" << endl;
    clearScreen();
    return 1;
}

int editBook() {
    cout << "Enter Book ID to edit: ";
    string id;
    cin >> id;
    cin.get(); // Consume the newline character left by cin

    int index = findBookIndex(id);
    if (index == -1) {
        cout << "Book not found." << endl;
        clearScreen();
        return 0;
    }

    cout << "Enter new Book Name: ";
    string name;
    getline(cin, name);

    cout << "Enter new Author Name: ";
    string author;
    getline(cin, author);

    bookName[index] = name;
    bookAuthor[index] = author;
    cout << "Book updated successfully!" << endl;
    clearScreen();
    return 1;
}

int deleteBook() {
    cout << "Enter Book ID to delete: ";
    string id;
    cin >> id;

    int index = findBookIndex(id);
    if (index == -1) {
        cout << "Book not found." << endl;
        clearScreen();
        return 0;
    }

    // Check if the book is issued
    if (bookStatus[index] == "Issued") {
        cout << "Cannot delete an issued book." << endl;
        clearScreen();
        return 0;
    }

    // Shift all elements after index to the left
    for (int i = index; i < bookCount - 1; i++) {
        bookID[i] = bookID[i + 1];
        bookName[i] = bookName[i + 1];
        bookAuthor[i] = bookAuthor[i + 1];
        bookStatus[i] = bookStatus[i + 1];
    }
    bookCount--;

    cout << "Book deleted successfully." << endl;
    clearScreen();
    return 1;
}

int viewBooksStatus() {
    cout << "Book ID\tBook Name\tAuthor Name\tStatus" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << bookID[i] << "\t" << bookName[i] << "\t" << bookAuthor[i] << "\t" << bookStatus[i] << endl;
    }
    return 1;
}

int viewBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    cout << "Your balance is: " << student_balance[index] << endl;
    return 1;
}

int depositBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    cout << "Enter amount to deposit: ";
    float amount;
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount." << endl;
        return 0;
    }
    student_balance[index] += amount;
    cout << "Amount deposited successfully. New balance: " << student_balance[index] << endl;
    return 1;
}

int issueBook(string username) {
    int studentIndex = findStudentIndex(username);
    if (studentIndex == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    if (student_issuedBook[studentIndex] != "") {
        cout << "You have already issued a book: " << student_issuedBook[studentIndex] << endl;
        return 0;
    }
    cout << "Available books: " << endl;
    for (int i = 0; i < bookCount; i++) {
        if (bookStatus[i] == "Available") {
            cout << bookID[i] << "\t" << bookName[i] << "\t" << bookAuthor[i] << endl;
        }
    }
    cout << "Enter Book ID to issue: ";
    string id;
    cin >> id;
    int bookIndex = findBookIndex(id);
    if (bookIndex == -1 || bookStatus[bookIndex] != "Available") {
        cout << "Book not found or not available." << endl;
        return 0;
    }
    // Assume issuing a book costs some amount, e.g., $10
    float issueCost = 10.0;
    if (student_balance[studentIndex] < issueCost) {
        cout << "Insufficient balance to issue book. Please deposit funds." << endl;
        return 0;
    }
    student_balance[studentIndex] -= issueCost;
    student_issuedBook[studentIndex] = bookID[bookIndex];
    bookStatus[bookIndex] = "Issued";
    cout << "Book issued successfully. Remaining balance: " << student_balance[studentIndex] << endl;
    return 1;
}

int findStudentIndex(string username) {
    for (int i = 0; i < studentCount; i++) {
        if (student_name[i] == username) {
            return i;
        }
    }
    return -1;
}

int findBookIndex(string id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookID[i] == id) {
            return i;
        }
    }
    return -1;
}