#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

#define MAIN 1
#define FIND 2
#define SORT 3
#define EDIT 4

using namespace std;

void printMenu(int mode);

struct Book{
    static int sortBy;
    string title;
    string author;
    int version;
    int year;
    int amount;

    Book(){
        this->title = "";
        this->author = "";
        this->version = 0;
        this->year = 0;
        this->amount = 0;
    }

    friend istream& operator >> (istream& is, Book& book) {
        cout << "Title: ";
        is >> book.title;
        cout << "Author: ";
        is >> book.author;
        cout << "Version: ";
        is >> book.version;
        cout << "Year: ";
        is >> book.year;
        cout << "Amount: ";
        is >> book.amount;
        return is;
    }

    friend ifstream& operator >> (ifstream& ifs, Book& book) {
        ifs >>  book.title >>
                book.author >>
                book.version >>
                book.year >>
                book.amount;
        return ifs;
    }

    friend ostream& operator << (ostream& os, Book& book) {
        os << "1. Title: " << book.title  << endl;
        os << "2. Author: "    << book.author << endl;
        os << "3. Version: "  << book.version  << endl;
        os << "4. Year: "      << book.year   << endl;
        os << "5. Amount: "    << book.amount  << endl;
        os << endl;
        return os;
    }

    friend ofstream& operator << (ofstream& ofs, Book& book) {
        ofs <<  book.title <<
                book.author <<
                book.version <<
                book.year <<
                book.amount;
    }

    void printBookInLine(){
        cout << this->author << ": \"" << this->title << "\" ";
        cout << "ver. " << this->version << " with amount of " << this->amount;
        cout << " " << this->year << "year" << endl;
    }

    bool operator == (const Book& cmp) {
        return (this->author == cmp.author) &&
                (this->title == cmp.title) &&
                (this->version == cmp.version) &&
                (this->amount == cmp.amount) &&
                (this->year == cmp.year);
    }

    bool operator < (const Book& cmp) const {
        switch (sortBy){
            case 1:
                return this->title < cmp.title;
            case 2:
                return this->author < cmp.author;
            case 3:
                return this->version < cmp.version;
            case 4:
                return this->year < cmp.year;
            case 5:
                return this->amount < cmp.amount;
        }
    }
};

struct Library{
    vector<Book> books;
    string path;

    Library(string path){
        this->path = path;
    }

    void loadLibrary(){
        ifstream stream(path);
        if(stream.is_open()){
            int size;
            stream >> size;
            for(int i = 0; i < size; i++){
                Book book;
                stream >> book;
                books.push_back(book);
            }
        } else {

        }
        stream.close();
    }

    void saveLibrary(){
        ofstream stream(path, ofstream::out | ofstream::trunc);
        int size = this->books.size();
        stream << size;
        for (Book book: books){
            stream << book;
        }
        stream.flush();
        stream.close();
    }

    void addBook(){
        Book book;
        cin >> book;
        books.push_back(book);
    }

    void editBook(Book* book){
        system("clear");
        cout << book;
        printMenu(EDIT);
        int key;
        cin >> key;
        if (!(key >= 1 && key < 6)) {
            cout << "Wrong key";
            return;
        }
        switch (key) {
            case 1: {
                string title;
                cin >> title;
                book->title = title;
                break;
            }
            case 2: {
                string author;
                cin >> author;
                book->author = author;
                break;
            }
            case 3: {
                int version;
                cin >> version;
                book->version = version;
                break;
            }
            case 4: {
                int year;
                cin >> year;
                book->year;
                break;
            }
            case 5: {
                int amount;
                cin >> amount;
                book->amount = amount;
                break;
            }
            case 6: {
                books.erase(find(books.begin(), books.end(), *book));
                break;
            }

        }
    }

    void listBooks(){
        int sortKey;
        printMenu(SORT);
        cin >> sortKey;
        if (!(sortKey >= 1 && sortKey <= 5)) {
            cout << "Wrong key";
        }
        Book::sortBy = sortKey;
        sort(books.begin(), books.end());
        for(Book book: books) {
            book.printBookInLine();
        }
    }

    void findBook(){
        vector<Book*> booksFound;
        int key;
        printMenu(FIND);
        cin >> key;
        if (!(key >= 1 && key <= 5)) {
            cout << "Wrong key";
            return;
        }

        switch (key) {
            case 1: {
                string title;
                cin >> title;
                for (Book book: books) {
                    if (book.title == title) {
                        booksFound.push_back(&book);
                    }
                }
                break;
            }
            case 2: {
                string author;
                cin >> author;
                for (Book book: books) {
                    if (book.author == author) {
                        booksFound.push_back(&book);
                    }
                }
                break;
            }
            case 3: {
                int version;
                cin >> version;
                for (Book book: books) {
                    if (book.version == version) {
                        booksFound.push_back(&book);
                    }
                }
                break;
            }
            case 4: {
                int year;
                cin >> year;
                for (Book book: books) {
                    if (book.year == year) {
                        booksFound.push_back(&book);
                    }
                }
                break;
            }
            case 5: {
                int amount;
                cin >> amount;
                for (Book book: books) {
                    if (book.amount == amount) {
                        booksFound.push_back(&book);
                    }
                }
                break;
            }
        }

        if (booksFound.size() == 0){
            cout << "No matches found";
            return;
        }
        cout << "Found " << booksFound.size() << " books" << endl;

        int i = 0;
        for (Book* book: booksFound) {
            cout << i++ << ". ";
            book->printBookInLine();
        }

        int num;
        cout << "Choose book to edit or 0 to exit" << endl;
        cout << ">> ";
        cin >> num;
        if (!(num >= 0 && num < booksFound.size())){
            cout << "Wrong index";
            return;
        } else if (num == 0){
            return;
        }

        editBook(booksFound[num]);
    }
};

void _bookProp(){
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. Version" << endl;
    cout << "4. Year" << endl;
    cout << "5. Amount" << endl;
}

void printMenu(int mode){
    system("clear");
    switch (mode){
        case MAIN:
            cout << "Choose action" << endl;
            cout << "1. Add book" << endl;
            cout << "2. Find/Edit book" << endl;
            cout << "3. List book" << endl;
            cout << "0. Exit" << endl;
            cout << ">> ";
            break;
        case FIND:
            cout << "Choose key for search" << endl;
            _bookProp();
            cout << ">> ";
            break;
        case SORT:
            cout << "Choose sort key" << endl;
            _bookProp();
            cout << "6. Delete book" << endl;
            cout << ">> ";
        case EDIT:
            cout << "What you want to change?" << endl;
            _bookProp();
            cout << ">> ";
        default:
            cout << "Unknown menu, error" << endl;
    }
}

int Book::sortBy = 1;

void lab9(){
    Library library("../Basics/db");
    library.loadLibrary();
    int choice = -1;
    while(choice != 0){
        printMenu(MAIN);
        cin >> choice;
        switch(choice){
        case 1:
            library.addBook();
            break;
        case 2:
            library.findBook();
            break;
        case 3:
            library.listBooks();
            break;
        case 0:
            break;
        default:
            cout << "Неверный пункт меню" << endl;
        }
        system("clear");
    }
    library.saveLibrary();
}
