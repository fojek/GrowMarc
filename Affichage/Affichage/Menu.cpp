#include "Menu.h"
#include <string>
#include <iostream>

using namespace std;

MENU::MENU(char ligne1[16], char ligne2[16], ACTION a[4])
{
	strcpy_s(l1, ligne1);
	strcpy_s(l2, ligne2);

	action[0] = a[0];
	action[1] = a[1];
	action[2] = a[2];
	action[3] = a[3];

	typeVal = NONE;
}

MENU::MENU(char ligne1[16], char ligne2[16], ACTION a[4], int v)
{
	strcpy_s(l1, ligne1);
	strcpy_s(l2, ligne2);

	action[0] = a[0];
	action[1] = a[1];
	action[2] = a[2];
	action[3] = a[3];

	intVal = intTemp = v;

	typeVal = INT;

	updateL2();
}

MENU::MENU(char ligne1[16], char ligne2[16], ACTION a[4], float v)
{
	strcpy_s(l1, ligne1);
	strcpy_s(l2, ligne2);

	action[0] = a[0];
	action[1] = a[1];
	action[2] = a[2];
	action[3] = a[3];

	floatVal = floatTemp = v;

	typeVal = FLOAT;

	updateL2();
}

bool MENU::incremente()
{
	if (typeVal == INT)
		++intTemp;
	else if (typeVal == FLOAT)
		floatTemp += FLOAT_INC;
	else
		return false;
	cout << "Valeur : "<< intTemp << endl;
	updateL2();
	return true;
}

bool MENU::decremente()
{
	if (typeVal == INT)
		--intTemp;
	else if (typeVal == FLOAT)
		floatTemp -= FLOAT_INC;
	else
		return false;

	updateL2();
	return true;
}

void MENU::updateL2(void)
{
	if (typeVal == INT)
		sprintf_s(l2, l2TemplateInt, intTemp);
	else if (typeVal == FLOAT)
		sprintf_s(l2, l2TemplateFloat, floatTemp);
}

bool MENU::confirme()
{
	if (typeVal == INT)
		intVal = intTemp;
	else if (typeVal == FLOAT)
		floatVal = floatTemp;
	else
		return false;

	return true;
}

void MENU::affiche()
{
	cout << "----------------" << endl;
	cout << l1 << endl << l2 << endl << endl;
	cout << "----------------" << endl;
}

void MENU::ferme()
{
	intTemp = intVal;
	floatTemp = floatVal;
	updateL2();
}
