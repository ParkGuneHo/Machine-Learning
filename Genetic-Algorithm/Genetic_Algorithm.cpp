#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <time.h>

using namespace std;
#define SIZE 8 //찾을 비밀번호 길이
#define CHROMOSOME 10 //염색체 수
#define POINT 4 //교배할 위치

struct gen {
	int num[SIZE];
	int score;
};
struct gen gene[CHROMOSOME];
struct gen next_gene[CHROMOSOME];
int pin_number[SIZE]; //비밀번호
int fit[10]; // 숫자 체크
double selectp[CHROMOSOME]; // 퍼센트
int tmp = 0;
int cnt = 0;
int check = -1;
int sum = 0;
int rdm;
int select1, select2;
double total = (10 + 2) * SIZE;

int FitnessFunc() { //적합도 함수
	tmp = 0;
	for (int i = 0; i < CHROMOSOME; i++) { //위치, 숫자 맞으면 10점
		for (int j = 0; j < SIZE; j++) {
			if (gene[i].num[j] == pin_number[j]) {
				gene[i].score = gene[i].score + 10;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) { // 숫자가 포함되어있는 만큼 2점
		for (int j = 0; j < SIZE; j++) {
			if (fit[gene[i].num[j]] == 1) {
				gene[i].score = gene[i].score + 2;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) {
		if (gene[i].score == (10 + 2) * SIZE) { //전부 일치 할 경우
			return i;
		}
	}
	return -1;
}
void SelectFunc() //유전자 2개 선택
{
	double sum = 0;
	for (int i = 0; i < CHROMOSOME; i++) {
		sum = sum + gene[i].score;
	}
	for (int i = 0; i < CHROMOSOME; i++) {
		selectp[i] = ((gene[i].score / sum) * 100); //100점 만점으로 환산
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
	while (true) { //첫번째와 두번째가 값이 다를 때 까지 반복
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
void CrossFunc() { //유전자 교배
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
	for (int i = 0; i < CHROMOSOME; i++) { //돌연변이
		for (int j = 0; j < SIZE; j++) {
			rdm = rand() % 100;
			if (rdm == 1) {
				next_gene[i].num[j] = rand() % 10;
			}
		}
	}
	for (int i = 0; i < CHROMOSOME; i++) { //교배시킨 유전자 대입
		for (int j = 0; j < SIZE; j++) {
			gene[i].num[j] = next_gene[i].num[j];
		}
		gene[i].score = 0;
	}
}
int main() {
	srand(time(NULL));
	cout << "초기 비밀번호 설정 (" << SIZE << "자리수) : ";
	for (int i = 0; i < SIZE; i++) {
		cin >> pin_number[i];
		fit[pin_number[i]] = 1;
	}
	//초기 염색체 생성
	for (int i = 0; i < CHROMOSOME; i++) {
		for (int j = 0; j < SIZE; j++) {
			gene[i].num[j] = rand() % 10;
		}
		gene[i].score = 0;
	}
	while (true) {
		cout << endl;
		cout << "-----" << cnt << "세대" << "-----" << endl;
		check = FitnessFunc();
		if (check > -1) {
			break;
		}
		for (int i = 0; i < CHROMOSOME; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << gene[i].num[j];
			}
			cout << " ---> " << (gene[i].score / total) * 100 << "% 일치" << endl;
		}
		CrossFunc();
		cnt++;
		cout << endl;
	}
	//결과 세대 출력
	for (int i = 0; i < CHROMOSOME; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << gene[i].num[j];
		}
		cout << " ---> " << (gene[i].score / total) * 100 << "% 일치" << endl;
	}
	//결과 출력
	cout << endl;
	cout << cnt << "세대 유전자에서 답 발견" << endl;
	cout << "비밀번호 : ";
	cout << " [ ";
	for (int i = 0; i < SIZE; i++) {
		cout << gene[check].num[i] << " ";
	}
	cout << "] ";
	cout << endl;
	return 0;
}