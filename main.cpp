#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void endProgram();
void cls();

HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
COORD c;

class timer{
private:
	int time = 0;
	bool isTimer = false;
public:
	void setTime(short s = 0, short m = 0, short h = 0){
		if(!s){
			cout<<"Hours: "; cin>>h;
			cout<<"Minutes: "; cin>>m;
			cout<<"Seconds: "; cin>>s;
		}
		
		int temp = m;
		m = h * 60 + temp;
		temp = s;
		s = m * 60 + temp;
		time = s * 1000; //ms
	}
	void start(){
		isTimer = true;
	}
	void pause(){
		isTimer = false;
	}
	void stop(){
		time = 0;
	}
	void clock(short delay){
		if (isTimer){
			if (time > 0){
				;
			}
			else{
				isTimer = false;
			}
		}
	}
	int getTime(){
		return time;
	}
}timer;

int main(){
	timer.setTime(1,1);

	cout<<timer.getTime();
	getch();
	SetConsoleTitleA("Timer");
	clock_t t(clock());
	unsigned short temp(0); //temp to set
	int timer(0), _timer(0); //couting down
	string title(""), _title(""); //title

	//set timer
	cout<<"Minutes: "; cin>>temp; timer+=temp*60000;
	cout<<"Seconds: "; cin>>temp; timer+=temp*1000;
	cout<<"Title: "; cin>>title;
	title += ' ';
	SetConsoleTitleA(title.c_str());
	
	cls();
	
	//hide cursor
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &CURSOR);

	_timer = timer; //temp
	//reset
	while(true){
		//counting
		while (timer>0){
			t = clock();
			c.X = 0; c.Y = 0; SetConsoleCursorPosition(hOut, c);

			Sleep(444);
			if(timer/60000<10) cout<<"0"; cout<<timer/60000<<":";
			if(timer/1000%60<10) cout<<"0"; cout<<timer/1000%60<<":";
			cout<<timer%1000<<"    "<<endl;	

			_title = title; //temp
			//int to string
			//minutes
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

			SetConsoleTitleA(title.c_str());
			title = _title;

			if(kbhit() == 27) {getch(); break;}

			timer -= clock()-t;
		}

		//beeps
		while(true)
		{
			if(kbhit() == 27) break;
			Beep(1500, 500);
			cout<<"Press any key to stop . . . "<<endl;
			if(kbhit()) {getch(); break;}
		}
		if(kbhit() == 27) break;
		cls();
		cout<<"[ESC] Exit"<<endl;
		cout<<"[Any key] Restart"<<endl;
		if(getch() == 27) break;
		else timer = _timer;
	}

	endProgram();
	return 0;
}

void endProgram()
{
	double t(clock()/(1000.0));
	cout<<"\nTime: "<<t<<'s'<<endl;
	cout<<"Press any key to continue . . . "<<endl;
	cls();
	getch();
}

void cls()
{
	c.X = 0; c.Y = 0; SetConsoleCursorPosition(hOut, c);
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			cout<<"          ";
		}
		cout<<"\n";
	}
	c.X = 0; c.Y = 0; SetConsoleCursorPosition(hOut, c);
}