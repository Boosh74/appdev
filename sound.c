#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"

void fillID(char *d, const char *s){
	for(int i=0; i<4; i++)
		*d++ = *s++;
}

void testTone(int c, int fl, int fr, float d){
	if(c<1 || c>2){
		printf("Wrong number of channels.\n");
		return;
	}
	if(fl<50 || fl>16000){
		printf("Frequency is out of range\n");
		return;
	}
	if(d<1.0 || d>10.0){
		printf("Wrong duration");
		return;
	}
// if arguments are okay we:
// 1) Make wave header
// 2) Generate samples
// 3) Write them into a file
	struct WAVHDR h;
	int samples = 44100*d;
	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.SubChunk1ID, "fmt ");
	fillID(h.SubChunk2ID, "data");
	h.SubChunk1Size = 16;
	h.AudioFormat = 1;
	h.SampleRate = 44100;
	h.BitsPerSample = 16;
	h.BlockAlign = c*16/8;
	h.NumChannels = c;
	h.ByteRate = 44100*c*16/8;
	h.SubChunk2Size = samples*c*16/8;
	h.ChunkSize = h.SubChunk2Size + 36;

	FILE *fp = fopen("testTone.wav", "w");
	if(fp==NULL){
		printf("Cannot open a file\n");
		return;
	}
	printf("TestTone is generated\n");
	fwrite(&h, sizeof(h), 1, fp);
	for(int i=0;i<samples;i++){
		short sL = 32767.0 * sin(2*PI*fl*i/44100);
		fwrite(&sL, sizeof(short), 1, fp);
		if(c==2){
			short sR = 32767.0 * sin(2*PI*fr*i/44100);
			fwrite(&sR, sizeof(short), 1, fp);
		}
	}
	fclose(fp);
}

void showID(char *idname, char 	*id){
	int i;
	printf("%s: ", idname);
	for(i=0;i<4;i++)
		printf("%c", id[i]);
	puts("");
}

int findPeaks(int d[]){
	int c = 0, i;
	for (i=1;i<80;i++){
		if(d[i]>=75 && d[i-1]<75){
			c++;
		}
	}
	if(d[0]>=75) c++;
	return c;
}

//function below gets one second of samples and calculates
//80 pieces of decibel value, one piece per 200 samples by RMS formula (ROOT MEAN SQUARE)
void displayWAVDATA(short s[]){
	int dB[80]; //bar chart in decibels
	double rms[80];
	short *ptr = s;
	int i, j;

	for(i=0;i<80;i++){
		double sum=0; //accumulates the sum of squares
		for(j=0;j<200;j++){
			sum += *ptr * *ptr;
			ptr++;
		}
		rms[i]=sqrt(sum/200);
#ifdef DEBUG
		printf("rms[%d] = %f\n", i, rms[i]);
#endif
		dB[i]=20*log10(rms[i]);
	}
#ifndef DEBUG
	barChart(dB);
	int peaks = findPeaks(dB);
	setColors(WHITE, bg(BLACK));
	printf("\033[1;42H");
	printf("Peaks:%d\n", peaks);
#endif
}


void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("ChunkID", h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	showID("Format", h.Format);
	showID("SubChunk1ID", h.SubChunk1ID);
	printf("SubChunk1 size: %d\n", h.SubChunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Num. of channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits per sample: %d\n", h.BitsPerSample);
	showID("SubChunk2ID", h.SubChunk2ID);
	printf("SubChunk2 size: %d\n", h.SubChunk2Size);
#else
	setColors(WHITE, bg(RED));
	printf("\033[1;1H");
	printf("test.wav");
	setColors(YELLOW, bg(BLUE));
	printf("\033[1;9H");
	printf("Sample rate:%dHz>", h.SampleRate);
	setColors(CYAN, bg(MAGENTA));
	printf("\033[1;26H");
	printf("Duration:%.2fsec",(float) h.SubChunk2Size/h.ByteRate);
	setColors(RED, bg(BLACK));
#endif
}
