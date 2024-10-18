#pragma once
#ifndef zooadd_hpp
#define zooadd_hpp
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Animal {
protected:
    int Age;
    string Place;
public:
    Animal(int _Age, const char* _Place) {
        Age = _Age;
        Place = _Place;
    }
    ~Animal() {}

    int GetAge() {
        return Age;
    }

    void Move_Animal(const char* _Place) {
        Place = _Place;
    }



    // friend ostream& operator<<(ostream& os, const Animal& An) {
    //     os << endl << endl << "---------------------------------------" << endl << "Error Spotted in File: " << ex.File << endl << "In Function: " << ex.Function << endl 
    //     << "In line: " << ex.Line << endl << ex.Descr << endl << "---------------------------------------" << endl;
    //     return os;
    // }
};

class Cat : public Animal {
protected:
    string Name;
public:
    Cat(int _Age, const char* _Place, const char* _Name) : Animal(_Age, _Place) {
        Name = _Name;
    }

    void Voice() {
        cout << endl << "Meow" << endl;
    }

    void print() {
        cout << "Животное класса: -Cat-, с возрастом " << Age << " лет/года, проживающее в "
        << Place << ", с именем: " << Name << ".";
    }

    void GetName() {
        cout << Name;
    }
};

class Dog : public Animal {
protected:
    string Name;
public:
    Dog(int _Age, const char* _Place, const char* _Name) : Animal(_Age, _Place) {
        Name = _Name;
    }

    void Voice() {
        cout << endl << "Haw" << endl;
    }

    void print() {
        cout << "Животное класса: -Dog-, с возрастом " << Age << " лет/года, проживающее в "
        << Place << ", с именем: " << Name << ".";
    }

    void GetName() {
        cout << Name;
    }
};

class Cow : public Animal {
protected:
    string Name;
public:
    Cow(int _Age, const char* _Place, const char* _Name) : Animal(_Age, _Place) {
        Name = _Name;
    }

    void Voice() {
        cout << endl << "Moo-oo" << endl;
    }

    void print() {
        cout << "Животное класса: -Cow-, с возрастом " << Age << " лет/года, проживающее в "
        << Place << ", с именем: " << Name << ".";
    }

    void GetName() {
        cout << Name;
    }
};

class Sheep : public Animal {
protected:
    string Name;
public:
    Sheep(int _Age, const char* _Place, const char* _Name) : Animal(_Age, _Place) {
        Name = _Name;
    }

    void Voice() {
        cout << endl << "Bee-ee" << endl;
    }

    void print() {
        cout << "Животное класса: -Sheep-, с возрастом " << Age << " лет/года, проживающее в "
        << Place << ", с именем: " << Name << ".";
    }

    void GetName() {
        cout << Name;
    }
};

#endif