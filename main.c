#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include <time.h>
#include "sound.h"
int main(){
	FILE *f;
	short sd[80000];
	while(1){
		system(RCMD);
		f = fopen("test.wav", "r");
		if(f == NULL){
			printf("Cannot open the file\n");
			return 1;
		}

		clearScreen();
		setColors(RED, bg(YELLOW));
		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1, f); //read wav header
		fread(&sd, sizeof(sd), 1, f);		//read wav data
		displayWAVHDR(hdr);
		//displayWAVDATA();
	}
	resetColors();
	printf("\033[1;1H");
	getchar();
	printf("\033[2J");
}
