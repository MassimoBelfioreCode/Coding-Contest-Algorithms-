#include <iostream> 
#include <fstream>

using namespace std;


//[ 5, 7, 6, 2, 8, 10, 5, 14, 3, 8] ---> [ 2, 3, 5, 5, 6, 7, 8, 8, 10, 14]
//COUNTING SORT

//countingsort determina per ogni elemento di input x il numero di elementi minori di x
//se ci sono 17 elementi minori di x allora in output x andrà in posizione 18
// A[1.....n] , B[1....n], C[1....K] dove k = A[max]-A[min]

/*Lo schema di funzionamento è di immediata semplicità . 
Noto a priori il range di variabilità K del vettore di interi, 
si costruisce un vettore ausiliario C di tale lunghezza che sia in grado di fornire, 
per ogni posizione, l'informazione circa il numero di elementi minori o uguali presenti all'interno del vettore di input.
Se il range di variabilità (K) = A[max]-A[min] è proporzionale al numero di elementi presenti nel vettore di input 
allora l'ordinamento può essere realizzato in tempo lineare.

*/


int massimo(int *v, int n){
	int max = v[0];
	for(int i = 1; i < n; i++){
		if(v[i] > max) max = v[i];
	}
	return max;
}

int minimo(int *v, int n){
	int min = v[0];
	for(int i = 1; i < n; i++){
		if(v[i] < min) min = v[i];
	}
	return min;
}

void initialize(int* vett, int size){
	for(int i = 0; i < size; i++){
		vett[i] = 0;
	}
}


void stampa(ofstream& visual, int* v, int size){
	for(int i = 0; i < size; i++){
		visual << v[i] <<" ";
	}
}


void countingSort(ofstream& out, int* A, int dim){
	int min = minimo(A, dim);
	int max = massimo(A, dim);
	int k = max - min + 1;
	int* RIS = new int[dim];
	int* C = new int[k];
	initialize(C, k);
	for(int i = 0; i < dim; i++){
		C[A[i]-min] = C[A[i]-min] +1; 
	}
	for(int j = 1; j < k; j++){
		C[j] = C[j] + C[j-1];
	}	
	for(int z = dim-1; z >= 0; z--){
		RIS[C[A[z]-min]-1] = A[z];
		C[A[z]-min] = C[A[z]-min] - 1;
	}
	for(int i = 0; i < dim; i++){
		A[i] = RIS[i];
	}
	stampa(out, C, k);
	stampa(out, A, dim);
	 
	delete []RIS;
}


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i = 0; i < 100; i++){
		
		int N;
		in >> N;
		
		int* arr = new int[N];
		
		for(int j = 0; j < N; j++){

			int val;
			in >> val;
			arr[j] = val;
		}
		countingSort(out, arr, N);
		out << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}
