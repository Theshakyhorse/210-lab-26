// COMSC-210 | Lab 26 | Alexander Sierra
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
using namespace std;
using namespace std::chrono;

const int W = 20, OPS = 4, STRUCTS = 3, runs = 15;

void V_sort(vector<string>&);
void L_insert(list<string>&);
void L_delete(list<string>&);
void S_delete(set<string>&);

int main() {
    vector<string> vectors;
    list<string> lists;
    set<string> sets;
    int data[2][OPS][STRUCTS];

    string t;
    ifstream fin ("codes.txt");
    ifstream fin2 ("codes.txt");
    ifstream fin3 ("codes.txt");

    //cout << setw(W) << "Operation"; 
    //cout << setw(W) << "Vector";
    //cout << setw(W) << "List";
    //cout << setw(W) << "Set";

    //cout << endl;
    //cout << setw(W) << "Read"; will do output later

    //Reading
    for (int run = 0; run < runs; run++) {
        if (fin.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin, t)){
                vectors.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][0] = duration.count();
            data[1][0][0] += data[0][0][0];
        }
        
    }

    for (int run = 0; run < runs; run++) {
        if (fin2.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin2, t)){
                lists.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][1] = duration.count();
            data[1][0][1] += data[0][0][1];
        }
        
    }

    for (int run = 0; run < runs; run++) {
        if (fin3.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin3, t)){
                sets.insert(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][2] = duration.count();
            data[1][0][2] += data[0][0][2];
        }
       
    }

    //sorting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        V_sort(vectors);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][1][0] = duration.count();
        data[1][1][0] += data[0][1][0];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        lists.sort();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][1][1] = duration.count();
        data[1][1][1] += data[0][1][1];
    }
    
    for (int run = 0; run < runs; run++) {
        data[0][1][2] = -1; //because it is a set
        data[1][1][2] += data[0][1][2];
    }

    //inserting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        vectors.insert(vectors.begin()+(vectors.size()/2), "TESTCODE");
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][2][0] = duration.count();
        accum[2][0] += data[run][2][0];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        L_insert(lists);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][2][1] = duration.count();
        accum[2][1] += data[run][2][1];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        sets.insert("TESTCODE");
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][2][2] = duration.count();
        accum[2][2] += data[run][2][2];
    }

    //deleting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        vectors.erase(vectors.begin()+(vectors.size()/2));
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][3][0] = duration.count();
        accum[3][0] += data[run][3][0];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        L_delete(lists);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][3][1] = duration.count();
        accum[3][1] += data[run][3][1];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        S_delete(sets);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][3][2] = duration.count();
        accum[3][2] += data[run][3][2];
    }

    return 0;
}

//sorts a vector
void V_sort(vector<string>& vectors){
    for (int i = 0; i < vectors.size(); i++) {
        for (int j = 0; j < vectors.size() - 1; j++) {
            if (vectors.at(j) > vectors.at(j + 1)) {
                string temp = vectors.at(j);
                vectors.at(j) = vectors.at(j + 1);
                vectors.at(j + 1) = temp;
            }
        }
    }
}

//inserts "TESTCODE" into middle of list
void L_insert(list<string>& lists) {
    int i = 1;
    for (auto it = lists.begin(); it != lists.end();) {
        if ((lists.size()/2) == i) {
            lists.insert(it, "TESTCODE");
            break;
        } else {
            ++it;
            ++i;
        }
    }  
}

//deletes middle of list
void L_delete(list<string>& lists) {
    int i = 1;
    for (auto it = lists.begin(); it != lists.end();) {
        if ((lists.size()/2) == i) {
            it = lists.erase(it);
        } 
        else {
            ++it;
        }
        ++i;
    }  
}

//deletes middle of set
void S_delete(set<string>& sets) {
    int i = 1;
    for (auto it = sets.begin(); it != sets.end();) {
        if ((sets.size()/2) == i) {
            it = sets.erase(it);
        } 
        else {
            ++it;
        }
        ++i;
    }  
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/