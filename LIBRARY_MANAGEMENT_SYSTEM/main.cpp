#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;
    string dueDate;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true), dueDate("") {}
};

class Library {
private:
    vector<Book> books;
    string fileName;

public:
    Library(const string& file) : fileName(file) {
        loadBooksFromCSV(); // Load books from CSV file when Library is initialized
    }

    void addBook(string title, string author, string ISBN) {
        Book newBook(title, author, ISBN);
        books.push_back(newBook);
        saveBooksToCSV(); // Automatically save to CSV after adding a book
    }

    // Other functions for edit, checkout, return...

    void saveBooksToCSV() {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        file << "Title,Author,ISBN,Availability,DueDate\n";
        for (const Book& book : books) {
            file << book.title << "," << book.author << "," << book.ISBN << ","
                 << (book.isAvailable ? "Available" : "Not Available") << ","
                 << book.dueDate << "\n";
        }
        file.close();
    }

    void loadBooksFromCSV() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        books.clear(); // Clear existing book data before loading from the file

        string line;
        getline(file, line); // Skip the header line
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, ISBN, availability, dueDate;

            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, ISBN, ',');
            getline(ss, availability, ',');
            getline(ss, dueDate, ',');

            bool isAvailable = (availability == "Available");

            Book newBook(title, author, ISBN);
            newBook.isAvailable = isAvailable;
            newBook.dueDate = dueDate;

            books.push_back(newBook);
        }
        file.close();
    }

    void displayLibrary() {
        if (books.empty()) {
            cout << "Library is empty." << endl;
            return;
        }

        cout << left << setw(25) << "Title" << setw(25) << "Author" << setw(25) << "ISBN" << setw(15) << "Availability" << setw(15) << "DueDate" << endl;
        cout << "========================================================================================================" << endl;

        for (const Book& book : books)
        {
            cout << left << setw(25) << book.title << setw(25) << book.author << setw(25) << book.ISBN
                 << setw(15) << (book.isAvailable ? "Available" : "Not Available") << setw(15) << book.dueDate << endl;
        }
    }
};

void displayMenu() {
    cout << "Library Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Edit Book\n";
    cout << "3. Check Out Book\n";
    cout << "4. Return Book\n";
    cout << "5. Display Library\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void addBookToLibrary(Library& library) {
    string title, author, ISBN;
    cout << "Enter book title: ";
    getline(cin >> ws, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    library.addBook(title, author, ISBN);
}

int main() {
    const string fileName = "library_books.csv";
    Library library(fileName);

    int choice = 0;
    while (choice != 6)
    {
        displayMenu();
        cin >> choice;

        system("cls");

        switch (choice)
        {
            case 1:
                addBookToLibrary(library);
                break;
            case 2:
                // Call edit book function
                break;
            case 3:
                // Call checkout function
                break;
            case 4:
                // Call return book function
                break;
            case 5:
                library.displayLibrary();
                system("pause");
                system("cls");
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
