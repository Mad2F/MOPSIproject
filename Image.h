#include<Imagine\Graphics.h>
using namespace Imagine; 

//Structure Image du TP MONASSE 7? DE 1A
struct Image{
	byte*T;
	int W;
	int H;
};

//Copie image
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

//Affiche Image
void AfficheImage(Image I){
	putGreyImage(0, 0, I.T, I.W, I.H);
}

//Définit le pixel i, j
void Set(Image I, int i, int j, double g){
	g = byte(g);
	I.T[i + I.W*j] = g;
}

//Récupère la valeur du pixel i, j
double Get(Image I, int i, int j){
	return double(I.T[i + I.W*j]);
}