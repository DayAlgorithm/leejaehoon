#include <iostream>
#include <vector>
#include <unordered_map> 
#include <algorithm>
std::vector<int> p1, p2;
std::unordered_map<int, int> p3, p4;
int n, p, q;
long long cnt = 0;
//A에서 가지는 경우
void allA() {
    for (int start = 0; start < p; ++start) {
        int sum = 0;
        for (int len = 1; len <= p; ++len) {
            sum += p1[(start + len - 1) % p];
            if (len == p) break; // 전체 한 바퀴 넘지 않게
            p3[sum]++;
        }
    }
    int total = 0;
    for (int x : p1) total += x;
    p3[total]++;
}
//B에서 가지는 경우 계산( A랑 거의 같은데 B집합에서 연산)
void allB() {
    for (int start = 0; start < q; ++start) {
        int sum = 0;
        for (int len = 1; len <= q; ++len) {
            sum += p2[(start + len - 1) % q];
            if (len == q) break;
            p4[sum]++;
        }
    }
    int total = 0;
    for (int x : p2) total += x;
    p4[total]++;
}

void AB() {
    // 단일 피자만 사용하는 경우
    cnt += p3[n];
    cnt += p4[n];
    // 조합으로 만드는 경우
    // 피자를 조합할 수 있을 경우에는 조합으로 진행해야하는듯함
    // 집합으로 중복되는 케이스(1+2+3, 3+1+2)둘다 6이지만, vector에 케이스로만 넣으면 중복연산 불가능
    // 집합에 해당 숫자 케이스 수 x 케이스 수 로 연산
    for (auto [a_sum, a_cnt] : p3) {
        int target = n - a_sum;
        if (p4.count(target)) {
            cnt += 1LL * a_cnt * p4[target];
        }
    }
}

void getArray() {
    p1.resize(p);
    p2.resize(q);
    for (int i = 0; i < p; ++i)std::cin >> p1[i];
    for (int i = 0; i < q; ++i)std::cin >> p2[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> p >> q;
    getArray();

    allA();
    allB();
    AB();

    std::cout << cnt << std::endl;
    return 0;
}
