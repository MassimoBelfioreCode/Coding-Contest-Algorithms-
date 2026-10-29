#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int max(int a, int b){ return (a > b)? a:b;}

class Nodo{
	public:
		Nodo *next;
		char val;

		Nodo(char v){
			val = v;
			next = nullptr;
		}
};


class Stack{
	//LIFO
	private:
		Nodo *top;
		int noe;

		public:

			Nodo* getTop()const{ return top;}
			int getSize()const{ return noe;}
			
			bool isEmpty()const{
				if(top == nullptr) return true;
				else return false;
			}

			Stack(){
				noe = 0;
				top = nullptr;
			}

			void push(char x){
				Nodo *nuovo = new Nodo(x);
				nuovo->next = top;
				top = nuovo;
				noe++;
			}

			char pop(){
				Nodo *tmp = this->top;
				char c = 0;
				if(!isEmpty()){
					c = top->val;
					top = top->next;
					delete tmp;
					noe--;
				}
				return c;
			}

};

void printLCS(string s1, string s2, int n, int m, ofstream& out){

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
	int length = matrix[n][m];

	int i = n;
	int j = m;
	Stack *st = new Stack();

	while(i > 0 && j > 0){
		if(s1[i-1] == s2[j-1]){
			st->push(s1[i-1]);
			i--;
			j--;
		}
		else{
			if(matrix[i-1][j] > matrix[i][j-1]){
				i = i-1;
			}
			else j = j-1;
		}
	}

	for(int i = 0; i < n; i++){
		out << st->pop();
	}

	for(int i = 0; i < n+1; i++){
		delete matrix[i];
	}

	if(matrix != nullptr){
		delete []matrix;
		matrix = nullptr;
	}
}

int main(){

	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");

	for(int task = 0; task < 100; task++){

		int N; in >> N;
		int M; in >> M;
		string X; in >> X;
		string Y; in >> Y;

		printLCS(X, Y, N, M, out);
		out << endl;
	}

	in.close();
	out.close();

	return 0;
}
