#include <stdio.h>
#include <math.h>
#include "sound.h"

void showID(char *idname, char 	*id){
	int i;
	printf("%s: ", idname);
	for(i=0;i<4;i++)
		printf("%c", id[i]);
	puts("");
}
//function below gets one second of samples and calculates
//80 pieces of decibel value, one piece per 200 samples by RMS formula (ROOT MEAN SQUARE)
void displayWAVDATA(short s[]){
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
		printf("rms[%d] = %f\n", i, rms[i]);
	}
}

void displayWAVHDR(struct WAVHDR h){
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
}
