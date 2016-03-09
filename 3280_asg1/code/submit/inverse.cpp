/*

	CSCI 3280, Introduction to Multimedia Systems
	Spring 2016
	
	Assignment 01 Skeleton

	inverse.cpp
	
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
	int 	w, h;
	
	//	Open ASCII Art file ( command line: argv[1] )
	//
	FILE *fin = fopen( argv[1], "r" );
	fscanf( fin, "%d %d", &w, &h );
		
	//	Create a Bitmap object accordingly
	Bitmap myBmp( w, h);

	//
	//	Your code goes here ....
	//
	//	Advice:
	//	Use Bitmap.setColor(x,y,R,G,B) for setting color of pixel at (x,y)
	//	Use fgetc()
	//
	char buffer;
	buffer = fgetc(fin);//the first \n
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			buffer = fgetc(fin);
			for(int s=0;s<MAX_SHADES;s++){
				if(buffer==shades[s]){
					double rate = (255/MAX_SHADES)*(s);
					myBmp.setColor(j,i,rate,rate,rate);
					break;
				}
				else if(buffer=='\n'){
					myBmp.setColor(j,i,255,0,0);
					//printf("heee");
				}
					
			}
			
			
		}
		buffer = fgetc(fin);// \n in ever line
	}

	
	//	Save Bitmap file ( command line: argv[2] )	
	myBmp.save( argv[2] );
	fclose(fin);
		
	return 0;

} 
