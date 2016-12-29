#include "affichageLCD.h"
#include <string>
#include <iostream>

using namespace std;

affichageLCD::affichageLCD()
{
}

int affichageLCD::ajouterMenu(string l1, string l2, ACTION a1, ACTION a2, ACTION a3, ACTION a4, int& val)
{	
	// Texte trop long
	if (static_cast<int>(l1.length()) > LARGEUR || static_cast<int>(l2.length()) > LARGEUR)
		return -1;

	string lignes[] = { l1, l2 };
	ACTION a[] = { a1, a2, a3, a4 };

	MENU m(lignes, a, val);

	menu.push_back(m);
	return menu.size() - 1;
}

bool affichageLCD::GoToMenu(unsigned int dest)
{
	if (dest < menu.size())
	{
		menu.at(menuEnCours).valTemp = 0;
		menuEnCours = dest;
		return true;
	}
	return false;
}

bool affichageLCD::PeseBouton(int bouton)
{
	switch (menu.at(menuEnCours).action[bouton].type)
	{
	case GoTo:
		return GoToMenu(menu.at(menuEnCours).action[bouton].dest);
	case INCREMENTE:
		++menu.at(menuEnCours).valTemp;
		return true;
	case DECREMENTE:
		--menu.at(menuEnCours).valTemp;
		return true;
	case CONFIRME:
		menu.at(menuEnCours).val = menu.at(menuEnCours).valTemp;
		return true;
	default:
		break;
	}
	return false;
}

void affichageLCD::AfficheMenu()
{
	cout << menu.at(menuEnCours);
}

affichageLCD::~affichageLCD()
{
}

MENU::MENU(string s[2], ACTION a[4], int &v)
	: val(v)
{
	texte[0] = s[0];
	action[0] = a[0];
	action[1] = a[1];
	action[2] = a[2];
	action[3] = a[3];
}

ostream &operator<<(ostream & s, const MENU &m)
{
	s << m.texte[0] << endl << m.texte[1] << endl << endl;
	return s;
}
