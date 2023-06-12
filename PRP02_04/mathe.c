
#include "mathe.h"

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
