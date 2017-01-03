#include "baseMenu.h"

using namespace std;

baseMenu::baseMenu()
{
}

int baseMenu::addMenu(char l1[16], char l2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4)
{
	ACTION a[] = { a1, a2, a3, a4 };

	MENU m(l1, l2, a);

	menu.push_back(m);
	return menu.size() - 1;
}

int baseMenu::addMenu(char l1[16], char l2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4, int val)
{	
	ACTION a[] = { a1, a2, a3, a4 };

	MENU m(l1, l2, a, val);

	menu.push_back(m);
	return menu.size() - 1;
}

int baseMenu::addMenu(char l1[16], char l2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4, float val)
{
	ACTION a[] = { a1, a2, a3, a4 };

	MENU m(l1, l2, a, val);

	menu.push_back(m);
	return menu.size() - 1;
}

bool baseMenu::GoToMenu(unsigned int dest)
{
	if (dest < menu.size())
	{
		menu.at(menuEnCours).ferme();
		menuEnCours = dest;
		return true;
	}
	return false;
}

bool baseMenu::PeseBouton(int bouton)
{
	switch (menu.at(menuEnCours).action[bouton].type)
	{
	case GoTo:
		return GoToMenu(menu.at(menuEnCours).action[bouton].dest);
	case INCREMENTE:
		if (menu.at(menuEnCours).incremente())
			return true;
		return false;
	case DECREMENTE:
		if (menu.at(menuEnCours).decremente())
			return true;
		return false;
	case CONFIRME:
		if (menu.at(menuEnCours).confirme())
			return true;
		return false;
	default:
		break;
	}
	return false;
}

void baseMenu::AfficheMenu()
{
	menu.at(menuEnCours).affiche();
}