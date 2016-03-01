#include<vector>
using namespace std;

#include "mot.h"

//Fonction qui ouvre un fichier test.txt
void opening(string entree, string sortie){
	ifstream fichier(entree, ios::in);  // on ouvre le fichier en lecture - doit �tre dans le build
	ofstream treat{ sortie };

	if (fichier)  // si l'ouverture a r�ussi
	{
		if (treat){
			string ligne{};
			string mot{};
			vector<string> Stock;
			//On r�cup�re toutes les lignes du fichier texte
			while (getline(fichier, ligne)){
				Stock.push_back(ligne);
			}
			for (int i = 0; i < Stock.size(); i++){
				string Res;
				int S = Stock[i].size();
				for (int j = 0; j < Stock[i].size(); j++){
					if (j < S - 2){
						//On r�gle les probl de type espace + ponctuation -> ponctuation et les ' + espace -> '
						if (Stock[i][j] == ' '){
							if (Stock[i][j + 1] != '.' && Stock[i][j + 1] != ',' && Stock[i][j + 1] != ';' && Stock[i][j + 1] != '?' && Stock[i][j + 1] != '!' && Stock[i][j + 1] != ' ' && Stock[i][j + 1] != '\'' && Stock[i][j - 1] != '\''){
								Res = Res + Stock[i][j];
							}

						}
						//On r�gle les probl de type ponctuation + Lettre -> ponctuation + espace + lettre
						else if (Stock[i][j] == '.' || Stock[i][j] == ',' || Stock[i][j] == ';' || Stock[i][j] == '?' || Stock[i][j] == '!'){
							if (Stock[i][j + 1] != ' '){
								Res = Res + Stock[i][j] + ' ';
							}
							else { Res = Res + Stock[i][j]; }
						}
						//On ajoute le caract�re normal
						else { Res = Res + Stock[i][j]; }
					}
					//On r�gle le probl�me de espace + /n -> /n
					else if (j == S - 1 && Stock[i][j] == ' '){}
					//On ajoute le caract�re normal
					else { Res = Res + Stock[i][j]; }
				}
				//On enl�ve le double retour � la ligne
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

//D�termine si c'est une lignua continua
bool lingua_continua(string sortie){
	ifstream fichier(sortie, ios::in);
	if (fichier){
		//Comptuer de caract�res + compteur d'espaces seulement
		int compteur = 0;
		int compteur_esp = 0;
		char a;
		//On r�cup�re tous les caract�res. 
		//On r�cup�re aussi les /n mais ce n'est pas grave, ayant align� et normalis� les paragraphes, il y a le mm nombre de /n, qu'on consid�re comme faisant partie des caract�res.
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
		cerr << "Impossible d'ouvrir le fichier trait�" << endl;
	return false;
}

//M�thodes pour s�parer des string en vecteur de string - parse en python
//Ajout de m�thode pour g�rer la ponctuation � la fin et les majuscules au d�but
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

//M�thodes pour s�parer des string en vecteur de string - parse en python
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
			//Si Lingua continua on parse tous les caract�res.
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
	//Probl�me ouverture fichier, renvoie texte vide
	else{
		cerr << "Impossible d'ouvrir le fichier trait�" << endl;
		return T;
	}
}
