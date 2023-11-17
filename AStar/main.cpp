#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

class Coords {
    public:
        int y;
        int x;

    Coords (int y, int x) {
        this->y = y;
        this->x = x;
    }

};

float Obliczf(Coords currentNode, double** MapaRodzicow) {

    float g = 0;
    while (MapaRodzicow[currentNode.y][currentNode.x] <= 4 && MapaRodzicow[currentNode.y][currentNode.x] >= 1) {
                        if (MapaRodzicow[currentNode.y][currentNode.x] == 1) {
                            g += 1;
                            currentNode=Coords(currentNode.y-1, currentNode.x);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 2) {
                            g += 1;
                            currentNode=Coords(currentNode.y, currentNode.x+1);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 3) {
                            g += 1;
                            currentNode=Coords(currentNode.y+1, currentNode.x);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 4) {
                            g += 1;
                            currentNode= Coords(currentNode.y, currentNode.x-1);
                        }
                    }
    float h = sqrt(pow(currentNode.x-20, 2) + pow(currentNode.y-1, 2));
    return g + h;
    /*
    float g = sqrt(pow(currentNode.y - 20, 2) - pow(currentNode.x - 1, 2));
    float h = sqrt(pow(currentNode.x - 20, 2) - pow(currentNode.y -1, 2));
    return g + h;*/
}

int main(void) {

    /*
	Sposob poruszania sie do rodzicow:
	1 /\
    2 ->
	3 \/
	4 <-
	*/

	cout << "Wczytywanie danych z pliku\n";

	string nazwapliku = "grid.txt";
	int wymiar1 = 20;
	int wymiar2 = 20;

	//Deklarujemy dynamicznie tablice do wczytywania grid

	int rows = wymiar2 + 1;
	double** Mapa;
	Mapa = new double* [rows];
	while (rows--) Mapa[rows] = new double[wymiar1 + 1];

	std::ifstream plik(nazwapliku.c_str());
	for (int i = 1; i < wymiar2 + 1; i++) {
		for (int j = 1; j < wymiar1 + 1; j++) {
			plik >> Mapa[i][j];
		}
	}
	plik.close();

	cout << "\nWczytana tablica:\n\n";

	for (int i = 1; i < wymiar2 + 1; i++) {
		for (int j = 1; j < wymiar1 + 1; j++) {

			if (Mapa[i][j] == 5) {
				cout << " " << "\033[1;31m" << Mapa[i][j] << "\033[1;0m";
			}
			else if (Mapa[i][j] == 3) {
				cout << " " << "\033[1;32m" << Mapa[i][j] << "\033[1;0m";
			}
			else {
				cout << " " << "\033[1;34m" << Mapa[i][j] << "\033[1;0m";
			}
		}
		cout << "\n";
	}

	//tworzymy liste otwarta zawierajaca kratki brane pod uwage do ekpansji

    std::vector <Coords> listaOtwarta;

    	if (Mapa[20][1] != 5) {
		listaOtwarta.push_back(Coords(20, 1));
	}

	//tworzymy liste zamknieta z polem startowym, trafiaja tu pola odwiedzone, znikajace z listy otwartej

	std::vector <Coords> listaZamknieta;

	//tworzymy liste rodzicow do przechowywania kierunkow

    rows = wymiar2 + 1;
	double** MapaRodzicow;
	MapaRodzicow = new double* [rows];
	while (rows--) MapaRodzicow[rows] = new double[wymiar1 + 1];

	for (int i = 1; i < wymiar2 + 1; i++) {
		for (int j = 1; j < wymiar1 + 1; j++) {
			MapaRodzicow[i][j] = Mapa[i][j];
		}
	}

    while(listaOtwarta.empty() == 0) {
        int curLow = 0;
        for (unsigned int i = 0; i < listaOtwarta.size(); i++) {
            if (Obliczf(listaOtwarta.at(i), MapaRodzicow) < Obliczf(listaOtwarta.at(curLow), MapaRodzicow)) {
                curLow = i;
            }
        }

        Coords curNode = listaOtwarta.at(curLow);
        listaOtwarta.erase(listaOtwarta.begin() + curLow);
        listaZamknieta.push_back(curNode);

        //Spradzamy czy osiagnieto cel

        if (curNode.x == 20 && curNode.y == 1) {
            cout << "\nCel osiagniety.\n";

            Coords currentNode = curNode;
                Mapa[20][1] = 3;
                Mapa[1][20] = 3;
                for (int i = 1; i < 21; i++) {
                    }
                    while (MapaRodzicow[currentNode.y][currentNode.x] <= 4 && MapaRodzicow[currentNode.y][currentNode.x] >= 1) {
                        if (MapaRodzicow[currentNode.y][currentNode.x] == 1) {
                            Mapa[currentNode.y][currentNode.x] = 3;
                            currentNode=Coords(currentNode.y-1, currentNode.x);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 2) {
                            Mapa[currentNode.y][currentNode.x] = 3;
                            currentNode=Coords(currentNode.y, currentNode.x+1);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 3) {
                            Mapa[currentNode.y][currentNode.x] = 3;
                            currentNode=Coords(currentNode.y+1, currentNode.x);
                        }
                        else if (MapaRodzicow[currentNode.y][currentNode.x] == 4) {
                            Mapa[currentNode.y][currentNode.x] = 3;
                            currentNode= Coords(currentNode.y, currentNode.x-1);
                        }
                    }

                        cout << "\nWczytana tablica koncowa:\n\n";

                    for (int i = 1; i < 21; i++) {
                        for (int j = 1; j < 21; j++) {

                            if (Mapa[i][j] == 5) {
                                cout << " " << "\033[1;31m" << Mapa[i][j] << "\033[1;0m";
                            }
                            else if (Mapa[i][j] == 3) {
                                cout << " " << "\033[1;32m" << Mapa[i][j] << "\033[1;0m";
                            }
                            else {
                                cout << " " << "\033[1;34m" << Mapa[i][j] << "\033[1;0m";
                            }
                        }
                        cout << "\n";
                        }

                    return 0;
                }

        //sprawdzamy sasiadow aktualnego node'a

        // Lewo

        if (curNode.x - 1 > 0) {
            int inList = 0;
            for (unsigned int i = 0; i < listaZamknieta.size(); i++) {
                if (listaZamknieta.at(i).y == curNode.y && listaZamknieta.at(i).x == curNode.x-1) {
                    inList = 1;
                    break;
                }
            }
            for (unsigned int i = 0; i < listaOtwarta.size(); i++) {
                if (listaOtwarta.at(i).y == curNode.y && listaOtwarta.at(i).x == curNode.x-1) {
                    inList = 1;
                    break;
                }
            }

            if (inList == 0) {
                if (Mapa[curNode.y][curNode.x-1] == 5) {
                    listaZamknieta.push_back(Coords(curNode.y, curNode.x-1));
                }
                else {
                    listaOtwarta.push_back(Coords(curNode.y, curNode.x-1));
                    MapaRodzicow[curNode.y][curNode.x-1] = 2;
                    }
                }
            }

        // Gora

        if (curNode.y - 1 > 0) {
            int inList = 0;
            for (unsigned int i = 0; i < listaZamknieta.size(); i++) {
                if (listaZamknieta.at(i).y == curNode.y-1 && listaZamknieta.at(i).x == curNode.x) {
                    inList = 1;
                    break;
                }
            }
            for (unsigned int i = 0; i < listaOtwarta.size(); i++) {
                if (listaOtwarta.at(i).y == curNode.y-1 && listaOtwarta.at(i).x == curNode.x) {
                    inList = 1;
                    break;
                }
            }

            if (inList == 0) {
                if (Mapa[curNode.y-1][curNode.x] == 5) {
                    listaZamknieta.push_back(Coords(curNode.y-1, curNode.x));
                }
                else {
                    listaOtwarta.push_back(Coords(curNode.y-1, curNode.x));
                    MapaRodzicow[curNode.y-1][curNode.x] = 3;
                    }
                }
            }

        // Prawo

        if (curNode.x + 1 < 21) {
            int inList = 0;
            for (unsigned int i = 0; i < listaZamknieta.size(); i++) {
                if (listaZamknieta.at(i).y == curNode.y && listaZamknieta.at(i).x == curNode.x+1) {
                    inList = 1;
                    break;
                }
            }
            for (unsigned int i = 0; i < listaOtwarta.size(); i++) {
                if (listaOtwarta.at(i).y == curNode.y && listaOtwarta.at(i).x == curNode.x+1) {
                    inList = 1;
                    break;
                }
            }

            if (inList == 0) {
                if (Mapa[curNode.y][curNode.x+1] == 5) {
                    listaZamknieta.push_back(Coords(curNode.y, curNode.x+1));
                }
                else {
                    listaOtwarta.push_back(Coords(curNode.y, curNode.x+1));
                    MapaRodzicow[curNode.y][curNode.x+1] = 4;
                    }
                }
            }

        // Dol

        if (curNode.y + 1 < 21) {
            int inList = 0;
            for (unsigned int i = 0; i < listaZamknieta.size(); i++) {
                if (listaZamknieta.at(i).y == curNode.y+1 && listaZamknieta.at(i).x == curNode.x) {
                    inList = 1;
                    break;
                }
            }
            for (unsigned int i = 0; i < listaOtwarta.size(); i++) {
                if (listaOtwarta.at(i).y == curNode.y+1 && listaOtwarta.at(i).x == curNode.x) {
                    inList = 1;
                    break;
                }
            }

            if (inList == 0) {
                if (Mapa[curNode.y+1][curNode.x] == 5) {
                    listaZamknieta.push_back(Coords(curNode.y+1, curNode.x));
                }
                else {
                    listaOtwarta.push_back(Coords(curNode.y+1, curNode.x));
                    MapaRodzicow[curNode.y+1][curNode.x] = 1;
                    }
                }
            }
        }


	//na koniec czyscimy pamiec po naszej tablicy

	for (int i = 0; i < wymiar2 + 1; i++) {
		delete[] Mapa[i]; // czyscimy wiersze
	}
	delete[] Mapa; //zwalniamy tablice wskaznikow do wierszy

	for (int i = 0; i < wymiar2 + 1; i++) {
		delete[] MapaRodzicow[i]; // czyscimy wiersze
	}
	delete[] MapaRodzicow; //zwalniamy tablice wskaznikow do wierszy

	cout << "Nie znaleziono drogi.";
	return 0;
}
