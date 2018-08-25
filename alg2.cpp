//
// Created by Tong Su on 8/12/18.
//
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <list>
#include <set>
#include <limits>
//#include "alg.h"

using namespace std;
int max_sum=INT8_MIN;

//case1
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

//case2
//void my_uti(int tgt,vector<int> it, vector<vector<int>> &res, vector<int> &cur){
//
//}
//vector<vector<int>> my_knap(int target,vector<int> item){
//
//}

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

    for (auto i=0; i<4; i++) {
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

//permutation3 [repeat allow]
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


//lucky nums
void luckynums(string nums,int target, vector<string> &result, string temp, int index, long cur, long last){
    if (index==nums.size()){
        if (cur==target) {
            result.push_back(temp);
        }
        return;
    }
    for (int i=index;i< nums.size();i++){
        if (nums[index]=='0' && i!=index) {
            break;
        }
        string m = nums.substr(index,i+1);
        long v=stol(m);
        if (index==0){
            luckynums(nums,target,result, temp+m, i+1,v,v);
        }
        else {
            luckynums(nums, target, result, temp + "+"+ m, i + 1, cur+v, v);
            luckynums(nums, target, result, temp + "-"+ m, i + 1, cur-v, -v);
            luckynums(nums, target, result, temp + "*"+ m, i + 1, cur-last+last*v, last*v);
            if (v != 0 && last % v == 0) {
                luckynums(nums, target, result, temp + "/"+ m, i + 1, cur-last+last/v, last/v);
            }
        }
    }
}

vector<string> luckn(string nums,long target){
    vector<string> res;
    luckynums(nums, target, res,"", 0, 0,0);
    return res;
}

//my_nqueens
//class Solution {
//public:
//
//    void solve_queen(int size, vector<int> cu, int& cot, int dx){
//        if (dx==size){
//            cot++;
//            return;
//        }
//        for(int index=0;index<size;index++) {
//            bool flag=false;
//            for(int i=0;i<dx;i++){
//                if(cu[i]==index || (abs(cu[i]-index)==abs(dx-i))){
//                    flag=true;
//                    break;
//                }
//            }
//            if (flag) continue;
//            cu[dx]=index;
//            solve_queen(size, cu, cot, dx+1);
//        }
//    }
//
//    int totalNQueens(int size){
//        vector<int> status(size);
//        int count=0;
//        solve_queen(size,status, count,0);
//        return count;
//    }
//};

//nqueens
bool conflict(vector<int> c, int dy){
    int dnext=c.size();
    for(int i=0;i<dnext;i++){
        if(c[i]==dy || (abs(c[i]-dy)==abs(dnext-i))){
            return true;
        }
    }
    return false;
}

void solve_queen(int size, vector<vector<int>>& res, vector<int> cu, int dx){
    if (dx==size){
        res.push_back(cu);
        return;
    }
    for(int i=0;i<size;i++) {
        if (!conflict(cu, i)) {
            cu.push_back(i);
            solve_queen(size, res, cu, dx+1);
            cu.pop_back();
        }
    }
}

int my_nqueen(int size){
    vector<int> status(size,0);
    vector<vector<int>> results;
    vector<int> cur;
    solve_queen(size, results,cur,0);
    int n=results.size();
    return n;
}


//OA
void helper(vector<int> nums, int target,vector<vector<int>> &res, vector<int> &cur, int index){
    if(target==0){
        res.push_back(cur);
        return;
    }
    if (target<0 || index >nums.size()){
        return;
    }
    helper(nums, target,res, cur,index+1);
    cur.push_back(nums[index]);
    helper(nums, target-nums[index],res, cur,index+1);
    cur.pop_back();
}

vector<vector<int>> oa1(vector<int> nums, int target){
    vector<vector<int>> result;
    vector<int> cur;
    sort(nums.begin(),nums.end());
    helper(nums, target,result,cur,0);
    return result;
}


//sticks
//int sumt(vector<int> s) {
//    int sum = 0;
//    for (auto item:s) {
//        sum += item;
//    }
//    return sum;
//}

//bool helpform(vector<int> sticks, int sides,vector<int> c, int index){
//    if (index==sticks.size()){
//        if()
//        }
//    }
//}

//bool formpoly(vector<int> sticks, int sides){
//    if(sticks.size()<sides){
//        return false;
//    }
//    int sum=sumt(sticks);
//    if (sum%sides!=0) return false;
//    int target=sum/sides;
//    for (auto stick:sticks){
//        if (stick>target){
//            return false;
//        }
//    }
//    vector<int> cur;
//    return helpform(sticks,sides,cur,0);
//}



//sticks-2
//void helper3(vector<int> index){
//
//}

//Build Tree
template <typename T>
struct Treenode{
    T _data;
    Treenode<T>* _left;
    Treenode<T>* _right;
    Treenode(T data=T())
        :_data(data)
        ,_left(nullptr)
        ,_right(nullptr){}
};

template <typename T>
class Bitree{
public:
    Bitree(const T* a, size_t size,int index, const T& invalid){
        _root=_make_tree(a,size,index,invalid);
    }
    Bitree(const Bitree<T>& t){
        _root=_copy(t._root);
    }
    ~Bitree(){
        _destroy(_root);
    };
private:
    Treenode<T>* _root;
};


template <typename T>
Treenode<T>* _make_tree(const T* a, size_t size, int& index, const T& invalid){
    Treenode<T>* root= nullptr;
    if (index<size && a[index]!=invalid){
        root= new Treenode<T>();
        root->_data=a[index];
        root->_left=_make_tree(a,size,index++,invalid);
        root->_right=_make_tree(a,size,index++,invalid);
    }
    return root;
}

template <typename T>
Treenode<T>* _copy(const Bitree<T>* root){
    if(root==nullptr){
        return nullptr;
    }
    auto node = new Treenode<T>(root->_data);
    node->_left=_copy(root->_left);
    node->_right=_copy(root->_right);
    return node;
}

template <typename T>
void _destroy(Bitree<T>* root){
    auto temp=root;
    if (temp==nullptr){
        return;
    }
    _destroy(temp->_left);
    _destroy(temp->_right);
    delete temp;
    temp=nullptr;
}



size_t my_max(size_t a, size_t b){
    if(a>b){return a;}
    return b;
}

template<typename T>
size_t depth(Treenode<T>* &root){
    if (root== nullptr){
        return 0;
    }
    return my_max(depth(root->right),depth(root->left))+1;
}





//int bitree
struct Bnode{
        int value;
        Bnode* left;
        Bnode* right;
        Bnode(int a=0):value(a),left(nullptr),right(nullptr){}
    };


Bnode* createT(const int* v,int invalid, size_t size, int index){
    Bnode* _root=nullptr;
    if (index <size && v[index]!=invalid){
        _root=new Bnode(invalid);
        _root->value=v[index];
        _root->left=createT(v, invalid, size, 2*index+1);
        _root->right=createT(v, invalid, size, 2*index+2);
    }
    return _root;
}

Bnode* copyT(Bnode* s){
    if(s==nullptr){
        return nullptr;
    }
    auto root=new Bnode(s->value);
    copyT(root->left);
    copyT(root->right);
    return root;
}

void destroyT(Bnode* s){
    auto temp=s;
    if(temp==nullptr){
        return;
    }
    destroyT(temp->left);
    destroyT(temp->right);
    delete temp;
    temp=nullptr;
}

size_t depthT(Bnode* s){
    if(s==nullptr){
        return 0;
    }
    int le=depthT(s->left)+1;
    int ri=depthT(s->right)+1;
    return le > ri ? le :ri;
}

bool isbalance(Bnode* s){
    if (s == nullptr){
        return true;
    }
    if (abs(int(depthT(s->left) - depthT(s->right)))>1){
        return false;
    }
    return isbalance(s->left)&& isbalance(s->right);
}

bool issy(Bnode* le, Bnode* ri){
    if (le == nullptr && ri== nullptr){
        return true;
    }
    if (le!= nullptr && ri!=nullptr){
        if(le->value==ri->value){
            return issy(le->left, ri->right) && issy(le->right,ri->left);
        }
        return false;
    }
    return false;
}

bool issymetric(Bnode* s){
    if (s == nullptr){
        return true;
    }
    return issy(s->left,s->right);
}

int getD(Bnode* s){
    if (s== nullptr){
        return 0;
    }
    int le=getD(s->left);
    int ri=getD(s->right);
    if(le==-1 ||ri==-1|| abs(le-ri)>1){
        return -1;
    }
    return le>ri?le+1:ri+1;
}

int miniD(Bnode* s){
    if (s==nullptr){
        return 0;
    }
    int le=miniD(s->left);
    int ri=miniD(s->right);
    if(le==0||ri==0){
        return le>ri?le+1:ri+1;
    }
    return le<ri?le+1:ri+1;
}

bool _hasPath(Bnode* s, int a){
    if (s==nullptr){
        return false;
    }
    if (s->left== nullptr && s->right== nullptr){
        if(a==s->value ){
            return true;
        }
        return false;
    }
    return _hasPath(s->left, a-s->value) || _hasPath(s->right, a-s->value);
}

int my_max(int a, int b){return a>b?a:b;};

int maxBranch(Bnode* s){
    if (s== nullptr){
        return 0;
    }
    int le=maxBranch(s->left);
    int ri=maxBranch(s->right);
    int maxbranch=s->value+my_max(0,my_max(le,ri));
    max_sum=my_max(max_sum, my_max(maxbranch,le+s->value+ri));
    return maxbranch;
}

int _maxS(Bnode* s){
    if (s==nullptr){
        return 0;
    }
    max_sum=INT8_MIN;
    maxBranch(s);
    return max_sum;
}

class Btree{
public:
    Btree(int* v,int invalid, size_t size, int index){
        root=createT(v, invalid,size,index);
    }
    Btree(const Btree& s){
        root=copyT(s.root);
    }
    ~Btree(){
        destroyT(root);
    };
    size_t _depth(){
        return depthT(root);
    }
    bool isba(){
        return getD(root)!=-1;
    }
    bool isBalan(){
        return isbalance(root);
    }
    bool isSym(){
        return issymetric(root);
    }

    int miniDepth(){
        return miniD(root);
    }

    int pathSum(int a){
        return _hasPath(root, a);
    }

    int maxSum(){
        return _maxS(root);
    }
private:
    Bnode* root;
};




//sudoku-stillworking
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        for(int ind=0;ind<9;ind++){
            helper(board,ind,0);
        }
    }
    void helper(vector<vector<char>>& board,int index,int c){
        if (c==9){
            return;
        }
        if(board[index][c]!='.'){
            helper(board,index,c+1);
        }
        for (int fi=1;fi<10;fi++){
            if (isrowcomplict(board,fi,index) || iscolcomplict(board,fi,c) || isregcomplict(board,fi,index,c)){
                continue;
            }
            char ch=fi;
            board[index][c]=ch;
            helper(board,index,c+1);
        }
    }

    bool isrowcomplict(vector<vector<char>>& board, int next,int row){
        for(auto item :board[row]){
            char nt=next;
            if(nt==item){
                return true;
            }
        }
        return false;
    }

    bool iscolcomplict(vector<vector<char>>& board, int next,int col){
        for(int r=0;r<9;r++){
            char nt=next;
            if(nt==board[r][col]){
                return true;
            }
        }
        return false;
    }

    bool isregcomplict(vector<vector<char>>& board, int next,int row, int col){
        if (row<3){
            if (col<3){
                for (int i=0;i<3;i++){
                    for (int j=0;j<3;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else if(col>5){
                for (int i=0;i<3;i++){
                    for (int j=6;j<9;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else{
                for (int i=0;i<3;i++){
                    for (int j=3;j<6;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
        }
        else if(row>5){
            if (col<3){
                for (int i=6;i<9;i++){
                    for (int j=0;j<3;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else if(col>5){
                for (int i=6;i<9;i++){
                    for (int j=6;j<9;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else{
                for (int i=6;i<9;i++){
                    for (int j=3;j<6;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
        }
        else{
            if (col<3){
                for (int i=3;i<6;i++){
                    for (int j=0;j<3;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else if(col>5){
                for (int i=3;i<6;i++){
                    for (int j=6;j<9;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
            else{
                for (int i=3;i<6;i++){
                    for (int j=3;j<6;j++){
                        char nt=next;
                        if(nt==board[i][j]){
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }

};

//word searching
bool searching(vector<vector<char>> board, string word, int index, int x, int y, vector<vector<bool>> visited){
        if(index==word.length()){
            return true;
        }
        if (x<0|| y<0|| x>=board.size() || y>=board[0].size()|| visited[x][y]|| board[x][y]!=word[index]){
            return false;
        }
        int dx[4]={0,-1,1,0};
        int dy[4]={-1,0,0,1};
        for (int i=0;i<4;i++){
            visited[x][y]=true;
            if(searching(board,word,index+1,x+dx[i],y+dy[i],visited)){
                return true;
            }
            visited[x][y]=false;
        }
        return false;
    }

bool exist(vector<vector<char>>& board, string word) {
    if(board.size()==0 || board[0].size()==0){
        return false;
    }
    if((board.size()*board[0].size())<word.length()){
        return false;
    }
    vector<bool> temp(board[0].size(),false);
    vector<vector<bool>> flag(board.size(),temp);
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++) {
            if (searching(board,word,0,i,j,flag)){
                return true;
            }
        }
    }
    return false;
}

//palindrome partitioning
bool ispalin(string sub,int begin){
    int len=sub.length();
    if (len==1){
        return true;
    }
    if (sub[begin]==sub[len-1]){
        sub.pop_back();
        return ispalin(sub,begin+1);
    }
    return false;
}


void parthelp(string tar, int index, vector<vector<string>> res, vector<string> cur){
    if (index==tar.length()){
        res.push_back(cur);
        return;
    }
    for (int len=1;len<tar.length()-index;len++) {
        string sub = tar.substr(index, len);
        if(ispalin(sub,0)){
            cur.push_back(sub);
            parthelp(tar,index+len,res,cur);
            cur.pop_back();
        }
    }


}

vector<vector<string>> parti(string target){
    vector<vector<string>> results;
    vector<string> current;
    parthelp(target, 0, results,current);
    return results;
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
//    vector<int> nu={1,1,3};
//    vector<vector<vector<int>>> res=combination(nu);
//    vector<vector<int>> res=my_pem3use(nu);
//    for(auto ie:res){
//        for (auto e:ie){
//                cout << e;
//            }
//        cout<<endl;
//        }
//    }

//    vector<string> res=luckn("7765332111",888);
//    vector<int> numlist={1,2,3,5,6 };
//    vector<vector<int>> result=oa1(numlist, 8);
//    for(auto ie:res){
//        for (auto e :ie) {
//            cout << e ;
//        }
//        cout<< endl;
//    }
//    vector<int> numlist={1,1,1,1,1};
//    vector<int> num={1,2,3,2,1};
//    vector<int> cur;
//    vector<bool> fl(numlist.size(),false);
//    sort(numlist.begin(),numlist.end());
//    vector<vector<int>> result;
//    helper2(numlist, 1,result,cur,0,fl);
//    for(auto ie:result){
//        for (auto e :ie) {
//            cout << e;
//        }
//        cout<< endl;
//    }
//    cout<<recur(num,3)<<endl;
//      cout<<my_nqueen(8)<<endl;
    int a[5]={1,2,3,4,5};
    Btree K(a,-1,5,0);
//    cout<<K._depth()<<endl;
//    cout<<K.isBalan()<<endl;
//    cout<<K.isSym()<<endl;
//    cout<<K.miniDepth()<<endl;
    cout<<K.pathSum(3)<<endl;
    cout<<K.maxSum()<<endl;
}


//    vector<vector<int>> fi=permut(nu,resu,cu,in);

