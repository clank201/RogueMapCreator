#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <math.h>
//falta perlin
using namespace std;
void clearscreen()//codirobat per evitar flickers
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void cleanMap(char map[100][100][100]) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 100; k++) {
				map[i][j][k] = 0;
			}
		}
	}
}
void showMap(char map[100][100][100], int height) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			cout << (int)map[j][i][height];
		}
		cout << endl;
	}
}
void saveMap(char map[100][100][100], int x, int y, int z) {

	ofstream file;
	string filename = "terrain.";
	filename = (filename + to_string(x) + '.' + to_string(y) + '.' + to_string(z));
	file.open(filename);
	char current = 255;
	int num = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 100; k++) {
				if ((int)map[i][j][k] != current) {
					file << (int)current << ' ' << num << endl;
					current = (int)map[i][j][k];
					num = 1;
				}
				else num++;
			}
		}
	}
	file << (int)current << ' ' << num << endl;
}

int main() {
	srand(time(NULL));
	char map[100][100][100];
	int height = 5;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				ofstream file;
				string filename = "terrain.";
				filename = (filename + to_string(i) + '.' + to_string(j) + '.' + to_string(k));
				file.open(filename);
				if (k < height) {
					file << 1 << ' ' << 1000000 << endl;
					file.close();
				}
				else if (k == height) {
					for (int l = 0; l < 100; l++) {
						for (int m = 0; m < 100; m++) {
							for (int n = 0; n < 100; n++) {
								file.open(filename);
								if (n < 50) {
									map[l][m][n] = 1;
								}
								else if (n == 50) {
									int bloc = rand() % 7;
									if (bloc == 1) { bloc++; }
									else bloc = 0;
									map[l][m][n] = bloc;
								}
								else {
									map[l][m][n] = 0;
								}
							}
						}
					}
					saveMap(map, i, j, k);
				}
				else {
					file << 0 << ' ' << 1000000 << endl;
					file.close();
				}
			}
		}
	}
}