#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "screen.h"
//#include <time.h>
#include "sound.h"
#include "comm.h"
int main(int argc, char **argv){
	if(argc>1){
		printf("Test tone generator\n");
		int fR, fL, ch;
		float duration;
		printf("No. of channels (1 or 2)\n");
		scanf("%d", &ch);
		if(ch==1){
			printf("Mono frequency: ");
			scanf("%d", &fL);
		}
		else if(ch==2){
			printf("Give Left and Right freq: ");
			scanf("%d %d", &fL, &fR);
		}
		else{
			printf("Wrong number of channels");
			return 1;
		}
		printf("Duration of sound: ");
		scanf("%f", &duration);
		testTone(ch, fL, fR, duration);
		return 0;
	}
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
