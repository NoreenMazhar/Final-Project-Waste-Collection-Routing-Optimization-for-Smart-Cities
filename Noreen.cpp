#include"Everything.h"

void display(bool& flag)
{
	const int length = 25;
	system("color 0a");
	system("mode con cols=100 lines=30");

	string prin = "Welcome to Garbage Collection System";

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 2 * length; i++)
		{
			cout << "*";
			if (flag)Sleep(50);
		}
	}
	cout << endl;
	for (int i = 0; i < length + 7; i++)
	{
		cout << "*";
		if (flag)Sleep(50);
	}
	for (int i = 0; i < prin.length(); i++)
	{
		cout << prin[i];
		if (flag)Sleep(50);
	}
	for (int i = 0; i < length + 7; i++)
	{
		cout << "*";
		if (flag)Sleep(50);
	}
	cout << endl;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 2 * length; i++)
		{
			cout << "*";
			if (flag)Sleep(50);
		}
	}
	cout << endl;
	flag = false;
}


void start(int choice)
{
	Graph g;
	bool flag = false;
	Controller c;
	TruckDriver d;
	while (true)
	{
		system("cls");
		
		switch (choice)
		{
		case 1:

			system("cls");
			c.controllerMenu(g);
			break;

		case 2:

			system("cls");
			d.Menu(g);
			break;

		case 3:

			system("cls");
			break;

		default:

			cout << "Invalid choice" << endl;
			break;

		}
		return;
	}

}

int main()
{
	UI u;
	bool flag = false;
	int cho=0;
	while (true)
	{
		system("cls");
		display(flag);

		cout << endl << endl;
		cout << endl << endl;
		cout << endl << endl;

		cout << "\t\t\t\t1. Login" << endl;
		cout << "\t\t\t\t2. Register" << endl;
		cout << "\t\t\t\t3. Exit" << endl;

		cout << endl << endl;

		cout << "\t\t\t\tEnter your choice:";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (u.Login())
			{
			cho=u.CheckNature(u.getEmail(),u.getPassword());
				start(cho);
			}
			break;
		case 2:
			u.Register();
			break;
		case 3:
			return 0;
			break;
		default:
			break;
		}

	}
	return 0;
}