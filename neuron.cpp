#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

class Perceptron {

public:
	int wymiar;
	int liczbaWejsc;
	int liczbaIteracji;
	double **wejscia;
	double *wyniki;
	double *wagi;
	double wspUczenia = 1;
	double eta;
	double obliczWartosc(double suma);
	void losujWagi();
	void uczPerceptron();
	void test(int p, int q);
	Perceptron();
};


Perceptron::Perceptron() {

	fstream plik;
	plik.open("zbior_uczacy1.txt");
	
	if (plik.good())
	{
		string linijka;
		getline(plik, linijka);
		wymiar = atoi(linijka.c_str());
		liczbaWejsc = 2;
		wejscia = new double*[liczbaWejsc];
		for (int i = 0;i < liczbaWejsc;i++)
			wejscia[i] = new double[wymiar];

		wyniki = new double[wymiar];
		wagi = new double[liczbaWejsc];

		int licznik = 0;
		while (getline(plik, linijka))  
		{
			wejscia[0][licznik] = atoi(linijka.substr(0, linijka.find_first_of(' ')).c_str());
			linijka = linijka.substr(linijka.find_first_of(' ') + 1, linijka.length());
			wejscia[1][licznik] = atoi(linijka.substr(0, linijka.find_first_of(' ')).c_str());
			linijka = linijka.substr(linijka.find_first_of(' ') + 1, linijka.length());
			wyniki[licznik] = atoi(linijka.c_str());
			cout  << wejscia[0][licznik] << "  " << wejscia[1][licznik] << "  " << wyniki[licznik] << endl;
			licznik++;
		}
		plik.close();
	}
	else
	{
		cout << "blad otwarcia pliku!";
	}
}

double Perceptron::obliczWartosc(double suma) {

	if (suma > eta)
		return 1;
	else
		return 0;
}

void Perceptron::losujWagi() {
	
	for(int i=0; i<liczbaWejsc; i++)
		wagi[i]= -10 + (double)rand() /RAND_MAX* (20);
		cout << wagi[0] << wagi[1] << endl;
}

void Perceptron::test(int p, int q)
{
	double wynik= p * wagi[0] + q * wagi[1];
	cout << p << " ^ " << q << " = " << obliczWartosc(wynik) << endl;
}

void Perceptron::uczPerceptron() {

	losujWagi();
	double licznikBledow = 0;
	double y = 0;
	double blad = 0;
	liczbaIteracji = 1000000;

	for (int i = 0; i < liczbaIteracji; i++)
	{
		licznikBledow = 0;
		for (int j = 0; j < wymiar; j++)
		{
			y = wejscia[0][j]*wagi[0]+wejscia[1][j]*wagi[1];
		
			if (wyniki[j] != obliczWartosc(y))
			{
				blad = wyniki[j] - obliczWartosc(y);
				wagi[0] = wagi[0] + wspUczenia*blad * wejscia[0][j];
				wagi[1]= wagi[1] + wspUczenia*blad * wejscia[1][j];
				eta = eta - blad;
				licznikBledow++;
			}
		}
		if (licznikBledow == 0)
		{
			cout << "Liczba potrzebnych iteracji:" <<  i+1 << endl;
           break;
		}
	}
	cout << "Perceptron nauczony :-)" << endl;
	cout << "Uzyskane wagi to: " << "w[0]: " << wagi[0] << " w[1]: " << wagi[1] << " eta: " << eta << endl;
	test(1, 1);
	test(0, 1);
	test(1, 0);
	test(0, 0);
}

int main()
{
	srand(time(NULL));
	Perceptron przykladowy;
	przykladowy.uczPerceptron();
	getchar();
}