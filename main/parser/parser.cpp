#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

/*
    Functia returneaza o matrice cu doua randuri
    conform fiecarui fisier CSV dat
*/
vector<vector<double>> parse_thr(string fname) {
    vector<vector<string>> content;
    vector<string> row;

    vector<vector<double>> thresholds;
    vector<double> d_numbers;

    string line, word;
    double temp_double = 0;

    fstream file (fname, ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            
            stringstream str(line);
            
            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    } else {
        cout << "Could not open the file\n";
    }
    
    for(int i = 0; i < content.size(); i++) {
        d_numbers.clear();
        for(int j = 0; j < content[i].size(); j++) {
            // Acest atof pierde din precizie din ce am vazut, puteti decomenta 41 ca sa vedeti
            temp_double = atof(content[i][j].c_str());
            // cout << content[i][j] << " --> " << temp_double << "\n";
            d_numbers.push_back(temp_double);
        }
        thresholds.push_back(d_numbers);
    }

    return thresholds;
}

void get_max(double &max_alg, double &max_Fmeasure,
    vector<vector<double>> thresholds) {
        double temp_double = 0;

        for (int j = 0; j < thresholds[0].size(); ++j) {
            temp_double = floor(thresholds[0][j] * 255);

            if (thresholds[1][temp_double] > max_Fmeasure) {
                max_Fmeasure = thresholds[1][temp_double];
                max_alg = thresholds[0][j];
            }
        }
    }

int main() {
    string fname = "[AVE_INT] 2_1.CSV";
    
    double temp_double, max_Fmeasure = 0, max_alg = 0;
 
    vector<vector<double>> thresholds = parse_thr(fname);

    get_max(max_alg, max_Fmeasure, thresholds);

    cout << "max_alg = " << max_alg << "\n";
    cout << "max_Fmeasure = " << max_Fmeasure << "\n";

    return 0;
}
