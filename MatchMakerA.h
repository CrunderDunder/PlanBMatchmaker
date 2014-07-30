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

#ifndef MatchMakerA_H
#define MatchMakerA_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>
#define M_PI 3.1415927

using namespace std;

class MatchMakerA
{
	private:

	public:
		int criteria, SNum, PNum;

		struct Storage
		{
			vector<float> Proj;
			vector<float> Reg;
		};

		struct Data;
	//General Calculating Functions
		//Finds the area within the polygon created by each response
		void FindArea(int index, int criteria, vector < vector<int> > Student, vector < vector<float> >& Area);

		//Calculates the total area bounded by the polygon
		void SumArea(int index, int criteria, vector < vector<float> > Area, vector <float>& Sum);

		//Compares the students overall, assesses their qualification, and makes a recommendation
		void Compare(int Pindex, int Sindex, vector < vector<float> > Diff);


	//Region Related Functions
		//Divides criteria into a number of distinct regions
		void RegionDivide(vector <int>& region, vector <int>& reqNum, int criteria );

		//Analyze responses in each region
		void RegionAnalyze(int criteria, int Num, vector <int> region, vector <int> reqNum, vector < vector<int> > Student, vector < vector<float> >& Totals);

		//Calculate region totals and compare results
		void RegionSum(int SNum, int PNum, vector <int> region, vector < vector<float> > TotalS, vector < vector<float> > TotalP, vector<Storage>& RegDiff);

		void RegionCompare(int SNum, int PNum, vector <int> region, vector<Storage> RegDiff);


	//Vector Sizing Functions
		//Set the appropriate array size for student and project information
		void StudentSize(vector < vector<int> >& Student, int SNum, int criteria);

		void ProjectSize(vector< vector<int> >& Project, int SNum, int criteria);

		//Sets the appropriate array size for student/project totals
		void TotalSize(vector < vector<float> >& Total, int SNum, vector <int> region);

		//Sets the size of the array for the region differences
		void RegDiffSize(vector <Storage>& RegDiff, int SNum, int PNum, vector <int> region);

		//Sets the size of arrays to store total student/project polygon area
		void AreaSize(vector < vector<float> >& Area, int SNum, int criteria);

		//Sets the size of the array containing the differences between student/project input
		void DiffSize(vector < vector<float> >& Diff, vector<float> SSum, vector<float> PSum);


};

#endif