#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int minimum(int* vett, int size){
	int min = 1;
	for(int i = 2; i <= size; i++){
		if(vett[i] <= vett[min])
			min = i;
	}
	return vett[min];
}

int maximum(int* vett, int size){
	int max = 1;
	for(int i = 2; i <=size; i++){
		if(vett[i] > vett[max])
			max = i;
	}
	return vett[max];
}

template <typename H>
void printArr(H* arr, int n, ofstream& out){
	for(int i = 1; i <= n; i++){
		out << arr[i] <<" ";
	}
}

template <typename H>
H* CountingSort(H* A, int size, ofstream& out){
	
	int *vett = new int[size+1];
	for(int i = 1; i <= size; i++)
		vett[i] = (int)(A[i]);
	
	int min = minimum(vett, size);
	int max = maximum(vett, size);
	int K = max - min + 1;
	int C[K+1];
	
	for(int i = 0; i <= K; i++){
		C[i] = 0;
	}
	
	for(int i = 1; i <= size; i++){
		C[vett[i] - min + 1]++;
	}
	
	for(int i = 2; i <= K; i++){
		C[i] += C[i-1];
	}
	
	printArr(C, K-1, out);
	H* B = new H[size+1];
	
	for(int i = size; i > 0; i--){
		B[C[vett[i] - min +1]] = vett[i];
		C[vett[i] - min + 1]--;
	}
	
	delete []vett;
	return B;
}

double* CountingSortDue(double* A, int size, ofstream& out){
	int *vett = new int[size+1];
	for(int i = 1; i <= size; i++)
		vett[i] = (int)(A[i]*10);
	
	int min = minimum(vett, size);
	int max = maximum(vett, size);
	int K = max - min + 1;
	int C[K+1];
	
	for(int i = 0; i <= K; i++){
		C[i] = 0;
	}
	
	for(int i = 1; i <= size; i++){
		C[vett[i] - min + 1]++;
	}
	
	for(int i = 2; i <= K; i++){
		C[i] += C[i-1];
	}
	
	printArr(C, K-1, out);
	double* B = new double[size+1];
	
	for(int i = size; i > 0; i--){
		B[C[vett[i] - min +1]] = (vett[i] / 10.0);
		C[vett[i] - min + 1]--;
	}
	
	delete []vett;
	return B;
}

int main(){
	
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	
	for(int t = 0; t < 100; t++){
		
		string tipo;
		in >> tipo;
		int N;
		in >> N;
		out << "0 ";
		if(tipo == "int"){
			int *A = new int[N+1];
			for(int i = 1; i <= N; i++){
				int val;
				in >> val;
				A[i] = val;
			}
			int* RIS = CountingSort(A, N, out);
			printArr(RIS, N, out);
			delete []A;
		}
		else if(tipo == "bool"){
			bool *A = new bool[N+1];
			for(int i = 1; i <= N; i++){
				bool val;
				in >> val;
				A[i] = val;
			}
			bool* RIS = CountingSort(A, N, out);
			printArr(RIS, N, out);
			delete []A;
		}
		else if(tipo == "double"){
			double *A = new double[N+1];
			for(int i = 1; i <= N; i++){
				double val;
				in >> val;
				A[i] = val;
			}
			double* RIS = CountingSortDue(A, N, out);
			printArr(RIS, N, out);
			delete []A;
		}
		else{
			char *A = new char[N+1];
			for(int i = 1; i <= N; i++){
				char val;
				in >> val;
				A[i] = val;
			}
			char* RIS = CountingSort(A, N, out);
			printArr(RIS, N, out);
			delete []A;
		}
		out << endl;
	}
	
	in.close();
	out.close();
	return 0;
}