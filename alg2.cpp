//
// Created by Tong Su on 8/12/18.
//
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <list>

using namespace std;


//case
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


//comb1
void my_comb(vector<int> num, vector<vector<int>> &res, vector<int> &cu,int index){
    if(index==num.size()){
        res.push_back(cu);
        return;
    }
    my_comb(num, res, cu, index+1);
    cu.push_back(num[index]);
    my_comb(num, res,cu, index+1);
    cu.pop_back();
}

vector<vector<int>> combin(vector<int> numlist){
    vector<vector<int>> result;
    vector<int> cur;
    int ind=0;
    my_comb(numlist,result,cur,ind);
    return result;
}

//Maze
bool my_maze(vector<vector<char>> a, int Bx, int By, int StartX, int StartY, int TargetX, int TargetY, vector<string> path){
    if (StartX == TargetX && StartY==TargetY){
        for (auto te:path){
            cout<<te<<endl;
        }
        return true;
    }
    if (StartX <0 || StartX > Bx-1 || StartY<0 || StartY> By-1 || a[StartX][StartY] =='X'){
        return false;
    }
    a[StartX][StartY]='X';
    int dx[4]{0,0,-1,1};
    int dy[4]{-1,1,0,0};
    vector<string> dir{"up","down","left","right"};

    for (auto i=0; i<5; i++) {
        path.push_back(dir[i]);
        if (my_maze(a, Bx, By, StartX + dy[i], StartY + dx[i], TargetX, TargetY, path)) {
            return true;
        }
        path.pop_back();
    }
    return false;
}

//permutation1
void permut(vector<int> nums,vector<vector<int>> &result, vector<int> &cur) {
    if (cur.size()==nums.size()){
        result.push_back(cur);
        return;
    }
    for (int i=0; i<nums.size();i++){
        if(find(cur.begin(), cur.end(), nums[i])!= cur.end()){
            continue;
        }
        cur.push_back(nums[i]);
        permut(nums,result,cur);
        cur.pop_back();
    }
}

vector<vector<int>> permutation(vector<int> numlist){
    vector<vector<int>> results;
    sort(numlist.begin(),numlist.end());
    vector<int> c;
    permut(numlist,results, c);
    return results;
}


//permutation2
void pmt(vector<int> &num, vector<vector<int>> &res, int n){
    if (n==num.size()){
        res.push_back(num);
        return;
    }
    for (int i=n;i<num.size();i++){
        swap(num[i],num[n]);
        pmt(num, res, n+1);
        swap(num[n],num[i]);
    }

}

vector<vector<int>> permutations(vector<int> numlist){
    vector<vector<int>> results;
    sort(numlist.begin(),numlist.end());
    int c=0;
    pmt(numlist,results, c);
    return results;
}

//
//comnb2 [poor]
void cbn(vector<int> numlist, vector<vector<int>> &res, vector<int> &cur,int id, int index){
    if (cur.size()==id){
        res.push_back(cur);
        return;
    }

    for (int pt=index; pt<numlist.size(); pt++) {
        if(find(cur.begin(), cur.end(), numlist[pt])!= cur.end()){
            continue;
        }
        cur.push_back(numlist[pt]);
        cbn(numlist, res, cur, id, index + 1);
        cur.pop_back();
    }
}

vector<vector<vector<int>>> combination(vector<int> num){
    vector<vector<vector<int>>> part;
    int kn = num.size();
    int in=0;
    for (int i =0;i<=kn;i++){
        vector<vector<int>> results;
        vector<int> c;
        cbn(num,results,c,i,in);
        part.push_back(results);
    }
    return part;
}

//permutation3 [repeat use allow]
void pem3(vector<int> numlist, vector<vector<int>> &res, vector<int> &cur,vector<bool> visited){
    if (cur.size()==numlist.size()){
        res.push_back(cur);
    }
    for (int i=0;i < numlist.size();i++) {
        if (visited[i]) {
            continue;
        }
        else if(numlist[i]==numlist[i-1] && !visited[i-1] &&!visited[i]){
            continue;
        }
        else{
            cur.push_back(numlist[i]);
            visited[i] = true;
            pem3(numlist, res, cur, visited);
            cur.pop_back();
            visited[i] = false;
        }
    }

}

vector<vector<int>> my_pem3use(vector<int> nums){
    sort(nums.begin(),nums.end());
    vector<vector<int>> result;
    vector<int> c;
    vector<bool> in(nums.size(), false);
    pem3(nums,result,c,in);
    return result;
}




int main() {
//    vector<int> k{2,3,4,5};
//    int val=13;
//    cout<<my_knapsake(k,val,0)<<endl;
//    char a[2][2]={{'.','X'},{'.','X'}};
//    cout<<*a<<endl;


//    vector<vector<char>> maze{{'.', 'X', '.', '.', '.', 'X'},
//                              {'.', '.', '.', 'X', '.', 'X'},
//                              {'X', 'X', '.', 'X', '.', '.'},
//                              {'.', 'X', 'X', 'X', '.', 'X'},
//                              {'X', '.', '.', '.', '.', 'X'},
//                              {'.', '.', '.', '.', '.', '.'}};
//    int startx = 0, starty = 0, targetx=5, targety = 5;
//    int Bx = maze.size();
//    int By = maze[0].size();
//    vector<string> p;
//    if (my_maze(maze, Bx, By, startx, starty, targetx, targety,p)){
//        cout<<1<<endl;
//    }
//    else{
//        cout<<0<<endl;
//    }
    vector<int> nu={1,1,3};
//    vector<vector<vector<int>>> res=combination(nu);
    vector<vector<int>> res=my_pem3use(nu);
    for(auto ie:res){
        for (auto e:ie){
                cout << e;
            }
        cout<<endl;
        }
    }


//    vector<vector<int>> fi=permut(nu,resu,cu,in);

