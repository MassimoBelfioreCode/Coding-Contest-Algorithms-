#include <iostream>
#include <fstream>

using namespace std;

//SELEZIONE DI ATTIVITà

//usare un array, stampare count, selezionare le attività, inserire le attività in un array, meglio fare una classe
//potrei usare una coda anzichè un array, estrarre l'attività dalla coda e 

class Activity{
	private:
		int s; //tempo di inizio di un'attività
		int f; //tempo di fine di un'attività
		
		public:
			
			Activity(int v1, int v2){
				s = v1;
				f = v2;
			}
			
			int getS()const{ return s;}
			int getF()const{ return f;}
			
			friend bool operator > (Activity& a1 , Activity& a2){
				return a1.getF() > a2.getF();
			}
			
			friend bool operator < (Activity& a1, Activity& a2){
				return a1.getF() < a2.getF();
			}
			
			friend bool operator >= (Activity& a1, Activity& a2){
				return a1.getF() >= a2.getF();
			}
			
			friend bool operator <= (Activity& a1, Activity& b1){
				return a1.getF() <= b1.getF();
			}
			
			
			friend ostream& operator <<(ostream& os, const Activity& a){
				return os <<"(" << a.getS() <<" "<< a.getF() <<")"<<" ";
			}
			
};


void sort(Activity** vett, int n){ 
    for(int i = 0; i < n; i++)
    	for(int j = i+1; j < n; j++)
            if(vett[j]->getF() < vett[i]->getF())
                swap(vett[i], vett[j]);
} 

 
void ActivitySelect(Activity** arr, int dim, ofstream& out){
	sort(arr, dim);
	int n_a = 1;
	int k = 0;
		 
	for(int i = 1; i < dim; i++){
		if(arr[k]->getF() <= arr[i]->getS()){
			n_a++;
			k = i; //perhè deve andare nella posizione dell'ultima attività selezionata
		}
	}
	out << n_a << endl;
}


void print(ofstream& out, Activity** v, int dim){
	for(int i = 0; i < dim; i++){
		out << *v[i] <<" ";
	}
	out << endl;
}


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int task = 0; task < 100; task++){
		int N;
		in >> N;
		//attività tipo e int tipo quindi 2 puntatori 
		Activity** v = new Activity*[N];
		
		for(int j = 0; j < N; j++){
			char parentesis; in >> parentesis;
			int x; in >> x;
			int y; in >> y;
			in >> parentesis;
			v[j] = new Activity(x, y);
		}
		//print(out, v, N);
		ActivitySelect(v, N, out);
		
		for(int i = 0; i < N; i++){
			delete v[i];
		}
		
		delete [] v;
	}

	return 0;
}