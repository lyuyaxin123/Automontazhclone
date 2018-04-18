#include <iostream>
#include <cstdio>
#include <cmath>
#include "string.h"
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

int read_video()
{
	system("ffmpeg -i C:/rick.avi -vn -ar 44100 -ac 2 -ab 192K -f wav sound.wav");
	return 0;
}

unsigned long duration;

//Wav Header
struct wav_header_t
{
	char chunkID[4]; 
	uint32_t chunkSize; 
	char format[4]; 
	char subchunk1ID[4]; 
	unsigned long subchunk1Size; 
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
};

struct chunk_t
{
	char ID[4]; 
	uint32_t size;  
};

void WavReader(const char* fileName, const char* fileToSave)
{
	FILE *fin = fopen(fileName, "rb");

	//Read WAV header
	wav_header_t header;
	fread(&header, sizeof(header), 1, fin);

	//Print WAV header
	printf("WAV File Header read:\n");
	printf("File Type: %s\n", header.chunkID);
	printf("File Size: %ld\n", header.chunkSize);
	printf("WAV Marker: %s\n", header.format);
	printf("Format Name: %s\n", header.subchunk1ID);
	printf("Format Length: %ld\n", header.subchunk1Size);
	printf("Format Type: %hd\n", header.audioFormat);
	printf("Number of Channels: %hd\n", header.numChannels);
	printf("Sample Rate: %ld\n", header.sampleRate);
	printf("Sample Rate * Bits/Sample * Channels / 8: %ld\n", header.byteRate);
	printf("Bits per Sample * Channels / 8.1: %hd\n", header.blockAlign);
	printf("Bits per Sample: %hd\n", header.bitsPerSample);

	//Reading file
	chunk_t chunk;
	printf("id\t" "size\n");
	
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin);
		printf("%c%c%c%c\t" "%li\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		fseek(fin, chunk.size, SEEK_CUR);
	}

	int sample_size = header.bitsPerSample / 8;
	int samples_count = chunk.size * 8 / header.bitsPerSample;
	printf("Samples count = %i\n", samples_count);

	short int *value = new short int[samples_count];
	memset(value, 0, sizeof(short int) * samples_count);

	
	for (int i = 0; i < samples_count; i++)
	{
		fread(&value[i], sample_size, 1, fin);
	}

	//Write data into the file
	FILE *fout = fopen(fileToSave, "w");
	int j = 0;
	fprintf(fout, "silence - \n");
	for (int i = 0; i < samples_count; i += header.byteRate / 1000)
	{
		j += 1;
		if (j > floor(samples_count / header.byteRate) * 1000) { break; }
		
			if (value[i] == 128 && value[i + 1] == 128) {
				fprintf(fout, "%d msec:\n\n", j);
	    	}
		}
		fclose(fin);
		fclose(fout);
	}




int main()
{
read_video();
WavReader("C:/Users/Vladislav/trim_song.wav", "list1.dat");
return 0;
}



