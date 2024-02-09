#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include<Windows.h>
#include <cstring>
#include <string>
#include<vector>
#include <fstream>
using namespace std;


ifstream f("medicamente.txt");
int nrMed;
int globalArgc = 0;
string parola = "1234";

class Medicament {
    string nume;
    string tip;
    int volum;
    int rezervat;
public:
    Medicament();
    Medicament(string, string, int, int);
    Medicament(const Medicament&);
    friend ostream& operator <<(ostream&, const Medicament&);

    string getNume() { return nume; };
    string getTip() { return tip; };
    int getVolum() { return volum; };
    int getRezervat() { return rezervat; }
    void setRezervat(int r) { rezervat = r; }
};

void meniuUser();
void meniuAdmin();
void meniuAdminUser();
void afisare();
void afisarePlusCautare();
void medicamenteRezervate();
void medicamenteDisponibile();
void cautare();
Medicament citire();
void citireMed(int);

Medicament::Medicament()
{
    this->volum = 0;
    this->rezervat = 0;
    this->nume = "";
    this->tip = "";
}

Medicament::Medicament(string nume, string tip, int volum, int rezervat)
{
    this->volum = volum;
    this->rezervat = rezervat;
    this->nume = nume;
    this->tip = tip;
}

Medicament::Medicament(const Medicament& a)
{
    this->volum = a.volum;
    this->rezervat = a.rezervat;
    this->nume = a.nume;
    this->tip = a.tip;
}

ostream& operator <<(ostream& st, const Medicament& a)
{
    st << a.nume << endl << a.tip << endl << a.volum << endl << a.rezervat << endl;
    return st;
}


vector<Medicament> medicamente(100);


Medicament citire()
{
    string nume, tip;
    int rezervat;
    int volum;
    getline(f, nume);
    getline(f, tip);
    f >> volum;
    f.get();
    f >> rezervat;
    f.get();
    Medicament c = Medicament(nume, tip, volum, rezervat);
    return c;
}




void adaugare()
{
    system("cls");
    cout << "-_-Adaugare medicamente-_-" << endl << endl;
    nrMed++;
    string nume, tip;
    int rezervat;
    int volum;
    cout << "Introduceti numele: ";
    //cin.ignore();
    getline(cin, nume);
    cout << "Introduceti tipul: ";
    //cin.ignore();
    getline(cin, tip);
    cout << "Volumul/Nr. Comprimate: ";
    cin >> volum;
    cout << "Disponibilitatea(0 sau 1):  ";
    cin >> rezervat;
    medicamente[nrMed - 1] = Medicament(nume, tip, volum, rezervat);
    ofstream f("medicamente.txt");
    f << nrMed << endl;
    for (int i = 0; i < nrMed; i++)
    {
        f << medicamente[i];
    }
    if (globalArgc == 4)
        exit(0);
    system("pause");
    meniuAdmin();
}

void stergere()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
        FOREGROUND_RED);
    cout << endl << "-_-Stergere-_-" << endl << endl;
    cout << "Introduceti numele medicamentului pe care doriti sa il stergeti: " << endl;
    string nume;
    cin >> nume;
    int k = -1, j, ok = 0;
    for (int i = 0; i < nrMed; i++)
    {
        if (nume == medicamente[i].getNume())
        {
            k = i;
            ok = 1;
            break;
        }
    }

    if (k != -1)
    {
        for (j = k; j < nrMed - 1; j++)
        {
            medicamente[j] = medicamente[j + 1];

        }
        nrMed -= 1;

        ofstream f("medicamente.txt");
        f << nrMed << endl;
        for (int i = 0; i < nrMed; i++)
        {
            f << medicamente[i];
        }
    }
    if (ok == 0)
    {
        cout << "Medicamentul nu a fost gasit!";
    }

    else
    {
        cout << "Medicamentul a fost sters cu succes!";
    }
    cout << endl;
    if (globalArgc == 4)
        exit(0);
    system("pause");
    cout << "\033[32m";
    meniuAdmin();
}


void cautare()
{
    int i;
    string nume;
    cout << endl;
    cout << "Introduceti numele medicamentului pe care doriti sa il cautati: ";

    getline(cin, nume);
    bool ok = true;
    for (i = 0; i < nrMed; i++)
        if (nume == medicamente[i].getNume())
        {
            if (ok == true)
                cout << "Medicamentul a fost gasit: " << endl;
            if (ok == false)
                cout << endl;
            cout << medicamente[i].getNume() << "(" << medicamente[i].getTip() << "-" << medicamente[i].getVolum() << ")->";
            if (medicamente[i].getRezervat() == 1)
                cout << "Rezervat";
            else
                cout << "Disponibil";
            ok = false;
        }
    if (ok == true)
    {
        cout << "Medicamentul introdus nu a fost gasit!";
    }
    cout << endl;
}


void afisare()
{
    system("cls");
    cout << "-_-Vizualizare-_-" << endl << endl;
    int i;
    cout << "1. Vizualizare medicamente disponibile" << endl;
    cout << "2. Vizualizare medicamente rezervate" << endl;
    cout << "3. Cautare" << endl;
    cout << "0. Back" << endl << endl;
    for (i = 0; i < nrMed; i++)
    {
        cout << "Nume: " << medicamente[i].getNume() << endl << "Tip: " << medicamente[i].getTip() << endl << "Volum/Nr. Comprimate: " << medicamente[i].getVolum() << endl;
        if (medicamente[i].getRezervat() == 1)
            cout << "Rezervat";
        else
            cout << "Disponibil";
        cout << endl << endl;
    }
    if (globalArgc == 3)
        exit(0);
    int optiune;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        if (optiune == 0)
        {
            meniuUser();
            break;
        }
        if (optiune == 1)
        {
            medicamenteDisponibile();
            break;
        }
        if (optiune == 2)
        {
            medicamenteRezervate();
            break;
        }
        else if (optiune == 3)
        {
            cin.ignore();
            cautare();
        }
        else
            cout << "Optiune invalida!" << endl;
    }

}

void afisarePlusCautare()
{
    system("cls");
    cout << "-_-Vizualizare-_-" << endl << endl;
    int i;
    cout << "1. Vizualizare medicamente disponibile" << endl;
    cout << "2. Vizualizare medicamente rezervate" << endl;
    cout << "3. Cautare" << endl;
    cout << "0. Back" << endl << endl;
    for (i = 0; i < nrMed; i++)
    {
        cout << "Nume: " << medicamente[i].getNume() << endl << "Tip: " << medicamente[i].getTip() << endl << "Volum/Nr. Comprimate: " << medicamente[i].getVolum() << endl;
        if (medicamente[i].getRezervat() == 1)
            cout << "Rezervat";
        else
            cout << "Disponibil";
        cout << endl << endl;
    }
    cautare();
    if (globalArgc == 3)
        exit(0);
}



void medicamenteDisponibile()
{
    system("cls");
    cout << endl << "-_-Medicamente Disponibile-_-" << endl << endl;
    int i;
    cout << "1. Cautare" << endl;
    cout << "0. Back" << endl << endl << endl;
    for (i = 0; i < nrMed; i++)
    {
        if (medicamente[i].getRezervat() == 0)
        {
            cout << "Nume: " << medicamente[i].getNume() << endl << "Tip: " << medicamente[i].getTip() << endl << "Volum/Nr. Comprimate: " << medicamente[i].getVolum() << endl;
            cout << "Disponibil";
            cout << endl << endl;
        }
    }
    if (globalArgc == 4)
        exit(0);
    int optiune;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        if (optiune == 0)
        {
            afisare();
            break;
        }
        if (optiune == 1)
        {
            int i;
            string nume;
            cout << endl;
            cout << "Introduceti numele medicamentului pe care doriti sa il cautati: ";
            cin.ignore();
            getline(cin, nume);
            bool ok = true;
            for (i = 0; i < nrMed; i++)
                if ((nume == medicamente[i].getNume()) && medicamente[i].getRezervat() == 0)
                {
                    if (ok == true)
                        cout << "Medicamentul a fost gasit: " << endl;
                    if (ok == false)
                        cout << endl;
                    cout << medicamente[i].getNume() << "(" << medicamente[i].getTip() << "-" << medicamente[i].getVolum() << ")->";
                    cout << "Disponibil";
                    ok = false;
                }
            if (ok == true)
            {
                cout << "Medicamentul introdus nu a fost gasit!";
            }
            cout << endl;
        }
        else
            cout << "Optiune invalida!" << endl;
    }
}

void medicamenteRezervate()
{
    system("cls");
    cout << endl << "-_-Medicamente Rezervate-_-" << endl << endl;
    int i;
    cout << "1. Cautare" << endl;
    cout << "0. Back" << endl << endl << endl;
    for (i = 0; i < nrMed; i++)
    {
        if (medicamente[i].getRezervat() == 1)
        {
            cout << "Nume: " << medicamente[i].getNume() << endl << "Tip: " << medicamente[i].getTip() << endl << "Volum/Nr. Comprimate: " << medicamente[i].getVolum() << endl;
            cout << "Rezervat";
            cout << endl << endl;
        }
    }
    if (globalArgc == 4)
        exit(0);
    int optiune;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        if (optiune == 0)
        {
            afisare();
            break;
        }
        if (optiune == 1)
        {
            int i;
            string nume;
            cout << endl;
            cout << "Introduceti numele medicamentului pe care doriti sa il cautati: ";
            cin.ignore();
            getline(cin, nume);
            bool ok = true;
            for (i = 0; i < nrMed; i++)
                if ((nume == medicamente[i].getNume()) && medicamente[i].getRezervat() == 1)
                {
                    if (ok == true)
                        cout << "Medicamentul a fost gasit: " << endl;
                    if (ok == false)
                        cout << endl;
                    cout << medicamente[i].getNume() << "(" << medicamente[i].getTip() << "-" << medicamente[i].getVolum() << ")->";
                    cout << "Rezervat";
                    ok = false;
                }
            if (ok == true)
            {
                cout << "Medicamentul introdus nu a fost gasit!";
            }
            cout << endl;

        }
        else
            cout << "Optiune invalida!" << endl;
    }

}

void rezervare()
{
    system("cls");
    cout << "-_-Rezervare-_-" << endl << endl;
    cout << "1. Rezervare medicament" << endl;
    cout << "0. Back" << endl << endl;
    /*citireMed(nrMed);*/
    int optiune;
    int ok = 0;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        cin.get();
        if (optiune == 0)
        {
            meniuUser();
            break;
        }
        if (optiune == 1)
        {
            string input;
            cout << "Introduceti numele medicamentului: ";
            getline(cin, input);
            for (int i = 0; i < nrMed; i++)
            {
                /*cout<<nrMed<<endl;
                cout << medicamente[i].getNume() << "----";*/
                if (input == medicamente[i].getNume())
                {
                    ok = 1;
                    if (medicamente[i].getRezervat() == 1)
                        cout << "Medicamentul este deja rezervat!" << endl;
                    else
                        if (medicamente[i].getRezervat() == 0)
                        {
                            medicamente[i].setRezervat(1);
                            cout << "Medicamentul " << medicamente[i].getNume() << " a fost rezervat cu succes!" << endl;
                            ofstream f("medicamente.txt");
                            f << nrMed << endl;
                            for (int i = 0; i < nrMed; i++)
                            {
                                f << medicamente[i];
                            }
                        }
                    break;

                }

            }
            if (ok != 1)
                cout << "Medicamentul nu a fost gasit!" << endl;
            if (globalArgc == 3)
                exit(0);

        }
        else
            cout << "Optiune invalida!" << endl;
    }


}

void anulareRezervare()
{
    system("cls");
    cout << "-_-Anulare Rezervare-_-" << endl << endl;
    cout << "1. Anulare rezervare medicament" << endl;
    cout << "0. Back" << endl << endl;

    int optiune;
    int ok = 0;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        cin.ignore();
        if (optiune == 0)
        {
            meniuUser();
            break;
        }
        if (optiune == 1)
        {
            string input;
            cout << "Introduceti numele medicamentului: ";
            getline(cin, input);
            for (int i = 0; i < nrMed; i++)
            {
                if (input == medicamente[i].getNume())
                {
                    ok = 1;
                    if (medicamente[i].getRezervat() == 0)
                        cout << "Medicamentul este disponibil!" << endl;
                    else
                        if (medicamente[i].getRezervat() == 1)
                        {
                            medicamente[i].setRezervat(0);
                            cout << "Rezervarea medicamentului " << medicamente[i].getNume() << " a fost anulata cu succes!" << endl;
                            ofstream f("medicamente.txt");
                            f << nrMed << endl;
                            for (int i = 0; i < nrMed; i++)
                            {
                                f << medicamente[i];
                            }
                        }
                    break;
                }

            }
            if (ok != 1)
                cout << "Medicamentul nu a fost gasit!" << endl;
            if (globalArgc == 3)
                exit(0);
        }
        else
            cout << "Optiune invalida!" << endl;
    }
}

void meniuAdminUser()
{
    system("cls");
    cout << "-_-Farmacie-_-";
    cout << endl << "-Selectare Cont-" << endl << endl;

    cout << "1. User" << endl;
    cout << "2. Admin" << endl;
    cout << "0. Iesire" << endl;

    int x;
    string input;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> x;
        if (x == 0)
        {
            exit(1);
            break;
        }
        if (x == 1)
        {
            meniuUser();
            break;
        }
        if (x == 2)
        {
            cout << "Introduceti parola: ";
            cin >> input;
            if (input == parola)
            {
                meniuAdmin();
                break;
            }
            else
                cout << "Parola incorecta!" << endl;
        }
        else
            cout << "Optiune invalida!" << endl;
    }
}

void meniuAdmin() {
    system("cls");
    cout << "-_-Meniu Admin-_-" << endl << endl;
    cout << "1. Adaugare medicament" << endl;
    cout << "2. Stergere" << endl;
    cout << "3. Comutare User" << endl;
    cout << "0. Iesire" << endl;

    int optiune;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        if (optiune == 0)
        {
            exit(1);
            break;
        }
        else if (optiune == 1)
        {
            cin.ignore();
            adaugare();
            break;
        }
        else if (optiune == 3)
        {
            meniuUser();
            break;
        }
        else if (optiune == 2)
        {
            stergere();
            break;
        }
        else
            cout << "Optiune invalida!" << endl;
    }
}

void meniuUser()
{
    system("cls");
    cout << "-_-Farmacie-_-" << endl << endl;
    cout << "1. Vizualizare medicamente" << endl;
    cout << "2. Rezervare medicamente" << endl;
    cout << "3. Anulare rezervare" << endl;
    cout << "4. Comutare Admin" << endl;
    cout << "0. Iesire" << endl;

    int optiune;
    string input;
    while (1)
    {
        cout << "Tasta introdusa: ";
        cin >> optiune;
        if (optiune == 0)
        {
            exit(1);
            break;
        }
        else if (optiune == 1)
        {
            afisare();
            break;
        }
        else if (optiune == 2)
        {
            rezervare();
            break;
        }
        else if (optiune == 3)
        {
            anulareRezervare();
            break;
        }
        else if (optiune == 4)
        {
            cout << "Introduceti parola: ";
            cin >> input;
            if (input == parola)
            {
                meniuAdmin();
                break;
            }
            else
                cout << "Parola incorecta!" << endl;
        }
        else
            cout << "Optiune invalida!" << endl;
    }
}

void citireMed(int n)
{
    for (int i = 0; i < n; i++)
        medicamente[i] = citire();
}


int main(int argc, char** argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
        FOREGROUND_GREEN);
    globalArgc = argc;

    char parolaChar[20] = "1234";
    f >> nrMed;
    f.get();
    citireMed(nrMed);

    if ((argc == 3) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "afisare") == 0)
        afisare();
    else if ((argc == 4) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "afisare") == 0 && strcmp(argv[3], "disponibile") == 0)
        medicamenteDisponibile();
    else if ((argc == 4) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "afisare") == 0 && strcmp(argv[3], "rezervate") == 0)
        medicamenteRezervate();
    else if ((argc == 3) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "rezervare") == 0)
        rezervare();
    else if ((argc == 3) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "anulareRezervare") == 0)
        anulareRezervare();
    else if ((argc == 3) && (strcmp(argv[1], "user") == 0) && strcmp(argv[2], "cautare") == 0)
        afisarePlusCautare();
    else if ((argc == 2) && (strcmp(argv[1], "user") == 0))
        meniuUser();
    else if ((argc == 3) && (strcmp(argv[1], "admin") == 0) && (strcmp(argv[2], parolaChar) == 0))
        meniuAdmin();
    else if ((argc == 4) && (strcmp(argv[1], "admin") == 0) && (strcmp(argv[2], parolaChar) == 0) && (strcmp(argv[3], "adaugare") == 0))
        adaugare();
    else if ((argc == 4) && (strcmp(argv[1], "admin") == 0) && (strcmp(argv[2], parolaChar) == 0) && (strcmp(argv[3], "stergere") == 0))
        stergere();
    else
        meniuAdminUser();

    return 0;
}