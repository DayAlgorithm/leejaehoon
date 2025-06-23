#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int n;
int minLiar = 51; 
std::vector<int>* arr;  
std::vector<int>* node;
//n max ==50 
//인터넷에서 참고를 해서 풀었습니다. 
//51명이면 무서워짐 (누가 한명 더 있음 ㄷㄷ)

void dfs(int idx, int liar) {
    if (liar >= minLiar) return; 
    //현재 탐사보다 더 많으면 굳이 더 안내려가고 종료 최소조합을 찾아야함 
    if (idx >= n) { 
        //last case 종료조건
        if ((*arr)[n-1] == -1) {
            //case: ?-> 모순조건이 없음
            minLiar = std::min(liar, minLiar);
            return;
        }
        if ((*node)[n-1]) {   
            //case: 정직한 사람 
            if ((*arr)[n-1] == (*node)[0]) minLiar = std::min(liar, minLiar); 
            //모순이 없을경우 ->그대로 min 
        }
        else {               
            //case: 거짓말쟁이
            if ((*arr)[n-1] != (*node)[0]) minLiar = std::min(liar, minLiar);
            // 모순이 없을 경우
        }
        return;
    }
    //? 에 대해서 분기 나누기 ?????일 경우 전부 00000으로 처리됨
    //-> 최소조건을 찾을 수 있음
    if ((*arr)[idx-1] == -1) {
        (*node)[idx] = 1;
        dfs(idx+1, liar);
        (*node)[idx] = 0;
        dfs(idx+1, liar+1);
        return;
    }
    //상태에 따라 배열에 값 적기
    (*node)[idx-1] ?
    (*node)[idx] =  (*arr)[idx-1]: 
    (*node)[idx] = !(*arr)[idx-1];
    
    if (!(*node)[idx]) liar++;
    dfs(idx+1, liar);
    return;
}

int main()
{    
    std::cin >> n;
    arr = new std::vector<int> (n,0);
    node= new std::vector<int> (n,0);
    std::string s;
    std::cin>>s; 
    char c; 
    for (int i=0; i< n;i++) {
        c= s[i];
        if (c == 'H') (*arr)[i] =  1;
        if (c == '?') (*arr)[i] = -1;
    }
    dfs(1, 1);
    (*node)[0] = 1;
    dfs(1, 0);
    if (minLiar == 51) minLiar = -1;
    std::cout << minLiar;
    return 0;
}
