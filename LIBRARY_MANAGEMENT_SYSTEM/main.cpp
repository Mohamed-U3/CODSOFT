#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book
{
    public:
        string title;
        string author;
        string ISBN;
        bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true)
    {

    }
};

class Library
{
    private:
        vector<Book> books;

    public:
        void addBook(string title, string author, string ISBN)
        {
            Book newBook(title, author, ISBN);
            books.push_back(newBook);
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
};

int main()
{
    Library library;

    library.addBook("The Catcher in the Rye", "J.D. Salinger", "9780316769488");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "9780061120084");
    library.addBook("1984", "George Orwell", "9780451524935");

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

    return 0;
}
