#include<vector>
using namespace std;

#include "mot.h"

//Fonction qui ouvre un fichier test.txt
void opening(string entree, string sortie){
	ifstream fichier(entree, ios::in);  // on ouvre le fichier en lecture - doit être dans le build
	ofstream treat{ sortie };

	if (fichier)  // si l'ouverture a réussi
	{
		if (treat){
			string ligne{};
			string mot{};
			vector<string> Stock;
			//On récupère toutes les lignes du fichier texte
			while (getline(fichier, ligne)){
				Stock.push_back(ligne);
			}
			for (int i = 0; i < Stock.size(); i++){
				string Res;
				int S = Stock[i].size();
				for (int j = 0; j < Stock[i].size(); j++){
					if (j < S - 2){
						//On règle les probl de type espace + ponctuation -> ponctuation et les ' + espace -> '
						if (Stock[i][j] == ' '){
							if (Stock[i][j + 1] != '.' && Stock[i][j + 1] != ',' && Stock[i][j + 1] != ';' && Stock[i][j + 1] != '?' && Stock[i][j + 1] != '!' && Stock[i][j + 1] != ' ' && Stock[i][j + 1] != '\'' && Stock[i][j - 1] != '\''){
								Res = Res + Stock[i][j];
							}

						}
						//On règle les probl de type ponctuation + Lettre -> ponctuation + espace + lettre
						else if (Stock[i][j] == '.' || Stock[i][j] == ',' || Stock[i][j] == ';' || Stock[i][j] == '?' || Stock[i][j] == '!'){
							if (Stock[i][j + 1] != ' '){
								Res = Res + Stock[i][j] + ' ';
							}
							else { Res = Res + Stock[i][j]; }
						}
						//On ajoute le caractère normal
						else { Res = Res + Stock[i][j]; }
					}
					//On règle le problème de espace + /n -> /n
					else if (j == S - 1 && Stock[i][j] == ' '){}
					//On ajoute le caractère normal
					else { Res = Res + Stock[i][j]; }
				}
				//On enlève le double retour à la ligne
				if (Res != ""){
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
}

//Détermine si c'est une lignua continua
bool lingua_continua(string sortie){
	ifstream fichier(sortie, ios::in);
	if (fichier){
		//Comptuer de caractères + compteur d'espaces seulement
		int compteur = 0;
		int compteur_esp = 0;
		char a;
		//On récupère tous les caractères. 
		//On récupère aussi les /n mais ce n'est pas grave, ayant aligné et normalisé les paragraphes, il y a le mm nombre de /n, qu'on considère comme faisant partie des caractères.
		while (fichier.get(a)){
			compteur++;
			if (a == ' '){
				compteur_esp++;
			}
		}
		fichier.close();
		//Si false, on n'a pas de Lingua Continua.
		return (compteur_esp / compteur > 0.1);
	}
	else
		cerr << "Impossible d'ouvrir le fichier traité" << endl;
	return false;
}

//Méthodes pour séparer des string en vecteur de string - parse en python
//Ajout de méthode pour gérer la ponctuation à la fin et les majuscules au début
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

//Méthodes pour séparer des string en vecteur de string - parse en python
vector<string> split(string s, char delim) {
	vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

//Classifie le texte en Mots, Paragraphes et Texte.
Text txt_to_Text(string sortie){
	//Init
	ifstream fichier(sortie, ios::in);
	Text T;
	bool LC = lingua_continua(sortie);
	string ligne{};
	string mot{};
	vector<string> Stock;

	//Essai d'ouvrir le fichier
	if (fichier){
		//Stocke les lignes dans un vecteur
		while (getline(fichier, ligne)){
			Stock.push_back(ligne);
		}
		for (int i = 0; i < Stock.size(); i++){
			//Si Lingua continua on parse tous les caractères.
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
			// Sinon on parse en fonction des espaces
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
		//On ferme le fichier et on update les positions globales du texte.
		fichier.close();
		T.update_pos();
		return T;
	}
	//Problème ouverture fichier, renvoie texte vide
	else{
		cerr << "Impossible d'ouvrir le fichier traité" << endl;
		return T;
	}
}
