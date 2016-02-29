#include<vector>
using namespace std;

//Fonction qui ouvre un fichier test.txt
void opening(){
	ifstream fichier("test.txt", ios::in);  // on ouvre le fichier en lecture - doit �tre dans le build
	ofstream treat{ "treated.txt" };

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

//D�termine si c'est une lignua continua
bool lingua_continua(){
	ifstream fichier("treated.txt", ios::in);
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

