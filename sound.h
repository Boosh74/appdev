//constants
//#define DEBUG
#define RATE 16000
#define PI 3.14159
#define DUR 1
#define RCMD "arecord -r16000 -c1 -f S16_LE -d1 -q test.wav"
//data structures
struct WAVHDR{
	char ChunkID[4];			//must be "RIFF"
	int ChunkSize;
	char Format[4];			 	//must be "WAVE"

	char SubChunk1ID[4]; 	//must be "fmt "
	int SubChunk1Size; 		//should be 16
	short AudioFormat; 		//should be 1
	short NumChannels; 		//should be 1
	int SampleRate; 			//we will use 16000
	int ByteRate; 					//calculated by SR, NS, B/S
	short BlockAlign; 			//calculated
	short BitsPerSample;		//must be 16

	char SubChunk2ID[4]; 	//must be "data"
	int SubChunk2Size;		//calculated
};
//functions
void displayWAVHDR(struct WAVHDR);
void displayWAVDATA(short []);
void showID(char *, char *);
void testTone(int ch, int fL, int fR, float dur);
