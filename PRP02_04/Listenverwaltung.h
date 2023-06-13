#pragma once
#include "main.h"
#include "mathe.h"

wegPunkt* newElement(wegPunkt* pH);
wegPunkt* appendElement(wegPunkt* pH, wegPunkt* pE);
wegPunkt* lastElement(wegPunkt* pH);
int anzWegPunkte(wegPunkt* pH);
double gesamtDistance(wegPunkt* pHead);
wegPunkt* lastElementDistance(wegPunkt* pH, double targetX, double targetY);