#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define wageeh ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(0)
#define ll long long
struct node {
    int data = 0;
    char dat ;
    node *left = nullptr , *right = nullptr;
    node(int d){
        data = d;
    }
    node(char c){
        dat = c;
    }
};
int c ;
// successor -> given node x , find y is the smallest element > x
class BST{
private:
    node* root ;
public:
    BST(int d){
        node *newnode = new node(d);
        root = newnode;
    }
    BST(vector<int>&v){
       root = build(root , 0 , v.size() - 1 , v);
    }
    BST(deque<int>&pre){
        assert(pre.size());
        root = build(root , pre);
        //cout << root-> data << " " << root->left ->data << " " << root->right-> data << endl;
    }
    BST(deque<ll>&level){
        assert(level.size());
        queue<pair<node*,pair<pair<int,int>,pair<int,int>>>>q;
        root = new node((int)level.front());
        level.pop_front();
        q.push({root , {{0,root->data},{root->data , 2e9}}});
        while (q.size()){
            auto temp = q.front().first;
            auto l = q.front().second.first , r = q.front().second.second;
            q.pop();
            if(level.empty())break;
            if(level.front() >= l.first && level.front() <= l.second){
                temp->left = new node((int)level.front());
                q.push({temp->left , {{l.first , level.front()} , {level.front(),r.first}}});
                level.pop_front();
            }
            if(level.empty())break;
            if(level.front() >= r.first && level.front() <= r.second) {
                temp->right = new node((int) level.front());
                q.push({temp->right , {{l.second , level.front()} , {level.front(),r.second}}});
                level.pop_front();
            }
            }
    }
   node *build(node *temp,deque<int>&q , int mn = 0 , int mx = 2e9){
        if(q.empty())return nullptr;
        if(!temp) {
            node *newnode = new node(q.front());
            temp = newnode;
            q.pop_front();
        }
        node* left = nullptr , *right = nullptr;
        if(q.size() && temp->data > q.front() && q.front() > mn){
           left =  build(temp->left , q , mn , temp->data);
        }
        if(q.size() && q.front() > temp->data && q.front() < mx){
           right =  build(temp->right , q , temp->data , mx);
        }
        temp->left = left , temp->right = right;
       return temp;

    }
    node* build (node *temp , int l , int r , vector<int>&v){
        if(r >= v.size() || l > r)return nullptr;
        int mid = (r + l) / 2 ;
        node *newnode = new node(v[mid]);
        temp = newnode;
       node* left =  build(newnode->left , l , mid - 1  ,v);
        node* right = build(newnode->right , mid + 1  , r ,v);
        temp->left = left , temp->right = right;
        return temp;
    }
    void insert(int d){
        insert(root ,  d);
    }
    void insert(node *temp, int data){
        if(data > temp->data){
            if(temp->right){
                insert(temp->right , data);
            }
            else{
                node *newnode = new node(data);
                temp -> right = newnode;
            }
        }
        else{
            if(temp->left){
                insert(temp->left , data);

            }
            else{
                node *newnode = new node(data);
                temp -> left = newnode;
            }
        }
    }
    void traverse_left(node* temp , node *put){
        if(!temp->left) {
            temp->left = put;
            return;
        }
        traverse_left(temp->left , put);

    }
    void traverse_right(node* temp , node *put){
        if(!temp->right) {
            temp->right = put;
            return;
        }
        traverse_right(temp->right , put);

    }
    void delete_node(int d){
         delete_node(root,d , root);
    }
    void delete_node(node *temp , int d , node* parent){
        if(d == temp->data){
            delete_node(temp , parent);
            return;
        }
        if(d > temp->data)delete_node(temp->right , d , temp);
        else delete_node(temp->left , d , temp);
    }
    void delete_node(node *temp , node *par){
        if(temp == root){
            if(!temp->left && !temp->right) temp = nullptr;
            else if(temp->right){
                node *left = temp->left;
                temp = temp->right;
                traverse_left(temp, left);
            }
            else{
                node *right = temp->right;
                temp = temp->left;
                traverse_right(temp, right);
            }
            root = temp;
        }
        else{
            if(!temp->left && !temp->right) {
                if(par->left == temp){
                    par->left = nullptr;
                    delete temp;
                }
                else{
                    par->right = nullptr;
                    delete temp;
                }
            }
            else if(temp->right){

                node *left = temp->left;
                if(par->left == temp){
                    par->left = temp->right;
                }
                else{

                    par->right = temp->right;
                }
                traverse_left(temp->right, left);
            }
            else{
                node *right = temp->right;
                if(par->left == temp){
                    par->left = temp->left;
                }
                else{
                    par->right = temp->left;
                }
                traverse_right(temp->left, right);
            }
        }
    }
    void print_in_order(){
        print_in_order(root);
        cout << endl;
    }
    void print_in_order(node* rot){
        if(!rot)return;
        print_in_order(rot->left);

        //char data -> dat
        //cout << rot->dat << " ";

        //integer data -> data
        cout << rot->data << " ";
        print_in_order(rot->right);
    }
    void pp(){
        cout << root->left->right->data <<" " <<root->data <<" "<< root->right->data << endl;
    }
    bool is_found(int d){
        return is_found(root , d);
    }
    bool is_found(node *temp, int d){
        if(temp->data == d) return 1;
        if(d > temp->data){
            if(temp->right) return is_found(temp->right , d);
            else return 0;
        }
        else{
            if(temp->left) return is_found(temp->left , d);
            else return 0;
        }
    }
    int find_successor(int node){
        // successor -> given node x , find y is the smallest element > x
        return find_successor(root , node);
    }
    int find_successor(node* temp , int data){
        if(!temp) return 2e9;
        int op1 = 2e9 , op2 = 2e9 , op3 = 2e9;
        if(temp->data > data) op1 = temp->data;
        if(temp->data >  data) op2 = find_successor(temp->left , data);
         else op3 = find_successor(temp->right , data);
        return min({op1 , op2 , op3});
    }
    bool search_iterative(int d){
        return search_iterative(root , d);
    }
    bool search_iterative(node* temp , int data){
        stack<node*> st;
        st.push(temp);
        while (1){
            if(st.top() == nullptr)break;
            if(st.top()->data == data)return 1;
            if(st.top()->data < data){
                node* R = st.top();
                st.pop();
                st.push(R->right);
            }
            else{
                node* R = st.top();
                st.pop();
                st.push(R->left);
            }
        }
        return 0;
    }
    bool is_bst_iterative(){
        return is_bst_iterative(root);
    }
    bool is_bst_iterative(node* temp){
        stack<pair<node*,pair<int,int>>>st;
        st.push({temp , {0 , 2e9}});
        while (st.size()){
            auto [k , range] = st.top();
            auto [mn , mx] = range;
            st.pop();
            if(k->left){
                if(k->left->data > k->data) return 0;
                st.push({k->left , {mn , k->data}});
            }
            if(k->right){
                if(k->right->data < k->data) return 0;
                st.push({k->right , {k->data , mx}});
            }
        }
        return 1;
    }
    int lca (int a , int b){
        assert(search_iterative(a) && search_iterative(b));
        assert(root);
        if(a > b)swap(a,b);
        return lca(root , a , b);
    }
    int lca(node *temp , int a , int b , int fa = 0 , int fb = 0){
        if(a > temp->data) return lca(temp->right , a , b , 0 , 0);
        else if(b < temp->data) return lca(temp->left , a ,b, 0 ,0);
        else return temp->data;
    }
    void ancestors_of_sec(deque<int>&q , deque<int>&ans ){
        ancestors_of_sec(root , q,ans);
    }
    void ancestors_of_sec(node*temp , deque<int>&q , deque<int>&ans){
        if(q.empty() || !temp)return;
        if(q.front() < temp->data) ancestors_of_sec(temp->left , q , ans);
         if(q.front() == temp->data){
            if(temp->right){
                ans.push_back(temp->right->data);
                q.pop_front();
            }
            ancestors_of_sec(temp->right, q , ans);
        }
        if(q.front() > temp->data){
            ancestors_of_sec(temp->right , q , ans);
        }
        if(q.empty())return;
        if(q.front() < temp->data) {
            cout << q.front() << " " << temp->data << endl;
            ans.push_back(temp->data);
            q.pop_front();
        }
    }
    bool is_dgeeneratetree(vector<int>&preorder){
        if(preorder.size() < 3)return 1;
       pair<int,int>l = {0 , preorder.front()} , r = {preorder.front() , 2e9} ;
        for (int i = 1; i < preorder.size()  ; ++i) {
           int x = preorder[i];
           if(x >= l.first && x <= l.second) {
               l.second = x;
               r.second = r.first;
               r.first = x;
           }
           else if (x >= r.first && x <= r.second){
               l = {l.second , x};
               r.first = x;
           }
           else return 0;
        }
        return 1;
    }



};

int main() {
    wageeh;
    int t = 1;
    //cin >> t;
    while (t--) {
        deque<ll> v = {50,20,60,15,45,70,35,47,73,46,49};
        BST bst(v);
//        BST bst(50);
//        bst.insert(20);
//        bst.insert(15);
//        bst.insert(45);
//        bst.insert(35);
//        bst.insert(36);
//        bst.insert(16);
//        bst.insert(60);
//        bst.insert(70);
//        bst.insert(73);
//        bst.insert(75);
//        bst.insert(58);
      //  bst.insert(20);bst.insert(20);bst.insert(20);
     bst.print_in_order();
     deque<int> q = {36,60,75} , ans;
     //bst.ancestors_of_sec(q,ans);
     //cout << ans.size() << endl;
    //cout << ans[0] <<" " << ans[1] << " " << ans[2] << endl;
     //cout << bst.is_bst_iterative();
//cout << bst.is_dgeeneratetree(v);
    }
}


