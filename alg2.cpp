//
// Created by Tong Su on 8/12/18.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool my_knapsake(vector<int> v, int w, int in)
{
    if(w==0){
        return true;
    }
    if(w<0 || in >= v.size()) {
        return false;
    }
    return my_knapsake(v, w, in+1) || my_knapsake(v, w-v[in], in+1);   //equivalent sub_question
}

int main() {
    vector<int> k{2,3,4,5};
    int val=13;
    cout<<my_knapsake(k,val,0)<<endl;
}
