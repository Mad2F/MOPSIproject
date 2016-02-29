#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Mot{
	string name;
	vector<vector<int> > position;
	vector<int> global_position;

public:
	Mot(string s, int No, int i);
	string get_name(){ return name; }
	vector<vector<int> > get_parag_positions(){ return position; }
	vector<int> get_positions(){ return global_position; }
	void add_new(int No, int i);
	void set_glb_pos(int i, int Pos){ global_position[i] = global_position[i] + Pos; }
	void display();
};

class Paragraph{
	vector<Mot> Stock;
	int Number;
	int len;

public:
	Paragraph(int i);
	int get_length(){ return len; }
	int get_number(){ return Number; };
	int get_word_number(){ return Stock.size(); }
	Mot get_word(int i);
	void set_word(int i, int j, int Pos){ Stock[i].set_glb_pos(j, Pos); }
	void add_new(Mot M, int pos);
	void set_length(int L){ len = L; }
	void set_number(int N){ Number = N; }
	void display();
};

class Text{
	vector<Paragraph> FullParagText;
	vector<Mot> FullWordText;
	int Language;

public:
	Text(vector<Paragraph> P, int Lang);
	Text();
	void add_new(Paragraph P, int i);
	int get_nb_parag(){ return FullParagText.size(); }
	Paragraph get_parag(int i){ return FullParagText[i]; }
	void update_pos();
	void display();
};