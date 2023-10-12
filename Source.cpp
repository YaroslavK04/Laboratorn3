#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include <math.h>
using namespace std;

struct one_day {
	char predmet[20];
	int hours, minute;
	struct one_day* next;
};
struct priority_queue
{
	int den, mauns, colvo_predmet;
	struct priority_queue* next; // ссылка на следующий элемент 
	struct one_day* head_day;
};

struct struck_ochered
{
	char data[256];  // полезная информация
	struct struck_ochered* next; // ссылка на следующий элемент 
};

struct priority_queue* head = NULL, * last = NULL; // указатели на первый и последний элементы списка
struct struck_ochered* head_ochered = NULL, * last_ochered = NULL;
int dlinna_ochered_stek = 0;

struct struck_ochered* get_ochered(void) //==============================================
{
	struct struck_ochered* p = NULL;
	char s[256];
	if ((p = (struck_ochered*)malloc(sizeof(struct struck_ochered))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", &s);
	if (s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->data, s);


	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

void  review_stek(int razmer) 
{
	struct struck_ochered* head_struc = head_ochered, * last_struc = head_ochered;
	if (head_ochered == NULL)
	{
		printf("Список пуст\n");
	}
	for (int i = 0; i < razmer; i++) {
		head_struc = head_ochered;
		printf("Имя - %s \n", head_ochered->data);
		head_ochered = head_ochered->next;
		delete head_struc;
	}
	return;
}


struct one_day* get_struct_predmet(void)
{
	struct one_day* p = NULL;
	double time;
	char s[20];
	int colvo_predmetov;
	if ((p = (one_day*)malloc(sizeof(struct one_day))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите время (формат 00.00) в которое будет проходить предмет: ");   // вводим данные
	cin >> time;
	p->hours = time;
	p->minute = floorf((time - p->hours) * 100);
	while (p->hours > 23 || p->minute > 59) {
		printf("Такого времени существовать не может\n Введите другое время: ");   // вводим данные
		cin >> time;
		p->hours = time;
		p->minute = floorf((time - p->hours) * 100);
	}

	printf("Введите название предмета: ");   // вводим данные
	scanf("%s", &s);
	if (s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->predmet, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

void input_po_priority_day(struct priority_queue* head_da) {

	struct one_day* q, * f = NULL;
	q = get_struct_predmet();


	if (head_da->head_day == NULL || (head_da->head_day->hours > q->hours || (head_da->head_day->hours == q->hours && head_da->head_day->minute > q->minute))) {
		q->next = head_da->head_day;
		head_da->head_day = q;

	}
	else {
		f = head_da->head_day;
		while (f->next != NULL && (f->next->hours < q->hours || (f->next->hours != q->hours && f->next->minute < q->minute))) {
			f = f->next;
		}

		if (f->next == NULL) {
			f->next = q;
		}
		else {
			q->next = f->next;
			f->next = q;
		}
	}

}

struct priority_queue* get_struct(void)
{
	struct priority_queue* p = NULL;
	double dat;
	int colvo_predmetov;
	if ((p = (priority_queue*)malloc(sizeof(struct priority_queue))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите дату (формат 31.12): ");   // вводим данные
	cin >> dat;
	p->den = dat;
	p->mauns = floorf((dat - p->den) * 100);
	while (p->den > 31 || p->mauns > 12) {
		printf("Такой даты существовать не может\n Введите другую дату: ");   // вводим данные
		cin >> dat;
		p->den = dat;
		p->mauns = floorf((dat - p->den) * 100);
	}

	p->head_day = NULL;

	cout << "Сколько предметов вы хотите внести: ";
	cin >> colvo_predmetov;
	p->colvo_predmet = colvo_predmetov;
	for (int i = 0; i < colvo_predmetov; i++) {
		input_po_priority_day(p);
	}

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

void input_po_priority() {
	struct priority_queue* q, * f = NULL;
	q = get_struct();


	if (head == NULL || head->mauns > q->mauns || (head->mauns == q->mauns && head->den > q->den)) {
		q->next = head;
		head = q;
	}
	else {
		f = head;
		while (f->next != NULL && (q->mauns > f->next->mauns || (f->next->mauns != q->mauns && f->next->den < q->den))) {
			f = f->next;
		}

		if (f->next == NULL) {
			f->next = q;
		}
		else {
			q->next = f->next;
			f->next = q;
		}
	}

}

void ochered_stek(void) { //==============================================
	struct struck_ochered* q, * f = NULL;
	q = get_ochered();
	if (head_ochered == NULL) {
		head_ochered = q;
		last_ochered = q;
	}
	else {
		q->next = head_ochered;
		head_ochered = q;
	}
}

void review_ochered(int razmer)
{
	struct struck_ochered* head_struc = head_ochered, * last_struc = last_ochered;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	for (int i = 0; i < razmer; i++) {

		printf("Имя - %s \n", last_struc->data);
		if (head_struc != last_struc) {
			while (head_struc->next != last_struc) {
				head_struc = head_struc->next;
			}
			delete last_struc;
			last_struc = head_struc;
			head_struc = head_ochered;
		}

	}
	last_ochered = last_struc;

	return;

}

struct priority_queue* proverka(int day, int month) {
	struct priority_queue* element= head;
	while (element != NULL && (month != element->mauns   || day != element->den)) {
		element = element->next;
	}
	return element;
};
void swap_plase() {
	double vvod;
	int day = 0, month, save_size;
	struct priority_queue* p, * dayt1 = NULL, * dayt2=NULL;
	struct one_day* save;
	cout << " Введите даты дней, которые хотите поменять местами: \n Первая дата (формат 31.12): ";
	for (int i = 0; i < 2; i++) {
		cin >> vvod;
		day = vvod;
		month = floorf((vvod - day) * 100);
		p = proverka(day, month);
		while (p == NULL) {
			cout << " Такой даты нет!\n Попробуйте ещё раз: ";
			cin >> vvod;
			day = vvod;
			month = floorf((vvod - day) * 100);
			p = proverka(day, month);
		}
		if ( i == 0) {
			dayt1 = p;
			cout << " Вторая дата (формат 31.12): ";
		}
		if (i == 1) {dayt2 = p;}
		
		
	}
	save = dayt2->head_day;
	save_size = dayt2->colvo_predmet;

	dayt2->head_day = dayt1->head_day;
	dayt2->colvo_predmet = dayt1->colvo_predmet;
	dayt1->head_day = save;
	dayt1->colvo_predmet = save_size;


};

void reviwe_one_day() {
	struct priority_queue* p = head;
	struct one_day* struct_predmet;
	double vvod;
	int day = 0, month;
	cout << "\nРасписание на какой день вы хотите узнать?\n Введите дату (формат 31.12): ";
	cin >> vvod;
	day = vvod;
	month = floorf((vvod - day) * 100);
	p = proverka(day, month);
	while (p == NULL) {
		cout << " Такой даты нет!\n Попробуйте ещё раз: ";
		cin >> vvod;
		day = vvod;
		month = floorf((vvod - day) * 100);
		p = proverka(day, month);
	}

	struct_predmet = p->head_day;
	cout << "---------------------" << endl;
	if (p->den < 10) {
		cout << "0" << p->den;
	}
	else {
		cout << p->den;
	}
	cout << ".";
	if (p->mauns < 10) {
		cout << "0" << p->mauns << "\n\n";
	}
	else {
		cout << p->mauns << "\n\n";
	}
	for (int j = 0; j < p->colvo_predmet; j++) {
		cout << struct_predmet->hours << ":" << struct_predmet->minute << "-" << struct_predmet->predmet << "\n";
		struct_predmet = struct_predmet->next;
	}
	cout << "---------------------" << endl;

	return;



}

void review(void)
{
	int size;
	struct priority_queue* struc = head;
	struct one_day* struct_predmet;
	cout << " Расписание на сколько дней вы хотите узнать? : ";
	cin >> size;
	for (int i = 0; i < size; i++) {
		struc = head;
		struct_predmet = struc->head_day;
		cout << "---------------------" << endl;
		if (struc->den < 10) {
			cout << "0" << struc->den;
		}
		else {
			cout << struc->den;
		}
		cout << ".";
		if (struc->mauns < 10) {
			cout << "0" << struc->mauns << "\n\n";
		}
		else {
			cout << struc->mauns << "\n\n";
		}
		for (int j = 0; j < struc->colvo_predmet; j++) {
			cout << struct_predmet->hours << ":" << struct_predmet->minute << "-" << struct_predmet->predmet << "\n";
			struct_predmet = struct_predmet->next;
		}
		cout << "---------------------" << endl;
		head = head->next;
		delete struc;
	}
	return;

}

int main() {
	setlocale(LC_ALL, "Rus");

	int colvo_elem, vibor, vibor1 = 0, vibor2 = 0;

	printf("1. Список с приоритетом \n2. Очередь \n3. Стек\n");
	printf("Выберите действие: ");
	scanf("%d", &vibor);

	// Обработка выбора пользователя
	switch (vibor) {
	case 1:
		while (vibor2 >= 0) {
			printf("\n1. Добавить элемент \n2. Вывести расписание на несколько дней подряд\n3. Поменять расписание в 2 днях\n4. Вывести расписание на 1 день\n5. Закончить программу\n");
			printf("Выберите действие: ");
			scanf("%d", &vibor2);
			while (head == NULL && (vibor2 == 2 || vibor2 == 3 || vibor2 == 4))
			{
				cout << "Список пуст!\n1. Добавить элемент \n5. Закончить программу\nВыберите действие: ";
				cin >> vibor2;
			}
			switch (vibor2) {
			case 1:
				int colvo_days;
				printf("Сколько дней в расписании вы хотите заполнить: \n");   // вводим данные
				cin >> colvo_days;
				for (int i = 0; i < colvo_days; i++) {
					input_po_priority();
				}
				break;
			case 2:
				review();

				break;
			case 3:
				swap_plase();
				break;
			case 4:
				reviwe_one_day();
				break;
			case 5:
				vibor2 = -1;
				break;
			default:
				printf("Ошибка. Попробуйте снова.\n");
			}
		}


		review();
		break;
	case 2:
		while (vibor1 >= 0) {
			printf("1. Добавить элемент \n2. Вывести и удалить элемент\n3. Закончить программу\n");
			printf("Выберите действие: ");
			scanf("%d", &vibor1);
			while (dlinna_ochered_stek == 0 && vibor1 == 2)
			{
				cout << "Список пуст! Удалять нечего\n1. Добавить элемент \n3. Закончить программу\nВыберите действие: ";
				cin >> vibor1;
			}
			switch (vibor1) {
			case 1:
				cout << "Сколько элементов вы хотите добавить: ";
				cin >> colvo_elem;
				while (colvo_elem <= 0)
				{
					cout << "Список не может существовать\n Попробуйте ещё раз: ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek += colvo_elem;
				for (int i = 0; i < colvo_elem;i++) {
					ochered_stek();
				}
				break;
			case 2:
				cout << "Сколько элементов вы хотите вывести на экран и удалить: ";
				cin >> colvo_elem;
				while (colvo_elem > dlinna_ochered_stek)
				{
					cout << "В очереди нет столько элементов.\n Попробуйте ещё раз : ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek -= colvo_elem;
				review_ochered(colvo_elem);

				break;
			case 3:
				vibor1 = -1;
				break;
			default:
				printf("Ошибка. Попробуйте снова.\n");
			}
		}
		break;
	case 3:
		while (vibor1 >= 0) {
			printf("1. Добавить элемент \n2. Вывести и удалить элемент\n3. Закончить программу\n");
			printf("Выберите действие: ");
			scanf("%d", &vibor1);
			while (dlinna_ochered_stek == 0 && vibor1 == 2)
			{
				cout << "Список пуст! Удалять нечего\n1. Добавить элемент \n3. Закончить программу\nВыберите действие: ";
				cin >> vibor1;
			}
			switch (vibor1) {
			case 1:
				cout << "Сколько элементов вы хотите добавить: ";
				cin >> colvo_elem;
				while (colvo_elem <= 0)
				{
					cout << "Список не может существовать\n Попробуйте ещё раз: ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek += colvo_elem;
				for (int i = 0; i < colvo_elem;i++) {
					ochered_stek();
				}
				break;
			case 2:
				cout << "Сколько элементов вы хотите вывести на экран и удалить: ";
				cin >> colvo_elem;
				while (colvo_elem > dlinna_ochered_stek)
				{
					cout << "В очереди нет столько элементов.\n Попробуйте ещё раз : ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek -= colvo_elem;
				review_stek(colvo_elem);

				break;
			case 3:
				vibor1 = -1;
				break;
			default:
				printf("Ошибка. Попробуйте снова.\n");
			}
		}

		break;
	default:
		printf("Ошибка. Попробуйте снова.\n");
	}

}





