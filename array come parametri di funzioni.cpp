#include <iostream>
#include <string>

using namespace std;
//nel prototipo si mettono i tipi e basta

void change(char c[4]){
	cout << c << endl;
	strcpy(c, "AMA");
	return;
}

int main(){
	
	char parola[4] = "ABC";
	change(parola);
	cout << parola << endl;
	
	return 0;
}