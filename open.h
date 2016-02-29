#include<vector>
using namespace std;

//Fonction qui ouvre un fichier test.txt
void opening(){
	ifstream fichier("test.txt", ios::in);  // on ouvre le fichier en lecture - doit être dans le build
	ofstream treat{ "treated.txt" };

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
}

//Détermine si c'est une lignua continua
bool lingua_continua(){
	ifstream fichier("treated.txt", ios::in);
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

