#ifndef COMMUNITY_DETECTION_H
#define COMMUNITY_DETECTION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <stdlib.h>
int* community_detection(int **A, const int NUM_NODES)//A is a adjacency matrix,
{       
	//if exist edge (i,j), A[i][j]=1 otherwise A[i][j]=0
	int* ans = new int[NUM_NODES];
	time_t t = time(0);
	long int now = static_cast<long int> (t);
	srand (now);
    for(int i = 0; i < NUM_NODES; i++)//answer
	{
		ans[i] = 0; 
	}

	//please write your program from here----------------------------------------------



	//end-------------------------------------------------------------------------------
	return ans;

}

#endif
