#include<cstdlib>
#include<iostream>
#include <fstream>
#include<ctime>
#include<string>
using namespace std;

#include "Graph.h"
#include "CostMat.h"

float rand_float(){
	float number1 = 1; float number2 = 1;
	number1 = rand(); number2 = rand();
	float number = min(number1, number2) / max(number1, number2);
	return number;
}




int main(){
	srand(time(0));

	ifstream fichier("test.txt", ios::in);  // on ouvre le fichier en lecture - doit être dans le build
	ofstream treat{ "treated.txt" };

	if (fichier)  // si l'ouverture a réussi
	{
		if (treat){
			string ligne{};
			string mot{};
			vector<string> Stock;
			while (getline(fichier, ligne)){
				Stock.push_back(ligne);
			}
			for (int i = 0; i < Stock.size(); i++){
				string Res;
				int S = Stock[i].size();
				for (int j = 0; j < Stock[i].size(); j++){
					if (j < S - 2){
						if (Stock[i][j] == ' '){
							if (Stock[i][j + 1] != '.' && Stock[i][j + 1] != ',' && Stock[i][j + 1] != ';' && Stock[i][j + 1] != '?' && Stock[i][j + 1] != '!' && Stock[i][j + 1] != ' ' && Stock[i][j + 1] != '\'' && Stock[i][j - 1] != '\''){
								Res = Res + Stock[i][j];
							}
							
						}
						else if (Stock[i][j] == '.' || Stock[i][j] == ',' || Stock[i][j] == ';' || Stock[i][j] == '?' || Stock[i][j] == '!'){
							if (Stock[i][j + 1] != ' '){
								Res = Res + Stock[i][j] + ' ';
							}
							else { Res = Res + Stock[i][j]; }
						}
						else { Res = Res + Stock[i][j]; }
					}
					else if (j == S - 1 && Stock[i][j] == ' '){}
					else { Res = Res + Stock[i][j]; }
				}
				if (Res != ""){
					cout << Res << endl;
					treat << Res << endl;
					Res = "";
				}
			}
			treat.close();
		}
		else{ cout << "ERREUR: Impossible de traiter le fichier." << endl; }

		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		cerr << "Impossible d'ouvrir le fichier !" << endl;



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