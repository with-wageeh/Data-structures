#include <bits/stdc++.h>

using namespace std;

// min binary heap -> is a compleate binary tree where any node <= ALL it's children
// max binary heap -> the opposite meaning
class MaxHeap {
private:
    pair<int,int> *arr;
    int size = 0 , cap = 0;
public:
    MaxHeap(){
        cap = 50;
        arr = new pair<int,int> [cap];
    }
    void exctend_cap (){
        pair<int,int> alter[size] ;
        for (int i = 0; i < size; ++i) {
            alter[i] = arr[i];
        }
        cap = min(cap * 100 ,(int) 1e6);
        arr = new pair<int,int>[cap];
        for (int i = 0; i < size; ++i) {
            arr[i] =  alter[i] ;
        }
    }
    int parent(int node){
        return node == 0 ? -1 : (node - 1) / 2;
    }
    int left(int node){
        return (2 * node + 1) >= cap ? -1 : 2 * node + 1;
    }
    int right(int node){
        return (2 * node + 2) >= cap ? -1 : 2 * node + 2;
    }
    void go_to_up(int node){
        int par = parent(node);
        if(node == 0 || arr[node].first <= arr[par].first) return;
        swap(arr[node] , arr[par]);
        go_to_up(par);
    }
    void go_to_down(int node){
        int l =left(node)  , r = right(node);
        int le = -1 , ri = -1;
        if(l < size) le = arr[l].first;
        if(r < size) ri = arr[r].first;
        int mx = max(le , ri);
        if(mx <= arr[node].first)return;
        if(le < ri)swap(l,r);
        swap(arr[node] , arr[l]);
        go_to_down(l);
    }
    void insert(int x , int p){
        if(size == cap)exctend_cap();
        assert(size != cap);
        arr[size++] = {p , x};
        go_to_up(size - 1);
    }
    int top(){
        assert(size);
        return arr[0].second;
    }
    void remove(){
        assert(size);
        pair<int,int> a = arr[size - 1];
        arr[size - 1] ={0,0};
        arr[0] = a;
        go_to_down(0);
        size--;
    }
    void print(){
        for (int i = 0; i <size ; ++i) {
            cout << i << "  " << arr[i].second << endl;
        }
        cout << endl;
    }
};
class pq{
private:
    MaxHeap heap;
public:
    void push(int x  , int p){
        heap.insert(x,p);
    }
    void remove(){
        heap.remove();
    }
    int top(){
        return heap.top();
    }
    void print(){
        heap.print();
    }

};

int main() {

    vector<pair<int,int>> v = {{2 , 1245},{17,8},{22,54},{10 , 7},{8 , 7},{37,1}};
    MaxHeap h;
    pq p ;
    for(auto &a : v)p.push(a.first , a.second);
    int c = v.size();
    while (c--){
        cout << p.top() << endl;
        p.remove();
    }
//    h.insert(8);
//    h.print();
//    h.insert(2);
//    h.print();
//    h.insert(5);
//    h.insert(12);
//    h.insert(45);
//    h.print();
//    h.insert(1);
//    h.print();
//    //h.insert(2);
//    h.insert(4);
//    h.print();
//    h.remove();
//    h.print();

}
