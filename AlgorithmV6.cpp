/*

This program was written for AFRL SATE 2014 by Andrew Urschel.
The algorithm was designed for the use of the  "Plan B" team 
for Student-Project Matchmaking. 
The algorithm assumes that the student/project responses are 
used to create a 2D polygon and calculates and compares the 
areas using Euclidean geometry.

Algorithm V6 implements vector replacements for arrays to 
enable the possibility of scalability.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>
#define M_PI 3.1415927
using namespace std;

struct Storage
{
	vector<float> Proj;
	vector<float> Reg;
};

void FindArea(int index, int criteria, vector < vector<int> > Student, vector < vector<float> >& Area)
{

	int x = 0;
	for (int i(0); i < index; i++)
	{
		Area[i][0] = ((Student[i][criteria - 1] * Student[i][x])*sin((2 * M_PI) / criteria)) / 2;
		for (x = 0; x < (criteria-1); x++)
		{
			Area[i][x + 1] = ((Student[i][x] * Student[i][x + 1])*sin((2 * M_PI) / criteria)) / 2;
		}
	}
}

void SumArea(int index, int criteria, vector < vector<float> > Area, vector <float>& Sum)
{
	for (int i(0); i < index; i++)
	{
		for (int x = 0; x < criteria; x++)
		{
			Sum[i] += Area[i][x];
		}
	}

}

void Compare(int Pindex, int Sindex, vector < vector<float> > Diff)
{
	int i = 0;
	for (int j(0); j < Pindex; j++)
	{
		cout << "For Project " << j + 1 << ":" << endl << endl;
		float maxExp = Diff[i][j];
		for (int i(0); i < Sindex; i++)
		{
			if (Diff[i][j] < 0)
			{
				cout << "Student " << i + 1 << " does not meet all of the Criteria." << endl;
			}
			if (Diff[i][j] > maxExp)
			{
				maxExp = Diff[i][j];
			}
		} cout << "Student " << i + 1 << " is the most qualified overall." << endl << endl;
	}
}

//-----------------------------------------

void RegionDivide(vector <int>& region, vector <int>& reqNum )
{
	int skillNum;

	cout << "Enter the number of skill regions:";
	cin >> skillNum;

	region[0] = { skillNum };

	for (int x = 0; x < skillNum; x++)
	{
		cout << "Enter the number of requirements in region " << (x + 1) << ":";
		cin >> reqNum[x];
	} cout << region[0] << "  " << reqNum[skillNum-1];
}

void RegionAnalyze(int criteria, int Num, vector <int> region, vector <int> reqNum, vector < vector<int> > Student, vector < vector<float> >& Totals)
{
	vector <float> Area(criteria);
	float RegionSum = 0;
	int counter = 0;
	int bin = 0;
	int marker = 0;
	int newstart = 0;
	for (int i(0); i < Num; i++)
	{
		for (int q(0); q < region[0]; q++)
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
			for (int x = newstart; x < counter; x++)
			{
				RegionSum += Area[x];
			} newstart = counter;
			Totals[i][bin] = RegionSum;
			cout << Totals[i][bin] << "  ";
			bin++;
			RegionSum = 0;
		} cout << endl;
	}
}

void RegionSum(int SNum, int PNum, vector <int> region, vector < vector<float> > TotalS, vector < vector<float> > TotalP, vector<Storage>& RegDiff)
{
	int index = region[0];
	for (int j(0); j < SNum; j++)
	{
		for (int k(0); k < PNum; k++)
		{
			RegDiff[j].Proj[k] = k;
			cout << "For Project " << k + 1 << ":" << endl;
			for (int i(0); i < index; i++)
			{
				RegDiff[j].Reg[i] = TotalS[j][i] - TotalP[k][i];
				cout << RegDiff[j].Reg[i] << "  ";
			} cout << endl;
		}
	}
}

void RegionCompare(int SNum, int PNum, vector <int> region, vector<Storage> RegDiff)
{
	int j = 0;
	for (int k(0); k < PNum; k++)
	{
		cout << "For Project " << k + 1 << ":" << endl << endl;
		for (int i(0); i < region[0]; i++)
		{
			cout << "For Region " << i + 1 << ":" << endl << endl;
			float maxExp = RegDiff[j].Reg[i];
			for (int j(0); j < SNum; j++)
			{
				if (RegDiff[j].Reg[i] < 0)
				{
					cout << "Student " << j + 1 << " does not meet all of the Criteria." << endl;
				}
				if (RegDiff[j].Reg[i] > maxExp)
				{
					maxExp = RegDiff[j].Reg[i];
				}
				else if (RegDiff[j].Reg[i] == maxExp)
				{
					cout << "There are multiple students that are most qualified." << endl;
				}
			} cout << "Student " << j + 1 << " is the most qualified in Region " << i + 1 << endl << endl;
		}
	}
}

//-----------------------------------------

int main (void) 
{
	srand(time(NULL)); //Define the random generator to use the system clock

	//Define the number of criteria, students, and projects
	int criteria, SNum, PNum;
	cout << "Enter the number of criteria you could like to see: ";
	cin >> criteria;
	cout << "Enter the number of students that are applying: ";
	cin >> SNum;
	cout << "Enter the number of projects available: ";
	cin >> PNum;

	//--------------------------------------------
	//Create a vector for generating student responses
	vector< vector<int> > Student;

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

	//--------------------------------------------
	//Create a vector for generating Project requirements
	vector< vector<int> > Project;

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
	
	//Divide the Graphed data into custom regions
	vector <int> region(1);
	vector <int> reqNum(criteria);
	RegionDivide(region, reqNum);
	
	//cout << reqNum[0];
	//cout << region[0];
	//Create an array for both student answers(radius) and radians(theta)
	
	//Analyze the student data for each region generated
	/*vector < vector<float> > TotalS;

	for (int i(0); i < SNum; i++)
	{
		vector<float> row;
		for (int j(0); j < region[0]; j++)
		{
			row.push_back(i * j);
		}
		TotalS.push_back(row);
	}
	RegionAnalyze(criteria, SNum, region, reqNum, Student, TotalS);
	
	//-----------------

	vector < vector<float> > TotalP;
	for (int i(0); i < PNum; i++)
	{
		vector<float> row;
		for (int j(0); j < region[0]; j++)
		{
			row.push_back(i * j);
		}
		TotalP.push_back(row);
	}
	RegionAnalyze(criteria, PNum, region, reqNum, Project, TotalP);*/

	//Compute the difference between response and criteria for each student
	/*struct Data;

	vector <Storage> RegDiff;
	RegDiff.push_back(Storage());
	RegDiff.resize(SNum);
	RegDiff[0].Proj.push_back(PNum);
	RegDiff[0].Reg.push_back(region[0]);
	
	vector < vector < vector<float> > > RegDiff;

	RegDiff.resize(SNum);
	for (int i(0); i < SNum; i++)
	{
		RegDiff[i].resize(PNum);
		for (int j(0); j < PNum; j++)
		{
			RegDiff[i][j].resize(region[0]);
		}
	}

	RegionSum(SNum, PNum, region, TotalS, TotalP, RegDiff);

	/*RegionCompare(SNum, PNum, region, RegDiff);

	//Create arrays for the product of the area calculations*/
	/*vector < vector<float> > SArea;

	for (int i(0); i < SNum; i++)
	{
		vector<float> row;
		for (int j(0); j < criteria; j++)
		{
			row.push_back(i * j);
		}
		SArea.push_back(row);
	}
	FindArea(SNum, criteria, Student, SArea);
	
	vector < vector<float> > PArea;

	for (int i(0); i < PNum; i++)
	{
		vector<float> row;
		for (int j(0); j < criteria; j++)
		{
			row.push_back(i * j);
		}
		PArea.push_back(row);
	}
	FindArea(PNum, criteria, Project, PArea);

	//Compute the total area for each profile
	vector <float> SSum(SNum);
	SumArea(SNum, criteria, SArea, SSum);

	for (int x(0); x < SNum; x++)
	{
		cout << "Overall answer for Student " << x + 1 << ": " << SSum[x] << endl << endl;
	}

	vector <float> PSum(SNum);
	SumArea(PNum, criteria, PArea, PSum);
	for (int x(0); x < PNum; x++)
	{
		cout << "Overall answer for Project " << x + 1 << ": " << PSum[x] << endl << endl;
	}

	//Find the difference for each profile from the project
	vector < vector<float> > Diff;

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

	//Compare2(DiffArea1, DiffArea2);
		Compare(PNum, SNum, Diff);*/

	//Hit Enter to exit the program
	cin.get();
	int finalword;
	cin >> finalword;
	
}