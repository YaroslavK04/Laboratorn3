#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include <math.h>
using namespace std;

struct one_day { // ��������� ��� 1 �������� � ����������
	char predmet[20];
	int hours, minute;
	struct one_day* next;
};
struct priority_queue
{
	int den, mauns, colvo_predmet;
	struct priority_queue* next; // ������ �� ��������� ������� 
	struct one_day* head_day; 
};

struct priority_queue* head = NULL, * last = NULL; // ��������� �� ������ � ��������� �������� ������
int dlinna_ochered_stek = 0;

struct one_day* get_struct_predmet(void) // ������ ������� ��������� ��� 1 ��������
{
	struct one_day* p = NULL;
	double time;
	char s[20];
	int colvo_predmetov;
	if ((p = (one_day*)malloc(sizeof(struct one_day))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� ����� (������ 00.00) � ������� ����� ��������� �������: ");   // ������ ������
	cin >> time;
	p->hours = time;
	p->minute = floorf((time - p->hours) * 100); // ��������� ���������� ������� ����� 
	while (p->hours > 23 || p->minute > 59) {
		printf("������ ������� ������������ �� �����\n ������� ������ �����: ");   // ������ ������
		cin >> time;
		p->hours = time;
		p->minute = floorf((time - p->hours) * 100);
	}

	printf("������� �������� ��������: ");   // ������ ������
	scanf("%s", &s);
	if (s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	strcpy(p->predmet, s);

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

void input_po_priority_day(struct priority_queue* head_da) { // ������ ���������� ����� ���������� ��������� ��� ���������

	struct one_day* q, * f = NULL;
	q = get_struct_predmet();


	if (head_da->head_day == NULL || (head_da->head_day->hours > q->hours || (head_da->head_day->hours == q->hours && head_da->head_day->minute > q->minute))) { // ���� ����� ��������� ��� ������ ������� ������������� � �������� head, 
		                                                                                                                                                        //�� ��������� ������� ����� �� ����� head
		q->next = head_da->head_day;
		head_da->head_day = q;

	}
	else {
		f = head_da->head_day;
		while (f->next != NULL && (f->next->hours < q->hours || (f->next->hours != q->hours && f->next->minute < q->minute))) { // ��������� ����, ���� �� ����� ����� ��� ��������
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

struct priority_queue* get_struct(void)// ������ ������� ��������� ��� 1 ���
{
	struct priority_queue* p = NULL;
	double dat;
	int colvo_predmetov;
	if ((p = (priority_queue*)malloc(sizeof(struct priority_queue))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� ���� (������ 31.12): ");   // ������ ������
	cin >> dat;
	p->den = dat;
	p->mauns = floorf((dat - p->den) * 100);
	while (p->den > 31 || p->mauns > 12) {
		printf("����� ���� ������������ �� �����\n ������� ������ ����: ");   // ������ ������
		cin >> dat;
		p->den = dat;
		p->mauns = floorf((dat - p->den) * 100);
	}

	p->head_day = NULL;

	cout << "������� ��������� �� ������ ������: ";
	cin >> colvo_predmetov;
	p->colvo_predmet = colvo_predmetov;
	for (int i = 0; i < colvo_predmetov; i++) {
		input_po_priority_day(p);
	}

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

void input_po_priority() { // ������ ���������� ����� ���������� ��������� ��� ����
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


struct priority_queue* proverka(int day, int month) {
	struct priority_queue* element = head;
	while (element != NULL && (month != element->mauns || day != element->den)) {
		element = element->next;
	}
	return element;
};
void swap_plase() {
	double vvod;
	int day = 0, month, save_size;
	struct priority_queue* p, * dayt1 = NULL, * dayt2 = NULL;
	struct one_day* save;
	cout << " ������� ���� ����, ������� ������ �������� �������: \n ������ ���� (������ 31.12): ";
	for (int i = 0; i < 2; i++) {
		cin >> vvod;
		day = vvod;
		month = floorf((vvod - day) * 100);
		p = proverka(day, month);
		while (p == NULL) {
			cout << " ����� ���� ���!\n ���������� ��� ���: ";
			cin >> vvod;
			day = vvod;
			month = floorf((vvod - day) * 100);
			p = proverka(day, month);
		}
		if (i == 0) {
			dayt1 = p;
			cout << " ������ ���� (������ 31.12): ";
		}
		if (i == 1) { dayt2 = p; }


	}
	save = dayt2->head_day;
	save_size = dayt2->colvo_predmet;

	dayt2->head_day = dayt1->head_day;
	dayt2->colvo_predmet = dayt1->colvo_predmet;
	dayt1->head_day = save;
	dayt1->colvo_predmet = save_size;


};

void reviwe_one_day() { // ������� ��� ������ ���������� �� ����������� ���� ( ������ ����� ���������)
	struct priority_queue* p = head;
	struct one_day* struct_predmet;
	double vvod;
	int day = 0, month;
	cout << "\n���������� �� ����� ���� �� ������ ������?\n ������� ���� (������ 31.12): ";
	cin >> vvod;
	day = vvod;
	month = floorf((vvod - day) * 100);
	p = proverka(day, month);// ��������� ���������� �� ������� � ����� ����� 
	while (p == NULL) { // ���� �������� �� ����������, ������ ������ ������ ����
		cout << " ����� ���� ���!\n ���������� ��� ���: ";
		cin >> vvod;
		day = vvod;
		month = floorf((vvod - day) * 100);
		p = proverka(day, month);
	}

	struct_predmet = p->head_day;
	cout << "---------------------" << endl;
	if (p->den < 10) { // ���� ����� ������������ � ��������� < 10, �� ������� ������������� "0" ��� �������� ��������� ����
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

void review(void)  // ������� ��� ������ ���������� �� ��������� ���� ������. ����� ������ �� ����� ������ ��������� 
{
	int size;
	struct priority_queue* struc = head;
	struct one_day* struct_predmet;
	cout << " ���������� �� ������� ���� �� ������ ������? : ";
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

	printf("1. ������ � ����������� \n2. ������� \n3. ����\n");
	printf("�������� ��������: ");
	scanf("%d", &vibor);

	// ��������� ������ ������������
	switch (vibor) {
	case 1:
		while (vibor2 >= 0) {
			printf("\n1. �������� ������� \n2. ������� ���������� �� ��������� ���� ������\n3. �������� ���������� � 2 ����\n4. ������� ���������� �� 1 ����\n5. ��������� ���������\n");
			printf("�������� ��������: ");
			scanf("%d", &vibor2);
			while (head == NULL && (vibor2 == 2 || vibor2 == 3 || vibor2 == 4))
			{
				cout << "������ ����!\n1. �������� ������� \n5. ��������� ���������\n�������� ��������: ";
				cin >> vibor2;
			}
			switch (vibor2) {
			case 1:
				int colvo_days;
				printf("������� ���� � ���������� �� ������ ���������: \n");   // ������ ������
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
				printf("������. ���������� �����.\n");
			}
		}


		review();
		break;
	case 2:
		cout << " �����\n";
		break;
	case 3:
		cout << " �����\n";
		break;
	default:
		printf("������. ���������� �����.\n");
	}
	system("pause");
}




