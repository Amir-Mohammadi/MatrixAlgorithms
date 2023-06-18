

#include <iostream>
#include <cmath>
using namespace std;


const int size = 10;

int main()
{

	double matrix[size][size] , d1 , d2, d3, s1, s2, s3;
	double T[size][size] = {0};


	for(int i=0; i < size; i++)
	{
		for(int k=0; k < size; k++)
		{
			matrix[i][k]=rand() / (double)RAND_MAX;
		}
	}

	d1 = matrix[0][0];
	d2 = matrix[1][1];
	d3 = matrix[2][2];

	s1 = matrix[0][1];
	s2 = matrix[1][2];
	s3 = matrix[2][3];

	//3gotri

	for(int i=0; i<size; i++)
	{
		for(int j=0; j < size; j++)
		{
			if(abs(i-j) == 1)
			{
				T[i][j] = (i == j - 1) ? s1: s2;
			}
			else if(abs(i-j) == 2)
			{
				T[i][j] = s3;
			}
			else if(i == j)
			{
				T[i][j] = (i == 0) ? d1 : ((i == 1) ? d2 : d3);
			}
		}
	}


	// print matris
	for(int i=0; i < size; i++)
	{
		for(int k=0; k < size; k++)
		{
			cout << T[i][k] << " ";
		}

		cout << endl;
	}



	return 0;
}