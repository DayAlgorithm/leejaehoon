#include <iostream>
#include <vector>
#include <sstream>

char direction[] = {'U','D','L','R'};

std::ostringstream out; // 출력 버퍼
static int cnt =0; 
int init= 0; 
void push(int dir, int i){ 
    out << direction[dir] << " " << i + 1 << " push\n";
    cnt++;

}
/*
예시: 
완성하기: 
2 2 에서 시작해서 완성하기

 ..# 
 .#. 
 #..  
지그재그로 탐색하면서 그냥 넣다 뺴보면서 브루트포스 
전부 없으면 정확하게 2*(N^2)나오는데
1
... 
##.
,.. 
2
#..
##. 
...
3
#..
.#.
... 
4
##.
.#.
...
5
..#
.#.
...
6
..#
.##
...
7
..#
.##
..#
8
..#
.#.
.##
9
..#
.#.
#..

*/
void pull(int dir, int i){
    out << direction[dir] << " " << i + 1 << " pull\n";
    cnt++;
}

int main (){
    int n, r, c;
    std::cin >> n >> r >> c;
    std::vector<std::vector<char>> ans(n, std::vector<char>(n, '.'));

    for (int i = 0; i < n; i++ ){
        for (int j = 0; j < n; j++){
            std::cin >> ans[i][j];
            if(ans[i][j]=='#') init++;   
        }
    }

    int x = c - 1;
    int y = r - 1;

    int U = 0;
    int D = 1;
    int L = 2;
    int R = 3;

    int i, j;
 
    // 위쪽 방향
    if(x!= 0){
            push(L,y);
            cnt++ ;
            x= x-1;
        }
    for (j = y; j >= 0;) {
        // 왼쪽 -> 위
        for (i = (j == y ? x : n-1); i > 0; i--) {
            push(L, j);
            
            if (ans[j][i] != '#') {
                pull(U, i);
                
            }
        }
        if (j == 0) {
            if (ans[j][0] != '#' &&(r!=1  || c!=1)) {
                pull(L, j);
            }
            break;
        }
        push(U, 0);
        

        if (ans[j][0] != '#' && (r!= j+1 ||  c!=i+1) ) {
            pull(L, j);
            
        }

        j--;

        // 오른쪽 -> 위
        for (i = 0; i < n-1; i++) {
            push(R, j);
            
            if (ans[j][i] != '#') {
                pull(U, i);
                
            }
        }

        if (j == 0) {
            if (ans[j][n-1] != '#' &&(r!=1 || c!=1)) {
                pull(R, j);
                
            }
            break;
        }

        push(U, n - 1);
        
        if (ans[j][n - 1] != '#'&&(r!= j+1 || c!=i+1)) {
            pull(R, j);
            
        }

        j--;
    }
    y= r-1; 
    x= c-1;
    // 아래쪽 방향
    for (j = y; j < n;) {
        // 오른쪽으로 밀기(push)
        for (i = (j == y ? x : 0); i < n-1; i++) {
            push(R, j);
            
            if (ans[j][i] != '#') {
                pull(D, i);
                
            }
        }

        if (j == n - 1) {
            if (ans[j][n - 1] != '#') {
                pull(R, j);
                
            }
            break;
        }
        push(D, n - 1);
        
        if (ans[j][n - 1] != '#') {
            pull(R, j);
            
        }
        j++;

        if (j >= n) break;

        // 왼쪽으로 밀기(push)
        for (i = n - 1; i > 0; i--) {
            push(L, j);
            
            if (ans[j][i] != '#') {
                pull(D, i);
                
            }
        }

        if (j == n - 1) {
            if (ans[j][0] != '#') {
                pull(L, j);
                
            }
            break;
        }
        push(D, 0);
        
        if (ans[j][0] != '#') {
            pull(L, j);
            
        }
        j++;
    }

    // 최종 출력
    std::cout << cnt << "\n";
    std::cout << out.str();
}
