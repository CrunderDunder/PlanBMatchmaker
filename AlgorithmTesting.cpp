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
#include "MatchmakerA.h"
#define M_PI 3.1415927

using namespace std;

MatchMakerA object;

int main()
{
	//Enter the number of criteria, students, and projects to contribute to analysis
	cout << "Enter the number of criteria you could like to see: ";
	cin >> object.criteria;
	cout << "Enter the number of students that are applying: ";
	cin >> object.SNum;
	cout << "Enter the number of projects available: ";
	cin >> object.PNum;

	//Initialize vectors and struct for calculations
	vector< vector<int> > Student, Project;
	vector <int> region(1), reqNum(object.criteria);
	vector < vector<float> > TotalS, TotalP, SArea, PArea;
	vector <float> SSum(object.SNum), PSum(object.PNum);
	vector <MatchMakerA::Storage> RegDiff;
	vector < vector<float> > Diff;
	struct Data;

	//Define the random generator to use the system clock
	srand(time(NULL)); 

	object.StudentSize(Student, object.SNum, object.criteria);
	object.ProjectSize(Project, object.PNum, object.criteria);

	object.RegionDivide(region, reqNum, object.criteria);

	object.TotalSize(TotalS, object.SNum, region);
	object.TotalSize(TotalP, object.PNum, region);

	object.RegionAnalyze(object.criteria, object.SNum, region, reqNum, Student, TotalS);
	object.RegionAnalyze(object.criteria, object.SNum, region, reqNum, Student, TotalP);

	object.RegDiffSize(RegDiff, object.SNum, object.PNum, region);

	object.RegionSum(object.SNum, object.PNum, region, TotalS, TotalP, RegDiff);
	object.RegionCompare(object.SNum, object.PNum, region, RegDiff);

	object.AreaSize(SArea, object.SNum, object.criteria);
	object.AreaSize(PArea, object.PNum, object.criteria);

	object.FindArea(object.SNum, object.criteria, Student, SArea);
	object.FindArea(object.PNum, object.criteria, Project, PArea);

	object.SumArea(object.SNum, object.criteria, SArea, SSum);

	cout << endl << "         General Analysis" << endl << endl;
	for (int x(0); x < object.SNum; x++)
	{
		cout << "Overall answer for Student " << x + 1 << ": " << SSum[x] << endl << endl;
	}

	object.SumArea(object.PNum, object.criteria, PArea, PSum);

	for (int x(0); x < object.PNum; x++)
	{
		cout << "Overall answer for Project " << x + 1 << ": " << PSum[x] << endl << endl;
	}

	object.DiffSize(Diff, SSum, PSum);

	object.Compare(object.PNum, object.SNum, Diff);

	//Hit Enter to exit the program
	cin.get();
	int finalword;
	cin >> finalword;
	
}