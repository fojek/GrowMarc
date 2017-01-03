#ifndef MENU_H
#define MENU_H

enum TYPE { GoTo, INCREMENTE, DECREMENTE, CONFIRME };
enum TYPEVAL { NONE, INT, FLOAT };

struct ACTION
{
	TYPE type;
	unsigned int dest;
};

class MENU
{
public:
	// Constantes
	const float FLOAT_INC = 0.5;
	const char l2TemplateInt[16] = "  %i  ";
	const char l2TemplateFloat[16] = "  %f  ";

	// Texte
	char l1[16];
	char l2[16];

	// Actions
	ACTION action[4];

	// Valeurs
	TYPEVAL typeVal;
	int intTemp;
	int intVal;
	float floatTemp;
	float floatVal;

	// Méthodes
	MENU(char[16], char[16], ACTION[4]);
	MENU(char[16], char[16], ACTION[4], int);
	MENU(char[16], char[16], ACTION[4], float);
	bool incremente();
	bool decremente();
	void updateL2(void);
	bool confirme(void);
	void affiche(void);
	void ferme(void);
};


#endif