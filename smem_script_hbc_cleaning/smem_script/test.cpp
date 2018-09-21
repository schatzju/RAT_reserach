#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <vector>

using namespace std;

bool find_vect(vector<int> vec, int item){
    
    int half = vec.size()/2;
    
    if(vec[half] == item){
        return true;
    }
    
    if(vec.size() == 1) return false;
    
    if(vec[half] > item){
        return find_vect(vector<int>(vec.begin(), vec.begin()+ half), item);
    }
    if(vec[half] < item){
        return find_vect(vector<int>(vec.begin()+ half, vec.end()), item);
    }
    
    return false;
}

int main(){
    vector<int> vec = {1, 3, 6};
    
    cout << find_vect(vec, 1) << endl;
    cout << find_vect(vec, 3) << endl;
    cout << find_vect(vec, 6) << endl;
    cout << find_vect(vec, 7) << endl;
    cout << find_vect(vec, 0) << endl;
    cout << find_vect(vec, 2) << endl;
    cout << find_vect(vec, 4) << endl;
    
    cout << endl;
    
    vector<int> vec2 = {1, 3, 6, 8};
    
    cout << find_vect(vec2, 1) << endl;
    cout << find_vect(vec2, 3) << endl;
    cout << find_vect(vec2, 6) << endl;
    cout << find_vect(vec2, 8) << endl;
    cout << find_vect(vec2, 7) << endl;
    cout << find_vect(vec2, 0) << endl;
    cout << find_vect(vec2, 2) << endl;
    cout << find_vect(vec2, 4) << endl;
    cout << find_vect(vec2, 9) << endl;



}
