/*
Dateiname: Schatzsuche.c
Autor: Torben Burandt & Artem H.
Datum: 11.06.2023
Version: 1.1
Ziel: Programm erzeugt random Zahl die der Benutzer anschließend erraten muss, dabei wird eine Liste zum speichern der eingabe verwendet
*/


#define _CRT_SECURE_NO_WARNINGS
#define ON_OFF 0


#include "main.h"
#include "mathe.h"
#include"Listenverwaltung.h"



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
		pElemn=lastElementDistance(pHead, targetX, targetY);
		appendElement(pHead, pElemn);
		lastDist = dist2target;
		printf("Letze Teilstrecke: %.2lf\n", lastDist);
	}


	//Ausgabe gesamt Strecke und Punktestand
	totalDist = gesamtDistance(pHead) + lastDist;
	anz = anzWegPunkte(pHead)-1;
	score = scoring(totalDist, initalDist, anz);
	printf("Zurueckgelegte Gesamtstrecke: %.2lf, in %d Zuegen.\n", totalDist, anz);
	printf("Dein Punktestand betraget: %d\n\n", score);
	return;
}













