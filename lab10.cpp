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

    MyList(T objects[], int size) : MyList() {
        T* prev = nullptr;
        for (size_t i = 0; i < size; i++) {
            if (_size == 0) {
                _begin = objects + i;
                prev = objects + i;
            } else {
                prev->setNext(objects + i);
                objects[i].setPrev(prev);
                _end = objects + i;
                prev = objects + i;
            }
            _size++;
        }
    }

    size_t size() const {
        return _size;
    }

    void push_back(T* t) {
        T *toPush = new T(*t);
        if (_size == 0) {
            _begin = toPush;
            _end = toPush;
        } else {
            _end->setNext(toPush);
            toPush->setPrev(_end);
            _end = toPush;
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
            os << i + 1 << ". " <<*(list[i]) << std::endl;
        }
        return os;
    }

    T* operator [] (size_t index) const {
        if (index >= _size) {
            return _end;
        }
        if (index == 0) {
            return _begin;
        }
        T* curr = _begin;
        for (size_t i = 0; i != index; i++) {
            curr = curr->next();
        }
        return curr;
    }

    MyList<T> operator || (const MyList<T>& another) const {
        MyList<T> list;
        for (size_t i = 0; i < _size; i++) {
            list.push_back((*this)[i]);
        }

        for (size_t i = 0; i < another.size(); i++) {
            if (list.get(another[i]) == -1) {
                list.push_back(another[i]);
            }
        }
        return list;
    }

    int get(T* t) {
        for (int i = 0; i < _size; i++) {
            if (*(*this)[i] == *t) {
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
    Student kr[] = {
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

    int krSize = 14;

    Student lab[] = {
        Student("Leonid", "Abuzin"),
        Student("Vladislav", "Anikanov"),
        Student("Gennagiy", "Vasilyev"),
        Student("Maxim", "Demchuk"),
        Student("Ivan", "Zhitnikov"),
        Student("Alexander", "Tischenko")
    };

    int labSize = 6;

    MyList<Student> krList(kr, krSize);
    MyList<Student> labList(lab, labSize);
    MyList<Student> goodGuys = krList || labList;

    std::cout << "Sdavshie TZ" << std::endl;
    std::cout << krList << std::endl;

    std::cout << "Sdavshie labi" << std::endl;
    std::cout << labList << std::endl;

    std::cout << "Molodci" << std::endl;
    std::cout << goodGuys << std::endl;
};
