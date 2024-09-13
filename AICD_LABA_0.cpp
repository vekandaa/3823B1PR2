#include <iostream>
#include <clocale>
#include <Windows.h>
using namespace std;


class Zoo {
	short age;
	string country;
	int month_in_zoo;
public:
	string enot_name = "Не установлено";
	string croco_name = "Не установлено";
	string ms_name = "Не установлено";
	string pavlin_name = "Не установлено";

	// КОНСТРУКТОР ПО УМОЛЧАНИЮ!

	void Enot()
	{
		enot_name = this->enot_name;
		age = 6;
		country = "Norway";
		month_in_zoo = 33;
		cout << "1. Енот" << '\n' << "Имя: " << enot_name << '\n' << "Возраст: " << age << '\n' << "Страна: " << country << '\n';
		cout << "В зоопарке: " << month_in_zoo << " мес." << '\n';
	}

	void Crocodile()
	{
		croco_name = this->croco_name;
		age = 14;
		country = "South Africa";
		month_in_zoo = 144;
		cout << "2. Крокодил" << '\n' << "Имя: " << croco_name << '\n' << "Возраст: " << age << '\n' << "Страна: " << country << '\n';
		cout << "В зоопарке: " << month_in_zoo << " мес." << '\n';
	}

	void Mouse()
	{
		ms_name = this->ms_name;
		age = 1;
		country = "Russia";
		month_in_zoo = 4;
		cout << "3. Мышь" << '\n' << "Имя: " << ms_name << '\n' << "Возраст: " << age << '\n' << "Страна: " << country << '\n';
		cout << "В зоопарке: " << month_in_zoo << " мес." << '\n';
	}

	void Pavlin()
	{
		pavlin_name = this->pavlin_name;
		age = 4;
		country = "Serbia";
		month_in_zoo = 37;
		cout << "4. Павлин" << '\n' << "Имя: " << pavlin_name << '\n' << "Возраст: " << age << '\n' << "Страна: " << country << '\n';
		cout << "В зоопарке: " << month_in_zoo << " мес." << '\n';
	}
};

void main_menu(Zoo s1)
{
	int a = 9;
	while (a == 9)
	{
		cout << "-----------------------------------------------------------" << '\n';
		cout << "Добро пожаловать в ваш зоопарк!" << '\n' << "Пожалуйста, выберите животное из списка!" << '\n';
		cout << "1. Енот" << '\n' << "2. Крокодил" << '\n' << "3. Мышь" << '\n' << "4. Павлин" << '\n' << "5. Установить имя" << '\n';
		int c;
		cin >> c;
		if (c == 1)
		{
			s1.Enot();
		}
		if (c == 2)
		{
			s1.Crocodile();
		}
		if (c == 3)
		{
			s1.Mouse();
		}
		if (c == 4)
		{
			s1.Pavlin();
		}
		if (c == 5)
		{
			cout << "1. Енот" << '\n' << "2. Крокодил" << '\n' << "3. Мышь" << '\n' << "4. Павлин" << '\n';
			int g;
			cin >> g;
			if (g == 1)
			{
				cout << "Введите имя для енота!" << endl;
				string name;
				cin >> name;
				s1.enot_name = name;
			}
			if (g == 2)
			{
				cout << "Введите имя для крокодила!" << endl;
				string name;
				cin >> name;
				s1.croco_name = name;
			}
			if (g == 3)
			{
				cout << "Введите имя для мыши!" << endl;
				string name;
				cin >> name;
				s1.ms_name = name;
			}
			if (g == 4)
			{
				cout << "Введите имя для павлина!" << endl;
				string name;
				cin >> name;
				s1.pavlin_name = name;
			}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	setlocale(0, "");
	Zoo s1;
	main_menu(s1);
}
