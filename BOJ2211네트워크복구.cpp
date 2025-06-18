#include <iostream>
#include <vector> 
#include <limits> 
#include <utility>
#include <memory>
#include <algorithm> 
#include <set> 

template <typename T>
class Heap {
public:
    std::unique_ptr<T[]> binaryT;  // 배열 형태의 스마트 포인터
    int idx;
    int size;
    bool (*compare)(T, T);
    Heap(int n, bool (*compareFunc)(T, T)) {
        binaryT = std::make_unique<T[]>(n + 1); // 인덱스 1부터 사용
        idx = 1;
        size = n;
        compare = compareFunc;
    }
    void push(T node) {
        if (idx > size) return;
        binaryT[idx++] = node;
        heapifyUp(idx - 1);
    }
    void heapifyUp(int i) {
        if (i == 1) return;
        int parent = i / 2;
        if (compare(binaryT[i], binaryT[parent])) {
            std::swap(binaryT[i], binaryT[parent]);
            heapifyUp(parent);
        }
    }
    T top() {
    if (idx <= 1) throw std::out_of_range("Heap is empty");
    return binaryT[1]; // 루트가 최우선값
    }
    void pop() {
        if (idx <= 1) return;
        binaryT[1] = binaryT[--idx]; // 마지막 노드를 루트로
        heapifyDown(1);
    }
    void heapifyDown(int i) {
        int left   = i * 2; 
        int right  = i * 2 + 1;
        int target = i;
        //heap은 아래로 내려갈때 2개로 갈리니까 case구분
        if (left < idx && compare(binaryT[left], binaryT[target]))
            target = left;
        if (right < idx && compare(binaryT[right], binaryT[target]))
            target = right;
        if (target != i) {
            std::swap(binaryT[i], binaryT[target]);
            heapifyDown(target);
        }
    }
    bool isEmpty(){
        return idx ==1 ;
    }
};

struct node { 
    int cost; 
    int idx;
}; 

bool cmp(node a, node b) {
    return a.cost < b.cost ; // min-heap
}


const int INF = std::numeric_limits<int>:: max();

int main() {
    int n,m;
    std::cin>> n>>m; 
    std::vector<std::vector<int>> adj(n+1, std::vector<int>(n+1,-1));
    std::vector<bool> visited(n + 1, false); 
        for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (adj[u][v] == -1) {
            adj[u][v] = w;
            adj[v][u] = w;
        } else {
            adj[u][v] = std::min(adj[u][v], w);
            adj[v][u] = std::min(adj[v][u], w);
        }
    }
    std::vector<int> log(n+1, -1); 

    Heap<node> heap(5*n,cmp);
    std::vector<int> dist(n + 1, INF);
    dist[1] = 0;
    node temp = {0,1}; 
    heap.push(temp);
    while(!heap.isEmpty()){
        temp =heap.top(); 
        heap.pop();
        int curr= temp.idx; 

        if (visited[curr]) continue;
        visited[curr] = true;

        if (dist[curr] < temp.cost) continue; // 이미 최단 경로 존재
        for (int next = 1; next <= n; next++) {
            if (adj[curr][next] == -1) continue;
            int cost = dist[curr] + adj[curr][next];
            if (cost < dist[next]) {
                heap.push({cost,next});
                dist[next] = cost;
                 log[next] = curr; 
            }
        }
    }

    //optimal substructure
    std::cout<<n-1<<std::endl;
    for (int i = 2; i <= n; i++) {
        {
            std::cout<<i <<" "<< log[i]<< std::endl;
        }
    }
    std::cout << "\n";

}


