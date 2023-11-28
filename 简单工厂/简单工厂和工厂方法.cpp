#include <iostream>
#include <string>
#include <memory>

class Car
{
public:
	Car(std::string name) : _name(name) {}
	virtual void show() = 0;
protected:
	std::string _name;
};

class BMW : public Car
{
public:
	BMW(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆宝马汽车" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆奥迪汽车" << _name << std::endl;
	}
};

class Factory
{
public:
	virtual Car* createCar(std::string name) = 0;
};

class BMWFactory : public Factory
{
public:
	Car* createCar(std::string name)
	{
		return new BMW(name);
	}
};

class AudiFactory : public Factory
{
public:
	Car* createCar(std::string name)
	{
		return new Audi(name);
	}
};

int main()
{
	std::unique_ptr<Factory> bmwfty(new BMWFactory());
	std::unique_ptr<Factory> audifty(new AudiFactory());
	std::unique_ptr<Car> p1(bmwfty->createCar("X6"));
	std::unique_ptr<Car> p2(audifty->createCar("A6"));
	p1->show();
	p2->show();
}

/* 简单工厂
enum CarType
{
	BMw,  AUDI
};

class SimpleFactory
{
public:
	Car* createCar(CarType ct, std::string name)
	{
		switch (ct)
		{
		case BMw:
			return new BMW(name);
		case AUDI:
			return new Audi(name);
		default:
			std::cerr << "传入工厂的参数不正确：" << ct << std::endl;
			break;
		}
	}
};

int main()
{
	//Car* p1 = new BMW("X1");
	//Car* p2 = new Audi("A6");
	std::unique_ptr<SimpleFactory> factory(new SimpleFactory());
	std::unique_ptr<Car> p1(factory->createCar(BMw, "X6"));
	std::unique_ptr<Car> p2(factory->createCar(AUDI, "A6"));
	p1->show();
	p2->show();

	return 0;
}
*/

