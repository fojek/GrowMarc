#include <iostream>
#include <string>
#include "affichageLCD.h"

using namespace std;

int main()
{
	affichageLCD menu;

	ACTION actions[4];
	string texte[2];
	int i =  12;

	menu.ajouterMenu("texte1", "texte2"
		, { TYPE::GoTo, 1 }
		, { TYPE::GoTo, 1 }
		, { TYPE::GoTo, 1 }
		, { TYPE::GoTo, 1 }
		, i);

	menu.ajouterMenu("deuxieme menu", "texte2"
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 2 }
	, i);

	menu.ajouterMenu("troisieme menu", "texte2"
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 }
	, i);

	do {
		unsigned int commande;
		menu.AfficheMenu();
		cin >> commande;
		menu.PeseBouton(commande);
	} while (true);
}