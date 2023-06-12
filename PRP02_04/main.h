#pragma once


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



//Strukturierter Datentyp
typedef struct wegPunkt {

	double x_koordinate;
	double y_koordinate;
	struct wegPunkt* pNext;
}wegPunkt;


//Fkt. Prototypen



