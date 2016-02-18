#include<vector>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;

float rand_float(){
	float number1 = 1; float number2 = 1;
	number1 = rand(); number2 = rand();
	float number = min(number1, number2) / max(number1, number2);
	return number;
}
#include<Imagine\Graphics.h>
using namespace Imagine;


struct Image{
	byte*T;
	int W;
	int H;
};

Image AlloueImage(int W, int H){
	Image Bis;
	Bis.W = W;
	Bis.H = H;
	Bis.T = new byte[W*H];
	for (int i = 0; i < W*H; i++){
		Bis.T[i] = 0;
	}
	putGreyImage(0, 0, Bis.T, Bis.W, Bis.H);
	return Bis;
}

void AfficheImage(Image I){
	putGreyImage(0, 0, I.T, I.W, I.H);
}

void Set(Image I, int i, int j, double g){
	g = byte(g);
	I.T[i + I.W*j] = g;
}

double Get(Image I, int i, int j){
	return double(I.T[i + I.W*j]);
}

float cost(float x, float y){
	return abs(x - y);
}


void Draw_X_Y(vector<float> X, vector<float> Y){
	openWindow(2*X.size(), 2*Y.size());
	Image I = AlloueImage(X.size(), Y.size());
	for (int i = 0; i < I.H; i++){
		for (int j = 0; j < I.W; j++){
			Set(I, j, i, double(255 * cost(X[i], Y[j])));
		}
	}
	AfficheImage(I);
	system("pause");
	endGraphics;
}

void Draw_D(vector<vector<float> > D, int N, int M){
	openWindow(2*N, 2*M);
	Image I = AlloueImage(N, M);
	float m = D[0][0]; 
	float P = D[0][0];

	for (int i = 0; i < I.H; i++){
		for (int j = 0; j < I.W; j++){
			if (D[i][j] < m){ m = D[i][j]; }
			if (D[i][j] > P){ P = D[i][j]; }
		}
	}

	for (int i = 0; i < I.H; i++){
		for (int j = 0; j < I.W; j++){
			Set(I, i, j, double(255*D[i][j]/(P-m) - 255*m/(P-m)));
		}
	}
	AfficheImage(I);
	system("pause");
	endGraphics;
}

vector<vector<float> > costmatrix(vector<float> X, vector<float> Y){
	vector<vector<float> > Result;
	//Init
	for (int i = 0; i < X.size(); i++){
		vector<float> I;
		I.push_back(1);
		for (int j = 1; j < Y.size(); j++){
			if (i == 0){ I.push_back(1); }
			else{ I.push_back(0); }
		}
		Result.push_back(I);
	}
	//Recurrence
	for (int i = 0; i < X.size(); i++){
		for (int j = 0; j < Y.size(); j++){
			if (i == 0 || j == 0){
				Result[i][j] = 1;
			}
			else{
				Result[i][j] = min(min(Result[i - 1][j - 1], Result[i - 1][j]), Result[i][j - 1]) + cost(X[i], Y[j]);
			}
		}
	}
	return Result;
}

/**vector<float> distance(vector<vector<float> > D, int N, int M){
	vector<float> Result;
	for (int i = 0; i <= N; i++){
		Result.push_back(D[N][i]);
	}
	return Result;
}

float max(vector<float> Delta){
	float M = Delta[0];
	for (int i = 0; i < Delta.size(); i++){
		if (Delta[i] > M){ M = Delta[i]; }
	}
	return M;
}

vector<int> simil_subseq(vector<float> X, vector<float> Y, float tau){
	vector<int> Result;
	vector<vector<float> > D = costmatrix(X, Y);
	vector<float> Delta = distance(D, X.size(), Y.size());
	float M = max(Delta);
	int b_star = min_dist(Delta);
	while (D[X.size()][b_star] <= tau){
		b_star = min_dist(Delta);
		int a = minimizing_index(X, Y, D);
		for (int i = a; i <= b_star; i++){
			Result.push_back(Y[i]);
		}
		if (b_star + 1 <= Delta.size()){
			Delta[b_star + 1] = 1000 * M;
		}
		if (b_star - 1 >= 0){
			Delta[b_star - 1] = 1000 * M;
		}
	}
	return Result;
}**/

int main(){
	srand(time(0));
	vector<float> X, Y;
	int N = rand() % 100 + 1;
	int M = rand() % 70 + 1;
	for (int i = 0; i < N; i++){
		X.push_back(rand_float());
	}
	for (int j = 0; j < N; j++){
		Y.push_back(rand_float());
	}

	//Draw_X_Y(X, Y);

	vector<vector<float> > D = costmatrix(X, Y);

	Draw_D(D, X.size(), Y.size());

	return 0;
}