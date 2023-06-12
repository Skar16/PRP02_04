/*
Dateiname: Schatzsuche.c
Autor: Torben Burandt & Artem H.
Datum: 11.06.2023
Version: 1.1
Ziel: Programm erzeugt random Zahl die der Benutzer anschließend erraten muss, dabei wird eine Liste zum speichern der eingabe verwendet
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
#define RANDMAX 5
#define ON_OFF 0


//Strukturierter Datentyp
typedef struct wegPunkt {

	double x_koordinate;
	double y_koordinate;
	struct wegPunkt* pNext;
}wegPunkt;


//Fkt. Prototypen
wegPunkt* newElement(wegPunkt* pH);
double getDouble(char text[]);
wegPunkt* appendElement(wegPunkt* pH, wegPunkt* pE);
int anzWegPunkte(wegPunkt* pH);
double randome();
double gesamtDistance(wegPunkt* pHead);
double Distance(double x, double y);
int scoring(double distance, double initalDistance, int anzWegPunkte);
wegPunkt* lastElement(wegPunkt* pH);


int main() {
	//Pointer fuer Liste
	wegPunkt* pHead = NULL; //startpunkt der Liste
	wegPunkt* pElemn; //pointer fuer neues Element

	//restliche Variablen
	double targetX = 0, targetY = 0, dX = 0, dY = 0;
	double totalDist = 0, traveldDist = 0, initalDist = 0, dist2target = 0, lastDist = 0;
	int anz = 0, score = 0;
	srand(time(NULL));



	//1. Punkt in Liste allokieren
	pHead = (wegPunkt*)malloc(sizeof(wegPunkt));
	pHead->x_koordinate = 0;
	pHead->y_koordinate = 0;
	pHead->pNext = NULL;


	//Bestimmen ob Target konstant oder zufaellig sein soll
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
	printf("Anfangsentfernung:%.2lfkm\n", initalDist);
	dist2target = initalDist;

	while (dist2target >= (initalDist * 0.1)) { //schleife solange nicht naeher als 10% von inital Distanz
		printf("Bitte eine Strecke eingeben.\n");
		pElemn = newElement(pHead);
		
		wegPunkt* lastElem=lastElement(pHead); //suche nach letzem Koordinaten Punkt
		/*
		wegPunkt* pSearch;
		while(pSearch->pNext!=NULL) //nach letztem neueintrag in liste suchen, so vewerwendet man listen normalerweise
		*/
		traveldDist = Distance((lastElem->x_koordinate-pElemn->x_koordinate), (lastElem->y_koordinate-pElemn->y_koordinate)); //Bestimmung aktueller Position
		dist2target = sqrt(pow(targetX - pElemn->x_koordinate, 2) + pow(targetY - pElemn->y_koordinate, 2)); //distanz zum Ziel bestimmen
		
		appendElement(pHead, pElemn); //eingegebenes Element an Liste anhängen
		printf("\n");
		
		
		//Ausgabe des Neuen Standortes
		printf("Neue Position: (x:%.2lf, y:%.2lf)\n", pElemn->x_koordinate, pElemn->y_koordinate);
		printf("Zurueckgelegte Teilstrecke: %.2lf\n", traveldDist);
		printf("Neue Entfernung zum Ziel: %.2lf\n", dist2target);
		printf("\n\n");

	}
	//letzen 10% werden automatisch zurückgelegt, letze Distanz wird berechnet
	if ((dist2target <= (initalDist * 0.1)) && (dist2target!=0)) {
		printf("Schatz in Sichtweite, du mobilisierst deine letzten Kraefte und setzt zum Sprint an.\n");
		lastDist = initalDist - traveldDist;
		printf("Letze Teilstrecke: %.2lf\n", lastDist);
		anz = 1;
	}


	//Ausgabe gesamt Strecke und Punktestand
	totalDist = gesamtDistance(pHead) + lastDist;
	anz = anzWegPunkte(pHead)-1;
	score = scoring(totalDist, initalDist, anz);
	printf("Zurueckgelegte Gesamtstrecke: %.2lf, in %d Zuegen.\n", totalDist, anz);
	printf("Dein Punktestand betraget: %d\n\n", score);
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

	val = (((double)(rand() % (RANDMAX * 200)) / 100) - RANDMAX); //generiert randome zahl zwischen +5 und -5

	return val;
}


/*
newElement: legt neues Element in der Liste an
input: none
return: struct values + pointer aufs naechste Elemnt pNext
*/
wegPunkt* newElement(wegPunkt* pH) {
	//Speicherallokierung
	wegPunkt* pE = (wegPunkt*)malloc(sizeof(wegPunkt));
	wegPunkt* pLast = lastElement(pH);//suche letztes Element zur Differenzbestimmung der Distanz zum neuen Punkt

	//einlesen der Werte und neue Verknuepfung auf pNext
	pE->x_koordinate = getDouble("delta-x:") + pLast->x_koordinate;
	pE->y_koordinate = getDouble("delta-y:") + pLast->y_koordinate;
	pE->pNext = NULL;
	return pE;
}

/*
lastElement: sucht letzes Element in Liste
input: pH(Startpunkt der Liste)
return: wegPunkt* pH (gebunden auf letztes Listen Element)
*/
wegPunkt* lastElement(wegPunkt* pH) {

	while (pH->pNext != NULL) { //Suche letzes Listelement
		pH = pH->pNext;
	}

	return pH;
}


/*
appendElement: haengt neuerzeugtes Element an bestehende Liste
input: pStart, pElement
return: pElement(angehaengt), pStart(Listenkopf) -- Typ: struct(wegPunkt)
*/
wegPunkt* appendElement(wegPunkt* pH, wegPunkt* pE) {


	wegPunkt* pSearch = pH; //Suchpointer
	if (pH == NULL) { //Falls liste leer, erstes Element= listenkopf
		return pE;
	}
	else {
		while (pSearch->pNext != NULL)  //Ansonsten suchen bis NULL Pointer (End of list) gefunden
			pSearch = pSearch->pNext; //suchpointer umlegen
		pSearch->pNext = pE;	  //suchpointer auf Listenelement verknuepfen
		return pH; //Listenkopf beibehalten

	}
}

/*
anzWegPunkte: gibt die Anzahl an Datenblock eintraegen in der Liste wieder
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
gessamtDistance: berechnet die absolut zurueck gelegte Strecke bis das Ziel gefunden wurde
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
		totalDistance += Distance(dx, dy); //aufsummierung saemtlicher zurueckgelegter Teilwege
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
Einlesenfkt fuer double Werte.
input: Ausgabe was eingegben werden soll
return: double value
*/
double getDouble(char text[]) {


	double val = 0;
	int test = 0;
	do {
		printf("%s", text);
		test = scanf_s("%lf", &val);
		if (test != 1) { // ||((val > MAXX)||(val>MAXY)))
			while (getchar() != '\n');
			printf("Maximal erlaubte eingabe x:+-%d und y:+-%d eingeben\n", MAXX, MAXY);

		}
	} while (test != 1);


	return val;
}

