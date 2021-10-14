#include <iostream>

using namespace std;

int pattern[5][25] = {
	{1, 1, 1, 1, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1 }, //ㄱ

	{1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 1, 1, 1, 1 }, //ㄴ

	{1, 1, 1, 1, 1,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 1, 1, 1, 1 }, //ㄷ

	{1 ,1 ,1 ,1 ,1,
	 0 ,0 ,0 ,0 ,1,
	 1 ,1 ,1 ,1 ,1,
	 1 ,0 ,0 ,0 ,0,
	 1 ,1 ,1 ,1 ,1 }, //ㄹ

	{1, 1, 1, 1, 1,
	 1, 0, 0, 0, 1,
	 1, 0, 0, 0, 1,
	 1, 0, 0, 0, 1,
	 1, 1, 1, 1, 1 } //ㅁ
};

int user[25]; //입력값
int w[25][25]; //가중치


int main() {
	cout << "----------------------학습패턴----------------------" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 25; j++) {
			cout << pattern[i][j] << ' ';
			if ((j % 5) == 4) {
				cout << endl;
			}
		}
		cout << endl;
	}

	//학습패턴 양극화
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 25; j++) {
			if (pattern[i][j] > 0) {
				pattern[i][j] = 1;
			}
			else {
				pattern[i][j] = -1;
			}
		}
	}

	cout << "----------------------학습패턴(양극화후)----------------------" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 25; j++) {
			cout << pattern[i][j] << ' ';
			if ((j % 5) == 4) {
				cout << endl;
			}
		}
		cout << endl;
	}

	//학습 패턴 가중치
	for (int t = 0; t < 5; t++) {
		int x[25];

		for (int i = 0; i < 25; i++) {
			x[i] = pattern[t][i];
		}

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				w[i][j] += (i == j ? 0 : x[i] * x[j]);
			}
		}
	}


	//패턴 입력
	cout << "패턴 입력(유효 : 1, 빈칸 : 0)" << endl;
	for (int i = 0; i < 25; i++) {
		cin >> user[i];
	}

	//입력패턴 양극화
	for (int i = 0; i < 25; i++) {
		if (user[i] > 0) {
			user[i] = 1;
		}
		else {
			user[i] = -1;
		}
	}

	// 결과 도출

	int output[25];
	int result[25];
	int tmp = 0;

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			tmp += user[j] * w[i][j];
		}

		result[i] = user[i] + tmp;
		tmp = 0;

		if (result[i] > 0) {
			output[i] = 1;
		}

		else if (result[i] == 0) {
			output[i] = user[i];
		}

		else if (result[i] < 0) {
			output[i] = -1;
		}

		if (output[i] != user[i]) {
			user[i] = output[i];
		}
	}

	//출력

	cout << "----------------------결과패턴----------------------" << endl;
	int cnt = 0;


	for (int i = 0; i < 25; i++) {
		if (output[i] == 1) {
			cout << "■";
		}
		else {
			cout << "□";
		}
		if ((i % 5) == 4) {
			cout << endl;
		}
	}


	return 0;
}
