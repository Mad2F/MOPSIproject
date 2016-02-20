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