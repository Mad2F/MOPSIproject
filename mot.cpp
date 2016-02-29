#include "mot.h"
//*****************MOT**************************************************************
//Constructeur tout bête
Mot::Mot(string s, int No, int i){
	if (!s.empty()){
		name = s;
		add_new(No, i);
	}
}

//Ajoute pour un mot qui a le même nom la position i et le no de paragraphe No
void Mot::add_new(int No, int i){
	vector<int> R;
	R.push_back(No);
	R.push_back(i);
	position.push_back(R);
	global_position.push_back(i);
}


//********************Paragraph*******************************************
//Ajoute un nouveau mot à la position pos au paragraphe
void Paragraph::add_new(Mot M, int pos){
	bool k = false;
	for (int i = 0; i < Stock.size(); i++){
		if (M.get_name() == Stock[i].get_name()){
			Stock[i].add_new(Number, pos);
			k = true;
		}
	}
	if (k == false){
		Stock.push_back(M);
	}
}

//Construit le paragraphe no i
Paragraph::Paragraph(int i){
	Number = i;
	len = 0;
	Stock = {};
}

//Renvoie le mot i du paragraphe
Mot Paragraph::get_word(int i){
	return Stock[i];
};


//*****************Text******************************
//constructeur à partir d'un paragraphe et d'une langue
Text::Text(vector<Paragraph> P, int L){
	Language = L;
	FullParagText = P;
	for (int i = 0; i < P.size(); i++){
		for (int j = 0; j < P[i].get_length() - 1; j++){
			FullWordText.push_back(P[i].get_word(j));
		}
	}
}

//Constructeur vide
Text::Text(){
	Language = 0;
	FullParagText = {};
	FullWordText = {};
}

//Ajoute le paragraphe no i au texte
void Text::add_new(Paragraph P, int i){
	P.set_number(i);
	FullParagText.push_back(P);
}

//Upgrade le texte : ajuste les positions globales
void Text::update_pos(){
	int S = FullParagText[0].get_length();
	for (int i = 1; i < FullParagText.size(); i++){
		for (int j = 0; j < FullParagText[i].get_word_number(); j++){
			int N = FullParagText[i].get_word(j).get_positions().size();
			if (N > 0){
				for (int k = 0; k < N; k++){
					FullParagText[i].set_word(j, k, S);
				}
			}
		}
		S += FullParagText[i].get_length() + 1;
	}

	vector<Mot> R;
	for (int i = 0; i < FullParagText.size(); i++){
		for (int j = 0; j < FullParagText[i].get_word_number(); j++){
			bool K = false;
			for (int k = 0; k < R.size(); k++){
				if (R[k].get_name() == FullParagText[i].get_word(j).get_name()){
					for (int m = 0; m < FullParagText[i].get_word(j).get_positions().size(); m++){
						R[k].add_new(i, FullParagText[i].get_word(j).get_positions()[m]);
					}
					K = true;
				}
			}
			if (!K){
				R.push_back(FullParagText[i].get_word(j));
			}
		}
	}
	FullWordText = R;
}



//*********CATEGORIE DISPLAY DES CLASSES*********************
//Display Mot
void Mot::display(){
	cout << name << " : ";
	for (int i = 0; i < global_position.size(); i++){
		cout << global_position[i] << " ";
	}
	cout << endl;
}

//Diplay Paragraphe
void Paragraph::display(){
	cout << Number << " : " << endl;
	for (int i = 0; i < Stock.size(); i++){
		Stock[i].display();
	}
}

//Display Text par paragraphe
void Text::display(){
	cout << "Text in language " << Language << " : " << endl;
	for (int i = 0; i < FullParagText.size(); i++){
		FullParagText[i].display();
		cout << endl;
	}
}

//Display Text par mot
void Text::display_glob(){
	cout << "Text in language " << Language << " : " << endl;
	for (int i = 0; i < FullWordText.size(); i++){
		FullWordText[i].display();
	}
}