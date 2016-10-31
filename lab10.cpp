#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Student{
private:
    Student* _prev;
    Student* _next;

public:
    string name;
    string lastname;

    Student() : name(""), lastname("") {}
    Student(string name, string lastname) : name(name), lastname(lastname){}
    Student(const Student& student) : name(student.name), lastname(student.lastname) {}

    bool operator == (const Student& student) const {
        return (this->name == student.name) && (this->lastname == student.lastname);
    }

    void setPrev(Student* student) {
        _prev = student;
    }

    void setNext(Student* student) {
        _next = student;
    }

    Student prev() {
        return *this->_prev;
    }

    Student next() {
        return *this->_next;
    }

};

template <typename T> class MyList {
private:
    T* _begin;
    T* _end;
    int _size;

public:
    MyList() : _begin(nullptr), _end(nullptr), _size(0){}

    MyList(vector<T> objects) : MyList() {
        T* prev;
        for (T t: objects) {
            _size++;
            if (_begin == nullptr) {
                _begin = &t;
                prev = &t;
            } else {
                prev->setNext(&t);
                t.setPrev(prev);
                _end = prev = &t;
            }
        }
    }

    T begin() {
        return *_begin;
    }

    T end() {
        return  *_end;
    }
};

void lab10(){
    vector<Student> students = {Student("Leonid", "Abuzin"), Student("Vladislav", "Anikanov")};
    MyList<Student> myList(students);
    std::cout << myList.begin().name;
    std::cout << myList.end().name;
};
