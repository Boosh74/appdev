#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "screen.h"
//#include <time.h>
#include "sound.h"
#include "comm.h"
int main(){
	FILE *f;
	short sd[RATE];
	while(1){
		int ret = system(RCMD);
		if(ret == SIGINT) break;
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
		displayWAVDATA(sd);
		sendDATA(sd);
	}
	resetColors();
	printf("\033[2J");
}
