#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

class Student{
private:
    Student* _prev = nullptr;
    Student* _next = nullptr;

public:
    string name;
    string lastname;

    Student() : name(""), lastname("") {}
    Student(string name, string lastname) : name(name), lastname(lastname){}
    Student(const Student& student) : name(student.name), lastname(student.lastname) {}

    bool operator == (const Student& student) const {
        return (this->name == student.name) && (this->lastname == student.lastname);
    }

    void operator = (const Student& student) {
        name = student.name;
        lastname = student.lastname;
    }

    friend std::ostream& operator << (std::ostream& os, const Student& student) {
        os << student.name << " " << student.lastname;
        return os;
    }

    void setPrev(Student* student) {
        _prev = student;
    }

    void setNext(Student* student) {
        _next = student;
    }

    Student* prev() {
        return this->_prev;
    }

    Student* next() {
        return this->_next;
    }

};

template <typename T> class MyList {
private:
    T* _begin;
    T* _end;
    size_t _size;

public:
    MyList() : _begin(nullptr), _end(nullptr), _size(0){}

    MyList(vector<T> objects) : MyList() {
        T* prev = nullptr;
        for (auto t = objects.begin(); t != objects.end(); t++) {
            if (_size == 0) {
                _begin = &*t;
                prev = &*t;
            } else {
                prev->setNext(&*t);
                (*t).setPrev(prev);
                _end = &*t;
                prev = &*t;
            }
            _size++;
        }
    }

    size_t size() const {
        return _size;
    }

    void push_back(T& t) {
        if (_size == 0) {
            _begin = &t;
            _end = &t;
        } else {
            _end->setNext(&t);
            t.setPrev(_end);
            _end = &t;
        }
        _size++;
    }

    T pop_back() {
        T* ret = _end;
        _end = _end->prev();
        _end->setNext(nullptr);
        return *ret;
    }

    friend std::ostream& operator << (std::ostream& os, MyList<T>& list) {
        for (size_t i = 0; i < list.size(); i++) {
            os << list[i] << std::endl;
        }
        return os;
    }

    T operator [] (size_t index) const {
        if (index >= _size) {
            return *_end;
        }
        if (index == 0) {
            return *_begin;
        }
        T* curr = _begin;
        for (size_t i = 0; i != index; i++) {
            curr = curr->next();
        }
        return *curr;
    }

    MyList<T> operator && (const MyList<T>& another) const {
        MyList<T> list;
        T tmp;
        for (size_t i = 0; i < _size; i++) {
            tmp = (*this)[i];
            list.push_back(tmp);
        }

        for (size_t i = 0; i < another.size(); i++) {
            tmp = another[i];
            if (list.get(tmp) == -1) {
                list.push_back(tmp);
            }
        }
        return list;
    }

    int get(T& t) {
        for (int i = 0; i < _size; i++) {
            if ((*this)[i] == t) {
                return i;
            }
        }
        return -1;
    }

    T begin() {
        return *_begin;
    }

    T end() {
        return  *_end;
    }
};

void lab10(){
    vector<Student> kr = {
        Student("Leonid", "Abuzin"),
        Student("Vladislav", "Anikanov"),
        Student("Vera", "Bezrukavaya"),
        Student("Gennagiy", "Vasilyev"),
        Student("Ilya", "Vasilyev"),
        Student("Danila", "Vorontsov"),
        Student("Anton", "Getman"),
        Student("Ilya", "Grischenko"),
        Student("Evgeniy", "Dominov"),
        Student("Daniil", "Evseev"),
        Student("Ivan", "Zhitnikov"),
        Student("Oleg", "Zaplatin"),
        Student("Alexander", "Tischenko"),
        Student("Yan", "Tsvitchenko")
    };

    vector<Student> lab = {
        Student("Leonid", "Abuzin"),
        Student("Vladislav", "Anikanov"),
        Student("Gennagiy", "Vasilyev"),
        Student("Maxim", "Demchuk"),
        Student("Ivan", "Zhitnikov"),
        Student("Alexander", "Tischenko")
    };

    MyList<Student> krList(kr);
    MyList<Student> labList(lab);
    MyList<Student> goodGuys = krList && labList;

//    std::cout << "Сдавшие ТЗ" << std::endl;
//    std::cout << krList << std::endl;
//
//    std::cout << "Сдающие лабы" << std::endl;
//    std::cout << labList << std::endl;
//
//    std::cout << "Молодцы" << std::endl;
//    std::cout << goodGuys;

};
