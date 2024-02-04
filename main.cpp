#include<iostream>
#include<cctype>
#include"Constants.h"
#include"Force.h"
#include"Object.h"
#include<string>

using namespace std;

const double UNITTIME = 0.01;
const double PI = 3.141592653589793;
vector<Force*> FORCES = {};
vector<Object*> OBJECTS = {};
Object EMPTYOBJECT = Object("EMPTY", {}, {}, 0, {0,0}, {0,0},0,0);
Force EMPTYFORCE = Force("EMPTY",&EMPTYOBJECT,&EMPTYOBJECT,0.0,0.0);


void Error(string text);

int Choose(string text, int start, int end);

void Input(string text);

Force AddForce();

void RemoveForce();

int main()
{
	Object O = Object("O", {}, {}, 10, { 0,0 }, {0,0},0,0);
	Force F = AddForce();
	F.Apply();
	F.ReactionForce();
	F.ForceOrthogonalDecomposition_x();
	O.Update();
	system("pause");
	return 0;
}


void Error(string text)
{
	system("cls");
	cout << text << endl;
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 02");
	system("pause");
}


int Choose(string text, int start, int end)
{
	int choice;
	while (true)
	{
		system("cls");
		cout << text << endl << ">>> ";
		cin >> choice;
		if (start <= choice && choice <= end)
		{
			return choice;
		}
		else
		{
			Error("ILLEGAL ARGUMENTS!!!");
			cin.ignore(INT_MAX, '\n');
			cin.clear();
		}
	}
}


void Input(string text)
{
	string input;
	system("cls");
	cout << text << endl << ">>> ";
}

Force AddForce()
{
	bool existed = 0;
	string name;
	Object* source = &EMPTYOBJECT;
	Object* target = &EMPTYOBJECT;
	string source_name;
	string target_name;
	double magnitude;
	int angle;
	do
	{
		existed = 0;
		Input("Please input force name");
		cin >> name;
		for (int i = 0; i < FORCES.size(); i++)
		{
			if (name == (*FORCES[i]).Name())
			{
				Error("The name has been being used.");
				existed = 1;
			}
		}
	} while (existed);

	do
	{
		existed = 0;
		Input("Please input the name of the object applying force");
		cin >> source_name;
		for (int i = 0; i <OBJECTS.size(); i++)
		{
			if ((*OBJECTS[i]).Name() == source_name)
			{
				source = OBJECTS[i];
				existed = 1;
			}
		}
		if (!existed)
		{
			Error("The object does not exist.");
		}
	} while (!existed);
	do
	{
		existed = 0;
		Input("Please input the name of the object under force");
		cin>> target_name;
		for (int i = 0; i <OBJECTS.size(); i++)
		{
			if ((*OBJECTS[i]).Name() == target_name)
			{
				target = OBJECTS[i];
				existed = 1;
			}
		}
		if (!existed)
		{
			Error("The object does not exist.");
		}
	} while (!existed);

		Input("Please input the magnitude of the force");
		cin >> magnitude;


	while (true)
	{
		Input("Please input the angle of the force(Rotate counterclockwise from the non-negative X-axis)");
		cin >> angle;
		if (angle > 360 || angle < 0 )
		{
			Error("Please input a float between 0 and 360!");
			cin.ignore(INT_MAX, '\n');
			cin.clear();
			continue;
		}
		break;
	}
	
	Force force = Force(name, source, target, magnitude, float((angle * PI) / 180));
	return force;
}

void RemoveForce()
{
	bool existed = 0;
	string name;
	do
	{
		existed = 0;
		Input("Please input force name");
		cin>>name;
		for (int i = 0; i <FORCES.size(); i++)
		{
			if ((*FORCES[i]).Name() == name)
			{
				(*FORCES[i]).Remove();
				FORCES.erase(FORCES.begin() + i);
				existed = 1;
			}
		}
		if (!existed)
		{
			Error("The force does not exist.");
		}
	} while (!existed);
}

