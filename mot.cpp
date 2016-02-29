#include "mot.h"

Mot::Mot(string s, int No, int i){
	if (!s.empty()){
		name = s;
		add_new(No, i);
	}
}

void Mot::add_new(int No, int i){
	vector<int> R;
	R.push_back(No);
	R.push_back(i);
	position.push_back(R);
	global_position.push_back(i);
}

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

Paragraph::Paragraph(int i){
	Number = i;
	len = 0;
	Stock = {};
}

Mot Paragraph::get_word(int i){
	return Stock[i];
};

Text::Text(vector<Paragraph> P, int L){
	Language = L;
	FullParagText = P;
	for (int i = 0; i < P.size(); i++){
		for (int j = 0; j < P[i].get_length() - 1; j++){
			FullWordText.push_back(P[i].get_word(j));
		}
	}
}

Text::Text(){
	Language = 0;
	FullParagText = {};
	FullWordText = {};
}

void Text::add_new(Paragraph P, int i){
	P.set_number(i);
	FullParagText.push_back(P);
}

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
}

void Mot::display(){
	cout << name << " : ";
	for (int i = 0; i < global_position.size(); i++){
		cout << global_position[i] << " ";
	}
	cout << endl;
}

void Paragraph::display(){
	cout << Number << " : " << endl;
	for (int i = 0; i < Stock.size(); i++){
		Stock[i].display();
	}
}

void Text::display(){
	cout << "Text in language " << Language << " : " << endl;
	for (int i = 0; i < FullParagText.size(); i++){
		FullParagText[i].display();
		cout << endl;
	}
}