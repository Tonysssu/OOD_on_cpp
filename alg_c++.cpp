//
// Created by Tong Su on 8/12/18.
//

//#include <iostream>
//#include <string>
//#include <vector>
//#include "leanring_alg.h"
//using namespace std;
//
//void helper(int a, vector<int> & temp){
//    if (a == 0){
//        temp.push_back(0);
//        return;
//    }
//    helper(a-1,temp);
//    int len = temp.size();
//    int k = len;
//    for (int i=len-1; i>=0; i--) {
//        temp.push_back(temp[i] + k);
//    }
//}
//
//vector<int> my_gray(int n){
//    vector<int> result;
//    helper(n,result);
//    return result;
//}
//
//int main() {
//    vector<int> a;
//    a = my_gray(3);
////    for (auto iti=a.begin();iti!=a.end();++iti){
////        cout<<*iti<<endl;
////    }
//    for (auto it:a){
//        cout<<it<<endl;
//    }
//}