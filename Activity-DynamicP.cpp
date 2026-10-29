#include <iostream>
#include <fstream>

using namespace std;
//vogliamo che S sia il sottoinsieme massimale di attività cioè contenga il numero massimo di attivitò mutuamente compatibili
//posso assegnare a 2 attività mutuamente compatibili la stessa risorsa in quanto non si intersecano
//ordino le attività rispettivamente ai loro tempi di fine con una complessità temporale di O(n*log(n))
class Activity{
	private:
		int s;
		int e;
		
		public:
			Activity(int a, int b): s(a), e(b){}
			int getS()const{ return s;} int getE()const{ return e;}
			int getDiff()const{ return e - s;}
			 
			friend ostream& operator <<(ostream& os, Activity& a){
				return os <<"(" << a.s << "," << a.e <<")";
			}
};


void sorting(Activity** vett, int n){
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++)
			if(vett[i]->getE() > vett[j]->getE())
				swap(vett[i], vett[j]);
			else if(vett[i]->getE() == vett[j]->getE() && vett[i]->getS() < vett[j]->getS())
				swap(vett[i], vett[j]);
	}
}

int select(Activity** v, int i){
	for(int j = i-1; j >= 0; j--){
		if(v[j]->getE() <= v[i]->getS())
			return j;
		}
	return -1;
}

void ActivitySelect(Activity** arr ,int n, ofstream& out){
	sorting(arr, n);
	int vett[n];
	vett[0] = arr[0]->getDiff();
	
	for(int i = 1; i < n; i++){
		int val = arr[i]->getDiff();
		int k = select(arr, i);
		
		if(k != -1){
			val = val + vett[k];
		}
		if(val > vett[i-1]){
			vett[i] = val;
		}
		else
			vett[i] = vett[i-1];
	}
	out << vett[n-1] << endl;	
}

int main(){
	
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	
	for(int t = 0; t < 100; t++){
		int N;
		in >> N;
		//dobbiamo creare un array di attività
		Activity** arr = new Activity*[N];
		
		for(int i = 0; i < N; i++){
			char parentesis;
			in >> parentesis;
			int x; in >> x;
			int y; in >> y;
			in >> parentesis;
			arr[i] = new Activity(x, y);
		}
		
		ActivitySelect(arr, N, out);
		delete [] arr;
	}
	
	in.close();
	out.close();
	return 0;
}