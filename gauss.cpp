#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void print_system(vector<vector<double> > &system) {
    unsigned int n = system.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < system[i].size(); ++j) {
            cout << system[i][j] << ' ';
        }
        cout << endl;
    }
}

vector<double> gauss(vector<vector<double> > system) {
    double max_element, max_row, coefficient;
    unsigned int n = system.size();
    vector<double> result(n);

    for (size_t i = 0; i < n; ++i) {
        max_element = system[i][i];
        max_row = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (system[j][i] > max_element) {
                max_element = system[j][i];
                max_row = j;
            }
        }

        for (size_t j = i; j < n + 1; ++j) {
            swap(system[max_row][j], system[i][j]);
        }

        for (size_t j = i + 1; j < n; ++j) {
            coefficient = -system[j][i]/system[i][i];

            for (size_t k = i; k < n + 1; ++k) {
                if (i == k) {
                    system[j][k] = 0;
                } else {
                    system[j][k] += coefficient * system[i][k];
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        result[i] = system[i][n]/system[i][i];
        for (int j = i - 1; j >= 0; --j) {
            system[j][n] -= system[j][i] * result[i];
        }
    }

    return result;
}

int main() {
    int n = 3;
    vector<double> result;

    vector<vector<double> > system(n, vector<double>(n + 1));

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < 10; ++z) {
                int input[3][4] = {
                    {(x + y), x, 0, 57},
                    {y, (x + z), 0, 82},
                    {0, z, y, 230}
                };

                for (size_t i = 0; i < n; ++i) {
                    for (size_t j = 0; j < n + 1; ++j) {
                        system[i][j] = input[i][j];
                    }
                }

                result = gauss(system);

                cout << "tano: " << x << ' ' << "bere: " << y << ' ' << "tato: " << z << endl;
                cout << "i: " << result[0] << ' ' << "e: " << result[1] << ' ' << "a: " << result[2] << endl;
                cout << endl;
            }
        }
    }
}
