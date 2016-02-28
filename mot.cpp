#include "mot.h"

Mot::Mot(string s, int No, int i){
	name = s;
	add_new(No, i);
}

void Mot::add_new(int No, int i){
	vector<int> R;
	R.push_back(No);
	R.push_back(i);
	position.push_back(R);
	global_position.push_back(i);
}

void Paragraph::add_new(string s, int pos){
	bool k = false;
	for (int i = 0; i < Stock.size(); i++){
		if (s == Stock[i].get_name()){
			Stock[i].add_new(Number, pos);
			k = true;
		}
	}
	if (k == false){
		Mot M = Mot(s, Number, pos);
		Stock.push_back(M);
	}
}

Paragraph::Paragraph(vector<Mot> Given, int Num, int L){
	Stock = Given;
	Number = Num;
	len = L;
};
Paragraph::Paragraph(Mot M, int Num, int L){
	Stock.push_back(M);
	Number = Num;
	len = L;
};

Mot Paragraph::get_word(int i){ 
	return Stock[i]; 
};

Text::Text(vector<Paragraph> P, int L){
	Language = L;
	FullParagText = P;
	for (int i = 0; i < P.size(); i++){
		for (int j = 0; j < P[i].get_length(); j++){
			FullWordText.push_back(P[i].get_word(j));
		}
	}
}