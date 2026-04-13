// COMSC-210 | Lab 26 | Alexander Sierra
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const int W = 20, OPS = 4, STRUCTS = 3, runs = 15;

void V_sort(vector<string>&);
void V_insert(vector<string>&);
void V_delete(vector<string>&);
void L_sort(list<string>&);
void L_insert(list<string>&);
void L_delete(list<string>&);
void S_insert(set<string>&);
void S_delete(set<string>&);

int main() {
    vector<string> vectors;
    list<string> lists;
    set<string> sets;
    int data[2][OPS][STRUCTS]= {0}; 
    //operation 1=read, 2=sort, 3=insert, 4=delete
    //struct 1=vector, 2=list, 3=set
    string t;

    //Reading
    for (int run = 0; run < runs; run++) {
        //each operation will be looped for runs times
        ifstream fin ("codes.txt");
        vectors.clear();
        if (fin.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin, t)){
                vectors.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][0] = duration.count(); //stores current timing
            data[1][0][0] += data[0][0][0]; //acumulates timings
            //this layout of looping the operation runs times then storing current timing
            //and accumulating the timing is the same for all operations except set sorting
        }
        fin.close();
    }

    for (int run = 0; run < runs; run++) {
        ifstream fin ("codes.txt");
        lists.clear();
        if (fin.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin, t)){
                lists.push_back(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][1] = duration.count();
            data[1][0][1] += data[0][0][1];
        }
        fin.close();
    }

    for (int run = 0; run < runs; run++) {
        ifstream fin ("codes.txt");
        sets.clear();
        if (fin.good()){
            auto start = high_resolution_clock::now();
            while (getline(fin, t)){
                sets.insert(t);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            data[0][0][2] = duration.count();
            data[1][0][2] += data[0][0][2];
        }
        fin.close();
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
        L_sort(lists);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][1][1] = duration.count();
        data[1][1][1] += data[0][1][1];
    }
    
    data[0][1][2] = 0; //because it is a set
    data[1][1][2] = 0;
    

    //inserting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        V_insert(vectors);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][2][0] = duration.count();
        data[1][2][0] += data[0][2][0]; 
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        L_insert(lists);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][2][1] = duration.count();
        data[1][2][1] += data[0][2][1];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        S_insert(sets);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][2][2] = duration.count();
        data[1][2][2] += data[0][2][2];
    }

    //deleting
    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        V_delete(vectors);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][3][0] = duration.count();
        data[1][3][0] += data[0][3][0];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        L_delete(lists);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][3][1] = duration.count();
        data[1][3][1] += data[0][3][1];
    }

    for (int run = 0; run < runs; run++) {
        auto start = high_resolution_clock::now();
        S_delete(sets);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        data[0][3][2] = duration.count();
        data[1][3][2] += data[0][3][2];
    }

    //output
    cout << "Number of simulations: " << runs << endl;
    cout << setw(W) << "Operation" << setw(W) << "Vector";
    cout << setw(W) << "List" << setw(W) << "Set" << endl;
    for (int i = 0; i < OPS; i++) {
        if (i==0){
            cout << setw(W) << "Read";
        }
        if (i==1){
            cout << setw(W) << "Sort";
        }
        if (i==2){
            cout << setw(W) << "Insert";
        }
        if (i==3){
            cout << setw(W) << "Delete";
        }
        for (int j = 0; j < STRUCTS; j++) {
            cout << setw(W) << data[1][i][j]/runs;
        }
        cout << endl;
    }

    return 0;
}

//sorts a vector
void V_sort(vector<string>& vectors){
    sort(vectors.begin(), vectors.end());
}

//inserts TESTCODE in the middle of a vector
void V_insert(vector<string>& vectors){
    vectors.insert(vectors.begin()+(vectors.size()/2), "TESTCODE");
}

//deletes middle element of a vector
void V_delete(vector<string>& vectors){
    vectors.erase(vectors.begin()+(vectors.size()/2));
}

//sorts a list
void L_sort(list<string>& lists){
    lists.sort();
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

//inserts TESTCODE into a set
void S_insert(set<string>& sets) {
    sets.insert("TESTCODE");
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