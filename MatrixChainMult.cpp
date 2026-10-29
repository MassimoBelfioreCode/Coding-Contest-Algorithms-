#include <iostream>
#include <fstream>

using namespace std;

int matrixChainMultiply(int* v, int n){
	int matrix[n][n];
	for(int i = 1; i < n; i++){
		matrix[i][i] = 0; 
	}
	
	for(int l = 2; l < n; l++){
		for(int i = 0; i < n-l+1; i++){
			int j = i + l -1;
			matrix[i][j] = INT_MAX;
			for(int k = i; k <= j-1; k++){
				int prodotto_scal = matrix[i][k] + matrix[k+1][j] + v[i-1] * v[k] * v[j];
				if(prodotto_scal < matrix[i][j]){
					matrix[i][j] = prodotto_scal;
				}	
			}
		}
	}
	
	return matrix[1][n-1];
}


int main(){
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	
	for(int task = 0; task < 100; task++){
		int N; in >> N;
		int *array = new int[N+1];
		int righe;
		int colonne;
		
		for(int i = 0; i < N; i++){
			char parentesis; 
			in >> parentesis;
			in >> righe; 
			in >> parentesis;
			in >> colonne;
			in >> parentesis;
			array[i] = righe;
		}
		array[N] = colonne;
		out << matrixChainMultiply(array, N+1) << endl;
		
		delete []array;
	}
	
	in.close();
	out.close();
	
	return 0;
}