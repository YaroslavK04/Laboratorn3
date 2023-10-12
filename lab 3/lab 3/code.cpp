#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include <math.h>
using namespace std;



struct struck_ochered
{
	char data[256];  // �������� ����������
	struct struck_ochered* next; // ������ �� ��������� ������� 
};

struct struck_ochered* head_ochered = NULL, * last_ochered = NULL;
int dlinna_ochered_stek = 0;

struct struck_ochered* get_ochered(void) // �������� �������� ���������
{
	struct struck_ochered* p = NULL;
	char s[256];
	if ((p = (struck_ochered*)malloc(sizeof(struct struck_ochered))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");   // ������ ������
	scanf("%s", &s);
	if (s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	strcpy(p->data, s);


	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

void ochered_stek(void) { // �������� ����� ����� ���������� ���������
	struct struck_ochered* q, * f = NULL;
	q = get_ochered();
	if (head_ochered == NULL) {
		head_ochered = q;
		last_ochered = q;
	}
	else {
		q->next = head_ochered; // ��������� ������� � ������ ���������
		head_ochered = q;
	}
}

void review_ochered(int razmer) // ������� ������ �� ������� �� �����
{
	struct struck_ochered* head_struc = head_ochered, * last_struc = last_ochered;
	if (head_ochered == NULL)
	{
		printf("������ ����\n");
	}
	for (int i = 0; i < razmer; i++) {

		printf("��� - %s \n", last_struc->data);
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

/*void reviwe_one_day() { // ������� ��������� � 1 �������
	struct priority_queue* p = head;
	struct one_day* struct_predmet;
	double vvod;
	int day = 0, month;
	cout << "\n���������� �� ����� ���� �� ������ ������?\n ������� ���� (������ 31.12): ";
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
}*/



int main() {
	setlocale(LC_ALL, "Rus");

	int colvo_elem, vibor, vibor1 = 0, vibor2 = 0;

	printf("1. ������ � ����������� \n2. ������� \n3. ����\n");
	printf("�������� ��������: ");
	scanf("%d", &vibor);

	// ��������� ������ ������������
	switch (vibor) {
	case 1:
		cout << "�����\n";
		break;
	case 2:
		while (vibor1 >= 0) {
			printf("1. �������� ������� \n2. ������� � ������� �������\n3. ��������� ���������\n");
			printf("�������� ��������: ");
			scanf("%d", &vibor1);
			while (dlinna_ochered_stek == 0 && vibor1 == 2)
			{
				cout << "������ ����! ������� ������\n1. �������� ������� \n3. ��������� ���������\n�������� ��������: ";
				cin >> vibor1;
			}
			switch (vibor1) {
			case 1:
				cout << "������� ��������� �� ������ ��������: ";
				cin >> colvo_elem;
				while (colvo_elem <= 0)
				{
					cout << "������ �� ����� ������������\n ���������� ��� ���: ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek += colvo_elem;
				for (int i = 0; i < colvo_elem; i++) {
					ochered_stek();
				}
				break;
			case 2:
				cout << "������� ��������� �� ������ ������� �� ����� � �������: ";
				cin >> colvo_elem;
				while (colvo_elem > dlinna_ochered_stek)
				{
					cout << "� ������� ��� ������� ���������.\n ���������� ��� ��� : ";
					cin >> colvo_elem;
				}
				dlinna_ochered_stek -= colvo_elem;
				review_ochered(colvo_elem);

				break;
			case 3:
				vibor1 = -1;
				break;
			default:
				printf("������. ���������� �����.\n");
			}
		}
		break;
	case 3:
		cout << "�����\n";
		break;
	default:
		printf("������. ���������� �����.\n");
	}

}





