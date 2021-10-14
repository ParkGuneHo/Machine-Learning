#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#define GRAPHSIZE 3 //�׷��� �翷 ������

using namespace std;

//��� ��ȣ ���� ����
int Azero = 0; // 0��
int Alight = 1; // 3��
int Anormal = 2; // 6��
int Aheavy = 3; // 9��

//���� ��ȣ ��� ����
int Bzero = 0; // 0��
int Blight = 1; // 3��
int Bnormal = 2; // 6��
int Bheavy = 3; // 9��

//��� ��ȣ ���� �ð�
int Czero = 0; // 0��
int Cshort = 1; // 3��
int Cmedium = 2; // 6��
int Clong = 3; // 9��

//��� ��Ģ ���� �����
double result_arr[4][4][3];

//���� ���ɰ� ��������� ���� �����ȣ Ȯ��ð� ����� ���� ��Ģ
static int arr[4][4] = {
{ Czero,Czero,Czero,Czero }, //Zero
{ Cshort, Czero,Czero,Czero }, //Light
{ Cmedium,Cshort,Czero,Czero }, //Normal
{ Clong,Cmedium,Cshort,Czero } //Heavy
};

//�ﰢ�� ������ �Լ�
double triangular_func(double r, double x) {
	r *= GRAPHSIZE; // Zero = 0, Light = 3. Normal = 6, Heavy = 9
	double p = r - GRAPHSIZE;
	double q = r + GRAPHSIZE;
	double result;
	if (p < x && x <= r) {
		result = (1 / (r - p)) * (x - r) + 1;
	}
	else if (r < x && x <= q) {
		result = -1 * (1 / (q - r)) * (x - r) + 1;
	}
	else { // x>=p or x<=p
		result = 0;
	}
	return ceil(result);
}

//�ﰢ�� ������ �Լ� ���� �Լ�
void apply_func(int A, int B) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				if (k == 0) {
					result_arr[i][j][k] = triangular_func(i, A);
				}
				if (k == 1) {
					result_arr[i][j][k] = triangular_func(j, B);
				}
				if (k == 2) {
					result_arr[i][j][k] = arr[i][j] * ((double)3);
				}
			}
		}
	}
}

//���� �߽ɹ�
double center_gravity() {
	double extension;
	double temp;
	double numerator = 0; //���ںκ�
	double denominator = 0; //�и�κ�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp = min(result_arr[i][j][0], result_arr[i][j][1]);
			numerator += temp * result_arr[i][j][2];
			denominator += temp;
		}
	}
	extension = numerator / denominator;
	return extension;
}

//���� ��� ��� �Լ�
void print_result(int A, int B) {
	int cnt = 0;
	apply_func(A, B);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cnt++;
			printf("R%d : ", cnt);
			for (int k = 0; k < 3; k++) {
				printf("%.1f ", result_arr[i][j][k]);
			}
			cout << endl;
		}
	}
}

//�Ҽ��� 1�ڸ����� �ݿø�
double ceil(double x) {
	x = round(x * 10) / ((double)10);
	return x;
}

//���� �Լ�
int main() {
	double result;
	int go, wait;
	cout << "�������� ���� �� : ";
	cin >> go;
	cout << "������� ���� �� : ";
	cin >> wait;
	cout << endl;
	print_result(go, wait);
	result = ceil(center_gravity());
	cout << endl;
	cout << "�����ȣ " << result << "�� ����" << endl;
	return 0;
}