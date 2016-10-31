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
        cout << "Название: ";
        is >> book.title;
        cout << "Автор: ";
        is >> book.author;
        cout << "Издание: ";
        is >> book.version;
        cout << "Год: ";
        is >> book.year;
        cout << "Тираж: ";
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
        os << "1. Название: " << book.title  << endl;
        os << "2. Автор: "    << book.author << endl;
        os << "3. Издание: "  << book.version  << endl;
        os << "4. Год: "      << book.year   << endl;
        os << "5. Тираж: "    << book.title  << endl;
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
        cout << "изд. " << this->version << " в кол-ве " << this->amount;
        cout << " " << this->year << "год" << endl;
    }
//
//    void write(ofstream& fs){
//        fs <<   this->title <<
//                this->author <<
//                this->version <<
//                this->year <<
//                this->amount;
//    }
//
//    void read(ifstream& fs){
//        fs >>   this->title >>
//                this->author >>
//                this->version >>
//                this->year >>
//                this->amount;
//    }

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
            cout << "Неверный ключ";
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
            cout << "Неверный ключ, поиск невозможен";
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
            cout << "Неверный ключ, поиск невозможен";
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
            cout << "По данному ключу и параметру книг не найдено";
            return;
        }
        cout << "Найдено " << booksFound.size() << " книг" << endl;

        int i = 0;
        for (Book* book: booksFound) {
            cout << i++ << ". ";
            book->printBookInLine();
        }

        int num;
        cout << "Выберите книгу для редактирования, или 0, чтобы выйти" << endl;
        cout << ">> ";
        cin >> num;
        if (!(num >= 0 && num < booksFound.size())){
            cout << "Неверный индекс";
            return;
        } else if (num == 0){
            return;
        }

        editBook(booksFound[num]);
    }
};

void _bookProp(){
    cout << "1. Название" << endl;
    cout << "2. Автор" << endl;
    cout << "3. Издание" << endl;
    cout << "4. Год издания" << endl;
    cout << "5. Количество" << endl;
}

void printMenu(int mode){
    system("clear");
    switch (mode){
        case MAIN:
            cout << "Выберите действие" << endl;
            cout << "1. Добавить книгу" << endl;
            cout << "2. Найти/Редактировать книгу" << endl;
            cout << "3. Список всех книг" << endl;
            cout << "0. Выход" << endl;
            cout << ">> ";
            break;
        case FIND:
            cout << "Выберите ключ для поиска" << endl;
            _bookProp();
            cout << ">> ";
            break;
        case SORT:
            cout << "Выберите ключ для сортировки" << endl;
            _bookProp();
            cout << "6. Удалить" << endl;
            cout << ">> ";
        case EDIT:
            cout << "Что хотите изменить?" << endl;
            _bookProp();
            cout << ">> ";
        default:
            cout << "Неизвестное меню. Ошибка..." << endl;
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
