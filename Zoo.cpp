#include <iostream>
#include <string>

using namespace std;

class Animal {
protected:
    string type;
    string habitat;

public:

    Animal(string type, string habitat) : type(type), habitat(habitat) {}

    virtual ~Animal() {}

    virtual void showInfo() const = 0;
};

class Dog : public Animal {
private:
    string sound;
    int age;
    string name;

public:

    Dog(string type, string habitat, string sound, int age, string name)
        : Animal(type, habitat), sound(sound), age(age), name(name) {}

    void showInfo() const override {
        cout << "ВИД: " << type << "\n";
        cout << "МЕСТООБИТАНИЕ: " << habitat << "\n";
        cout << "КЛИЧКА: " << name << "\n";
    }

    void makeSound() const {
        cout << "ЗВУК: " << sound << "\n";
    }
};

class Cat : public Animal {
private:
    string sound;
    int age;
    string name;

public:

    Cat(string type, string habitat, string sound, int age, string name)
        : Animal(type, habitat), sound(sound), age(age), name(name) {}

    void showInfo() const override {
        cout << "ВИД: " << type << "\n";
        cout << "МЕСТООБИТАНИЕ: " << habitat << "\n";
        cout << "ВОЗРАСТ: " << age << "\n";
    }

    void makeSound() const {
        cout << "ЗВУК: " << sound << "\n";
    }
};

class Bird : public Animal {
private:
    string sound;
    int age;
    string name;

public:

    Bird(string type, string habitat, string sound, int age, string name)
        : Animal(type, habitat), sound(sound), age(age), name(name) {}

    void showInfo() const override {
        cout << "ВИД: " << type << "\n";
        cout << "МЕСТООБИТАНИЕ: " << habitat << "\n";
        cout << "ВОЗРАСТ: " << age << "\n";
    }

    void showAge() const {
        cout << "ЗВУК: " << sound << "\n";
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    Dog dog("СОБАКА", "ВАЛЬЕР", "ГАВ-ГАВ", 5, "ШАРИК");
    Cat cat("КОШКА", "ДОМ", "МЯУ", 3, "ЛЕПЕШКА");
    Bird bird("ПОПУГАЙ", "КЛЕТКА", "ЧИК-ЧИРЫК", 2, "КЕША");

    cout << "СОБАКА:\n";
    dog.showInfo();
    dog.makeSound();
    cout << endl;

    cout << "КОШКА:\n";
    cat.showInfo();
    cat.makeSound();
    cout << endl;

    cout << "ПТИЦА:\n";
    bird.showInfo();
    bird.showAge();
    cout << endl;

    return 0;
}