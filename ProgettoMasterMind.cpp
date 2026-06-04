#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void modalitaCodificatore();
void modalitaDecifratore();
void mostraRegole();
bool nessunaDuplicata(int cifre[], int n);
int calcolaX(int codice[], int tentativo[]);
int calcolaO(int codice[], int tentativo[]);
void generaDisposizioni(int tutte[][4], int &totale);
bool compatibile(int config[], int tentativo[], int x, int o);

int main()
{
    int scelta;
    cout << "=== MASTER MIND - NUMERINO ===\n\n";
    cout << "1. Computer come Codificatore (tu indovini)\n";
    cout << "2. Computer come Decifratore (lui indovina)\n";
    cout << "3. Leggi le regole\n";
    cout << "\nScelta: ";
    cin >> scelta;
    if (scelta==1)
        modalitaCodificatore();
    else if (scelta==2)
        modalitaDecifratore();
    else if (scelta==3)
        mostraRegole();
    else
        cout << "Scelta non valida.\n";
    system("pause");
    return 0;
}

void mostraRegole()
{
    system("cls");
    cout << "=== REGOLE DEL GIOCO ===\n\n";
    cout << "IL CODICE\n";
    cout << " 1. Il codice segreto e' una sequenza di 4 cifre distinte.\n";
    cout << " 2. Le cifre sono comprese tra 1 e 6.\n";
    cout << " 3. Non sono ammesse cifre ripetute nel codice.\n\n";
    cout << "I TENTATIVI\n";
    cout << " 4. Il Decifratore ha a disposizione 10 tentativi.\n";
    cout << " 5. Ogni tentativo deve rispettare le stesse regole del codice\n";
    cout << " (4 cifre distinte tra 1 e 6).\n\n";
    cout << "LA RISPOSTA\n";
    cout << " 6. Dopo ogni tentativo si riceve una risposta con X e O:\n";
    cout << " X = cifra giusta al posto giusto\n";
    cout << " O = cifra giusta al posto sbagliato\n";
    cout << " 7. Le X vengono sempre mostrate prima delle O.\n";
    cout << " 8. Se nessuna cifra e' giusta, la risposta e' 0000.\n\n";
    cout << " Esempio:\n";
    cout << " Codice: 3 5 1 4\n";
    cout << " Tentativo: 6 3 2 4 -> Risposta: XO\n";
    cout << " (4 e' al posto giusto = X, 3 e' presente ma fuori posto = O)\n\n";
    cout << "LE DUE MODALITA'\n";
    cout << " 9. Codificatore: il computer genera il codice, tu lo indovini.\n";
    cout << " 10. Decifratore: tu pensi il codice, il computer lo indovina.\n\n";
    system("pause");
}

bool nessunaDuplicata(int cifre[], int n)
{
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (cifre[i]==cifre[j])
                return false;
    return true;
}

int calcolaX(int codice[], int tentativo[])
{
    int x=0;
    for (int i=0; i<4; i++)
        if (tentativo[i]==codice[i])
            x++;
    return x;
}

int calcolaO(int codice[], int tentativo[])
{
    int o=0;
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (i!=j && tentativo[i]==codice[j])
                o++;
    return o;
}

void modalitaCodificatore()
{
    srand(time(0));
    int codice[4];
    int n=0;
    while (n<4)
    {
        int c=rand()%6+1;
        bool trovato=false;
        for (int i=0; i<n; i++)
            if (codice[i]==c)
                trovato=true;
        if (!trovato)
        {
            codice[n]=c;
            n++;
        }
    }
    system("cls");
    cout << "=== MODALITA': TU DECIFRI ===\n\n";
    cout << "Codice generato! Hai 10 tentativi.\n";
    cout << "Inserisci 4 cifre distinte tra 1 e 6.\n\n";
    int tentativi=0;
    bool vinto=false;
    while (tentativi<10 && !vinto)
    {
        int t[4];
        bool valido=false;
        while (!valido)
        {
            cout << "Tentativo " << tentativi+1 << ": ";
            for (int i=0; i<4; i++)
                cin >> t[i];
            bool inRange=true;
            for (int i=0; i<4; i++)
                if (t[i]<1 || t[i]>6)
                    inRange=false;
            if (inRange && nessunaDuplicata(t,4))
                valido=true;
            else
                cout << "Input non valido. Cifre distinte tra 1 e 6.\n";
        }
        int x=calcolaX(codice,t);
        int o=calcolaO(codice,t);
        cout << "Risposta: ";
        for (int i=0; i<x; i++) cout << "X";
        for (int i=0; i<o; i++) cout << "O";
        if (x==0 && o==0) cout << "0000";
        cout << "\n\n";
        if (x==4)
            vinto=true;
        tentativi++;
    }
    if (vinto)
        cout << "Hai vinto in " << tentativi << " tentativi!\n";
    else
    {
        cout << "Hai perso. Il codice era: ";
        for (int i=0; i<4; i++) cout << codice[i];
        cout << "\n";
    }
}

void generaDisposizioni(int tutte[][4], int &totale)
{
    totale=0;
    for (int a=1; a<=6; a++)
        for (int b=1; b<=6; b++)
            for (int c=1; c<=6; c++)
                for (int d=1; d<=6; d++)
                {
                    int tmp[4]={a,b,c,d};
                    if (nessunaDuplicata(tmp,4))
                    {
                        tutte[totale][0]=a;
                        tutte[totale][1]=b;
                        tutte[totale][2]=c;
                        tutte[totale][3]=d;
                        totale++;
                    }
                }
}

bool compatibile(int config[], int tentativo[], int x, int o)
{
    return calcolaX(config,tentativo)==x && calcolaO(config,tentativo)==o;
}

void modalitaDecifratore()
{
    int tutte[360][4];
    int totale;
    generaDisposizioni(tutte,totale);
    bool attive[360];
    for (int i=0; i<totale; i++) attive[i]=true;
    system("cls");
    cout << "=== MODALITA': COMPUTER DECIFRA ===\n\n";
    cout << "Pensa un codice segreto di 4 cifre distinte tra 1 e 6.\n";
    cout << "Rispondi con il numero di X e di O.\n\n";
    int tentativi=0;
    bool vinto=false;
    while (tentativi<10 && !vinto)
    {
        int idx=-1;
        int attiveCount=0;
        for (int i=0; i<totale; i++)
            if (attive[i])
            {
                attiveCount++;
                if (idx==-1) 
					idx=i;
            }
        if (idx==-1)
        {
            cout << "Nessuna soluzione compatibile. Hai inserito risposte errate?\n";
            break;
        }
        if (attiveCount==1)
        {
            cout << "La soluzione e' sicuramente: ";
            for (int i=0; i<4; i++) cout << tutte[idx][i];
            cout << "\nHo impiegato " << tentativi+1 << " tentativi!\n";
            vinto=true;
            break;
        }
        cout << "Tentativo " << tentativi+1 << ": ";
        for (int i=0; i<4; i++) cout << tutte[idx][i];
        cout << "\n";
        int x, o;
        cout << "Quante X? "; cin >> x;
        cout << "Quante O? "; cin >> o;
        if (x==4)
        {
            cout << "\nHo indovinato in " << tentativi+1 << " tentativi!\n";
            vinto=true;
            break;
        }
        for (int i=0; i<totale; i++)
            if (attive[i] && !compatibile(tutte[i],tutte[idx],x,o))
                attive[i]=false;
        tentativi++;
    }
    if (!vinto)
        cout << "\nNon sono riuscito a indovinare.\n";
}
