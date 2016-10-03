/*
This program is intended to simulate random-walk.
First uploaded at : ideone.com/SKngfg
Code written by M A H Rahat.
Contact : fountaein<no-spam>yandex.com
Github : github.com/MAHRahat
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//Global variables
int 
	stepsize = 1,   //step-size, size of each step
	fr = 1,   //set to non-zero if you are interested in first-return simulation
	zr = 1;   //set to non-zero for zero-return calculations
	
double * stepfr, * myarray;

FILE * mylog, * myop;

//RANDOM-WALK GENERATING FUNCTION
void randomwalkgenerator (int steptot) 
{
	int i=0;
	int pos = 0;
	int frdone = 0;
	//printf("%d\n",pos);
	for (i=0; i<steptot; i++ )
	{
		if (rand()%2)
			pos += stepsize;
		else
			pos -= stepsize;
		if ( (fr) && (!frdone) && (!pos) && (i) )
			frdone = 1, stepfr[i/2]++ ;
		//printf("%d\n",pos);
	}
	myarray[(steptot+pos)/2]++;
//	return pos;
}



//MAIN
int main () 
{
	//Varible declarations
	int id = time(NULL);
	srand(id);
	int i=0;
	int steptot=0;
	int iteration, iterationmax=100000;
	char mystring[100];
	//Starting ...
	printf("...............................\n");
	printf("Random-walk simulator starts!\n");
	sprintf(mystring,"RWinC_%d_log",id);
	mylog = fopen(mystring,"w");
	fprintf(mylog,"...............................\n");
	fprintf(mylog,"%d : Random-walk simulator starts!\n",id);
	fclose(mylog);
	//Main processes
	for ( steptot=1000; steptot<=3000; steptot+=1000)
	{
		sprintf(mystring,"RWinC_%d_log",id);
		mylog = fopen(mystring,"a");
		printf("...............................\n");
		printf("Simulating random-walk for %d steps\n",steptot);
		fprintf(mylog,"...............................\n");
		fprintf(mylog,"%d : Simulating random-walk for %d steps\n",time(NULL),steptot);
		if (zr)
			steptot += steptot%2;
		myarray = malloc((steptot+1)*sizeof(double));
		memset (myarray, 0, (steptot+1)*sizeof(double));
		if (fr) 
		{
			stepfr = (double *) malloc((steptot/2)*sizeof(double));
			memset (stepfr, 0, (steptot/2)*sizeof(double));
		}
		//generate walk
		printf("... Generating positions ...\n");
		fprintf(mylog,"%d : Generating positions ...\n",time(NULL));
		for ( iteration=1; iteration<=iterationmax; iteration++)
		{
			randomwalkgenerator(steptot);
		}
		//output position-data
		sprintf(mystring,"RWinC_%d_data_%dsteps",id,steptot);
		myop = fopen(mystring,"w");
		printf("... Writing %s ...\n",mystring);
		fprintf(mylog,"%d : Writing output file %s ...\n",time(NULL),mystring);
		for ( i=0; i<steptot*2+1; i+=2 )
		{
			fprintf(myop,"%d\t%.0lf\t%lf\n",i-steptot,myarray[i/2],myarray[i/2]/iterationmax);
		}
		fclose(myop);
		//first-return data
		if (fr) 
		{
			sprintf(mystring,"RWinC_%d_first-return-data_%dsteps",id,steptot);
			myop = fopen(mystring,"w");
			printf("... Writing %s ...\n",mystring);
			fprintf(mylog,"%d : Writing output file for first-return - %s ...\n",time(NULL),mystring);
			for ( i=1; i<=steptot; i+=2 )
			{
				fprintf(myop,"%d\t%.0lf\t%lf\n",i+1,stepfr[i/2],stepfr[i/2]/iterationmax);
			}
			fclose(myop);
		}
		if (zr)
		{
			printf("Zero-returned for %.0lf times\n",myarray[steptot/2]);
			fprintf(mylog,"%d : Zero-returned for %.0lf times\n",time(NULL),myarray[steptot/2]);
		}
		if (fr) 
			free(stepfr);
		free(myarray);
		fclose(mylog);
	}
	//Ending ...
	sprintf(mystring,"RWinC_%d_log",id);
	mylog = fopen(mystring,"a");
	fprintf(mylog,"...............................\n");
	fprintf(mylog,"%d : Random-walk simulator ends!\n",time(NULL));
	fprintf(mylog,"...............................\n");
	fclose(mylog);
	printf("...............................\n");
	printf("Random-walk simulator ends!\n");
	printf("(log saved to '%s')\n",mystring);
	printf("...............................\n");
	
	return 0;
}