#include<iostream> 
#include<vector>

std::vector<int> tree;
std::vector<int> v;
//세그먼트 트리 -> 합대신 곱을 저장해서 풀기 
void segment_tree(int start, int end, int node)
{
	if (start == end){
		tree[node] = v[start];
        return;
    } 

	int mid = (start + end) / 2;
    segment_tree(start,   mid, node * 2); 
    segment_tree(mid + 1, end, node * 2 + 1);
	tree[node] = tree[node*2]* tree[node*2+1];
}
void update(int start, int end, int node, int index, int value){
    if(index < start || index > end) return;
    if(start == end){
        tree[node] = value;
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, node*2,   index, value);
    update(mid+1, end, node*2+1, index, value);
    tree[node] = tree[node*2] * tree[node*2+1];
}

int multi(int left, int right, int start, int end, int node){
    if (right < start || end < left)   return 1; 
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return multi(left, right, start, mid, node*2) * multi(left, right, mid+1, end, node*2+1);
}

int main(){
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    int n,m,k;
    std::cin>>n>>m>>k; 
    v.assign(n+1,0);
    tree.assign(n*n+n,0);
 
    for(int i=0; i<n; i++){
        std::cin>>v[i];
    }
    segment_tree(1,n,1);

    int temp,a,b; 
    for(int i=0; i<m+k; i++){
        std::cin>>temp>>a>>b;
        if(temp==1){
            update(1, n, 1, a, b);
        }else{
            std::cout << multi(a, b, 1, n, 1)%1000000007 << '\n';
        }
    }
}
