#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void endProgram();

int main()
{
	SetConsoleTitle("Timer");
	HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
	COORD c;
	clock_t t(clock());
	unsigned short temp(0); //temp to set
	int timer(0); //couting down
	string title(""); //title
	string _title(""); //title

	//set timer
	cout<<"Minutes: "; cin>>temp; timer+=temp*60000;
	cout<<"Seconds: "; cin>>temp; timer+=temp*1000;
	cout<<"Title: "; cin>>title;
	title += ' ';
	SetConsoleTitle(title.c_str());
	
	//clear
	c.X = 0; c.Y = 0; SetConsoleCursorPosition(hOut, c);
	for (size_t i = 0; i < 20; i++)
	{
		cout<<"                                                                                                                        "<<endl;
	}
	
	//hide cursor
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &CURSOR);

	//counting
	while (timer>0)
	{
		t = clock();
		c.X = 0; c.Y = 0; SetConsoleCursorPosition(hOut, c);
		Sleep(111);
		if(timer/60000<10)
			cout<<"0";
		cout<<timer/60000<<":";
		if(timer/1000%60<10)
			cout<<"0";
		cout<<timer/1000%60<<":";
		cout<<timer%1000<<"    "<<endl;

		_title = title;
		//int to string, minutes
		temp = timer/60000;
		if(temp<10)
			title += temp+48;
		else
		{
			short last(temp%10);
			temp /= 10; temp %= 10;
			title += temp+48; title += last+48;
		}
		//seconds
		title+=':';
		temp = timer/1000%60;
		if(temp<10)
		{
			title += 48; //0
			title += temp+48;
		}
		else
		{
			short last(temp%10);
			temp /= 10; temp %= 10;
			title += temp+48; title += last+48;
		}

		SetConsoleTitle(title.c_str());
		title = _title;
		if(kbhit()) break;
		timer -= clock()-t;
	}
	while(true)
	{
		if(kbhit()) break;
		Beep(1500, 500);
	}

	endProgram();
	return 0;
}

void endProgram()
{
	double t(clock()/(1000.0));
	cout<<"\nTime: "<<t<<'s'<<endl;
	cout<<"Press any key to continue . . . "<<endl;
	getch();
}