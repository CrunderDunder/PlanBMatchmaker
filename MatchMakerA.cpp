/*
MatchMakerA
Version 1.0
7/23/2014

This program was written for AFRL SATE 2014 by Andrew Urschel.
The algorithm was designed for the use of the  "Plan B" team
for Student-Project Matchmaking.
The algorithm assumes that the student/project responses are
used to create a 2D polygon spider-graph and calculates and
compares the areas using Euclidean geometry.

MatchMakerA Version 1.0 inlcudes randomly generated responses
for both students and project requirements and should be
replaced with actual data for implementation.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>
#include "MatchMakerA.h"
#define M_PI 3.1415927

using namespace std;


void MatchMakerA::FindArea(int index, int criteria, vector < vector<int> > Student, vector < vector<float> >& Area){

	int x = 0;
	for (int i(0); i < index; i++)
	{
		Area[i][0] = ((Student[i][criteria - 1] * Student[i][0])*sin((2 * M_PI) / criteria)) / 2;
		for (x = 0; x < (criteria-1); x++)
		{
			Area[i][x + 1] = ((Student[i][x] * Student[i][x + 1])*sin((2 * M_PI) / criteria)) / 2;
		}
	}
}


void MatchMakerA::SumArea(int index, int criteria, vector < vector<float> > Area, vector <float>& Sum){
	for (int i(0); i < index; i++)
	{
		for (int x = 0; x < criteria; x++)
		{
			Sum[i] += Area[i][x];
		}
	}
}


void MatchMakerA::Compare(int Pindex, int Sindex, vector < vector<float> > Diff){
	int studIndex = 0;
	int i = 0;
	cout << endl << "         General Assessment" << endl;
	for (int j(0); j < Pindex; j++)
	{
		cout << endl << "For Project " << j + 1 << ":" << endl << endl;
		float maxExp = Diff[i][j];
		for (int i(0); i < Sindex; i++)
		{
			if (Diff[i][j] > 0)
			{
				cout << "Student " << i + 1 << " meets the Criteria." << endl;
			}
			if (Diff[i][j] > maxExp)
			{
				maxExp = Diff[i][j];
			}
		} 
	}
	float maxExp = Diff[i][0];
	cout << endl << "         General Recommendation" << endl;
	for (int i(0); i < Sindex; i++)
	{
		if (Diff[i][0] > maxExp)
		{
			maxExp = Diff[i][0];
			studIndex = i;
		}
	} cout << endl << "Student " << studIndex + 1 << " is the most qualified overall." << endl;
}


void MatchMakerA::RegionDivide(vector <int>& region, vector <int>& reqNum, int criteria ){
	int skillNum, placeholder, sum = 0, code = 0, x;

	cout << "Enter the number of skill regions:";
	cin >> skillNum;

	region[0] = { skillNum };

	do
	{
		for (x = 0; x < skillNum; x++)
		{
			cout << "Enter the number of requirements in region " << (x + 1) << ":";
			cin >> placeholder;
			sum += placeholder;
			if (sum > criteria)
			{
				cout << "Not enough criteria. Please enter a number of requirements within the number of criteria." << endl << endl;
				sum = 0;
				break;
			}
			else if (sum == criteria)
			{
				for (x; x < (skillNum - 1); x++)
				{
					reqNum[x + 1] = 0;
					cout << "Enter the number of requirements in region " << (x + 2) << ": 0";
				}
				code = 1;
				break;
			}
			else
			{
				reqNum[x] = placeholder;
			}
		}
	} while (code == 0);
}


void MatchMakerA::RegionAnalyze(int criteria, int Num, vector <int> region, vector <int> reqNum, vector < vector<int> > Student, vector < vector<float> >& Totals){
	vector <float> Area(criteria);
	int q;
	for (int i(0); i < Num; i++)
	{
		int counter = 0, bin = 0, marker = 0, x = 0;
		for (q = 0; q < region[0]; q++)
		{
			marker += reqNum[q];
			for (counter; counter < marker; counter++)
			{
				if (counter == (criteria - 1))
				{
					Area[counter] = ((Student[i][counter] * Student[i][0])*sin((2 * M_PI) / criteria)) / 2;
				}
				else
				{
					Area[counter] = ((Student[i][counter] * Student[i][counter + 1])*sin((2 * M_PI) / criteria)) / 2;
				}
			}
			for (x; x < marker; x++)
			{
				Totals[i][bin] += Area[x];
			}
			//cout << Totals[i][bin] << "  ";
			if (q < region[0])
			{
				bin++;
			}
		} 
	}cout << endl;
}


void MatchMakerA::RegionSum(int SNum, int PNum, vector <int> region, vector < vector<float> > TotalS, vector < vector<float> > TotalP, vector<Storage>& RegDiff){
	int index = region[0];
	for (int j(0); j < SNum; j++)
	{
		cout << endl << "--------For Student " << j + 1 << "--------" << endl;
		for (int k(0); k < PNum; k++)
		{
			RegDiff[j].Proj[k] = k;
			cout << endl << "For Project " << k + 1 << ":" << endl;
			for (int i(0); i < index; i++)
			{
				RegDiff[j].Reg[i] = TotalS[j][i] - TotalP[k][i];
				cout << RegDiff[j].Reg[i] << "  ";
			} cout << endl;
		}
	}
}


void MatchMakerA::RegionCompare(int SNum, int PNum, vector <int> region, vector<Storage> RegDiff){
	int j = 0;
	cout << endl << endl << "         Assessment" << endl;
	for (int k(0); k < PNum; k++)
	{
		cout << endl << "--------For Project " << k + 1 << "--------" << endl;
		for (int i(0); i < region[0]; i++)
		{
			cout << endl << "For Region " << i + 1 << ":" << endl;
			float maxExp = RegDiff[0].Reg[i];
			for (int j(0); j < SNum; j++)
			{
				if (RegDiff[j].Reg[i] < 0)
				{
					cout << "Student " << j + 1 << " meets all of the Criteria." << endl;
				}
			}
			for (int j(0); j < (SNum-1); j++)
			{
				if (RegDiff[j + 1].Reg[i] > maxExp)
				{
					maxExp = RegDiff[j + 1].Reg[i];
				}
				else if (RegDiff[j + 1].Reg[i] == maxExp)
				{
					cout << "There are multiple students that are most qualified." << endl;
				}
			} 
		}
	}
	cout << endl << endl << "         Recommendations" << endl << endl;

	for (int i(0); i < region[0]; i++)
	{
		float maxExp = RegDiff[0].Reg[i];
		for (int j(0); j < (SNum - 1); j++)
		{
			if (RegDiff[j + 1].Reg[i] > maxExp)
			{
				maxExp = RegDiff[j + 1].Reg[i];
			}
		}
		for (int j(0); j < SNum; j++)
		{
			if (RegDiff[j].Reg[i] == maxExp)
			{
				cout << "Student " << j + 1 << " is the most qualified in Region " << i + 1 << endl;
			}
		}
	} cout << endl;
}





void MatchMakerA::StudentSize(vector < vector<int> >& Student, int SNum, int criteria){
	for (int i(0); i < SNum; i++) 
	{
		vector<int> row; // Create an empty row
		for (int j(0); j < criteria; j++) 
		{
			row.push_back(i * j); // Add an element (column) to the row
		}
		Student.push_back(row); // Add the row to the main vector
	}
	for (int i(0); i < SNum; i++)
	{
		cout << "Student number: " << i + 1 << endl;
		for (int j(0); j < criteria; j++)
		{
			Student[i][j] = rand() %11;
			cout << Student[i][j] << "  ";
		} cout << endl << endl;
	}
}


void MatchMakerA::ProjectSize(vector< vector<int> >& Project, int PNum, int criteria){
	for (int i(0); i < PNum; i++)
	{
		vector<int> row; 
		for (int j(0); j < criteria; j++)
		{
			row.push_back(i * j); 
		}
		Project.push_back(row);
	}
	for (int i(0); i < PNum; i++)
	{
		cout << "Project number: " << i + 1 << endl;
		for (int j(0); j < criteria; j++)
		{
			Project[i][j] = rand() % 11;
			cout << Project[i][j] << "  ";
		} cout << endl << endl;
	}
}


void MatchMakerA::TotalSize(vector < vector<float> >& Total, int SNum, vector <int> region){
	for (int i(0); i < SNum; i++)
	{
		vector<float> row;
		for (int j(0); j < region[0]; j++)
		{
			row.push_back(i * j);
		}
		Total.push_back(row);
	}
}


void MatchMakerA::RegDiffSize(vector <MatchMakerA::Storage>& RegDiff, int SNum, int PNum, vector <int> region){
	RegDiff.push_back(MatchMakerA::Storage());
	RegDiff.resize(SNum);
	for (int x(0); x < SNum; x++)
	{
		RegDiff[x].Proj.resize(PNum);
		RegDiff[x].Reg.resize(region[0]);
	}
}


void MatchMakerA::AreaSize(vector < vector<float> >& Area, int SNum, int criteria){
	for (int i(0); i < SNum; i++)
	{
		vector<float> row;
		for (int j(0); j < criteria; j++)
		{
			row.push_back(i * j);
		}
		Area.push_back(row);
	}
}


void MatchMakerA::DiffSize(vector < vector<float> >& Diff, vector<float> SSum, vector<float> PSum){
	for (int i(0); i < SNum; i++)
	{
		vector<float> row;
		for (int j(0); j < PNum; j++)
		{
			row.push_back(i * j);
		}
		Diff.push_back(row);
	}
	for (int i(0); i < SNum; i++)
	{
		//cout << "Project number: " << i + 1 << endl;
		for (int j(0); j < PNum; j++)
		{
			Diff[i][j] = SSum[i] - PSum[j];
		} 
	}
}
