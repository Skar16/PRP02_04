/*
Dateiname: Schatzsuche.c
Autor: Torben Burandt & Artem H.
Datum: 11.06.2023
Version: 1.1
Ziel: Programm erzeugt random Zahl die der Benutzer anschlieﬂend erraten muss, dabei wird eine Liste zum speichern der eingabe verwendet
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


#define X 5
#define Y 3.5
#define MAXX 5
#define MAXY 5
#define RANDMAX 10
#define ON_OFF 1


//Strukturierter Datentyp
typedef struct {

	double x_koordinate;
	double y_koordinate;
	struct wegPunkt* pNext;
}wegPunkt;


//Fkt. Prototypen
wegPunkt* newElement();
double getDouble(char text[]);
wegPunkt* appendElement(wegPunkt* pH, wegPunkt* pE);
int anzWegPunkte(wegPunkt* pH);
double randome();

//void showList(wegPunkt* pH);
//void showElem(wegPunkt* pE);

int main() {
	wegPunkt* pStart = NULL;
	wegPunkt* pElemn;


	srand(time(NULL));
	//1. Punkt in Liste auf Ursprung setzen
	pStart = (wegPunkt*)malloc(sizeof(wegPunkt));

	if (ON_OFF == 0) {
		pStart->x_koordinate = 0;
		pStart->y_koordinate = 0;
		pStart->pNext;
	}

	else {
		pStart->x_koordinate = randome();
		pStart->y_koordinate = randome();
		pStart->pNext;

	}



	double test = getDouble("zw. 1-10");
	printf("%lf", test);

	return;
}





double randome() {
	double val;

	val = ((double)rand() / (double)RANDMAX);

	return val;
}


/*
newElement: legt neues Element in der Liste an
input: none
return: struct values + pointer aufs n‰chste Elemnt pNext
*/
wegPunkt* newElement() {
	//Speicherallokierung
	wegPunkt* pE = (wegPunkt*)malloc(sizeof(wegPunkt));

	//einlesen der Werte und neue Verkn¸pfung auf pNext
	pE->x_koordinate = getDouble("delta-x:");
	pE->y_koordinate = getDouble("delta-y:");
	pE->pNext = NULL;
	return pE;
}

/*
appendElement: h‰ngt neuerzeugtes Element an bestehende Liste
input: pStart, pElement
return: pElement(angeh‰ngt), pStart(Listenkopf) -- Typ: struct(wegPunkt)
*/
wegPunkt * appendElement(wegPunkt* pH, wegPunkt* pE) {


	wegPunkt * pSearch = pH; //Suchpointer
	if (pH == NULL) { //Falls liste leer, erstes Element= listenkopf
		return pE;
	}
	else {
		while (pSearch->pNext != NULL) { //Ansonsten suchen bis NULL Pointer (End of list) gefunden
			pSearch = pSearch->pNext; //suchpointer umlegen
			pSearch->pNext = pE;	  //suchpointer auf Listenelement verkn¸pfen
			return pH; //Listenkopf beibehalten
		}
	}
}

/*
anzWegPunkte: gibt die Anzahl an Datenblock eintr‰gen in der Liste wieder
input: pH(pStart), listenkopf
return: int anz
*/
int anzWegPunkte(wegPunkt* pH) {
	int anz = 1;
	if (pH == NULL) //Liste leer
		return 0;
	while (pH->pNext != NULL) {
		anz++;
		pH = pH->pNext;
	}
	return anz;
}




/*
Einlesenfkt f¸r double Werte.
input: Ausgabe was eingegben werden soll
return: double value
*/
double getDouble(char text[]) {


	double val = 0;
	int test = 0;
	do {
		test = scanf_s("%lf", &val);
		if ((test != 1) || (val > MAXX)) {
			while (getchar() != '\n');
			printf("Bitte maximal x-%d und y-%d eingeben\n", MAXX, MAXY);
			printf("%s", text);
		}
	} while (test != 1);


	return val;
}



/*
void showList(wegPunkt* pH) {
	wegPunkt* pE;
	unsigned int i;
	for (i = 0, pE = pH; i < getCount(pH); i++) {
		printf("%2d", i + 1);
		showElem(pE);
		pE = pE->pNext;
	}
}

void showElem(wegPunkt* pE) {
	printf("%lf  %lf", pE->pNext, pE->y_koordinate);
}
*/