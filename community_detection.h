#ifndef COMMUNITY_DETECTION_H
#define COMMUNITY_DETECTION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <stdlib.h>

using namespace std;

int test_times = 10000;

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
	vector<vector<vector<int>>> possible_group_cnt(NUM_NODES, vector<vector<int>>(test_times, vector<int>(2, -1)));
	vector<vector<int>>tmp_possible_group(2, vector<int>());
	vector<vector<int>>sorting_group(2, vector<int>());
	vector<int>group(NUM_NODES);
	vector<int>group_serial_num(0);
	bool complete_flag;
	int rand_result;

	for (int col_index = 0; col_index < NUM_NODES; col_index++) {
		possible_group_cnt[col_index][0][0] = col_index;
		possible_group_cnt[col_index][1][0] = 1;
	}

	for (int times = 1; times < test_times; times++) {
		for (int col_index = 0; col_index < NUM_NODES; col_index++) {
			while (tmp_possible_group[0].size()) {
				tmp_possible_group[0].pop_back();
				tmp_possible_group[1].pop_back();
			}
			for (int row_index = 0; row_index < NUM_NODES; row_index++) {
				//cout << "row" << row_index << endl;
				if (A[col_index][row_index] == 1 && row_index != col_index) {
					complete_flag = false;
					rand_result = possible_group_cnt[row_index][rand() % times][0];
					//cout << row_index<<endl<<tmp_possible_group[0].size()<<endl;
					for (int tmp_index = 0; tmp_index < tmp_possible_group[0].size() && complete_flag == false; tmp_index++) {
						if (tmp_possible_group[0][tmp_index] == rand_result) {
							//cout << tmp_possible_group[1][tmp_index] << endl;
							tmp_possible_group[1][tmp_index]++;
							complete_flag = true;
						}
					}
					if (complete_flag == false) {
						tmp_possible_group[0].push_back(rand_result);
						//cout << "tpg00"<<tmp_possible_group[0][0] << endl;
						tmp_possible_group[1].push_back(1);
						//cout << tmp_possible_group[1][0]<<endl;
					}
				}
			}
			//cout << 1;
			for (int sorting_index_i = 1; sorting_index_i < tmp_possible_group[1].size(); sorting_index_i++) {
				for (int sorting_index_j = sorting_index_i - 1; sorting_index_j >= 0; sorting_index_j--) {
					if (tmp_possible_group[1][sorting_index_j + 1] > tmp_possible_group[1][sorting_index_j]) {
						int swap_tmp = tmp_possible_group[0][sorting_index_j];
						tmp_possible_group[0][sorting_index_j] = tmp_possible_group[0][sorting_index_j + 1];
						tmp_possible_group[0][sorting_index_j + 1] = swap_tmp;
						swap_tmp = tmp_possible_group[1][sorting_index_j];
						tmp_possible_group[1][sorting_index_j] = tmp_possible_group[1][sorting_index_j + 1];
						tmp_possible_group[1][sorting_index_j + 1] = swap_tmp;
					}
				}
			}
			//cout << 1;
			int greatest_cnt=tmp_possible_group[1][0], greatest_cnt_index = 1;
			for (; greatest_cnt_index<tmp_possible_group[1].size()&&tmp_possible_group[1][greatest_cnt_index] == greatest_cnt; greatest_cnt_index++);
			possible_group_cnt[col_index][times][0] = tmp_possible_group[0][rand() % greatest_cnt_index];
			possible_group_cnt[col_index][times][1] = 1;
		}
	}

	for (int col_index = 0; col_index < NUM_NODES; col_index++) {
		while(sorting_group[0].size())sorting_group[0].pop_back();
		while (sorting_group[1].size())sorting_group[1].pop_back();
		for (int times = 0; times < test_times; times++) {
			complete_flag = false;
			for (int tmp_index = 0; tmp_index < sorting_group[0].size(); tmp_index++) {
				if (sorting_group[0][tmp_index] == possible_group_cnt[col_index][times][0]) {
					sorting_group[1][tmp_index]++;
					complete_flag = true;
					int sorting_index = tmp_index - 1;
					for (; sorting_index >= 0 && sorting_group[1][tmp_index] >= sorting_group[1][sorting_index]; sorting_index--);
					int swap_tmp = sorting_group[0][tmp_index];
					sorting_group[0][tmp_index] = sorting_group[0][sorting_index + 1];
					sorting_group[0][sorting_index + 1] = swap_tmp;
					swap_tmp = sorting_group[1][tmp_index];
					sorting_group[1][tmp_index] = sorting_group[1][sorting_index + 1];
					sorting_group[1][sorting_index + 1] = swap_tmp;
				}
			}
			if (complete_flag == false) {
				sorting_group[0].push_back(possible_group_cnt[col_index][times][0]);
				sorting_group[1].push_back(1);
			}
		}
		int sorting_tmp = sorting_group[1][0], sorting_index=1;
		for (; sorting_group[1][sorting_index] == sorting_tmp; sorting_index++);
		group[col_index] = sorting_group[0][rand() % sorting_index];
	}
	//for testing
	//for (int i = 0; i < NUM_NODES; i++) cout << i<<" "<<group[i]<<endl;
	for (int node_index = 0; node_index < NUM_NODES; node_index++) {
		int group_index = 0;
		//cout << group_serial_num.size();
		for (; group_index < group_serial_num.size() && group[node_index] != group_serial_num[group_index]; group_index++);
		if (group_index >= group_serial_num.size()) {
			ans[node_index] = group_serial_num.size()+1;
			group_serial_num.push_back(group[node_index]);
		}
		else {
			ans[node_index] = group_index+1;
		}
	}

	//end-------------------------------------------------------------------------------
	return ans;

}

#endif
