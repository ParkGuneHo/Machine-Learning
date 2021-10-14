#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#define GRAPHSIZE 3 //그래프 양옆 사이즈

using namespace std;

//녹색 신호 진입 차량
int Azero = 0; // 0대
int Alight = 1; // 3대
int Anormal = 2; // 6대
int Aheavy = 3; // 9대

//적색 신호 대기 차량
int Bzero = 0; // 0대
int Blight = 1; // 3대
int Bnormal = 2; // 6대
int Bheavy = 3; // 9대

//녹색 신호 연장 시간
int Czero = 0; // 0초
int Cshort = 1; // 3초
int Cmedium = 2; // 6초
int Clong = 3; // 9초

//계산 규칙 적용 결과값
double result_arr[4][4][3];

//진입 차령과 대기차량에 따른 녹색신호 확장시간 계산을 위한 규칙
static int arr[4][4] = {
{ Czero,Czero,Czero,Czero }, //Zero
{ Cshort, Czero,Czero,Czero }, //Light
{ Cmedium,Cshort,Czero,Czero }, //Normal
{ Clong,Cmedium,Cshort,Czero } //Heavy
};

//삼각형 퍼지수 함수
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

//삼각형 퍼지수 함수 적용 함수
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

//무게 중심법
double center_gravity() {
	double extension;
	double temp;
	double numerator = 0; //분자부분
	double denominator = 0; //분모부분
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

//진행 결과 출력 함수
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

//소숫점 1자리까지 반올림
double ceil(double x) {
	x = round(x * 10) / ((double)10);
	return x;
}

//메인 함수
int main() {
	double result;
	int go, wait;
	cout << "진입중인 차량 수 : ";
	cin >> go;
	cout << "대기중인 차량 수 : ";
	cin >> wait;
	cout << endl;
	print_result(go, wait);
	result = ceil(center_gravity());
	cout << endl;
	cout << "녹색신호 " << result << "초 연장" << endl;
	return 0;
}