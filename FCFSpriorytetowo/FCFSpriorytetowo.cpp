#include <iostream>
#include <fstream>
using namespace std;

const int wiersze = 4;
const int kolumny = 15;
int proces[wiersze][kolumny]; // Tablica danych testowych procesow
int czasOczekiwania[kolumny];
int czasZakonczenia[kolumny];
int kwantCzasu,taktCzasu = 0,postarzanie = 0,liczbaWczytanychProcesow = 0,sumaCzasowPrzybycia = 0,procesyPrzybyle = 0;
int procesKopia[wiersze][kolumny];
int wyswietlWynik[wiersze-1][kolumny];
bool czyPostarzony = false;

int main() {
    ifstream plik("dane.txt"); // Otwiera plik do odczytu
    for (int i = 0; i < wiersze-1; i++) {
        for (int j = 0; j < kolumny; j++) plik >> proces[i][j];   // Wczytuje kolejną liczbę z pliku do tablicy
    }
    plik >> kwantCzasu; // Wczytanie 4 linii z pliku do zmiennej
    plik.close();   // Zamyka plik
    for (int i = 0; i < kolumny; i++) proces[3][i] = i; // Utworzenie wiersza indeksow, aby mozna bylo utworzyc tablice do wyswietlania wynikow
    while(liczbaWczytanychProcesow < kolumny){ // Glowna petla algorytmu
        if(liczbaWczytanychProcesow > 0){ // Pominiecie pierwszej iteracji
            for (int j = procesyPrzybyle; j < kolumny; j++) { // Okreslenie ile procesow przybylo w danym takcie czasu
                if(sumaCzasowPrzybycia <= taktCzasu && proces [0][j] <= taktCzasu && sumaCzasowPrzybycia + proces [0][j] <= taktCzasu){
                    if(sumaCzasowPrzybycia != taktCzasu) sumaCzasowPrzybycia += proces [0][j];
                    procesyPrzybyle = j;
                }
            cout << "Suma Czasow przybycia = " << sumaCzasowPrzybycia << " Procesy przybyle = " << procesyPrzybyle << " taktCzasu = " << taktCzasu << " Postarzanie = " << postarzanie << endl; 
            }
            for (int i = 0; i < kolumny; i++) { // Decyzja czy zmienic priorytety
                if(taktCzasu - proces[0][i] - postarzanie >= kwantCzasu && proces[2][i] > 0 && procesyPrzybyle >= i){ 
                    proces[2][i] -= 1;
                    czyPostarzony = true;
                }
                if(czyPostarzony){
                    postarzanie += kwantCzasu;
                    czyPostarzony = false;
                }
            }
        }
        for (int i = 0; i < wiersze; i++) { // Tworzenie kopii tablicy proces
            for (int j = 0; j < kolumny; j++) procesKopia[i][j] = proces[i][j];
        }
        for (int i = 0; i < kolumny - 1; i++) { // Sortowanie procesów według priotytetow w kopii tablicy
            for (int j = 0; j < kolumny - i - 1; j++) {
                if (procesKopia[0][j] == procesKopia[0][j + 1]) {
                    if (procesKopia[2][j] > procesKopia[2][j + 1]) {
                        for (int k = 0; k < wiersze; k++) swap(procesKopia[k][j], procesKopia[k][j + 1]);
                        }}}}
        for (int i = 0; i < wiersze; i++) { // cout
            for (int j = 0; j < kolumny; j++) cout << procesKopia[i][j] << " ";
            cout << endl;
            }
        for (int i = liczbaWczytanychProcesow; i < kolumny; i++) { // Petla decydujaca ktory proces przeznaczyc do wykonania
            taktCzasu += procesKopia[1][i]; // Modyfikacja taktuCzasu o czas wykonania procesu
            czasZakonczenia[i] = taktCzasu; // Zapisanie czasu zakonczenia procesu
            czasOczekiwania[i] = czasZakonczenia[i] - procesKopia[0][i] - procesKopia[1][i]; // Zapisanie czasu oczekiwania procesu
            liczbaWczytanychProcesow++;
            wyswietlWynik[0][procesKopia[3][i]] = czasOczekiwania[i]; // Zapisywanie danych do tablicy,
            wyswietlWynik[1][procesKopia[3][i]] = czasZakonczenia[i]; // dzieki ktorej wyswietlone zostana wyniki
            if(taktCzasu >= postarzanie) break; // Warunek wykonania nastepnej iteracji petli for
        }
    }
    for (int i = 0; i < kolumny; i++) cout << "Proces " << i+1 << ": czas oczekiwania = " << wyswietlWynik[0][i] << ", czas zakończenia = " << wyswietlWynik[1][i] << endl;
    double sredniCzasOczekiwania = 0;
    for (int i = 0; i < kolumny; i++) sredniCzasOczekiwania += czasOczekiwania[i];
    sredniCzasOczekiwania /= kolumny;
    cout << "Sredni czas oczekiwania dla algorytmu FCFS priorytetowo: " << sredniCzasOczekiwania << endl; // Wyswietlenie sredniego czasu oczekiwania procesu
    ofstream plikk; // Przesyla raport programu do pliku
    plikk.open("wynikFCFSpriorytetowo.txt");
    plikk << "Sredni czas oczekiwania dla metody FCFSpriorytetowo: " << sredniCzasOczekiwania << endl;
    plikk.close();
    return 0;
}