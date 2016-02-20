#include "Image.h"

float cost(float x, float y){
	return abs(x - y);
}


void Draw_X_Y(vector<float> X, vector<float> Y){
	openWindow(2 * X.size(), 2 * Y.size());
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
	openWindow(2 * N, 2 * M);
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
			Set(I, i, j, double(255 * D[i][j] / (P - m) - 255 * m / (P - m)));
		}
	}
	AfficheImage(I);
	system("pause");
	endGraphics;
}