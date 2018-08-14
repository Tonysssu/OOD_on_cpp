//
// Created by Tong Su on 8/12/18.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//bool my_knapsake(vector<int> v, int w, int in)
//{
//    if(w==0){
//        return true;
//    }
//    if(w<0 || in >= v.size()) {
//        return false;
//    }
//    return my_knapsake(v, w, in+1) || my_knapsake(v, w-v[in], in+1);   //equivalent sub_question
//}
//

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

int main() {
//    vector<int> k{2,3,4,5};
//    int val=13;
//    cout<<my_knapsake(k,val,0)<<endl;
//    char a[2][2]={{'.','X'},{'.','X'}};
//    cout<<*a<<endl;
    vector<vector<char>> maze{{'.', 'X', '.', '.', '.', 'X'},
                              {'.', '.', '.', 'X', '.', 'X'},
                              {'X', 'X', '.', 'X', '.', '.'},
                              {'.', 'X', 'X', 'X', '.', 'X'},
                              {'X', '.', '.', '.', '.', 'X'},
                              {'.', '.', '.', '.', '.', '.'}};
    int startx = 0, starty = 0, targetx=5, targety = 5;
    int Bx = maze.size();
    int By = maze[0].size();
    vector<string> p;
    if (my_maze(maze, Bx, By, startx, starty, targetx, targety,p)){
        cout<<1<<endl;
    }
    else{
        cout<<0<<endl;
    }
}