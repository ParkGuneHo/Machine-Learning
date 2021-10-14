#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <time.h>

using namespace std;
#define SIZE 8 //ã�� ��й�ȣ ����
#define CHROMOSOME 10 //����ü ��
#define POINT 4 //������ ��ġ

struct gen {
	int num[SIZE];
	int score;
};
struct gen gene[CHROMOSOME];
struct gen next_gene[CHROMOSOME];
int pin_number[SIZE]; //��й�ȣ
int fit[10]; // ���� üũ
double selectp[CHROMOSOME]; // �ۼ�Ʈ
int tmp = 0;
int cnt = 0;
int check = -1;
int sum = 0;
int rdm;
int select1, select2;
double total = (10 + 2) * SIZE;

int FitnessFunc() { //���յ� �Լ�
	tmp = 0;
	for (int i = 0; i < CHROMOSOME; i++) { //��ġ, ���� ������ 10��
		for (int j = 0; j < SIZE; j++) {
			if (gene[i].num[j] == pin_number[j]) {
				gene[i].score = gene[i].score + 10;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) { // ���ڰ� ���ԵǾ��ִ� ��ŭ 2��
		for (int j = 0; j < SIZE; j++) {
			if (fit[gene[i].num[j]] == 1) {
				gene[i].score = gene[i].score + 2;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) {
		if (gene[i].score == (10 + 2) * SIZE) { //���� ��ġ �� ���
			return i;
		}
	}
	return -1;
}
void SelectFunc() //������ 2�� ����
{
	double sum = 0;
	for (int i = 0; i < CHROMOSOME; i++) {
		sum = sum + gene[i].score;
	}
	for (int i = 0; i < CHROMOSOME; i++) {
		selectp[i] = ((gene[i].score / sum) * 100); //100�� �������� ȯ��
	}
	rdm = rand() % 100;
	sum = 0;
	for (int i = 0; i < CHROMOSOME; i++) {
		sum = sum + selectp[i];
		if (rdm < sum) {
			select1 = i;
			break;
		}
	}
	while (true) { //ù��°�� �ι�°�� ���� �ٸ� �� ���� �ݺ�
		rdm = rand() % 100;
		sum = 0;
		for (int i = 0; i < CHROMOSOME; i++) {
			sum = sum + selectp[i];
			if (rdm < sum) {
				select2 = i;
				break;
			}
		}
		if (select1 == select2) {
			continue;
		}
		else {
			break;
		}
	}
}
void CrossFunc() { //������ ����
	for (int i = 0; i < CHROMOSOME; i += 2) {
		SelectFunc();
		for (int j = 0; j < POINT; j++) {
			next_gene[i].num[j] = gene[select1].num[j];
			next_gene[i + 1].num[j] = gene[select2].num[j];
		}
		for (int j = POINT; j < SIZE; j++) {
			next_gene[i].num[j] = gene[select2].num[j];
			next_gene[i + 1].num[j] = gene[select1].num[j];
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) { //��������
		for (int j = 0; j < SIZE; j++) {
			rdm = rand() % 100;
			if (rdm == 1) {
				next_gene[i].num[j] = rand() % 10;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) { //�����Ų ������ ����
		for (int j = 0; j < SIZE; j++) {
			gene[i].num[j] = next_gene[i].num[j];
		}
		gene[i].score = 0;
	}
}
int main() {
	srand(time(NULL));
	cout << "�ʱ� ��й�ȣ ���� (" << SIZE << "�ڸ���) : ";
	for (int i = 0; i < SIZE; i++) {
		cin >> pin_number[i];
		fit[pin_number[i]] = 1;
	}
	//�ʱ� ����ü ����
	for (int i = 0; i < CHROMOSOME; i++) {
		for (int j = 0; j < SIZE; j++) {
			gene[i].num[j] = rand() % 10;
		}
		gene[i].score = 0;
	}
	while (true) {
		cout << endl;
		cout << "-----" << cnt << "����" << "-----" << endl;
		check = FitnessFunc();
		if (check > -1) {
			break;
		}
		for (int i = 0; i < CHROMOSOME; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << gene[i].num[j];
			}
			cout << " ---> " << (gene[i].score / total) * 100 << "% ��ġ" << endl;
		}
		CrossFunc();
		cnt++;
		cout << endl;
	}
	//��� ���� ���
	for (int i = 0; i < CHROMOSOME; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << gene[i].num[j];
		}
		cout << " ---> " << (gene[i].score / total) * 100 << "% ��ġ" << endl;
	}
	//��� ���
	cout << endl;
	cout << cnt << "���� �����ڿ��� �� �߰�" << endl;
	cout << "��й�ȣ : ";
	cout << " [ ";
	for (int i = 0; i < SIZE; i++) {
		cout << gene[check].num[i] << " ";
	}
	cout << "] ";
	cout << endl;
	return 0;
}