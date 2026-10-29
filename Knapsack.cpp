#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//PROBLEMA DELLO ZAINO GREEDY  
//potrebbe utilizzare un array per indicare lo zaino? Un oggetto di tipo zaino?
//prende in input l'insieme degli n oggetti
/*determinare il valore massimale ottenibile con un sottoinsieme degli n oggetti con peso(P) complessivo <= al peso P
 sopportabile dallo zaino (Knapsack) */
//per ogni oggetto i, con i = 0,1,....n-1, il peso dell'oggetto è indicato da G[i] e il valore del relativo oggetto è indicato con V[i]
//peso unitario, tutti gli oggetti hanno peso pari ad 1


class Knapsack{
	
	private:
		
		int p; //peso dello zaino
		int n;	
		vector<int> vec; //lo utilizzo come se fosse V[i]
			
		public:
			
			int getP()const{ return p;}
			int getN()const{ return n;} 
			//costruttore
			Knapsack(int weight, vector<int> arr){
				p = weight;
				vec = arr;
				n = 0; 
			}
			
			//distruttore
			~Knapsack(){}
			
			void print(ofstream& out, int p_massimo){
				int somma = 0;
				for(int i = 0; i < p_massimo; i++){
					somma = somma + sorting(vec)[i];
				}
				out << somma << endl;
			}
			
			
			vector<int> sorting(vector<int> A){
				vec = A;
				sort(vec.begin(), vec.end(), greater<int>());
				return vec;
			}
				
};


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int k = 0; k < 100; k++){
		int N;
		in >> N;
		int peso; 
		in >> peso;
		
		vector<int> V;
		
		for(int i = 0; i < N; i++){
			int val;
			in >> val;
			V.push_back(val);
		}
		
		Knapsack* b = new Knapsack(peso, V); // creo un oggetto di tipo Zaino con un peso sopportabile
		b->print(out, peso);
		
		b->~Knapsack();
	}		
	
	in.close(); 
	out.close();
	
	return 0;
}