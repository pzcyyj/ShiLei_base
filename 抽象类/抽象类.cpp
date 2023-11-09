#include <iostream>
using namespace std;
#include <string>

class Car
{
public:
	Car(string name, double oil) : _name(name), _oil(oil) {}
	double getLeftMiles() {
		return _oil * getMilesPerGallon();
	}
	string getName() { return _name; }
protected:
	string _name;
	double _oil;
	virtual double getMilesPerGallon() = 0;
};

double showLeftMiles(Car& car)
{
	return car.getLeftMiles();
}

class Benz : public Car
{
public:
	Benz(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 19.0; }
};

class BMW : public Car
{
public:
	BMW(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 17.0; }
};

class Audi : public Car
{
public:
	Audi(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 16.0; }
};

int main()
{
	Benz c1("Benz", 10.0);
	cout << c1.getName() << ": " << showLeftMiles(c1) << endl;
	BMW c2("BMW", 10.0);
	cout << c2.getName() << ": " << showLeftMiles(c2) << endl;
	Audi c3("Audi", 10.0);
	cout << c2.getName() << ": " << showLeftMiles(c3) << endl;


	return 0;
}