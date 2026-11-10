#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Store the information about each book
struct Book {
    string title;
    string author;
    int pages;
    string id;
    bool available;
};

// Read all books from the CSV-formatted text file
vector<Book> loadBooks(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Unable to open " << filename << endl;
        return books;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pages, id, status;

        if (getline(ss, title, ',') &&
            getline(ss, author, ',') &&
            getline(ss, pages, ',') &&
            getline(ss, id, ',') &&
            getline(ss, status)) {

            try {
                Book book;
                book.title = title;
                book.author = author;
                book.pages = stoi(pages);
                book.id = id;
                book.available = (status == "true");
                books.push_back(book);
            }
            catch (...) {
                cout << "Skipping invalid book record." << endl;
            }
        }
    }

    return books;
}

// Save books to the file
bool saveBooks(const vector<Book>& books,
               const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Unable to save books!" << endl;
        return false;
    }

    for (const Book& book : books) {
        file << book.title << ","
             << book.author << ","
             << book.pages << ","
             << book.id << ","
             << (book.available ? "true" : "false")
             << "\n";
    }

    return true;
}

// Display all books
void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }

    for (const Book& book : books) {
        cout << "\nID: " << book.id
             << "\nTitle: " << book.title
             << "\nAuthor: " << book.author
             << "\nPages: " << book.pages
             << "\nAvailable: "
             << (book.available ? "Yes" : "No")
             << "\n";
    }
}

// Search for a book by ID
int findBook(const vector<Book>& books,
             const string& id) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    const string filename = "bookData.txt";
    vector<Book> books = loadBooks(filename);

    if (books.empty()) {
        cout << "No book records loaded. "
             << "Check books.txt." << endl;
        return 1;
    }

    string input;

    while (true) {
        cout << "\n===== BOOK MANAGER =====\n";
        cout << "1. Display all books\n";
        cout << "2. Search for a book\n";
        cout << "3. Add a new book\n";
        cout << "4. Update book availability\n";
        cout << "5. Save and exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        if (input == "1") {
            displayBooks(books);
        }
        else if (input == "2") {
            cout << "Enter book ID: ";
            getline(cin, input);

            int index = findBook(books, input);

            if (index == -1) {
                cout << "Book not found.\n";
            }
            else {
                vector<Book> result;
                result.push_back(books[index]);
                displayBooks(result);
            }
        }
        else if (input == "3") {
            Book book;
            string pagesInput;

            cout << "Enter title: ";
            getline(cin, book.title);

            cout << "Enter author: ";
            getline(cin, book.author);

            cout << "Enter number of pages: ";
            getline(cin, pagesInput);

            try {
                book.pages = stoi(pagesInput);
                if (book.pages <= 0) {
                    cout << "Pages must be positive.\n";
                    continue;
                }
            }
            catch (...) {
                cout << "Invalid number of pages.\n";
                continue;
            }

            cout << "Enter book ID: ";
            getline(cin, book.id);

            if (findBook(books, book.id) != -1) {
                cout << "This ID already exists.\n";
                continue;
            }

            book.available = true;
            books.push_back(book);
            cout << "Book added successfully!\n";
        }
        else if (input == "4") {
            cout << "Enter book ID: ";
            getline(cin, input);

            int index = findBook(books, input);

            if (index == -1) {
                cout << "Book not found.\n";
            }
            else {
                books[index].available =
                    !books[index].available;

                cout << "Availability updated to: "
                     << (books[index].available
                         ? "Available" : "Unavailable")
                     << endl;
            }
        }
        else if (input == "5") {
            if (saveBooks(books, filename)) {
                cout << "Books saved. Goodbye!\n";
                break;
            }
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
