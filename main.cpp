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
    int data[runs][OPS][STRUCTS];
    int accum[OPS][STRUCTS];

    string t;
    ifstream fin ("codes.txt");
    ifstream fin2 ("codes.txt");
    ifstream fin3 ("codes.txt");

    cout << setw(W) << "Operation"; 
    cout << setw(W) << "Vector";
    cout << setw(W) << "List";
    cout << setw(W) << "Set";

    cout << endl;
    cout << setw(W) << "Read"; // will do output later

    //Reading
    for (int run = 0; run < runs; run++) {
        if (fin.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin, t)){
                vectors.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[run][0][0] = duration.count();
            accum[0][0] += data[run][0][0];
        }
        fin.close();
    }

    for (int run = 0; run < runs; run++) {
        if (fin2.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin2, t)){
                lists.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[run][0][1] = duration.count();
            accum[0][1] += data[run][0][1];
        }
        fin2.close();
    }

    for (int run = 0; run < runs; run++) {
        if (fin3.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin3, t)){
                sets.insert(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[run][0][2] = duration.count();
            accum[0][2] += data[run][0][2];
        }
        fin3.close();
    }

    //sorting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        V_sort(vectors);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][1][0] = duration.count();
        accum[1][0] += data[run][1][0];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        lists.sort();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[run][1][1] = duration.count();
        accum[1][1] += data[run][1][1];
    }
    
    for (int run = 0; run < runs; run++) {
        data[run][1][2] = -1; // because it is a set
        accum[1][2] += data[run][1][2];
    }

    //inserting
    auto four = high_resolution_clock::now();
    vectors.insert(vectors.begin()+(vectors.size()/2), "TESTCODE");
    auto five = high_resolution_clock::now();
    auto six = duration_cast<nanoseconds>(five - four);
    cout << setw(W) << six.count();

    auto seven = high_resolution_clock::now();
    L_insert(lists);
    auto eight = high_resolution_clock::now();
    auto nine = duration_cast<nanoseconds>(eight - seven);
    cout << setw(W) << nine.count();

    auto one = high_resolution_clock::now();
    sets.insert("TESTCODE");
    auto two = high_resolution_clock::now();
    auto three = duration_cast<nanoseconds>(two - one);
    cout << setw(W) << three.count() << endl << setw(W) << "Delete";

    //deleting
    auto ten = high_resolution_clock::now();
    vectors.erase(vectors.begin()+(vectors.size()/2));
    auto eleven = high_resolution_clock::now();
    auto twelve = duration_cast<nanoseconds>(eleven - ten);
    cout << setw(W) << twelve.count();

    auto thirteen = high_resolution_clock::now();
    L_delete(lists);
    auto fourteen = high_resolution_clock::now();
    auto fifteen = duration_cast<nanoseconds>(fourteen - thirteen);
    cout << setw(W) << fifteen.count();

    auto sixteen = high_resolution_clock::now();
    S_delete(sets);
    auto seventeen = high_resolution_clock::now();
    auto eighteen = duration_cast<nanoseconds>(seventeen - sixteen);
    cout << setw(W) << eighteen.count() << endl;

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