#include<iostream>
#include <iomanip>
#include<vector>
#include "resource.h"

using namespace std;

vector<vector<char>> field(10, vector <char>(10));  //game field 10x10
int G_money = 500;
int G_people = 50;
int G_plus = 0;       
int G_fabrik_count = 0;
int G_difficult = 0;
int G_total_people = 0;

class Fabrik {
public:
	int Get_People() {
		return f_people;
	}
	int Get_Kost() {
		return f_kost;
	}
	int Get_Payment() {
		return f_payment;
	}
private:
	int f_people = 50; //how much people need
	int f_kost = 200;  // how much need to pay for this building
	int f_payment = 25;//how much it gives
};

class Dorf {
public:
	int Get_People() {
		return d_people;
	}
	int Get_Kost() {
		return d_kost;
	}
private:
	int d_people = 10; //how much people need
	int d_kost = 40;   // how much need to pay for this building
};

int MainMenu();
void Game();
void Rules();
void Update_Display();
void Entering_of_xy_type(bool& FLAG);
void End_game(const bool &FLAG);
void Random_event();
int Becom_normal_int(const char& type);
void Paint_menu();
void Enter_difficult();


int main() {
	
	MainMenu();

	return 0;
}

int MainMenu() {
	int user_enter;
	do {
		Paint_menu();
		user_enter= Becom_normal_int(' ');
	} while (user_enter != 1 && user_enter != 2&&user_enter!=3);
	
	if (user_enter == 1) {
		system("cls");
		Enter_difficult();
	}
	else if(user_enter==2) {
		system("cls");
		Rules();
	}
	else {
		system("cls");
		exit(0);
	}
}

void Rules() {
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(38) << "ECONOMIC  REVOLUTION\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl << endl;
	cout<<setw(45) << "YOU ARE PLAYING ON THE FIELD 10x10\n\n";
	cout << setw(45) << "YOU NEED SCORE 1000 POINTS TO WIN\n\n";
	cout << setw(45) << "YOU CAN CHOISE NUMBERS OF POSITION\n\n";
	cout << setw(45) << "WHERE YOU WILL BUILD NEW BUILDING\n\n";
	cout << setw(47) << "WHERE 'F' IS FABRIK AND 'D' IS VILLAGE\n\n";
	cout << setw(39) << "USE ENGLISH KEYBOARD\n\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout<<endl << setw(45) << "ENTER '0 0 Q' IF YOU WILL END GAME\n\n";
	cout << setw(50) << "ENTER '0 0 -' IF YOU WILL SKIPPING A MOVE\n\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl << endl;
	cout << setw(48) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
	char type;
	cin >> type;
	MainMenu();
}

void Game( ) {

	bool FLAG = 0;
		for (int i = 0; i < 10;i++) {
			for (int j = 0; j < 10; j++) {   //first time making game field
				field[i][j] = '-';           //that symbole mean nothing
			}
		}
		G_total_people += G_people;
		
		while (G_money<1000&&G_money>=0) {
			Entering_of_xy_type(FLAG);
			G_money += G_plus;
			Random_event();
			
	}
		if (G_money >= 1000) {
			End_game(1);
		}
		if (G_money < 0) {
			End_game(0);
		}
}

void Update_Display() {
	system("cls");
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	for (int i = 0; i < 10; i++) cout << setw(5) << i + 1;
	cout << endl;
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	for (int i = 0; i < 10; i++) {
		//cout << i + 1 <<setw(1);
		for (int j = 0; j < 10; j++) {
			cout << setw(5) << field[i][j];
		}
		cout << endl << endl;
	}
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	//for score...
	cout << setw(20) << "TOTAL MONEY - " << G_money << setw(23) << "TOTAL PEOPLE - " << G_people << endl;
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
}

void Entering_of_xy_type(bool& FLAG) {
	int x_position=0, y_position=0;
	char type;   //type of building 
	do {
		Update_Display();
		cout << setw(40) << "ENTER THE X POSITION - ";
		x_position= Becom_normal_int('X');
	} while (x_position < 0 && x_position > 10);
	
	do {
		Update_Display();
		cout << setw(40) << "ENTER THE Y POSITION - ";
		y_position = Becom_normal_int('Y');
	} while (y_position < 0 && y_position > 10);
	do {
		Update_Display();
		cout << setw(40) << "ENTER THE TYPE OF BUILDING - ";
		cin >> type;
	} while (type != 'F'&&type!='f'&&type!='d' && type != 'D' && type != '-'
		&&type!='q'&&type!='Q');

	if (x_position == 0 && y_position == 0 && type == '-') {
		
	}
	if (x_position == 0 && y_position == 0 &&(( type == 'q')||(type=='Q'))) {
		
		End_game(FLAG);
		FLAG = 0;
	}
	else {
		if (type == 'f' || type == 'F') {
			Fabrik firma;
			if (firma.Get_Kost ()<= G_money ) {
				if (firma.Get_People() <= G_people) {
					if (field[x_position - 1][y_position - 1] == '-') {
						G_money -= firma.Get_Kost();
						field[x_position - 1][y_position - 1] = 'F';
						G_people -= firma.Get_People();
						G_plus += firma.Get_Payment();
						G_fabrik_count++;
					}
					else {
						Update_Display();
						cout << setw(40) << "THIS PLACE IS NOT EMPTY!\n";
						cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
						cin >> type;
					}
				}
				else {
					Update_Display();
					cout << setw(40) << "YOU HAVE NOT PEOPLE!\n";
					cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
					cin >> type;
				}
			}
			else {
				Update_Display();
				cout << setw(40) << "YOU HAVE NOT MONEY!\n";
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
		}
		else if (type == 'd' || type == 'D') {
			Dorf village;
			if (village.Get_Kost() <= G_money) {
				if (field[x_position-1][y_position-1] == '-') {
					G_money = G_money - village.Get_Kost();
					field[x_position-1][y_position-1] = 'D';
					G_people += village.Get_People();
					G_total_people+= village.Get_People();
				}
				else {
					Update_Display();
					cout << setw(40) << "THIS PLACE IS NOT EMPTY!\n";
					cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
					cin >> type;
				}
			}
			else {
				Update_Display();
				cout << setw(40) << "YOU HAVE NOT MONEY!\n";
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
		}
	}
}

void End_game(const bool &FLAG) {
	system("cls");
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(38) << "ECONOMIC  REVOLUTION\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl << endl;
	if (FLAG == 0) {
		cout << setw(33) << "GAME  OVER\n";
	}
	else {
		cout << setw(33) << "YOU WIN\n";
	}
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(20) << "TOTAL MONEY - " << G_money << setw(23) << "TOTAL PEOPLE - " << G_total_people << endl;
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	char type;
	cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
	cin >> type;
	MainMenu();
}

void Random_event() {
	srand(time(0));
	char type;

	if (G_difficult == 1) {
		if (G_fabrik_count > 0) {
			int random_event_num = 0 + rand() % (9 - 0 + 1);
			if (random_event_num == 1) {
				Update_Display();
				int num = 20 + rand() % (90 - 20 + 1);
				cout << setw(20) << "MONEY INT THE AMOUNT OF " << num << " WAS REQUESTED FOR THE WAR\n";
				G_money -= num;
				for (int i = 0; i < 55; i++) cout << "-";
				cout << endl;
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
			else if (random_event_num == 5) {
				Update_Display();
				int num = 5 + rand() % (10 - 5 + 1);
				cout << setw(20) << "MONEY IN THE AMOUNT OF " << num << " WAS REQUESTED FOR THE REPAIR OF BUILDINGS\n";
				G_money -= num;
				for (int i = 0; i < 55; i++) cout << "-";
				cout << endl;
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
		}
	}
	else if (G_difficult == 2) {
		if (G_fabrik_count > 0) {
			int random_event_num = 0 + rand() % (5 - 0 + 1);
			if (random_event_num == 1) {
				Update_Display();
				int num = 30 + rand() % (100 - 30 + 1);
				cout << setw(20) << "MONEY INT THE AMOUNT OF " << num << " WAS REQUESTED FOR THE WAR\n";
				G_money -= num;
				for (int i = 0; i < 55; i++) cout << "-";
				cout << endl;
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
			else if (random_event_num == 2) {
				Update_Display();
				int num = 5 + rand() % (10 - 5 + 1);
				cout << setw(20) << "MONEY IN THE AMOUNT OF " << num << " WAS REQUESTED FOR THE REPAIR OF BUILDINGS\n";
				G_money -= num;
				for (int i = 0; i < 55; i++) cout << "-";
				cout << endl;
				cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
				cin >> type;
			}
		}
	}
	else if (G_difficult == 3) {
		int random_event_num = 0 + rand() % (5 - 0 + 1);
		if (random_event_num == 1) {
			Update_Display();
			int num = 20 + rand() % (100 - 20 + 1);
			cout << setw(20) << "MONEY INT THE AMOUNT OF " << num << " WAS REQUESTED FOR THE WAR\n";
			G_money -= num;
			for (int i = 0; i < 55; i++) cout << "-";
			cout << endl;
			cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
			cin >> type;
		}
		else if (random_event_num == 2||random_event_num==5) {
			Update_Display();
			int num = 5 + rand() % (10 - 5 + 1);
			cout << setw(20) << "MONEY IN THE AMOUNT OF " << num << " WAS REQUESTED FOR THE REPAIR OF BUILDINGS\n";
			G_money -= num;
			for (int i = 0; i < 55; i++) cout << "-";
			cout << endl;
			cout << setw(50) << "ENTER SOMETHINK ON KEYBOARD TO RESUME - ";
			cin >> type;
		}
	}
}

void Paint_menu() {
	system("cls");
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(38) << "ECONOMIC  REVOLUTION\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl << endl;
	cout << setw(33) << "1 NEW GAME\n\n";
	cout << setw(31) << "2 RULES\n\n";
	cout << setw(31) << "3  EXIT\n\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(43) << "VERSION 1.1   BY  DIMAS_DUDKA\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
}

void Enter_difficult() {
	system("cls");
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	cout << setw(38) << "ENTER DIFFICULT OF GAME\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl << endl;
	cout << setw(32) << "1   EASY\n\n";
	cout << setw(34) << "2   NORMAL\n\n";
	cout << setw(32) << "3   HARD\n\n";
	for (int i = 0; i < 55; i++) cout << "-";
	cout << endl;
	int num = Becom_normal_int('d');
	if (num == 1) { G_difficult = 1; }
	else if (num == 2) { G_difficult = 2; }
	else if (num == 3) { G_difficult = 3; }
	Game();
}

int Becom_normal_int(const char& type) {
	int num ;
	if (type == 'd') {
		while ((!(cin >> num)) || (num < 0) || (num > 3)) {
			cin.clear();
			cin.ignore(1);
			system("cls");
			Enter_difficult();
		}
	}
	else {
		while ((!(cin >> num)) || (num < 0) || (num > 10)) {
			if (type == 'X') {
				Update_Display();
				cout << setw(40) << "ENTER THE X POSITION - ";
			}
			else if (type == 'Y') {
				Update_Display();
				cout << setw(40) << "ENTER THE Y POSITION - ";
			}
			else {
				Paint_menu();
			}
			cin.clear();
			cin.ignore(1);
		}
	}
	return num;
}