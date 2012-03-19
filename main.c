/*
cHistogram utility permit the ASCII histogram renderization on screen
from a terminal input.
Copyright (C) 2012  Lorenzo Pavesi

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/



#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#define LINE_MAX 1000

int    xRange=50;
int    yRange=50;


int    *list;   
int    *result;

double avg =0;
int    avgc=0;

int    range = 1000;


int main(int argc,char **argv){
   int c=0;

   if(argc>1){
       range = atoi(argv[1]) ;
   }
   if(argc>2){
       xRange = atoi(argv[2]) ;
   }
   if(argc>3){
       yRange = atoi(argv[3]) ;
   }

   list   = (int*)calloc(xRange,sizeof(int));
   result = (int*)calloc(xRange,sizeof(int));

   FILE * in = fdopen(0,"r");

   char line[LINE_MAX];
   while (fgets(line, LINE_MAX, in) != NULL) {
//    printf(line);
      collect(line);
      update();
   }

   free(list);
   free(result);
   return 0;
}

/*
 * Increment counters
 */
int collect(char * line){

  int  intValue = atoi(line) ;

  int i =  intValue/range;
  if(i<xRange) 
     ++list[i];
  else
     ++list[xRange-1];

  //update global avg  
  avg+=intValue;
  ++avgc;
  return 0;
}

/*
 * Draw on console
 */
int update(){
 int alpha  = 1;
 int teta=0;
 int i=0;
 while(i<xRange){
   teta=0;
   for(i=0; i<xRange;++i){
     int sigma=list[i]/(alpha);
     result[i]=sigma;
     teta+=result[i];
     if(sigma>yRange){
       alpha*=2;
       break;
       }
   }
 }

 teta/=xRange;

 for(i = yRange-1 ; i>= 0;--i){
   int j;

   for(j=0;j<xRange;++j ){
     if(result[j]>i)
        printf("▊ ");
     else
       if(teta==i)
         printf("..");
       else
         printf("  ");

   }
   if(i==yRange-1)  
     printf("\t %d-+inf  \t:\t%d\n",(i+1)*range, list[i]);
   else
     printf("\t %d-%d  \t:\t%d\n",(i+1)*range,i*range, list[i]);
 }
 
 for(i=0;i<xRange;++i)  
   printf("--");
 printf("> \n");
 printf("Avg : %f (%f / %f)\n",(avg/(avgc*1.0f)),avg,avgc*1.0f);
}

