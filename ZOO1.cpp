#include <iostream>
#include <string>

using namespace std;

class Animal {
protected:
    string species;  // название вида
    string habitat;  // местообитание

public:

    Animal(string species, string habitat) : species(species), habitat(habitat) {}

    virtual ~Animal() {}

    virtual void showInfo() const = 0;
};

class Dog : public Animal {
private:
    string sound;  
    int age;       
    string name;   

public:

    Dog(string species, string habitat, string sound, int age, string name)
        : Animal(species, habitat), sound(sound), age(age), name(name) {}

    void showInfo() const override {
        cout << "ВИД: " << species << "\n";
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
   
    Cat(string species, string habitat, string sound, int age, string name)
        : Animal(species, habitat), sound(sound), age(age), name(name) {}

    void showInfo() const override {
        cout << "ВИД: " << species << "\n";
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
   
    Bird(string species, string habitat, string sound, int age, string name)
        : Animal(species, habitat), sound(sound), age(age), name(name) {}
   
    void showInfo() const override {
        cout << "ВИД: " << species << "\n";
        cout << "МЕСТООБИТАНИЕ: " << habitat << "\n";
        cout << "ЗВУК: " << sound << "\n";
    }
   
    void showAge() const {
        cout << "ВОЗРАСТ: " << age << "\n";
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    Dog dog("СОБАКА", "ДОМ", "ГАВ-ГАВ", 5, "ПОНЬЧИК");
    Cat cat("КОШКА", "КВАРТИРА", "МЯЯЯЯЯЯЯЯЯУ", 3, "ДРАНАЯ");
    Bird bird("ПОПУГ", "КЛЕТКА", "ЧИРИК-ЧИРИК", 2, "КИРИЛЛ");

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
