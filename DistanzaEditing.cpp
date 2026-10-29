#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void EditDistance(ofstream& out, string s1, string s2, int m, int n){
	
	int **matrix = new int*[m+1];
	for(int i = 0; i < m+1; i++){
		matrix[i] = new int[n+1];
	}
	
	for(int i = 0; i < m+1; i++){
		matrix[i][0] = i;
	}
	for(int j = 0; j < n+1; j++){
		matrix[0][j] = j;
	}
	
	for(int i = 1; i < m+1 ; i++){
		for(int j = 1; j < n+1; j++){
			if(s1[i-1] == s2[j-1]) 
				matrix[i][j] = matrix[i-1][j-1];
			else
				matrix[i][j] = min(min(matrix[i-1][j], matrix[i][j-1]), matrix[i-1][j-1]) +1; 
		}
	}
	out << matrix[m][n] << endl;
}


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i = 0; i < 100; i++){
		int M; in >> M;
		int N; in >> N;			
		string X; in >> X;
		string Y; in >> Y;
		
		EditDistance(out, X, Y, M, N);
	}
	
	in.close();
	out.close();
	return 0;
}
