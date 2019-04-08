//sound levels as a bar chart
#include <stdio.h>
#include "screen.h"
#include <math.h>
void clearScreen(void){
	printf("\033[2J");
	fflush(stdout);
}

void setColors(short bg, short fg){
	printf("\033[%d;%d;1m", bg, fg);
	fflush(stdout);
}

void resetColors(void){
	printf("\033[0m");
	fflush(stdout);
}

void barChart(int db[]){
	int i, j;
	for(i=0;i<COL;i++){
		for(j=0;j<round(db[i]/3.0);j++){
			if((j>=25)&&(db[i]>=75)){
				setColors(GREEN, bg(BLACK));
			}
			else{
				setColors(RED, bg(BLACK));
			}
			printf("\033[%d;%dH", 35-j, i+1);

#ifdef UNICODE
			printf("%s", BAR);
#else
			printf("%c", '*');
#endif
		}
	}
}

int peakcount(int db[]){
	int count=0;
	for(int i=1;i<80;i++){
		if(db[i]>=75&&(db[i-1]<75)) count++;
	}
	return count;
}
