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
        idx     = 1;
        size    = n;
        compare = compareFunc; // 비교 포인터 저장
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
        if (left  < idx && compare(binaryT[left], binaryT[target]))
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

std::set<std::pair<int,int>> printedEdges;

void pathSet(int u, const std::vector<int>& log) {
    std::vector<int> path;
    for (int cur = u; cur != -1; cur = log[cur])
        path.push_back(cur); //각 위치별로 로그 넣기
    std::reverse(path.begin(), path.end());

    // 간선 등록 및 출력
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        printedEdges.insert({path[i], path[i + 1]});
    }
    // 출력
 
}
const int INF = std::numeric_limits<int>:: max();

int main() {
    int n,m;
    std::cin>> n>>m;
    //인접행렬
    std::vector<std::vector<int>> adj(n+1, std::vector<int>(n+1,-1));
    std::vector<bool> visited(n + 1, false); 
        for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (adj[u][v] == -1) {
            adj[u][v] = w;
            adj[v][u] = w;
        } else {
            //가중치 최소값
            adj[u][v] = std::min(adj[u][v], w);
            adj[v][u] = std::min(adj[v][u], w);
        }
    }
    std::vector<int> log(n+1, -1);
    //힙에 노드가 중복되어 들어가므로 size> n
    Heap<node> heap(5*n,cmp); 
    std::vector<int> dist(n + 1, INF); 
    dist[1] = 0;
    node temp = {0,1}; 
    heap.push(temp);
    while(!heap.isEmpty()){
        temp =heap.top(); 
        heap.pop();
        int curr= temp.idx; 

        if (visited[curr]) continue; //중복 간선 제거
        visited[curr] = true;

        if (dist[curr] < temp.cost) continue; // 경로 업데이트 조건 
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
    for (int i = 2; i <= n; i++) {
        {
            pathSet(i, log);// 각 간선에 대한 정보를 집합에 넣기
        }
    }
    std::cout<< printedEdges.size()<<std::endl; 
    for(auto i: printedEdges)
        std::cout<<i.first<<" " << i.second <<std::endl;
    std::cout << "\n";
}


