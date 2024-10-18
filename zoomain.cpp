#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include "zooadd.hpp"
#include <string>

using namespace std;

int main () {
    Cat cat1(3, "Кухня", "Кира");
    Cow cow1(7, "Ангар", "Буренка");
    Sheep sh1(5, "Поле", "Ова");

    cout << endl;
    cat1.print();
    cout << endl;
    cow1.print();
    cout << endl;
    sh1.print();
    cout << endl;

    cat1.GetAge();
    cow1.GetAge();
    sh1.GetAge();

    cat1.Voice();
    cow1.Voice();
    sh1.Voice();
    cout << endl;

    cat1.GetName();
    cout << endl;

    cow1.Move_Animal("Поле");
    sh1.Move_Animal("Ангар");

    cout << endl;
    cat1.print();
    cout << endl;
    cow1.print();
    cout << endl;
    sh1.print();
    cout << endl;

}
