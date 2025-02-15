#include"MapGen.h"
#include<vector>
#include<random>
#include<iostream>
#include<Windows.h>
using namespace std;
//A global variable
int mapcount = 0;
//Display the map

void display(vector < vector<double>>a) 
{
	HANDLE hcolor;
	hcolor = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
		{
			if (a[i][j] < 0.5)
			{
				SetConsoleTextAttribute(hcolor, 1);
				cout << "0";
			}
			else if (a[i][j] < 0.53)
			{
				SetConsoleTextAttribute(hcolor, 14);
				cout << "1";
			}
			else if (a[i][j] < 0.83)
			{
				SetConsoleTextAttribute(hcolor, 2);
				cout << "1";
			}
			else if (a[i][j] < 0.92)
			{
				SetConsoleTextAttribute(hcolor, 8);
				cout << "2";
			}
			else
			{
				SetConsoleTextAttribute(hcolor, 7);
				cout << "3";
			}
		}
		cout << endl;
	}
}


//Generate the map using the diamond square algorithm
vector<vector<double>> gen_map(int n)
{
	
	//Random engines and distributions
	mt19937 eng(time(NULL)+mapcount);

	uniform_real_distribution<double> distart(0.01, 1);
	uniform_real_distribution<double> dis2(-0.5, 0.5);
	//Max width and height
	int max = pow(2, n);
	int	k = max;
	//The 2D Terrain Vector
	vector<vector<double>> terr;
	terr.resize(max+1, vector<double>(max+1));

	//Setting initial points
	terr[0][0] = distart(eng);
	terr[0][max] = distart(eng);
	terr[max][0] = distart(eng);
	terr[max][max] = distart(eng);
	double div = 1;//This is to add some more randomness 
	while (k > 1)
	{
		
		for (int i = 0; i <= (max - k); i += k)
		{
			for (int j = 0; j <= (max - k); j += k)
			{
				//The values for the 4 points
				double v1, v2, v3, v4;
				v1 = terr[i][j];
				v2 = terr[i][j + k];
				v3 = terr[i + k][j];
				v4 = terr[i + k][j + k];
				
				
				//Firstly the square
				double mid = ((v1 + v2 + v3 + v4) / 4.0)+ dis2(eng)/div;
				terr[(((2 * i) + k) / 2)][(((2 * j) + k) / 2)] = mid;
				double v5;
				//Now the diamond

				//up
				if (j == 0)
				{
					terr[i][(((2 * j) + k) / 2)] = ((v1 + v2 + mid) / 3.0) + dis2(eng) / div;
				}
				else 
				{
					v5 = terr[i][j - k / 2];
					terr[i][(j + k/2)] = ((v1 + v2+v5 + mid) / 4.0) + dis2(eng) / div;
				}
				//down
				if (j == max - k)
				{
					terr[i + k][j + k / 2] = ((v3 + v4 + mid) / 3.0) + +dis2(eng) / div;
				}
				else 
				{
					v5 = v5 = terr[i][j + k / 2];
					terr[i + k][j + k / 2] = ((v3 + v4 + v5 + mid) / 4.0) + +dis2(eng) / div;
				}
				//Left
				if (i == 0)
				{
					terr[i + k / 2][j] = ((v1 + v3 + mid) / 3.0) + dis2(eng) / div;
				}
				else 
				{
					v5 = terr[i-k/2][j ];
					terr[i + k / 2][j] = ((v1 + v3 + v5 + mid) / 4.0) + dis2(eng) / div;
				}
				//Right
				if (i == max - k)
				{
					terr[i + k / 2][j + k] = ((v2 + v4 + mid) / 3.0) + dis2(eng) / div;
				}
				else 
				{
					v5 = terr[i + k / 2][j];
					terr[i + k / 2][j + k] = ((v2 + v4 + v5 + mid) / 4.0) + dis2(eng) / div;
				}
				

				/*/Midpoint Displacement
				double v5 = (v1 + v2) / 2 + dis2(eng)/div;
				terr[i][j + k / 2] = v5;

				double v6 = (v1 + v3) / 2 + dis2(eng) / div;
				terr[i+k/2][j] = v6;

				double v7 = (v3 + v4) / 2 + dis2(eng) / div;
				terr[i + k][j+k/2] = v7;

				double v8 = (v2 + v4) / 2 + dis2(eng) / div;
				terr[i + k/2][j + k] = v8;

				terr[i + k / 2][j + k / 2] = (v5 + v6 + v7 + v8) / 4.0 + dis2(eng) / (2 * div);
				*/
			}
		}
		k /= 2;
		div *= 2;
		
	}
	
	mapcount++;
	return terr;
}

//Merging two maps together
std::vector<std::vector<double>> mergemap(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, int overlap, int code)
{
	
	vector<vector<double>> newmap;

	vector<vector<double>> interim;

	for (int i = 0; i < overlap; i++) 
	{
		vector<double>temp;
		for (int j = 0; j < a[i].size(); j++)
		{
			double val = (((double)overlap - (double)i) * a[a.size()-overlap+i][j] + (double)i * b[i][j]) / (double)overlap;
			temp.push_back(val);
		}
		interim.push_back(temp);
	}
	for (int i = 0; i < a.size() - overlap; i++) 
	{
		newmap.push_back(a[i]);
		
	}
	for (int i = 0; i < interim.size(); i++)
	{
		newmap.push_back(interim[i]);
	}
	for (int i = overlap; i < b.size(); i++)
	{
		newmap.push_back(b[i]);
	}
	return newmap;
}


//Generate a one dimension map
vector<double> genoned(int n)
{
	vector<double> oned;
	mt19937 eng(time(NULL));
	uniform_real_distribution<double> dis(0, 300);
	double max, min;
	oned.push_back(dis(eng));
	oned.push_back(dis(eng));
	max = *max_element(oned.begin(),oned.end());
	min = *min_element(oned.begin(), oned.end());
	for (int j = 0; j < n; j++) 
	{
		
		for (int i = 1; i < oned.size(); i+=2)
		{
			double val = ((oned[i-1]+oned[i])/2.0)+(dis(eng)/pow(2.0,((j+1)/2)));
			if (val > max)max = val;
			if (val < min)min = val;

			oned.insert(oned.begin() + i, val);
		}



	
	}
	for (int i = 0; i < oned.size(); i++)
	{
		cout  << i << "," << oned[i]<< endl;


	}
	return oned;
}

vector<vector<double>> normalize(vector <vector<double>> a) 
{
	double max = a[0][0], min = a[0][0];
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
		{

			if (max < a[i][j])max = a[i][j];
			if (min > a[i][j])min = a[i][j];
		}

	}
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
		{

			a[i][j] = ((a[i][j] - min) / (max - min));
		}

	}
	return a;
}