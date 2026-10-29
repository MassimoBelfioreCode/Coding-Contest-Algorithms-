#include <iostream>
#include <cstring>

using namespace std;

void incrementare8(int* a){
	*a += 8;
}

int main(){
	
	int* p; 
	int* q;
	
	cout << p;
	cout << endl;
	cout <<q;
	cout << endl;
	p = q;
	cout << "indirizzo di p: " << p << endl;
	cout << "indirizzo di q: " << q << endl;
	
	
	string dogs[] = {"Buck", "Shadow", "Maya", "Dewey", "Truman", "Max", "Shorty", "Old_Jack", "Hachiko", "Ringhio"};
	string tiger[] = {"Savana", "jungle", "Rua", "Malpe", "Thunder", "Prum", "Richard_Parker"};
	
	cout << endl;
	
	for(int i=0; i< 10; i++){
		cout << dogs[i]<< "  ";
	}
	cout << endl;
	
	for(int j = 0; j < 7; j++){
		cout << tiger[j] << "  ";
	}
	cout << endl << endl;
	
	string* vett = dogs; //il nome di un array è un puntatore che punta all' indirizzo di memoria dove risiede il primo elemento(cane)
	
	cout << "dogs: "  << dogs << endl;
	cout << "vett: " << vett << endl;
	cout << "\n";
	
	for(int k = 0; k < 10; k++){
		cout << vett[k] <<"\t";
	}
	cout << endl;
	
	cout << *tiger << endl;
	
	cout << "OK" << endl;
	
	//puntatori come parametri di funzioni
	int j = 2;
	incrementare8(&j);
	cout <<"valore di j = "<< j << endl;
	
	//passaggio per valore si passa un VALORE, passaggio per riferimento si passa un PUNTATORE come parametro
	//si possono combinare
	
	
	
	return 0;
}