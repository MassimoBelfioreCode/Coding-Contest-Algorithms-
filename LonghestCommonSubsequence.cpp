#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//*********LCS********
//voglio trovare il valore Matrix[m][n]
//fare altri due cicli for e confrontare se i caratteri sono uguali

int LCS(string s1, string s2, int n, int m){

	int **matrix = new int*[n+1];
	for(int i = 0; i < n+1; i++){
		matrix[i] = new int[m+1];
	}
	//caso base;
	for(int i = 0; i < n+1; i++){
		matrix[i][0] = 0;
	}
	for(int j = 1; j < m+1; j++){
		matrix[0][j] = 0;
	}
	//passo induttivo 
	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < m+1; j++){
			if(s1[i-1] == s2[j-1])
				matrix[i][j] = (matrix[i-1][j-1])+1;
			else 
				matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
		}		
	}
	int length = 0;
	for(int i = 0; i < n+1; i++){
		for(int j = 0; j < m+1; j++){
			length = matrix[i][j];
		}
	}
	
	for(int i = 0; i < n+1; i++){
		delete matrix[i];
	}
	
	if(matrix != nullptr){
		delete []matrix;
		matrix = nullptr;	
	}
	
	return length;
}


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int task = 0; task < 100; task++){
		
		int N; in >> N;
		int M; in >> M;
		string X; in >> X;
		string Y; in >> Y;
		int val = LCS(X, Y, N, M);
		out << val << endl;
	}
	
	return 0;

}