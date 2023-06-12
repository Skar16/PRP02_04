#include "Listenverwaltung.h"



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