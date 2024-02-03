#include<iostream>
#include"Constants.h"
#include"Force.h"
#include"Object.h"
#include<string>

using namespace std;

const double UNITTIME = 0.01;
Object EMPTYOBJECT = Object();
Force EMPTYFORCE = Force();
vector<Force> FORCES = {};
extern vector<Object> OBJECTS = {};


void Error(string text);

int Choose(string text, int start, int end);

template<typename T>
T Input(string text);


int main()
{
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

template<typename T>
T Input(string text)
{
	string input;
	T value;
	while (true)
	{
		system("cls");
		cout << text << endl << ">>> ";
		cin >> input;
		auto result = from_chars(input.data(), input.data() + input.size(), value);
		//istringstream iss(input);
		if (result.ec == errc{})
		{
			return value;
		}
		else
		{
			Error("ILLEGAL ARGUMENTS!!!");
		}
	}
}

Force AddForce()
{
	bool used = 0;
	string name;
	string source_name;
	string target_name;
	do 
	{
		used = 0;
		 name = Input<string>("Please input force name:");
		for (Force force : FORCES)
		{
			if (name == force.Name())
			{
				Error("The name has been being used.");
				used = 1;
			}
		}
	} while (used);

	do
	{
		used = 0;
		 source_name = Input<string>("Please input the name of the object applying force:");
		for (Object object : OBJECTS)
		{
			if (source_name == object.Name())
			{
				used = 1;
			}
		}
		if (!used)
		{
			Error("The object does not exist.");
		}
	} while (!used);

	do
	{
		used = 0;
		source_name = Input<string>("Please input the name of the object under force:");
		for (Object object : OBJECTS)
		{
			if (source_name == object.Name())
			{
				used = 1;
			}
		}
		if (!used)
		{
			Error("The object does not exist.");
		}
	} while (!used);
}

Force RemoveForce()
{

}

