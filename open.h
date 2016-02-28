#include<vector>
using namespace std;

void opening(){
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
}

bool lingua_continua(){
	ifstream fichier("treated.txt", ios::in);
	if (fichier){
		int compteur = 0;
		int compteur_esp = 0;
		char a;
		while (fichier.get(a)){
			compteur++;
			if (a == ' '){
				compteur_esp++;
			}
		}
		cout << compteur << " : " << compteur_esp << endl;
		fichier.close();
		return (compteur_esp / compteur > 0.1);
	}
	else
		cerr << "Impossible d'ouvrir le fichier traité" << endl;
	return false;
}

