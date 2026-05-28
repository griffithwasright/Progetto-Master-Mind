#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));

    const int N = 6;
    int segreto[N];
    int tentativo[N];

    bool controlloSegreto[N] = {false};
    bool controlloTentativo[N] = {false};

    bool indovinato = false;

    for(int i = 0; i < N; i++)
        segreto[i] = rand() % 10 + 1;

    cout << "-----------------------" << endl;
    cout << "|| GIOCO MASTER MIND ||" << endl;
    cout << "-----------------------" << endl;

    while(!indovinato) {

        for(int i = 0; i < N; i++) {
            controlloSegreto[i] = false;
            controlloTentativo[i] = false;
        }

        int cont = 0;
        cout << "Inserisci 6 numeri da 1 a 10:" << endl;
        for(int i = 0; i < N; i++)
            cin >> tentativo[i];


        for(int i = 0; i < N; i++) {
            if(tentativo[i] == segreto[i]) {
                cout << "O";
                cont++;
                
				controlloSegreto[i] = true;
                
				controlloTentativo[i] = true;
            }
        }

        for(int i = 0; i < N; i++) {
            if(controlloTentativo[i])
                continue;
            
			bool trovato = false;
            
            for(int j = 0; j < N; j++) {
                if(!controlloSegreto[j] && tentativo[i] == segreto[j]) {
                    trovato = true;
                    
                    controlloSegreto[j] = true;
                    
                    controlloTentativo[j] = true;
                    
                    break;
                }
            }

            if(trovato)
                cout << "P";
            else
                cout << "X";
        }
        cout << endl;

        if(cont == N) {
            cout << "Hai indovinato la combinazione!" << endl;
            indovinato = true;
        }
    }
}
