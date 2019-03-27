#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include <time.h>

int main(){
	int dec[COL], i;
	srand(time(NULL));
	for(i=0;i<COL;i++) dec[i]=rand()%70+30;
	clearScreen();
	setColors(RED, bg(YELLOW));
	barChart(dec);
	resetColors();
	printf("\033[1;1H");
	getchar();
	printf("\033[2J");
}
