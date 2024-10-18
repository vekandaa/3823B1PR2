#include <iostream>
#include <string>

using namespace std;

class Animals {
protected:
    string type;
    int age;
    string place;
public:
    Animals(string t, int a, string p) : type(t), age(a), place(p) {}

    virtual void voice() = 0;
    void setplace(string newplace) { place = newplace; }

    int getage() { return age; };
    string gettype() { return type; };
    string getplace() { return place; }
};

class Cat : public Animals {
public:
    Cat(int a, string p) : Animals("Cat", a, p) {}

    virtual void voice() { cout << "~ Meow " << endl; }
};

class Dog : public Animals {
public:
    Dog(int a, string p) : Animals("Dog", a, p) {}

    virtual void voice() { cout << "~ Woof " << endl; }
};

class Mouse : public Animals {
public:
    Mouse(int a, string p) : Animals("Mouse", a, p) {}

    virtual void voice() { cout << "~ Pi " << endl; }
};

void swapplaces(Animals* a1, Animals* a2) {
    string tmp = a1->getplace();
    a1->setplace(a2->getplace());
    a2->setplace(tmp);
}

int main()
{
    Animals* a[5];
    a[1] = new Cat(3, "House");
    a[2] = new Dog(10, "Box");
    a[3] = new Mouse(1, "Field");

    int animalnumber, actionchoice;
    char continuechoice = 'y';

    while (continuechoice == 'y') {

        cout << "Enter the number of the animal: 1 - Cat, 2 - Dog, 3 - Mouse: ";
        cin >> animalnumber;

        switch (animalnumber) {
        case 1:
        case 2:
        case 3:
            cout << "Choose an action: 1 - Voice, 2 - Age, 3 - Place, 4 - Swap places: ";
            cin >> actionchoice;
            switch (actionchoice) {
            case 1:
                cout << a[animalnumber]->gettype() << " says: ";
                a[animalnumber]->voice();
                break;
            case 2:
                cout << a[animalnumber]->gettype() << " age: " << a[animalnumber]->getage() << endl;
                break;
            case 3:
                cout << a[animalnumber]->gettype() << " place: " << a[animalnumber]->getplace() << endl;
                break;
            case 4:
                int animal1, animal2;
                cout << "Enter the animals to swap places (1-3): ";
                cin >> animal1 >> animal2;
                swapplaces(a[animal1], a[animal2]);
                cout << "Swapped places between " << a[animal1]->gettype() << " and " << a[animal2]->gettype() << endl;
                break;
            }

            break;
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> continuechoice;

    }
}