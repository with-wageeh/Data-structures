#include <bits/stdc++.h>

using namespace std;

// min binary heap -> is a compleate binary tree where any node <= ALL it's children
// max binary heap -> the opposite meaning
class MinHeap {
private:
    int *arr;
    int size = 0 , cap = 0;
public:
    MinHeap(int sz){
        cap = sz + 50;
        arr = new int [cap];
    }
    MinHeap(){
        cap = 50;
        arr = new int [cap] {};
    }
    MinHeap(vector<int>&v){
        cap = v.size() + 50;
        size = v.size();
        arr = new int [cap];
        for (int i = 0; i < size; ++i) {
        arr[i] = v[i];
        }
        for (int i = size - 1; i >= 0 ; --i) { // O(n) not O(nlogn) i don't know why !
            go_to_down(i);
        }
    }
    void exctend_cap (){
        int alter[size] ;
        for (int i = 0; i < size; ++i) {
            alter[i] = arr[i];
        }
        cap = min(cap * 100 ,(int) 1e6);
        arr = new int[cap];
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
        if(node == 0 || arr[node] >= arr[par]) return;
        swap(arr[node] , arr[par]);
        go_to_up(par);
    }
    void go_to_down(int node){
        int l =left(node)  , r = right(node);
        int le = 2e9 , ri = 2e9;
        if(l < size) le = arr[l];
        if(r < size) ri = arr[r];
        int mn = min(le , ri);
        if(mn >= arr[node])return;
        if(le > ri)swap(l,r);
        swap(arr[node] , arr[l]);
        go_to_down(l);
    }
    void insert(int x){
        cout << arr[5] << endl << arr[9] << endl;
        if(size == cap)exctend_cap();
        assert(size != cap);
        arr[size++] = x;
        go_to_up(size - 1);
    }
    int top(){
        assert(size);
        return arr[0];
    }
    void remove(){
        assert(size);
        int a = arr[size - 1];
        arr[size - 1] = 2e9;
        arr[0] = a;
        go_to_down(0);
        size--;
    }
    void print_less(int x){
        vector<int>v;
        while (size && top() < x){
            cout << top() << " ";
            v.push_back(top());
            remove();
        }
        cout << endl;
        for(auto &a : v) insert(a);
    }
    void print(){
        for (int i = 0; i <size ; ++i) {
            cout << i << "  " << arr[i] << endl;
        }
        cout << endl;
    }
    void go_to_down(int node , int n , int *ar){
        int l =left(node)  , r = right(node);
        int le = 2e9 , ri = 2e9;
        if(l < n) le = ar[l];
        if(r < n) ri = ar[r];
        int mn = min(le , ri);
        if(mn >= ar[node])return;
        if(le > ri)swap(l,r);
        swap(ar[node] , ar[l]);
        go_to_down(l);
    }
    void make_it_heap(int *p ,int n){
        for (int i = n - 1; i > -1 ; --i) {
            go_to_down(i,n,p);
        }
    }
};
bool isheap (int *a , int n){
    queue<int>q;
    q.push(0);
    while (q.size()){
        auto node = q.front();
        q.pop();
        if(node >= n)continue;
        int l = node * 2 + 1 , r = node * 2 + 2;
        if(l < n && a[node] > a[l])return 0;
        if(r < n && a[node] > a[r])return 0;
        q.push(l);
        q.push(r);
    }
    return 1;
}

int main() {

   // vector<int> v = {2,17,22,10,8,37,14,19,7,6,5,12,25,30};
    MinHeap h;
    //for(auto &a : v)h.insert(a);
   // h.print_less(10);
   // int c = v.size();
//    while (c--){
//        cout << h.top() << endl;
//        h.remove();
//    }
int arr[14] = {6,5,12,7,6,22,14,19,10,17,8,37,25,30};
   cout <<  isheap(arr , 14) << endl;
   // h.insert(8);
    h.sorting(arr , 14);
    for (int i = 0; i < 14 ; ++i) {
        cout << arr[i] << " " ;
    }
    cout << endl;
    cout <<  isheap(arr , 14) << endl;
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
