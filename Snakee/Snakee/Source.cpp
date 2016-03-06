//Autor Miko³aj M., Mikee

#include<iostream>
#include<cstdio>
#include<windows.h>
#include<ctime>

using namespace std;

#define right 1
#define left 2
#define up 3
#define down 4


int x[20];
int y[20];
int length = 5;                               //sta³a struktur robaka
int score = 0;                                //poczatkowy wynik gry to 0
int last_key = right;                         //kierunek robaka na starcie gry standardowo jest w prawo
bool feed = false;                            //sta³a boolowska odpowiadajaca czy * jest ju¿ na planszy czy nie, w pocz¹tkowym stadium gry * nie ma


int key_press();                            //sterowanie robakiem
int food();                                 //funkcja odpowiadaj¹ca za losowanie i wyœwietlanie *
int wall();                                 //tworzenie scian
void gotoxy(int, int);                       //sterowanie kursorem CMD


int main()
{
	int i;
	srand(time(NULL));
	gotoxy(20, 20);
	cout << "Wcisnij klawisz enter, aby kontynuowac...";
	getchar();
	system("cls");
	wall();                                    //tworzenie planszy
	for (i = length; i >= 0; i--)                        //pozycja weza na starcie gry
	{
		x[i] = 15 - i;
		y[i] = 15;
	}
	while (1)
	{
		gotoxy(68, 1);   cout << "Wynik: " << score;             //wyswietlanie zdobytych * z boku planszy
		food();
		for (i = length - 1; i>0; i--)                         //pêtla przesuwajaca segmenty robaka
		{
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}

		for (i = length - 1; i >= 0; i--)                       //tworzenie struktury robaka
		{
			gotoxy(x[i], y[i]);            //"cialo" robaka
			cout << "o";
		}

		gotoxy(x[0], y[0]);                              //"glowa" robaka
		cout << "O";

		gotoxy(x[length - 1], y[length - 1]);                //wstawianie pustych pol w miejsca po segmentach robaka
		cout << " ";

		key_press();

		//jezeli gracz zdobyl 10 punktow to wygrywa
		if (score == 10)
		{
			Sleep(2000);
			system("cls");
			gotoxy(20, 20);
			cout << "Wygrales! Zdobyles maksymalna ilosc punktow.\n";
			gotoxy(20, 21);
			break;
		}
		//jezeli robak uderzyl w bande (sciane) to gracz przegrywa
		if (y[1] == 1 || y[1] == 23 || x[1] == 1 || x[1] == 63)
		{
			Sleep(2000);
			system("cls");
			gotoxy(15, 20);
			cout << "Udzerzyles w sciane. Przegrales!";
			break;
		}
		//jezeli robak najedzie na siebie to gracz przegrywa
		for (i = length; i>1; i--)
			if (x[1] == x[i] && y[1] == y[i])
			{
				Sleep(2000);
				system("cls");
				gotoxy(15, 20);
				cout << "Wjechales sam na siebie. Przegrales!" << " Twoj wynik to: " << score;
				Sleep(3000);
				getchar();
				return 1;
				break;
			}
		Sleep(50);
	}
	cout << " Twoj wynik to: " << score;
	Sleep(3000); getchar();
	return 0;
}


int key_press() {              //sprawdz jesli jest wcisnieny dowolny przycisk i ktory
	if (GetAsyncKeyState(VK_DOWN) && last_key != up)last_key = down;
	if (GetAsyncKeyState(VK_RIGHT) && last_key != left)last_key = right;
	if (GetAsyncKeyState(VK_LEFT) && last_key != right)last_key = left;
	if (GetAsyncKeyState(VK_UP) && last_key != down)last_key = up;

	if (last_key == down)y[0]++;
	if (last_key == right)x[0]++;
	if (last_key == left)x[0]--;
	if (last_key == up)y[0]--;
	return 0;
}

int j, k;
int food()
{
	int i;
	if (feed == false)
	{
		j = rand() % 61 + 2;
		k = rand() % 19 + 2;
		for (int i = 0; i<length; i++)       //sprawdzenie czy wylosowana * nie znajduje siê na strukturach robaka
		{
			if (j == x[i] && k == y[i])
			{
				j = rand() % 61 + 2;
				k = rand() % 19 + 2;
				i = 0;
			}
		}
	}
	gotoxy(j, k);
	cout << "*";
	if (x[0] == j && y[0] == k)
	{
		feed = false;
		length = length + 1;         //dodanie segmentu do weza
		score = score + 1;           //dodanie punktow
	}
	else feed = true;
	return 0;
}

int wall()
{
	int xpos, ypos;

	gotoxy(1, 1);                //tworzenie + w rogach planszy
	cout << "+";
	gotoxy(63, 1);
	cout << "+";
	gotoxy(1, 23);
	cout << "+";
	gotoxy(63, 23);
	cout << "+";

	for (xpos = 2; xpos <= 62; xpos++)  //poziome krawedzie
	{
		gotoxy(xpos, 1);
		cout << "-";
		gotoxy(xpos, 23);
		cout << "-";
	}

	for (ypos = 2; ypos <= 22; ypos++)  //pionowe krawedzie
	{
		gotoxy(1, ypos);
		cout << "|";
		gotoxy(63, ypos);
		cout << "|";
	}

	return 0;
}

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}