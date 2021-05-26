#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <sstream>

using namespace std;

class students{
public:
    string fio;
    int dayborn, monthborn, yearborn;
    int yearenter;
    string faculty;
    string department;
    string group;
    string book;
};

struct subject{
    string namesubject;
    int mark;
    subject* next_subject;
};

class session {
    public:
    int number;
    subject* Subjects;
    session* next_session;
    ~session() {
        subject* tempsub;
        while (Subjects->next_subject!=Subjects) {
            tempsub = Subjects->next_subject;
            delete (Subjects->next_subject);
            Subjects->next_subject = tempsub->next_subject;
        }
        delete (Subjects);
    }
};

struct spis{
    students Student;
    session* Sessions;
    spis *next_item;
     ~spis() {
        session* tempses;
        while (Sessions->next_session != Sessions) {
            tempses = Sessions->next_session;
            delete(Sessions->next_session);
            Sessions->next_session = tempses->next_session;
        }
        delete(Sessions);
    }
};

spis *pStart, *pCurrent,*pTemp;
session *pStart1, *pCurrent1,*pTemp1;
subject *pStart2, *pCurrent2,*pTemp2;
int count0 = -1;
void input_item();
void writing(ofstream *input);
string delete1();
void change();
void changestudent(int);
void changesessia(int);
void findstudents(char);
void read(ifstream *input);
void menu();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int spos, chek, z;
    do{
    chek = 0;
    do{
        cout << "Вы хотите:\n 1.Открыть существующий\n 2.Создать файл\n";
        cin >> spos; cin.clear(); _flushall();
    } while(spos < 1 || spos > 2);
    if(spos == 1){
        ifstream file1;
        cout << "Введите путь к файлу ";
        string access;
        getline(cin,access); cin.clear(); _flushall();
        file1.open(access.c_str());
        if (!file1){
            perror("error opening the file");
            chek = -1;
        }
        else{
        read(&file1);
        menu();
        file1.close();
        ofstream file1;
        file1.open(access.c_str());
        writing(&file1);
        file1.close();
        }
    }
    else{
        ofstream file1;
        file1.open("D:\\Vera.txt");
         if (!file1){
            perror("error opening the file");
            chek = -1;
        }
        else{
        for(;;){
            input_item();
            do {
			cout << "Добавить студента? \n 0. Нет;\n 1. Да." << endl;
			cin >> z; cin.clear(); _flushall();
		} while (z < 0 || z > 1);
            if (z == 0) break;
        }
    menu();
    writing(&file1);
    file1.close();
            }
        }
    }while(chek == -1);
    return 0;
}

void menu(){
    int z;
    string symbols;
    for(;;){
        do{
        cout << "Выберете действие:\n 1.Добавить студента\n 2.Удалить студента\n 3.Изменить данные студента\n 4.Основное задание\n 5.Выход" << endl;
        cin>>z; cin.clear(); _flushall();
        } while (z < 1 || z > 5);
        switch(z){
        case 1:
            input_item();
            break;
        case 2:
            cout << delete1();
            break;
        case 3:
            change();
            break;
        case 4:
            cout << endl << "Поиск студентов, у которых за все время обучения нет ни одной оценки:\n а) 3\n б) 3 и 4\n в) 5\n г) 3 и 5\n д) 4 и 5\n ";
            getline(cin, symbols); cin.clear(); _flushall();
            for(int i = 0; i < symbols.length(); i++){
                if(symbols[i] == 'а' || symbols[i] == 'б' || symbols[i] == 'в' || symbols[i] == 'г' || symbols[i] == 'д') findstudents(symbols[i]);

            }
            break;
            case 5:
            break;
        }
        if (z == 5) break;
    }

}

void input_item(){
    int kol;
    pCurrent = new spis;
    string z;
	int s, p = 0;
	do {
		s = 0;
		cout << "Введите ФИО студента ";
		getline(cin, pCurrent->Student.fio); cin.clear(); _flushall();
		for (int i = 0; i < pCurrent->Student.fio.length(); i++)
			if (pCurrent->Student.fio[i] == ' ') s++;
		if (s != pCurrent->Student.fio.length()) p = 1;
	} while (p != 1);
	do {
		cout << "Введите год рождения студента ";
		cin >> pCurrent->Student.yearborn; cin.clear(); _flushall();
	} while ((pCurrent->Student.yearborn < 1900) || (pCurrent->Student.yearborn > 2005));
	do {
		cout << "Введите месяц рождения студента ";
		cin >> pCurrent->Student.monthborn; cin.clear(); _flushall();
	} while ((pCurrent->Student.monthborn < 1) || (pCurrent->Student.monthborn > 12));
	do {
		cout << "Введите день рождения студента ";
		cin >> pCurrent->Student.dayborn; cin.clear(); _flushall();
	} while ((pCurrent->Student.dayborn < 1) && (pCurrent->Student.dayborn > 31));
	p = 0;
	do {
		cout << "Введите год поступления студента ";
		cin >> pCurrent->Student.yearenter; cin.clear(); _flushall();
		if ((pCurrent->Student.yearenter - pCurrent->Student.yearborn >= 15) && (pCurrent->Student.yearenter < 2021)) p = 1;
	} while (p != 1);
	p = 0;
	do {
		s = 0;
		cout << "Введите факультет студента ";
		getline(cin, pCurrent->Student.faculty); cin.clear(); _flushall();
		for (int i = 0; i < pCurrent->Student.faculty.length(); i++)
			if (pCurrent->Student.faculty[i] == ' ') s++;
		if (s != pCurrent->Student.faculty.length()) p = 1;
	} while (p != 1);
	p = 0;
	do {
		s = 0;
		cout << "Введите кафедру студента ";
		getline(cin, pCurrent->Student.department); cin.clear(); _flushall();
		for (int i = 0; i < pCurrent->Student.department.length(); i++)
			if (pCurrent->Student.department[i] == ' ') s++;
		if (s != pCurrent->Student.department.length()) p = 1;
	} while (p != 1);
	p = 0;
	do {
		s = 0;
		cout << "Введите группу студента ";
		getline(cin, pCurrent->Student.group); cin.clear(); _flushall();
		for (int i = 0; i < pCurrent->Student.group.length(); i++)
			if (pCurrent->Student.group[i] == ' ') s++;
		if (s != pCurrent->Student.group.length()) p = 1;
	} while (p != 1);
	p = 0;
	do {
		s = 0;
		spis* pCurrentS = pStart;
		cout << "Введите номер зачетной книжки студента ";
		getline(cin, pCurrent->Student.book); cin.clear(); _flushall();
		for (int i = 0; i < pCurrent->Student.book.length(); i++)
			if (pCurrent->Student.book[i] == ' ') s++;
		z = pCurrent->Student.book;
		int a = 0;
		if (count0 > -1) {
			do {
				if (z == pCurrentS->Student.book) a = 1;
				pCurrentS = pCurrentS->next_item;
			} while (pCurrentS != pStart);
		}
		if ((s != pCurrent->Student.book.length()) and (a == 0)) p = 1;
	} while (p != 1);

	do {
		cout << "Введите количество сессий ";
		cin >> kol; cin.clear(); _flushall();
	} while ((kol < 1) || (kol > 9));
	for (int i = 0; i < kol; i++) {
		if (i == 0) {
			pCurrent->Sessions = new session;
			pCurrent1 = pCurrent->Sessions;
			pCurrent1->next_session=pCurrent1;
			pCurrent1->number = i;
			pStart1 = pCurrent1;
		}
		else {
			pCurrent1->next_session = new session;
			pCurrent1 = pCurrent1->next_session;
			if (i == 1) {
				pStart1->next_session = pCurrent1;
			}
			pCurrent1->next_session = pStart1;
			pCurrent1->number = i;
		}
		int pred;
		do {
			cout << "Введите количество предметов на " << i + 1 << " сессии ";
			cin >> pred; cin.clear(); _flushall();
		} while ((pred < 1) or (pred > 10));
		for (int j = 0; j < pred; j++) {
			if (j == 0) {
				pCurrent1->Subjects = new subject;
				pCurrent2 = pCurrent1->Subjects;
				pCurrent2->next_subject = pCurrent2;
				pStart2 = pCurrent2;
			}
			else {
				pCurrent2->next_subject = new subject;
				pCurrent2 = pCurrent2->next_subject;
				if (j == 1) {
					pStart2->next_subject = pCurrent2;
				}
				pCurrent2->next_subject = pStart2;
			}
			p = 0;
			do {
				s = 0;
				cout << "Введите название предмета ";
				getline(cin, pCurrent2->namesubject); cin.clear(); _flushall();
				for (int i = 0; i < pCurrent2->namesubject.length(); i++)
					if (pCurrent2->namesubject[i] == ' ') s++;
				if (s != pCurrent2->namesubject.length()) p = 1;
			} while (p != 1);
			do {
				cout << "Введите оценку за предмет ";
				cin >> pCurrent2->mark; cin.clear(); _flushall();
			} while ((pCurrent2->mark < 2) or (pCurrent2->mark > 5));
		}
	}
	if (count0 == -1) {
		count0 += 1;
		pStart = pCurrent;
		pCurrent->next_item = pCurrent;
		pTemp = pCurrent;
	}
	else {
		count0 += 1;
		pCurrent->next_item = pTemp->next_item;
		pTemp->next_item = pCurrent;
		pTemp - pCurrent;
	}
}


void writing(ofstream *input){
    if (count0 > -1) {
    pCurrent = pStart;
    do {
        *input << pCurrent->Student.fio << "\t";
        if (pCurrent->Student.dayborn < 10) {
            *input << "0" << pCurrent->Student.dayborn << "\t";
        }
        else {
            *input << pCurrent->Student.dayborn << "\t";
        }
        *input << pCurrent->Student.monthborn << "\t";
        *input << pCurrent->Student.yearborn << "\t";
        *input << pCurrent->Student.yearenter << "\t";
        *input << pCurrent->Student.faculty << "\t";
        *input << pCurrent->Student.department << "\t";
        *input << pCurrent->Student.group << "\t";
        *input << pCurrent->Student.book << "\t";
        pCurrent1 = pCurrent->Sessions;
        pStart1 = pCurrent1;
        do {
            *input << (pCurrent1->number + 1) << " сессия:\t";
            pCurrent2 = pCurrent1->Subjects;
            pStart2 = pCurrent2;
            do {
                *input << pCurrent2->namesubject << "\t";
                *input << pCurrent2->mark << "\t";
                pCurrent2 = pCurrent2->next_subject;
            } while (pCurrent2 != pStart2);

            pCurrent1 = pCurrent1->next_session;
        } while (pCurrent1 != pStart1);
        pCurrent = pCurrent->next_item;
        *input << endl;
    } while (pCurrent != pStart);
    }
}

void read(ifstream *input){
    string line;
    while (getline(*input, line))
		{   pCurrent = new spis;
			istringstream iss(line);
			string token;
			int k = 0;
			int j = 0;
			while (getline(iss, token, '\t')) {
                if(token.length() == 9 && k == 12){
                    string a = token;
                    a.erase(1,8);
                    if(a == "1" || a == "2" || a == "3" || a == "4" || a == "5" || a == "6" || a == "7" || a == "8" || a == "9" ){
                    k = 9;
                    j = 0;
                    }
                }
                if(k == 12) k = 10;
				if (k == 0) pCurrent->Student.fio = token;
				if (k == 1) pCurrent->Student.dayborn = atoi(token.c_str());
				if (k == 2) pCurrent->Student.monthborn = atoi(token.c_str());
				if (k == 3) pCurrent->Student.yearborn = atoi(token.c_str());
				if (k == 4) pCurrent->Student.yearenter = atoi(token.c_str());
				if (k == 5) pCurrent->Student.faculty = token;
				if (k == 6) pCurrent->Student.department = token;
				if (k == 7) pCurrent->Student.group = token;
				if (k == 8) pCurrent->Student.book = token;
				if (k == 9) {
                    token.erase(1,8);
                    if (atoi(token.c_str()) - 1 == 0) {
                        pCurrent->Sessions = new session;
                        pCurrent1 = pCurrent->Sessions;
                        pCurrent1->next_session=pCurrent1;

                        pCurrent1->number = atoi(token.c_str()) - 1;
                        pStart1 = pCurrent1;
                        }
                        else {
                            pCurrent1->next_session = new session;
                            pCurrent1 = pCurrent1->next_session;
                            if (atoi(token.c_str()) - 1 == 1) {
                                pStart1->next_session = pCurrent1;
                            }
                            pCurrent1->next_session = pStart1;
                            pCurrent1->number = atoi(token.c_str()) - 1;
                            }
                            }
                if(k == 10){
                    if (j == 0) {
                        pCurrent1->Subjects = new subject;
                        pCurrent2 = pCurrent1->Subjects;
                        pCurrent2->next_subject = pCurrent2;
                        pStart2 = pCurrent2;
                    }
                    else {
                        pCurrent2->next_subject = new subject;
                        pCurrent2 = pCurrent2->next_subject;
                        if (j == 1) {
                            pStart2->next_subject = pCurrent2;
                        }
                        pCurrent2->next_subject = pStart2;
                    }
                    j++;
                    pCurrent2->namesubject = token;
                    }
                    if(k == 11){
                        pCurrent2->mark = atoi(token.c_str());
                    }

                k++;
			}
        if (count0 == -1){
        count0 += 1;
        pStart = pCurrent;
        pCurrent->next_item = pCurrent;
        pTemp = pCurrent;
    }
    else{
        count0 += 1;
        pCurrent->next_item = pTemp->next_item;
        pTemp->next_item = pCurrent;
        pTemp = pCurrent;
    }
    }
		}

string delete1() {
	string deletebook;
	spis *temp;
	int s, p = 0;
	do {
		s = 0;
		cout << "Введите номер зачетной книжки студента, данные которого следует удалить ";
		getline(cin, deletebook); cin.clear(); _flushall();
		for (int i = 0; i < deletebook.length(); i++)
			if (deletebook[i] == ' ') s++;
		if (s != deletebook.length()) p = 1;
	} while (p != 1);
	pCurrent = pStart;
	while (pCurrent->next_item != pStart) {
		if (pCurrent->next_item->Student.book == deletebook) {
			temp = pCurrent->next_item;
			delete (pCurrent->next_item);
			pCurrent->next_item = temp->next_item;
			count0--;
			return "Студент удалён\n";
		}
		pCurrent = pCurrent->next_item;
	}
	if (pCurrent->next_item->Student.book == deletebook) {
		temp = pCurrent->next_item;
		delete (pCurrent->next_item);
		pCurrent->next_item = temp->next_item;
		pStart = pCurrent->next_item;
		count0--;
		return "Студент удален\n";
	}
	else {
		return "Студент с таким номером зачетной книжки не найден\n";
	}
}

void change(){
    int k;
    int prov1 = -1;
    string changebook;
    cout << "Введите номер зачетной книги студента,данные которого следует заменить ";
    getline(cin, changebook); cin.clear(); _flushall();
    pCurrent = pStart;
    do{
        string changebook1 = pCurrent->Student.book;
        if(changebook1 == changebook){
            prov1 = 1;
            do{
            cout << "Выберете, какие данные следует изменить:\n 1.Личные данные о студенте\n 2.Сессионные данные студента\n";
            cin >> k; cin.clear(); _flushall();
            } while (k < 1 || k > 2);
            int a;
            if(k == 1){
                do{
                    cout << "Выберите позицию, которую хотите изменить:\n 1.Фио\n 2.Год рождения\n 3.Месяц рождения\n 4.День рождения\n 5.Год поступления\n 6.Название факультета\n 7.Название кафедры\n 8.Номер группы\n 9.Номер зачетной книжки\n";
                    cin >> a; cin.clear(); _flushall();
                }while (a < 1 || a > 9);
                changestudent(a);
            }
            else{
                do{
                    cout << "Выберите позицию, которую хотите изменить:\n 1.Сессию\n 2.Предмет\n 3.Оценку\n";
                    cin >> a; cin.clear(); _flushall();
               } while(a < 1 || a > 3);
               changesessia(a);
            }
        }
        pCurrent = pCurrent->next_item;
    } while(pCurrent != pStart);
    if (prov1 == -1) cout << "Студента с такой зачетной книжкой не найдено ";
}

void changestudent(int a){
    string changeposition1;
	int changeposition2;
	int s, p = 0;
	switch (a) {
		case 1:
			do {
				s = 0;
				cout << "Введите новое ФИО ";
				getline(cin, changeposition1); cin.clear(); _flushall();
				for (int i = 0; i < changeposition1.length(); i++)
					if (changeposition1[i] == ' ') s++;
				if (s != changeposition1.length()) p = 1;
			} while (p != 1);
			pCurrent->Student.fio = changeposition1;
			break;
		case 2:
			do {
				cout << "Введите новый год рождения ";
				cin >> changeposition2; cin.clear(); _flushall();
			} while ((changeposition2 < 1900) || (changeposition2 > 2005));
			pCurrent->Student.yearborn = changeposition2;
			break;
		case 3:
			do {
				cout << "Введите новый месяц рождения ";
				cin >> changeposition2; cin.clear(); _flushall();
			} while ((changeposition2 < 1) || (changeposition2 > 12));
			pCurrent->Student.monthborn = changeposition2;
			break;
		case 4:
			do {
				cout << "Введите новый день рождения ";
				cin >>changeposition2; cin.clear(); _flushall();
			} while ((changeposition2 < 1) && (changeposition2 > 31));
			pCurrent->Student.dayborn = changeposition2;
			break;
		case 5:
			p = 0;
			do {
				cout << "Введите новый год поступления ";
				cin >> changeposition2; cin.clear(); _flushall();
				if (changeposition2 - pCurrent->Student.yearenter >= 15) p = 1;
			} while (p != 1);
			pCurrent->Student.yearenter = changeposition2;
			break;
		case 6:
			do {
				s = 0;
				cout << "Введите новое название факультета ";
				getline(cin, changeposition1); cin.clear(); _flushall();
				for (int i = 0; i < changeposition1.length(); i++)
				if (changeposition1[i] == ' ') s++;
				if (s != changeposition1.length()) p = 1;
			} while (p != 1);
			pCurrent->Student.faculty = changeposition1;
			break;
		case 7:
			do {
				s = 0;
				cout << "Введите новое название кафедры ";
				getline(cin, changeposition1); cin.clear(); _flushall();
				for (int i = 0; i < changeposition1.length(); i++)
				if (changeposition1[i] == ' ') s++;
				if (s != changeposition1.length()) p = 1;
			} while (p != 1);
			pCurrent->Student.department = changeposition1;
			break;
		case 8:
			do {
				s = 0;
				cout << "Введите новую группу ";
				getline(cin, changeposition1); cin.clear(); _flushall();
				for (int i = 0; i < changeposition1.length(); i++)
				if (changeposition1[i] == ' ') s++;
				if (s != changeposition1.length()) p = 1;
			} while (p != 1);
			pCurrent->Student.group = changeposition1;
			break;
		case 9:
			int a = 0;
			string z;
			p = 0;
			do {
				s = 0;
				spis* pCurrentS = pStart;
				cout << "Введите номер зачетной книжки студента ";
				getline(cin, changeposition1); cin.clear(); _flushall();
				for (int i = 0; i < changeposition1.length(); i++)
					if (changeposition1[i] == ' ') s++;
				z = changeposition1;
				a = 0;
				if (count0 > -1) {
					do {
						if (z == pCurrentS->Student.book) a = 1;
						pCurrentS = pCurrentS->next_item;
					} while (pCurrentS != pStart);
				}
				if ((s != changeposition1.length()) and (a == 0)) p = 1;
			} while (p != 1);
			pCurrent->Student.book = changeposition1;
			break;
	}
}

void changesessia(int a){
    int b;
	int s, p = 0;
	string changesubject;
	if (a == 1) {
		do {
			cout << "Введите номер сесиии, которую хотите изменить ";
			cin >> b; cin.clear(); _flushall();
		} while ((b < 1) or (b > 9));
		pCurrent1 = pCurrent -> Sessions;
		for (int i = 0; i < b-1; i++) {
			pCurrent1 = pCurrent1->next_session;
		}
		if (pCurrent1->next_session->number == b - 1) {
			session* temp;
			temp = pCurrent1->next_session->next_session;
			delete (pCurrent1->next_session);
			pCurrent1->next_session = new session;
			pCurrent1->next_session->next_session = temp;
			pCurrent1->next_session->number = b - 1;
			int pred;
			do {
				cout << "Введите количество предметов на " << b << " сессии ";
				cin >> pred; cin.clear(); _flushall();
			} while ((pred < 1) or (pred > 10));
			for (int j = 0; j < pred; j++) {
				if (j == 0) {
					pCurrent1->Subjects = new subject;
					pCurrent2 = pCurrent1->Subjects;
					pCurrent2->next_subject = pCurrent2;
					pStart2 = pCurrent2;
				}
				else {
					pCurrent2->next_subject = new subject;
					pCurrent2 = pCurrent2->next_subject;
					if (j == 1) {
						pStart2->next_subject = pCurrent2;
					}
					pCurrent2->next_subject = pStart2;
				}
				do {
					s = 0;
					cout << "Введите название предмета ";
					getline(cin, pCurrent2->namesubject); cin.clear(); _flushall();
					for (int i = 0; i < pCurrent2->namesubject.length(); i++)
						if (pCurrent2->namesubject[i] == ' ') s++;
					if (s != pCurrent2->namesubject.length()) p = 1;
				} while (p != 1);
				do {
					cout << "Введите оценку за предмет ";
					cin >> pCurrent2->mark; cin.clear(); _flushall();
				} while ((pCurrent2->mark < 2) or (pCurrent2->mark > 5));
			}
		}
		else cout << "Сессия с таким номером не найдена\n";
	}
	if (a == 2) {
		string changesubject1;
		do {
			cout << "Введите номер сессии, в которой следует изменить предмет ";
			cin >> b; cin.clear(); _flushall();
		} while ((b < 1) or (b > 9));
		p = 0;
		do {
			s = 0;
			cout << "Введите название предмета, который следует заменить ";
			getline(cin, changesubject); cin.clear(); _flushall();
			for (int i = 0; i < changesubject.length(); i++)
				if (changesubject[i] == ' ') s++;
			if (s != changesubject.length()) p = 1;
		} while (p != 1);
		p = 0;
		do {
			s = 0;
			cout << "Введите название предмета, на который следует заменить ";
			getline(cin, changesubject1); cin.clear(); _flushall();
			for (int i = 0; i < changesubject1.length(); i++)
				if (changesubject1[i] == ' ') s++;
			if (s != changesubject1.length()) p = 1;
		} while (p != 1);
		pCurrent1 = pCurrent->Sessions;
		for (int i = 0; i < b; i++) {
			pCurrent1 = pCurrent1->next_session;
		}
		pCurrent2 = pCurrent1->Subjects;
		pStart2 = pCurrent1->Subjects;
		int prov = 0;
		do {
			if (pCurrent2->namesubject == changesubject) {
				pCurrent2->namesubject = changesubject1;
				prov = 1;
			}
			pCurrent2 = pCurrent2->next_subject;
		} while (pCurrent2 != pStart2);
		if (prov == 0) cout << "Предмет с таким названием не найден\n";
	}
	if (a == 3) {
		int mark1;
		do {
			cout << "Введите номер сессии ";
			cin >> b; cin.clear(); _flushall();
		} while ((b < 1) or (b > 9));
		p = 0;
		do {
			s = 0;
			cout << "Введите название предмета, по которому следует изменить оценку ";
			getline(cin, changesubject); cin.clear(); _flushall();
			for (int i = 0; i < changesubject.length(); i++)
				if (changesubject[i] == ' ') s++;
			if (s != changesubject.length()) p = 1;
		} while (p != 1);
		do {
			cout << "Введите оценку, на которую следует изменить ";
			cin >> mark1; cin.clear(); _flushall();
		} while ((mark1 < 3) or (mark1 > 5));
		pCurrent1 = pCurrent->Sessions;
		for (int i = 0; i < b; i++) {
			pCurrent1 = pCurrent1->next_session;
		}
		pCurrent2 = pCurrent1->Subjects;
		pStart2 = pCurrent1->Subjects;
		int prov = 0;
		do {
			if (pCurrent2->namesubject == changesubject) {
				pCurrent2->mark = mark1;
				prov = 1;
			}
			pCurrent2 = pCurrent2->next_subject;
		} while (pCurrent2 != pStart2);
		if (prov == 0) cout << "Предмет с таким названием на найден\n";
	}
    }

void findstudents(char choise){
    int mark1;
    int prov2 = 0;
    int god1;
    int god2;
    do {
		cout << "Введите начальную границу интервала года поступления ";
		cin >> god1; cin.clear(); _flushall();
	} while ((god1 < 2012) or (god1 > 2020));
    do {
		cout << "Введите конечную границу интервала года поступления ";
		cin >> god2; cin.clear(); _flushall();
	} while ((god2 < 2012) or (god2 > 2020));
	if (god1 > god2)swap(god1, god2);
    pCurrent = pStart;
    if(choise == 'а' || choise == 'в'){
        if(choise == 'а'){
            mark1 = 3;
        }
        else{
            mark1 = 5;
        }
    cout << "Cтуденты, не имеющие " << mark1 << endl;
    do{
        pStart1 = pCurrent->Sessions;
        pCurrent1 = pCurrent->Sessions;
        do{
            pStart2 = pCurrent1->Subjects;
            pCurrent2 = pCurrent1->Subjects;
            do{
                if(pCurrent2->mark == mark1) break;
                pCurrent2 = pCurrent2->next_subject;
            } while(pCurrent2 != pStart2);
            if(pCurrent2->mark == mark1) break;
            pCurrent1 = pCurrent1->next_session;
        } while (pCurrent1 != pStart1);
        if(pCurrent2->mark != mark1 && pCurrent->Student.yearenter >= god1 && pCurrent->Student.yearenter <= god2){
            cout << endl << pCurrent->Student.fio << endl;
            prov2 = 1;
        }
        pCurrent = pCurrent->next_item;
    } while(pCurrent != pStart);
    if (prov2 == 0) cout << " не найдено ";
    }
    if(choise == 'б' || choise == 'г' || choise == 'д' ){

        if(choise == 'б') mark1 = 5;
        if(choise == 'г') mark1 = 4;
        if(choise == 'д') mark1 = 3;
    pCurrent = pStart;
    cout << "Cтуденты, имеющие только: " << mark1 << endl;
    do{
        pStart1 = pCurrent->Sessions;
        pCurrent1 = pCurrent->Sessions;
        do{
            pStart2 = pCurrent1->Subjects;
            pCurrent2 = pCurrent1->Subjects;
            do{
                if(pCurrent2->mark != mark1) break;
                pCurrent2 = pCurrent2->next_subject;

            } while(pCurrent2 != pStart2);
            if(pCurrent2->mark != mark1) break;
            pCurrent1 = pCurrent1->next_session;
        } while (pCurrent1 != pStart1);
        if(pCurrent2->mark == mark1 && pCurrent->Student.yearenter >= god1 && pCurrent->Student.yearenter <= god2){
            cout << endl << pCurrent->Student.fio << endl;
            prov2 = 1;
        }
        pCurrent = pCurrent->next_item;
    } while(pCurrent != pStart);
    if (prov2 == 0) cout << " не найдено ";
    }

}

