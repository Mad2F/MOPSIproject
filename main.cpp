#include<cstdlib>
#include <fstream>
#include<ctime>
#include <sstream>
using namespace std;

#include "Graph.h"
#include "CostMat.h"
#include "open.h"

//Méthode random
float rand_float(){
	float number1 = 1; float number2 = 1;
	number1 = rand(); number2 = rand();
	float number = min(number1, number2) / max(number1, number2);
	return number;
}

vector<vector<float> > DTW_texts(Text T1, Text T2, int significativite){
	vector<vector<float> > Result;
	for (int i = 0; i < T1.get_nb_words(); i++){
		vector<float> Interm;
		if (T1.get_word(i).get_positions().size() > significativite){
			for (int j = 0; j < T2.get_nb_words(); j++){
				if (T2.get_word(j).get_positions().size() > 0.5*T1.get_word(i).get_positions().size() && T2.get_word(j).get_positions().size() < 2 * T1.get_word(i).get_positions().size()){
					vector<float> t1, t2;
					for (int k = 0; k < T1.get_word(i).get_positions().size(); k++){
						t1.push_back(float(T1.get_word(i).get_positions()[k]) / float(T1.get_nb_words()));
					}
					for (int k = 0; k < T2.get_word(j).get_positions().size(); k++){
						t2.push_back(float(T2.get_word(j).get_positions()[k]) / float(T2.get_nb_words()));
					}
					vector<vector<float> > CM = costmatrix(t1, t2);
					Interm.push_back(CM[CM.size() - 1][CM[0].size() - 1]);
				}
				else{
					Interm.push_back(-1); 
					// Si le mot n'est pas représenté suffisammen de fois, il n'est pas significatif pour le DTW - gain de temps.
				}
			}
		}
		else{
			for (int j = 0; j < T2.get_nb_words(); j++){
				Interm.push_back(-1); // Si le mot n'est représenté qu'une fois, il n'est pas significatif pour le DTW - gain de temps.
			}
		}
		Result.push_back(Interm);
		cout << "Progression " << float(i) / float(T1.get_nb_words()) * 100 << " %" << endl;
	}
	return Result;
}

int main(){
	srand(time(0));

	//Ouvre le fichier d'entrée
	cout << "Opening first Text" << endl;
	opening("BigL1.txt", "treat1.txt");
	cout << "Opening second Text" << endl;
	opening("BigL2.txt", "treat2.txt");

	// lingua continua returns false if the opening is wrong or if the language is not continua.

	cout << "First Text lingua continua ? " << lingua_continua("treat1.txt") << endl;
	cout << "Second Text lingua continua ? " << lingua_continua("treat2.txt") << endl;

	//On obtient un texte avec des mots
	cout << "Converting Text 1 to an inside structure" << endl;
	Text T1 = txt_to_Text("treat1.txt");
	cout << "Converting Text 2 to an inside structure" << endl;
	Text T2 = txt_to_Text("treat2.txt");

	//Affichage du texte
	cout << "Displaying Text 1" << endl;
	T1.display_glob();
	cout << "Displaying Text 2" << endl;
	T2.display_glob();

	//On transforme les mots en DTW
	cout << "Applying DTW between words of Txt 1 and 2" << endl;
	vector<vector<float> > R = DTW_texts(T1, T2, 50);

	vector<vector<int> > Corresp;
	for (int i = 0; i < R.size() - 1; i++){
		int k = 0;
		for (int j = 0; j < R[0].size() - 1; j++){
			if ((R[i][j] < R[i][k] && R[i][j] != -1) || (R[i][k] == -1 && R[i][j] >= 0)){ k = j; }
		}
		if (R[i][k] != -1){
			Corresp.push_back({ i, k });
		}
	}
	cout << "Writing results in ..\build\Results.txt" << endl;
	ofstream Result{ "Results.txt" };
	if (Result){
		for (int i = 0; i < Corresp.size(); i++){
			Result << T1.get_word(Corresp[i][0]).get_name() << " <-> " << T2.get_word(Corresp[i][1]).get_name() << endl;
		}
		Result.close();
	}
	else{ cout << "ERREUR: Impossible de traiter le fichier." << endl; }
	cout << "Well done, everything went perfectly fine !" << endl;

	return 0;
}