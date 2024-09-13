// Программа для того, чтобы вспомнить наследование классов.
 
#include <iostream>
#include <clocale>
#include <Windows.h>

using namespace std;

class Zoo { // класс-родитель для двух других (Cat, Dog).
private:
	int weight; // у дочерних классов нет доступа к private!
	string country;
	string type;
protected:
	string sound; // protected для !примера! того, что данные переменные 
	int cost; // можно использовать в дочерних классах (классах-наследниках).
public:
	Zoo() {}
	Zoo(string type, string country, int weight)
	{
		this->type = type;
		this->country = country;
		this->weight = weight;
	}

	void print()
	{
		cout << this->type << ", " << country << ", " << cost << " RUB, " << weight << " кг, " << "'" << sound << "'" << endl;
	}
};


class Cat: public Zoo { // дочерний класс от Zoo.
private:
	string name;
public:
	Cat(string type, string country, int weight, string name) : Zoo(type, country, weight)
	{
		this->name = name;
		this->sound = "МЯВ";
		this->cost = 5480;
		Zoo::print();
		cout << "ИМЯ: " << name << endl;
	}
};

class Dog: public Zoo { // также дочерний класс от Zoo
private:
	string name;
public:
	Dog() {}
	Dog(string type, string country, int weight, string name): Zoo(type, country, weight)
	{
		this->name = name;
		this->sound = "ГАВ";
		this->cost = 23500;
		Zoo::print();
		cout << "ИМЯ: " << name << endl;
	}

	void print_info()
	{
		Zoo::print();
		cout << "ИМЯ: " << name << endl;
	}
};

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	cout << "Введите имя для собаки." << endl;
	string a;
	cin >> a;
	Dog d1("Собака", "Польша", 5, a);
	cout << "Введите имя для кошки." << endl;
	string b;
	cin >> b;
	Cat c1("Кошка", "Чехия", 2, b);
	return 0;
}