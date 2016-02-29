#include<cstdlib>
#include <fstream>
#include<ctime>
#include <sstream>
using namespace std;

#include "Graph.h"
#include "CostMat.h"
#include "open.h"
#include "mot.h"

float rand_float(){
	float number1 = 1; float number2 = 1;
	number1 = rand(); number2 = rand();
	float number = min(number1, number2) / max(number1, number2);
	return number;
}

vector<string> &split(string s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (item[item.length() - 1] < 65 || item[item.length() - 1] > 122){
			item.pop_back();
		}
		if (item[0] >= 'A' && item[0] <= 'Z'){
			item[0] += 32;
		}
		elems.push_back(item);
	}
	return elems;
}


vector<string> split(string s, char delim) {
	vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

Text txt_to_Text(){
	ifstream fichier("treated.txt", ios::in);
	Text T;
	bool LC = lingua_continua();
	if (fichier){
		string ligne{};
		string mot{};
		vector<string> Stock;
		while (getline(fichier, ligne)){
			Stock.push_back(ligne);
		}
		for (int i = 0; i < Stock.size(); i++){
			if (LC){
				Paragraph P = Paragraph(i);
				for (int j = 0; j < Stock[i].size(); j++){
					string s;
					s.push_back(Stock[i][j]);
					Mot M = Mot(s, i, j);
					P.add_new(M, j);
				}
				P.set_length(Stock[i].size());
				T.add_new(P, i);
			}
			else{
				vector<string> Understock = split(Stock[i], ' ');
				Paragraph P = Paragraph(i);
				for (int j = 0; j < Understock.size(); j++){
					Mot M = Mot(Understock[j], i, j);
					P.add_new(M, j);
				}
				P.set_length(Understock.size() - 1);
				T.add_new(P, i);
			}
		}
		fichier.close();
		T.update_pos();
		return T;
	}
	else{
		cerr << "Impossible d'ouvrir le fichier traité" << endl;
		return T;
	}	
}


int main(){
	srand(time(0));

	opening();
	// lingua continua returns false if the opening is wrong or if the language is not continua.
	cout << lingua_continua() << endl;

	Text T = txt_to_Text();

	T.display();

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