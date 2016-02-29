#include<string>
#include<vector>
#include<iostream>
using namespace std;

// Classe mot : a un nom name, un vecteur de position avec (no de paragraphe, position) et un veteur de position globale (position)
class Mot{
	string name;
	vector<vector<int> > position;
	vector<int> global_position;

public:
	Mot(string s, int No, int i); //Constructeur
	string get_name(){ return name; } //M�thodes d'acc�s
	vector<vector<int> > get_parag_positions(){ return position; } //M�thodes d'acc�s
	vector<int> get_positions(){ return global_position; } //M�thodes d'acc�s
	void set_parag_pos(int N, int i){ position.push_back({ N, i }); } //M�thodes d'acc�s
	void set_glb_pos(int i, int Pos){ global_position[i] = global_position[i] + Pos; } //M�thodes d'acc�s
	void add_new(int No, int i); //Ajout de position pour un mot de nom donn�
	void display(); //display
};

//Class Paragraph : vecteur de mots, avec un num�ro et une longueur
class Paragraph{
	vector<Mot> Stock;
	int Number;
	int len;

public:
	Paragraph(int i); //Constructeur
	int get_length(){ return len; } //M�thodes d'acc�s
	int get_number(){ return Number; }; //M�thodes d'acc�s
	int get_word_number(){ return Stock.size(); } //M�thodes d'acc�s
	Mot get_word(int i); //M�thodes d'acc�s
	void set_word(int i, int j, int Pos){ Stock[i].set_glb_pos(j, Pos); } //M�thodes d'acc�s
	void add_new(Mot M, int pos); //Ajoute un mot � la position p du paragraphe
	void set_length(int L){ len = L; } //M�thodes d'acc�s
	void set_number(int N){ Number = N; } //M�thodes d'acc�s
	void display(); //display
};

//Class Text : vecteur de paragraphes, vecteur avec tous les mots, langue
class Text{
	vector<Paragraph> FullParagText;
	vector<Mot> FullWordText;
	int Language;

public:
	Text(vector<Paragraph> P, int Lang); //Constructeur
	Text(); //Constructeur
	void add_new(Paragraph P, int i); //Ajout d'un paragraph no i
	int get_nb_parag(){ return FullParagText.size(); } //M�thodes d'acc�s
	Paragraph get_parag(int i){ return FullParagText[i]; } //M�thodes d'acc�s
	void update_pos(); //Update les positions globales
	void display(); //Display les mots par paragraphes
	void display_glob(); //Display les mots par mots
};