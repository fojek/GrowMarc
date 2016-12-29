#ifndef AFFICHAGELCD_H
#define AFFICHAGELCD_H
#include <vector>
#include <iostream>

using namespace std;

enum TYPE { GoTo, INCREMENTE, DECREMENTE, CONFIRME };

struct ACTION
{
	TYPE type;
	unsigned int dest;
};

class MENU
{
public:
	string texte[2];
	ACTION action[4];
	int valTemp;
	int& val;
	MENU(string[2], ACTION[4], int&);
	friend ostream &operator<<(ostream&, const MENU&);
};

class affichageLCD
{
	const int LARGEUR = 16;
	const int HAUTEUR = 2;

	vector<MENU> menu;
	int menuEnCours = 0;

public:
	affichageLCD();
	int ajouterMenu(string, string, ACTION, ACTION, ACTION, ACTION, int&);
	bool GoToMenu(unsigned int);
	bool PeseBouton(int);
	int MenuActuel() { return menuEnCours; }
	void AfficheMenu();
	string L1() { return menu.at(menuEnCours).texte[0]; }
	string L2() { return menu.at(menuEnCours).texte[1]; }
	
	~affichageLCD();
};

#endif