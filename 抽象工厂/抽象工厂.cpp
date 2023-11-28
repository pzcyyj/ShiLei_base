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

class Light
{
public:
	virtual void show() = 0;
};

class BmwLight : public Light
{
public:
	void show() { std::cout << "BMW light!" << std::endl; }
};

class AudiLight : public Light
{
public:
	void show() { std::cout << "Audi light!" << std::endl; }
};

// 对有一组关联关系的产品簇提供产品对象的统一创建
class AbstractFactory
{
public:
	virtual Car* createCar(std::string name) = 0;
	virtual Light* createCarLight() = 0;
};

class BMWFactory : public AbstractFactory
{
public:
	Light* createCarLight()
	{
		return new BmwLight();
	}
	Car* createCar(std::string name)
	{
		return new BMW(name);
	}
};

class AudiFactory : public AbstractFactory
{
public:
	Light* createCarLight()
	{
		return new BmwLight();
	}
	Car* createCar(std::string name)
	{
		return new Audi(name);
	}
};

int main()
{
	std::unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	std::unique_ptr<AbstractFactory> audifty(new AudiFactory());
	std::unique_ptr<Car> p1(bmwfty->createCar("X6"));
	std::unique_ptr<Car> p2(audifty->createCar("A6"));
	std::unique_ptr<Light> l1(audifty->createCarLight());
	p1->show();
	p2->show();
	l1->show();
}