#include <iostream>
#include <deque>
#include <string>

/*
deque로 뒤집기 조작

f:      S ->T 
f^(-1)  T ->S 
를 만족한다. 


f^(-1)를 사용할 수 없을때까지 조작한다. 
if (S==T) ->  1을 출력한다.
else      ->  0을 출력한다.



*/
std::deque<char> S, T;
bool reverse_flag = false;

void popA() {
    if (reverse_flag) {
        T.pop_front();
    } else {
        T.pop_back();
    }
}

void popB() {
    if (reverse_flag) {
        T.pop_front();
    } else {
        T.pop_back();
    }
    reverse_flag = !reverse_flag;
}

bool check() {
    if (S.size() != T.size()) return false;
    if (!reverse_flag) {
        return S == T;
    } else {
        // reverse_flag가 true면 T가 뒤집힌 상태임
        for (size_t i = 0; i < S.size(); ++i) {
            if (S[i] != T[T.size() - 1 - i]) return false;
        }
        return true;
    }
}

bool canOperate() {
    if (T.empty()) return false;
    char c = reverse_flag ? T.front() : T.back();
    return c == 'A' || c == 'B';
}

void run() {
    bool printed = false; // 이미 1을 출력했는지 체크

    while (canOperate()) {
        char c = reverse_flag ? T.front() : T.back();
        if (c == 'A') {
            popA();
        } else if (c == 'B') {
            popB();
        }
        if (!printed && check()) {
            std::cout << 1 << "\n";
            printed = true;
        }
    }

    if (!printed) { // 한번도 출력 안 된 경우 0 출력
        std::cout << 0 << "\n";
    }
}


int main() {
    std::string s_input, t_input;
    std::cin >> s_input >> t_input;

    for (char c : s_input) S.push_back(c);
    for (char c : t_input) T.push_back(c);

    run();


    return 0;
}
