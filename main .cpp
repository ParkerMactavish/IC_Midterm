#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "community_detection.h"
using namespace std;
int main()
{
        ifstream myfile;
	// you need to change 'MidtermTest_23x23.txt' to the "FILENAME" which you want to read
        myfile.open("MidtermTest_23x23.txt", ios::in);
        int **A = NULL;
        //locale loc;

        int size = 0;
        if(myfile.is_open())
        {
                string line;
                getline(myfile, line);
                for (int i = 0; i < line.size(); i++)
                {
                        if( isdigit(line[i]) )
                                size++;
                }
                A = new int*[size];
                for (int i = 0; i < size; i++)
                        A[i] = new int[size];
                myfile.clear();
                myfile.seekg(0, ios::beg);

                unsigned int row = 0;
                while( getline(myfile,line) )
                {
                    string pch = line;
                    int col = 0;
                    for(unsigned i = 0; i < pch.length(); i++)
                        if( isdigit(pch[i]) )
                        {
                            A[row][col] = pch[i] - '0';
                            col +=1;
                        }
                    row += 1;
                }
                myfile.close();
        }
        const int NUM_NODES = *const_cast<int*>(&size);
        int* ans = community_detection(A,NUM_NODES);//do community detection, Please see community detection.h
        for(int i= 0; i < NUM_NODES; i++)
        {
                cout<< ans[i] << endl;
        }
		system("pause");
	return 0;
}
