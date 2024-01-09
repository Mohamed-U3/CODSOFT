#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <windows.h>

using namespace std;

class Book
{
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;
    string dueDate;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true), dueDate("") {}
};

class Library
{
private:
    vector<Book> books;
    string fileName;

    // Helper function to calculate the due date for books
    string calculateDueDate()
    {
        auto now = chrono::system_clock::now();
        auto nextWeek = now + chrono::hours(24 * 7); // One week from now
        time_t nextWeekTime = chrono::system_clock::to_time_t(nextWeek);

        tm dueDate = *localtime(&nextWeekTime);
        stringstream ss;
        ss << put_time(&dueDate, "%Y-%m-%d"); // Format as YYYY-MM-DD
        return ss.str();
    }

public:
    Library(const string& file) : fileName(file)
    {
        loadBooksFromCSV();
    }

    void addBook(string title, string author, string ISBN)
    {
        Book newBook(title, author, ISBN);
        books.push_back(newBook);
        saveBooksToCSV();
    }

    vector<Book*> searchBook(const string& keyword)
    {
        vector<Book*> foundBooks;
        for (auto& book : books)
        {
            // Convert keyword and book information to lowercase for case-insensitive comparison
            string keywordLower = keyword;
            transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);
            string titleLower = book.title;
            transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
            string authorLower = book.author;
            transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
            string ISBNLower = book.ISBN;
            transform(ISBNLower.begin(), ISBNLower.end(), ISBNLower.begin(), ::tolower);
            if (titleLower.find(keywordLower)   != string::npos ||
                authorLower.find(keywordLower)  != string::npos ||
                ISBNLower.find(keywordLower)    != string::npos      )
                {   foundBooks.push_back(&book);        }
        }
        return foundBooks;
    }

    void checkoutBook(const string& ISBN)
    {
        for (Book& book : books)
        {
            if (book.ISBN == ISBN)
            {
                if (book.isAvailable)
                {
                    book.isAvailable = false;
                    book.dueDate = calculateDueDate(); // Set the due date one week from now
                    saveBooksToCSV();
                    cout << "Book with ISBN " << ISBN << " has been checked out." << endl;
                    return;
                }
                else
                {
                    cout << "Book with ISBN " << ISBN << " is already checked out." << endl;
                    return;
                }
            }
        }
        cout << "Book with ISBN " << ISBN << " not found." << endl;
    }

    void returnBook(const string& ISBN)
    {
        for (Book& book : books)
        {
            if (book.ISBN == ISBN)
            {
                if (!book.isAvailable)
                {
                    book.isAvailable = true;
                    double fine = calculateFine(book);
                    if (fine > 0)
                    {
                        cout << "Book with ISBN " << ISBN << " has been returned. ";
                        cout << "Overdue fine: $" << fine << endl;
                    }
                    else
                    {
                        cout << "Book with ISBN " << ISBN << " has been returned. No overdue fine.\n" << endl;
                    }
                    book.dueDate = ""; // Implement due date clearing
                    saveBooksToCSV();
                    return;
                }
                else
                {
                    cout << "Book with ISBN " << ISBN << " is already available." << endl;
                    return;
                }
            }
        }
        cout << "Book with ISBN " << ISBN << " not found." << endl;
    }

    void saveBooksToCSV()
    {
        ofstream file(fileName);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        file << "Title,Author,ISBN,Availability,DueDate\n";
        for (const Book& book : books)
        {
            file << book.title << "," << book.author << "," << book.ISBN << ","
                 << (book.isAvailable ? "Available" : "Not Available") << ","
                 << book.dueDate << "\n";
        }
        file.close();
    }

    void loadBooksFromCSV()
    {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        books.clear();

        string line;
        getline(file, line);
        while (getline(file, line))
        {
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

    void displayLibrary()
    {
        if (books.empty())
        {
            cout << "Library is empty." << endl;
            return;
        }

        cout << left <<"| "<< setw(25) << "Title" << "| "<< setw(15) << "Author" << "| "<< setw(25) << "ISBN" << "| "<< setw(15) << "Availability" << "| "<< setw(15) << "DueDate" << endl;
        cout << "========================================================================================================" << endl;

        for (const Book& book : books)
        {
            cout << left << "| "<< setw(25) << truncateString(book.title, 25) << "| "<< setw(15) << truncateString(book.author, 15) << "| "<< setw(25) << book.ISBN
                 << "| "<< setw(15) << (book.isAvailable ? "Available" : "Not Available") << "| "<< setw(15) << book.dueDate << endl;
        }
        cout << "========================================================================================================" << endl;
    }

    // Function to truncate string if longer than specified width
    string truncateString(const string& str, int width)
    {
        if (str.length() > width)
        {
            return str.substr(0, width - 3) + "..."; // Truncate and append "..." for indication
        }
        else
        {
            return str;
        }
    }

    void editBook(const string& ISBN)
    {
        for (Book& book : books)
        {
            if (book.ISBN == ISBN)
            {
                cout << "Enter new title: ";
                getline(cin >> ws, book.title);
                cout << "Enter new author: ";
                getline(cin, book.author);
                cout << "Book with ISBN " << ISBN << " has been updated." << endl;
                saveBooksToCSV();
                return;
            }
        }
        cout << "Book with ISBN " << ISBN << " not found." << endl;
    }

    // Function to calculate fines for overdue books
    double calculateFine(const Book& book)
    {
        if (book.isAvailable)
        {
            // Get the current system time
            auto now = std::chrono::system_clock::now();

            // Convert due date string to time_point
            std::tm dueDate = {};
            std::istringstream ss(book.dueDate);
            ss >> std::get_time(&dueDate, "%Y-%m-%d");
            std::time_t dueTime = std::mktime(&dueDate);
            std::chrono::system_clock::time_point dueDateTime = std::chrono::system_clock::from_time_t(dueTime);

            // Calculate the duration between due date and now
            std::chrono::duration<double> overdueDuration = now - dueDateTime;

            // Calculate overdue days and fines
            int overdueDays = (double)std::chrono::duration_cast<std::chrono::hours>(overdueDuration).count() / 24;
            if (overdueDays > 0)
            {
                // Fine $1 per day for overdue books
                return static_cast<double>(overdueDays);
            }
        }
        return 0.0; // No fine if book is available or if due date is empty
     }
};

void displayMenu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 2); // Set text color to red
    cout << "Library Management System\n\n";
    SetConsoleTextAttribute(hConsole, 23); // Set text color to weight
    cout << "1. Add Book\n";
    cout << "2. Edit Book\n";
    cout << "3. Check Out Book\n";
    cout << "4. Return Book\n";
    cout << "5. Display Library\n";
    cout << "6. Search For Book\n";
    cout << "7. Exit\n\n";
    SetConsoleTextAttribute(hConsole, 7); // Set text color to weight
    cout << "Enter your choice: ";
}

void addBookToLibrary(Library& library)
{
    string title, author, ISBN;
    cout << "Enter book title: ";
    getline(cin >> ws, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    library.addBook(title, author, ISBN);
}

void checkoutBookFromLibrary(Library& library)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string ISBN;
    SetConsoleTextAttribute(hConsole, 4); // Set text color to red
    cout << "\nInstructions: select ISBN and copy (Ctrl + C) and paste it (Mouse right Click). ";
    SetConsoleTextAttribute(hConsole, 7); // Set text color to red
    cout << "\nEnter book ISBN to check out: ";
    //cin.ignore();  //that line was causing a bug
    getline(cin, ISBN);

    library.checkoutBook(ISBN);
}

void returnBookToLibrary(Library& library)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string ISBN;
    SetConsoleTextAttribute(hConsole, 4); // Set text color to red
    cout << "\nInstructions: select ISBN and copy (Ctrl + C) and paste it (Mouse right Click). ";
    SetConsoleTextAttribute(hConsole, 7); // Reset text color to default
    cout << "\nEnter book ISBN to return: ";
    //cin.ignore();  //that line was causing a bug
    getline(cin, ISBN);

    library.returnBook(ISBN);
}

void editBookInLibrary(Library& library)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string ISBN;
    SetConsoleTextAttribute(hConsole, 4); // Set text color to red
    cout << "\nInstructions: select ISBN and copy (Ctrl + C) and paste it (Mouse right Click). ";
    SetConsoleTextAttribute(hConsole, 7); // Reset text color to default
    cout << "\nEnter book ISBN to edit: ";
    //cin.ignore();  //that line was causing a bug
    getline(cin, ISBN);

    library.editBook(ISBN);
}

void searchforBookInLibrary(Library& library)
{
    string searchKeyword;
    cout << "Enter book name, author, or ISBN to search: ";
    getline(cin, searchKeyword);

    vector<Book*> foundBooks = library.searchBook(searchKeyword);

    if (foundBooks.empty())
    {
        cout << "No books found." << endl;
    }
    else
    {
        cout << "Books found:" << endl;
        for (auto book : foundBooks)
        {
            cout << "- " << book->title << " by " << book->author << " (ISBN: " << book->ISBN << ")" << endl;
        }
    }
}

int main()
{
    const string fileName = "library_books.csv";
    Library library(fileName);

    int choice = 0;
    while (choice != 7)
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        system("cls");

        switch (choice)
        {
            case 1:
                addBookToLibrary(library);
                break;
            case 2:
                library.displayLibrary();
                editBookInLibrary(library);
                library.displayLibrary();
                system("pause");
                system("cls");
                break;
            case 3:
                library.displayLibrary();
                checkoutBookFromLibrary(library);
                library.displayLibrary();
                system("pause");
                system("cls");
                break;
            case 4:
                library.displayLibrary();
                returnBookToLibrary(library);
                library.displayLibrary();
                system("pause");
                system("cls");
                break;
            case 5:
                library.displayLibrary();
                system("pause");
                system("cls");
                break;
            case 6:
                searchforBookInLibrary(library);
                system("pause");
                system("cls");
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    return 0;
}
