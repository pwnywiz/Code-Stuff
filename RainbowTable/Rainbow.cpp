#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include "blake.h"
#include <stdio.h>
#include <stdlib.h>  

using namespace std;

#define BLOCK256 32
#define RAIN_TABLES 10000
#define CHAINS	10000

string validLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";

void blake_hash(const char* input , uint8_t out[32])
{

	state256 S;
  blake256_init( &S );

  int i = 0;
  while ( i < 6 ) {
  	blake256_update( &S, (uint8_t *)input , input[i] );
  	i++;
  }

  blake256_final( &S, out );
}

string blake_reduce(uint8_t hashed[32])
{
	string reduced = "";

  int counter = 0;
  int i = 0;
  while ( i < 32 && counter < 6) {
    if ( validLetters.find( hashed[i] ) != string::npos ) {
      reduced += hashed[i];
      counter++;
    }
    i++;
  }

	return reduced;
}


int main( int argc, char **argv )
{
 
  ofstream file;
  file.open("rainfile");


  srand(time(NULL));

  string reduced = "";

  for (int i = 0; i < RAIN_TABLES; ++i)
  {
    if (system("CLS")) system("clear");
    printf("%d/%d\n",i,RAIN_TABLES) ;
    // TODO generate random first string
  	// Note search maybe that we have not already used this as a first string
 	  reduced = "";
    reduced += validLetters.at(rand() % 64 );
 	  reduced += validLetters.at(rand() % 64 );
 	  reduced += validLetters.at(rand() % 64 );
 	  reduced += validLetters.at(rand() % 64 );
 	  reduced += validLetters.at(rand() % 64 );
 	  reduced += validLetters.at(rand() % 64 );

 	  file << reduced << ":";
 	  //cout << reduced << ":";
    

    for (int j = 0; j < CHAINS; ++j)
 	  {
       //cout << j << endl;
       uint8_t out[32];
       const char* creduced = reduced.c_str();
 	  	 blake_hash(creduced,out);

 	  	 reduced = blake_reduce(out);


       if ( j == CHAINS - 1) {

          // here we have the last hash of the chains 
         file << out << endl;
         //cout << out << endl;
       }
 	  }

  }


  file.close();
  return 0;
}