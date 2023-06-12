#pragma once
#include "main.h"
#include "mathe.h"

wegPunkt* newElement(wegPunkt* pH);
wegPunkt* appendElement(wegPunkt* pH, wegPunkt* pE);
wegPunkt* lastElement(wegPunkt* pH);
int anzWegPunkte(wegPunkt* pH);
double gesamtDistance(wegPunkt* pHead);