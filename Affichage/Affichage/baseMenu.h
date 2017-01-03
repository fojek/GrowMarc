#ifndef BASEMENU_H
#define BASEMENU_H
#include <vector>
#include <iostream>
#include "Menu.h"

using namespace std;

class baseMenu
{
	const int LARGEUR = 16;
	const int HAUTEUR = 2;

	vector<MENU> menu;
	int menuEnCours = 0;

public:
	baseMenu();

	int addMenu(char[16], char[16], ACTION, ACTION, ACTION, ACTION);
	int addMenu(char[16], char[16], ACTION, ACTION, ACTION, ACTION, int);
	int addMenu(char[16], char[16], ACTION, ACTION, ACTION, ACTION, float);

	bool GoToMenu(unsigned int);
	bool PeseBouton(int);
	int MenuActuel() { return menuEnCours; }
	void AfficheMenu();
	string L1() { return menu.at(menuEnCours).l1; }
	string L2() { return menu.at(menuEnCours).l2; }
};

#endif