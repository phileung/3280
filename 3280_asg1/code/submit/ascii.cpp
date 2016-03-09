/*

	CSCI 3280, Introduction to Multimedia Systems
	Spring 2015
	
	Assignment 01 Skeleton

	ascii.cpp
	
	1155032329
	Leung Kwan Ho
*/

#include "stdio.h"
#include "malloc.h"
#include "memory.h"
#include "math.h"
#include "bmp.h"		//	Simple .bmp library

#define MAX_SHADES 8


//
//	***** PUT ALL YOUR CODE INSIDE main() *****
//
int main( int argc, char** argv)
{

	char shades[MAX_SHADES] = {' ', '.', '+', '*', 'X', '%', '#', '@'};
	int		w, h;

	//	Read in image data ( command line: argv[1] )
	//
	Bitmap myBmp( argv[1] );
	
	w = myBmp.getWidth();
	h = myBmp.getHeight();

	//	Prepare output TXT file ( command line: argv[2] )
	//
	FILE *fout = fopen( argv[2], "w" );
	fprintf( fout, "%d %d\n", w, h );
	
	//
	//	Your code goes here ....
	//	
	//	Advice:
	//	Use Bitmap.getColor(x,y,R,G,B) for getting color of pixel at (x,y)
	//	Use fputc() to read character and "\n" to end your line.
	//
	
	unsigned char Rv,Gv,Bv,Grey;
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			myBmp.getColor(j,i,Rv,Gv,Bv);
			Grey = 0.299 * Rv + 0.587 * Gv + 0.114 * Bv;
			if(Grey<32){
				fputc(shades[0],fout);
			}
			else if(Grey<64){
				fputc(shades[1],fout);
			}
			else if(Grey<96){
				fputc(shades[2],fout);
			}
			else if(Grey<128){
				fputc(shades[3],fout);
			}
			else if(Grey<160){
				fputc(shades[4],fout);
			}
			else if(Grey<192){
				fputc(shades[5],fout);
			}
			else if(Grey<224){
				fputc(shades[6],fout);
			}
			else if(Grey<256){
				fputc(shades[7],fout);
			}			
		}
		fputc('\n',fout);
	}
	
	//	close ASCII file
	fclose(fout);

	return 0;

} 
