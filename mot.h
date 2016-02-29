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
	string get_name(){ return name; } //Méthodes d'accès
	vector<vector<int> > get_parag_positions(){ return position; } //Méthodes d'accès
	vector<int> get_positions(){ return global_position; } //Méthodes d'accès
	void set_parag_pos(int N, int i){ position.push_back({ N, i }); } //Méthodes d'accès
	void set_glb_pos(int i, int Pos){ global_position[i] = global_position[i] + Pos; } //Méthodes d'accès
	void add_new(int No, int i); //Ajout de position pour un mot de nom donné
	void display(); //display
};

//Class Paragraph : vecteur de mots, avec un numéro et une longueur
class Paragraph{
	vector<Mot> Stock;
	int Number;
	int len;

public:
	Paragraph(int i); //Constructeur
	int get_length(){ return len; } //Méthodes d'accès
	int get_number(){ return Number; }; //Méthodes d'accès
	int get_word_number(){ return Stock.size(); } //Méthodes d'accès
	Mot get_word(int i); //Méthodes d'accès
	void set_word(int i, int j, int Pos){ Stock[i].set_glb_pos(j, Pos); } //Méthodes d'accès
	void add_new(Mot M, int pos); //Ajoute un mot à la position p du paragraphe
	void set_length(int L){ len = L; } //Méthodes d'accès
	void set_number(int N){ Number = N; } //Méthodes d'accès
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
	int get_nb_parag(){ return FullParagText.size(); } //Méthodes d'accès
	Paragraph get_parag(int i){ return FullParagText[i]; } //Méthodes d'accès
	void update_pos(); //Update les positions globales
	void display(); //Display les mots par paragraphes
	void display_glob(); //Display les mots par mots
};