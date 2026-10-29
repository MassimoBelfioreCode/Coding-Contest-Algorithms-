#include <iostream>
#include <fstream>

using namespace std;
//la massimizzazione stavolta sta nel guadagno dei soldi vinti giocando le partite
class Partita{

	private:

		int giorno;
		int ora_i;
		int ora_f;
		int tassa_p;
		int soldi_vinti;
		int somma_max;

		public:

			Partita(int giorno, int ora_i, int ora_f, int tassa_p, int soldi_vinti){
				this->giorno = giorno;
				this->ora_i = ora_i;
				this->ora_f = ora_f;
				this->tassa_p = tassa_p;
				this->soldi_vinti = soldi_vinti;
			}
			
			Partita(Partita& p){
				this->giorno = p.getGiorno();
				this->ora_f = p.getOra_F();
				this->ora_i = p.getOra_I();
				this->tassa_p = p.getTassa_P();
				this->soldi_vinti = p.getSoldi_Vinti();
			}
			

			int getGiorno()const{ return this->giorno;}
			int getOra_F()const{ return this->ora_f;}
			int getOra_I()const{ return this->ora_i;}
			int getTassa_P()const{ return this->tassa_p;}
			int getSoldi_Vinti()const{ return this->soldi_vinti;}
			int getDiff()const{ return this->ora_f - this->ora_i;}
			int getGuadagno()const{ return this->soldi_vinti - this->tassa_p;}

			friend ostream& operator << (ostream& os, const Partita& p){
				return os <<"("<< p.giorno <<" "<< p.ora_i <<" "<< p.ora_f <<" "<< p.tassa_p <<" "<< p.soldi_vinti <<")";
			}

};


void sorting(Partita** arr, int n){
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(arr[i]->getOra_F() < arr[j]->getOra_F())
				swap(arr[i], arr[j]);
		}
	}
}

//distribuire le partite in giorni
//ricordiamo che uno degli utilizzi del radixSort è quello di ordinare le date per giorno, mese e anno
void print(ofstream& out, int n, Partita** arr){
	for(int i = 0; i < n; i++){
		cout << *arr[i] <<" ";
	}
	cout << endl;
}


int guadagno_max(int size, int budget, Partita** arr){
	int count = 0;
	int somma_max = 0;
	Partita** table = new Partita*[size];
	
	for(int i = 0; i < size; i++){
		if(budget < arr[i]->getTassa_P()){
			count++;
		}
		else{
			table[i] = new Partita(*arr[i]);
		}
	}
	//avrò un array con tutte e sole le partite giocabili
	//forse però si deve usare una lista o meglio un array di liste per giorni ma vabeh
	//le partite le inserisco in lista già ordinate con l'inserimento in lista ordinata
	//rispetto al tempo di fine partita e poi prendo il sottoinsieme di partite giocabili
	//che massimizzano il guadagno
		
	if(count == size)
		return budget;
		
	return somma_max + budget;
}


int main(int argc, char *argv[]){
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");

	for(int t = 0; t < 100; t++){
		int N; in >> N;//numero di partite da giocare
		int M; in >> M;//budget a disposizione iniziale
		Partita** array_di_partite = new Partita*[N];//array di partite o gruppi

		for(int i = 0; i < N; i++){
			int gg; in >> gg;
			int s; in >> s;
			int e; in >> e;
			int cp; in >> cp;
			int vin; in >> vin;
			array_di_partite[i] = new Partita(gg, s, e, cp, vin);
		}
		out << guadagno_max(N, M, array_di_partite) <<endl;
		print(out, N, array_di_partite);
	}

	in.close();
	out.close();

	return 0;
}
