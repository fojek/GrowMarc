#include <iostream>
#include <string>
#include "baseMenu.h"

using namespace std;

int main()
{
	baseMenu menu;

	ACTION actions[4];
	string texte[2];
	int i =  12;

	menu.addMenu("ChocoMarc v1.0", "< hit any key >"
		, { TYPE::GoTo, 1 }
		, { TYPE::GoTo, 2 }
		, { TYPE::GoTo, 0 }
		, { TYPE::GoTo, 0 });

	menu.addMenu("Valeur int", "valInt"
		, { TYPE::INCREMENTE, 0 }
		, { TYPE::DECREMENTE, 0 }
		, { TYPE::CONFIRME, 0 }
		, { TYPE::GoTo, 0 }
	, 12);

	menu.addMenu("Valeur float", "floatVal"
		, { TYPE::INCREMENTE, 0 }
		, { TYPE::DECREMENTE, 0 }
		, { TYPE::CONFIRME, 0 }
		, { TYPE::GoTo, 0 }
	, 3.1415F);

	do {
		unsigned int commande;
		menu.AfficheMenu();
		cin >> commande;
		menu.PeseBouton(commande);
	} while (true);
}