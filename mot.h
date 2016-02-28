#include<string>
#include<vector>
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
};

class Paragraph{
	vector<Mot> Stock;
	int Number;
	int len;

public:
	Paragraph(vector<Mot> Given, int Num, int L);
	Paragraph(Mot M, int Num, int L);
	int get_length(){ return len; }
	int get_number(){ return Number; };
	Mot get_word(int i);
	void add_new(string s, int pos);
};

class Text{
	vector<Paragraph> FullParagText;
	vector<Mot> FullWordText;
	int Language;

public:
	Text(vector<Paragraph> P, int Lang);
};