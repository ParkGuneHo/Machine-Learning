#include <iostream>

using namespace std;

int pattern[5][25] = {
	{1, 1, 1, 1, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1,
	 0, 0, 0, 0, 1 }, //��

	{1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 1, 1, 1, 1 }, //��

	{1, 1, 1, 1, 1,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 0, 0, 0, 0,
	 1, 1, 1, 1, 1 }, //��

	{1 ,1 ,1 ,1 ,1,
	 0 ,0 ,0 ,0 ,1,
	 1 ,1 ,1 ,1 ,1,
	 1 ,0 ,0 ,0 ,0,
	 1 ,1 ,1 ,1 ,1 }, //��

	{1, 1, 1, 1, 1,
	 1, 0, 0, 0, 1,
	 1, 0, 0, 0, 1,
	 1, 0, 0, 0, 1,
	 1, 1, 1, 1, 1 } //��
};

int user[25]; //�Է°�
int w[25][25]; //����ġ


int main() {
	cout << "----------------------�н�����----------------------" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 25; j++) {
			cout << pattern[i][j] << ' ';
			if ((j % 5) == 4) {
				cout << endl;
			}
		}
		cout << endl;
	}

	//�н����� ���ȭ
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

	cout << "----------------------�н�����(���ȭ��)----------------------" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 25; j++) {
			cout << pattern[i][j] << ' ';
			if ((j % 5) == 4) {
				cout << endl;
			}
		}
		cout << endl;
	}

	//�н� ���� ����ġ
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


	//���� �Է�
	cout << "���� �Է�(��ȿ : 1, ��ĭ : 0)" << endl;
	for (int i = 0; i < 25; i++) {
		cin >> user[i];
	}

	//�Է����� ���ȭ
	for (int i = 0; i < 25; i++) {
		if (user[i] > 0) {
			user[i] = 1;
		}
		else {
			user[i] = -1;
		}
	}

	// ��� ����

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

	//���

	cout << "----------------------�������----------------------" << endl;
	int cnt = 0;


	for (int i = 0; i < 25; i++) {
		if (output[i] == 1) {
			cout << "��";
		}
		else {
			cout << "��";
		}
		if ((i % 5) == 4) {
			cout << endl;
		}
	}


	return 0;
}
