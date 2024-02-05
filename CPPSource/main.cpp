#include<iostream>
#include<cctype>
#include"Constants.h"
#include"Force.h"
#include"Object.h"
#include<string>
#include<Windows.h>

using namespace std;

const int X = 200;
const int Y = 150;
const double UNITTIME = 0.01;
const double PI = 3.141592653589793;
vector<Force*> FORCES = {};
vector<Object*> OBJECTS = {};
Object EMPTYOBJECT = Object("EMPTY", {}, {}, 0, { 0,0 }, { 0,0 }, 0, 0,0,0);
Force EMPTYFORCE = Force("EMPTY", &EMPTYOBJECT, &EMPTYOBJECT, 0.0, 0.0);

void Error(string text);

int Choose(string text, int start, int end);

void Input(string text);

Force AddForce();

void RemoveForce();

void DrawRectangle(int x, int y,int w,int h);

void BuildScene(int x, int y);

void UpdateSecne(int x, int y);

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	Object O = Object("O", {}, {}, 10, { 0,0 }, { 0,0 }, 150, 100,10,10);
	Force F = Force("F",&O,&O,float(100),double(0));
	F.Apply();
	//Force f = Force("f", &O, &O, float(9), double(PI));
	//f.Apply();
	//O.Update();
	cout << F << endl;
	//cout << f << endl;
	cout << O << endl;
	system("pause");
	FreeConsole();
	AllocConsole();
	BuildScene(X, Y);
	system("pause");

	//DrawRectangle(50,50,50,50);
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE,0);
	// 
	while (true)
	{
		Sleep(UNITTIME);
		UpdateSecne(X, Y);
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
			GetAsyncKeyState(VK_SHIFT) & 0x8000 and
			GetAsyncKeyState('E') & 0x8000)
		{
			break;
		}
	}
	system("PAUSE");
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
	float magnitude;
	double angle;
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
		for (int i = 0; i < OBJECTS.size(); i++)
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
		cin >> target_name;
		for (int i = 0; i < OBJECTS.size(); i++)
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
		if (angle > 360 || angle < 0)
		{
			Error("Please input a float between 0 and 360!");
			cin.ignore(INT_MAX, '\n');
			cin.clear();
			continue;
		}
		break;
	}

	Force force = Force(name, source, target, float(magnitude), double(angle));
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
		cin >> name;
		for (int i = 0; i < FORCES.size(); i++)
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

void DrawRectangle(int x, int y,int w,int h)
{
	string rect;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(2*x),short(y) });
	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			if (j == 1 || j == w || i == 1 || i == h)
			{
				cout << "■";
			}
			else
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(2 * x + 2 * j),short(y + i - 1) });
			}
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(2*x),short(y+i) });
	}
	
}

void BuildScene(int x, int y)
{
	system("cls");
	string scene;
	for (int i = 1; i <= y; i++)
	{
		for (int j = 1; j <= x; j++)
		{
			if (i == 1 || i == y || j == 1 || j == x)
			{
				scene+= "■";
			}
			else
			{
				scene += "  ";
			}

		}
		scene += "\n";
	}

	cout<<scene;
}

void UpdateSecne(int x, int y)
{
	//COORD cursor_pos = { 0,0 };
	system("cls");
	BuildScene(x, y);
	double x_object;
	double y_object;
	int w_object;
	int h_object;
	for (int i = 0; i < OBJECTS.size(); i++)
	{
		if ((*OBJECTS[i]).Name() != "EMPTY")
		{
			x_object = (*OBJECTS[i]).XPosition();
			y_object = (*OBJECTS[i]).YPosition();
			w_object = (*OBJECTS[i]).Width();
			h_object = (*OBJECTS[i]).Height();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(x_object),short(y_object) });
			DrawRectangle(x_object, y_object,w_object,h_object);
			(*OBJECTS[i]).Update();
		}
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,short(Y) });

}