#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
������� ������������ ��� ���������� ������ ��� ������ � ������� ����������� ������ ��������.
������� ��������� ���� �������, ����� ��������� ��� ����������������� �������:
- � ���������� ������������ ������� ����� ��������;
- ��-�� ����� ��������� ������� �� �������� ������;
- ������� ����� ��������� �������� ����� ������� �����;
- ������ ������ �������� ����� �������� ������������ ��������� ����������� ����������� ��������, ��������� ������� ��������� ��������.
*/

// Flyweight (House) - ��������� ���������, � ������� �������� �������������� ����� �������� ������� ���������.

class Base abstract	
{
protected:
	int speed;
	int force;

public:
	virtual void Show(double longitude, double latitude) abstract;		
};

/*
ConcreteFlyweight (PanelHouse) - ���������� ��������������.
��������� ��������� ������ Flyweight � ��������� ��� ������������� ���������� ���������.
������ ������ ConcreteFlyweight ������ ���� �����������.
����� ����������� �� ��������� ������ ���� ����������, �� ���� �� ��������� �� ���������.
*/
class LightInfantry: public Base
{

public:
	LightInfantry()
	{
		speed = 20;
		force = 10;	
	}
	void Show(double longitude, double latitude) override	
	{
		char buffer[500];
		sprintf_s(buffer, "Light infantry has speed 20 strength 10: \ncoordinates: %f - latitude   %f - longitude", latitude, longitude);
		cout << buffer << endl;
	}
};

/*
ConcreteFlyweight (BrickHouse) - ���������� ��������������.
��������� ��������� ������ Flyweight � ��������� ��� ������������� ���������� ���������.
������ ������ ConcreteFlyweight ������ ���� �����������.
����� ����������� �� ��������� ������ ���� ����������, �� ���� �� ��������� �� ���������.
*/
class TransportVehicles: public Base
{
public:
	TransportVehicles()
	{	
		speed = 70;
		force = 0;	
	}
	void Show(double longitude, double latitude) override	
	{
		char buffer[500];
		sprintf_s(buffer, "Transport vehicles has speed 70 strength 0: \ncoordinates: %f - latitude   %f - longitude", latitude, longitude);
		cout << buffer << endl;
	}
};

class UnearthlyMilitaryEquipment : public Base	
{
public:
	UnearthlyMilitaryEquipment()
	{	
		speed = 15;
		force = 150;	
	}
	void Show(double longitude, double latitude) override	
	{
		char buffer[500];
		sprintf_s(buffer, "Unearthly military equipment has speed 15 strength 150: \ncoordinates: %f - latitude   %f - longitude", latitude, longitude);
		cout << buffer << endl;
	}
};

class Aircraft : public Base
{
public:
	Aircraft()	
	{
		speed = 300;
		force = 100;
	}
	void Show(double longitude, double latitude) override
	{
		char buffer[500];
		sprintf_s(buffer, "Aircraft has speed 300 strength 100: \ncoordinates: %f - latitude   %f - longitude", latitude, longitude);
		cout << buffer << endl;
	}
};

/*
FlyweightFactory - ������� ���������������:
- ������� �������-�������������� � ��������� ���;
- ������������ ������� ���������� ���������������. ����� ������ ����������� ��������������,
������ FlyweightFactory ������������� ������������ ���������.
*/
class BaseFactory
{
	map<string, Base*> base;	
public:
	BaseFactory()
	{
		base["infantry"] = new LightInfantry();	
		base["transport"] = new TransportVehicles();
		base["equipment"] = new UnearthlyMilitaryEquipment();	
		base["aircraft"] = new Aircraft();
	}
	~BaseFactory()
	{
		delete base["infantry"];	
		delete base["transport"];
		delete base["equipment"];	
		delete base["aircraft"];	
		base.clear();
	}
	Base* GetBase(string key)	
	{
		if (base[key]!= nullptr)
			return base[key];
		else
			return nullptr;
	}
};

int main()
{
	/*
	 Client - ������:
		- ������ ������ �� ������ ��� ���������� ���������������;
		- ��������� ��� ������ ������� ��������� ���������������.
	 */

	double longitude = 37.61;
	double latitude = 55.74;

	BaseFactory *baseFactory = new BaseFactory();	

	for (int i = 0; i < 5; i++)
	{
		Base*infantryBase = baseFactory->GetBase("infantry");		
		if (infantryBase != nullptr)
			infantryBase->Show(longitude, latitude);	
		longitude += 0.1;
		latitude += 0.1;
	}
	cout << "\n";	
	for (int i = 0; i < 5; i++) 
	{
		Base*transportBase = baseFactory->GetBase("transport");				
		if (transportBase != nullptr)		
			transportBase->Show(longitude, latitude);		
		longitude += 0.1;
		latitude += 0.1;
	}
	cout << "\n";
	for (int i = 0; i < 5; i++)
	{
		Base*equipmentBase = baseFactory->GetBase("equipment");	
		if (equipmentBase != nullptr)
			equipmentBase->Show(longitude, latitude);	
		longitude += 0.1;
		latitude += 0.1;
	}

	cout << "\n";
	for (int i = 0; i < 5; i++)
	{
		Base* aircrafttBase = baseFactory->GetBase("aircraft");	
		if (aircrafttBase != nullptr)	
			aircrafttBase->Show(longitude, latitude);	
		longitude += 0.1;
		latitude += 0.1;
	}

	delete baseFactory;
	system("pause");
}