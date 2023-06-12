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
typedef struct wegPunkt{

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
double gesamtDistance(wegPunkt* pHead);
double Distance(double x, double y);

//void showList(wegPunkt* pH);
//void showElem(wegPunkt* pE);

int main() {
	//Pointer f¸r Liste
	wegPunkt* pStart = NULL;
	wegPunkt* pElemn;
	//restliche Variablen
	double targetX = 0, targetY = 0, dX = 0, dY = 0;
	double totalDist = 0, traveldDist=0, initalDist = 0, dist2target = 0;
	int anz = 0, score=0;
	srand(time(NULL));
	//1. Punkt in Liste allokieren
	pStart = (wegPunkt*)malloc(sizeof(wegPunkt));

	
		pStart->x_koordinate = 0;
		pStart->y_koordinate = 0;
		pStart->pNext;
	
		//Bestimmen ob Target konstant oder zuf‰llig sein soll
		if (ON_OFF == 1) {
			targetX = 3;
			targetY = 2;
			initalDist = Distance(targetX, targetY);
		}
		else {
			targetX = randome();
			targetY = randome();
			initalDist = Distance(targetX, targetY);
		}
		printf("Zielkoordinaten: x:%.2lf \t y:%.2lf.\n", targetX, targetY);
		printf("Anfangsentfernung:%.2lf\n", initalDist);
		dist2target = initalDist;

		while (dist2target >= (initalDist * 0.1)) { //schleife solange nicht n‰her als 10% von inital Distanz
			printf("Bitte eine Strecke eingeben.\n");
			pElemn=newElement();
			appendElement(pStart, pElemn);
			 
			traveldDist = Distance(pElemn->x_koordinate, pElemn->y_koordinate);
			dist2target = sqrt(pow(targetX - pElemn->x_koordinate, 2) + pow(targetY - pElemn->y_koordinate, 2));
			
			
			//Ausgabe des Neuen Standortes
			printf("Neue Position: (x:%.2lf, y:%.2lf)\n", pElemn->x_koordinate, pElemn->y_koordinate);
			printf("Zur¸ckgelegte Teilstrecke: %.2lf\n", traveldDist);
			printf("Neue Entfernung zum Ziel: %.2lf\n", dist2target);


			pStart->pNext; //hier vllt fehler?
		}

	totalDist = gesamtDistance(pStart);
	anz = anzWegPunkte(pStart);
	score = scoring(totalDist, initalDist, anz);
	printf("Zur¸ckgelegte Gesamtstrecke: %.2lf, in %d Z¸gen", totalDist, anz);
	printf("Dein Punktestand betraget: %d", score);
	return;
}

/*
initalDistance: bestimmt Distanz vom Anfang bis zum Schatz
input: "Schatz" koordinaten
return: double distanz
*/
double Distance(double x, double y) {

	double dist;

	dist = sqrt((x * x) + (y * y));

	return dist;
}


/*
randome: generiert eine random zahl die mit dem Makro RANDMAX begrenz wird
input: none (makro, RANDMAX->Invervall)
return: double value
*/
double randome() {
	double val;

	val = (((double)rand() / (double)RANDMAX)*6-5); //generiert randome zahl zwischen +5 und -5
	
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
gessamtDistance: berechnet die absolut zur¸ck gelegte Strecke bis das Ziel gefunden wurde
input: wegPunkt pHead (Head pointer von Liste)
return: double totalDistance (gesamte Distanz)
*/
double gesamtDistance(wegPunkt* pHead) {
	double totalDistance = 0;
	double dx = 0, dy = 0;
	wegPunkt* current = pHead;
	while (current->pNext != NULL) {
		dx = current->pNext->x_koordinate;
		dy = current->pNext->y_koordinate;
		totalDistance += sqrt((dx * dx) + (dy * dy)); //aufsummierung s‰mtlicher zur¸ckgelegter Teilwege
		current = current->pNext;
	}
	return totalDistance;
}

/*
scoring: rechnet anhand gegebener Formel die Punktzahl des Users aus
input: initaldistance, traveldDistance, anzMovment,
return: int score
*/
int scoring(double distance, double initalDistance, int anzWegPunkte) {

	int score = 0;

	score = 100 * (initalDistance / (distance * sqrt(anzWegPunkte)));

	return score;
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
		printf("%s", text);
		test = scanf_s("%.2lf", &val);
		if ((test != 1) || (val > MAXX)) {
			while (getchar() != '\n');
			printf("Maximal erlaubte eingabe x:+-%d und y:+-%d eingeben\n", MAXX, MAXY);
			
		}
	} while (test != 1);


	return val;
}

