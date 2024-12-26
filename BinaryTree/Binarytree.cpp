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
class BinaryTree{
private:
    node* root ;
public:
    BinaryTree(int d){
        node *newnode = new node(d);
        root = newnode;
    }
    BinaryTree(string s){
        stack<node*>st;
        for (int i = 0; i < s.size(); ++i) {
            // if sympol -> there right and left nodes  ,, merge them at one node
            // if digit -> is leaf and single node without (left & right)
            node* newnode = new node(s[i]);
            if(!isdigit(s[i])){
                node* r , *l;
                r = st.top();
                st.pop();
                l = st.top();
                st.pop();
                newnode->left = l , newnode-> right = r;
            }
            st.push(newnode);
        }
        root = st.top();
    }
    void add_node(vector<int> nodes , string path){
        assert(root);
        assert(nodes.size() == path.size());
        node* temp = root;
        for (int i = 0; i < path.size() ; ++i) {
            if(path[i] == 'L'){
                node *newnode = new node(nodes[i]);
                if(!temp->left) temp->left = newnode;
                temp = temp->left;
            }
            else {
                node *newnode = new node(nodes[i]);
                if(!temp->right) temp->right = newnode;
                temp = temp->right;
            }
            assert(temp->data == nodes[i]);
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
    // tree max
    int tree_max(){
        return tree_max(root);
    }
    int tree_max(node* temp){
        if(temp->right == nullptr && temp->left == nullptr)return temp->data;
        int op1 = -1 , op2 = -1;
        if(temp->right) op1 = tree_max(temp->right);
        if(temp->left) op2 = tree_max(temp->left);
        return  max(op1,op2);
    }
    // tree hieght
    int tree_hieght(){
        return tree_hieght(root);
    }
    int tree_hieght(node* temp ) {
        if (!temp->left && !temp->right)return 0;
        int op1 = -1, op2 = -1;
        if (temp->right) op1 = tree_hieght(temp->right) + 1;
        if (temp->left) op2 = tree_hieght(temp->left) + 1;
        return max(op1, op2);
    }
        // count_nodes
        int count_nodes(){
            return count_nodes(root) + 1;
        }
        int count_nodes(node *temp){
          if (!temp->left && !temp->right)return 0;
            int op1 = 0, op2 = 0;
            if (temp->right) op1 = count_nodes(temp->right) + 1;
            if (temp->left) op2 = count_nodes(temp->left) + 1;
            return op1 + op2 ;
    }
    // count_LEAVES
    int count_leaves(){
        return count_leaves(root) ;
    }
    int count_leaves(node *temp){
        if (!temp->left && !temp->right)return 1;
        int op1 = 0, op2 = 0;
        if (temp->right) op1 = count_leaves(temp->right) ;
        if (temp->left) op2 = count_leaves(temp->left) ;
        return op1 + op2 ;
    }
    // search
    bool search_tree(int val){
        return search_tree(root , val);
    }
    bool search_tree(node *temp , int val){
        if (!temp)return 0;
        int op1  = 0 , op2 = 0 , op3 = (temp->data  == val);
        if (temp->right) op1 = search_tree(temp->right , val);
        if (temp->left) op2 = search_tree(temp->left , val);
        return op1 | op2 | op3;
    }
    // is perfect or not ?
    bool is_perfect (){
        return is_perfect (root);
    }
    bool is_perfect (node *temp ) {
        if (!temp->left && !temp->right)return 1;
        if (!temp->left || !temp->right) return 0;
        int op1 = 0, op2 = 0;
        if (temp->right) op1 = is_perfect(temp->right);
        if (temp->left) op2 = is_perfect(temp->left);
        return op1 & op2;
    }
    // clear
    void clear(){
        clear(root);
    }
    void clear(node *temp) {
        if (!temp)return;
        clear(temp->left);
        clear(temp->right);
        delete temp;
        return;
    }
    // re_root
    void re_root(int val){
            node *newnode = new node (val);
            root = newnode;
    }
    // diameter
    int diameter(){
        return diameter(root).first;
    }
    pair<int,int>diameter(node *temp){
        if(!temp)return {0,0};
        pair<int,int>p1,p2;
        p1 = p2 = {0 , 0};
        p1 = diameter(temp->left);
        p2 = diameter(temp->right);
        return {max({p1.first , p2.first , p1.second + p2.second}) , max(p1.second , p2.second) + 1};
    }
    void print_inorder_iterative(){
        stack<pair<node*,bool>>st;
        node *another = root;
        st.push({another,0});
        while (st.size()){
            auto [temp , sign] = st.top();
            st.pop();
            if(sign)cout << temp->data <<" ";
            else {
                if(temp->right) st.push({temp->right,0});
                st.push({temp,1});
                if(temp->left) st.push({temp->left,0});
            }
        }
        cout << endl;
    }
    string print_infix(){
       return print_infix(root);
    }
    string print_infix(node *temp){
        if(!temp)return "";
        if(isdigit(temp->dat)){
            string ans ;
            ans.push_back(temp->dat);
            return ans;
        }
        string op1 , op2;
        string ans;
        if(temp->left) op1 = print_infix(temp->left);
        if(temp->right) op2 = print_infix(temp->right);
        ans = '(' + op1 + temp->dat + op2 + ')';
        return ans;
    }
    void print_level_traversal(){
        int n = tree_hieght() + 1;
        vector<vector<int>>v(n);
        print_level_traversal(root , 0 , v);
        for (int i = 0; i < n; ++i) {
            cout << "LEVEL " << i << " : ";
            for(auto &it : v[i])cout << it << ' ';
            cout << endl;
        }
    }
    void print_level_traversal(node *temp , int level , vector<vector<int>> &v){
        if(!temp)return;
        print_level_traversal(temp->left , level + 1 , v);
        print_level_traversal(temp->right, level + 1 , v);
        v[level].push_back(temp->data);
    }
    void print_level_spiral(){
        int n = tree_hieght() + 1;
        vector<deque<int>>v(n);
        print_level_spiral(root , 0 , v);
        for (int i = 0; i < n; ++i) {
            cout << "LEVEL " << i << " : ";
            for(auto &it : v[i])cout << it << ' ';
            cout << endl;
        }
    }
    void print_level_spiral(node *temp , int level , vector<deque<int>> &v){
        if(!temp)return;

            print_level_spiral(temp->left , level + 1 , v);
            print_level_spiral(temp->right, level + 1 , v);
        if(level & 1)v[level].push_front(temp->data);
        else
        v[level].push_back(temp->data);
    }
    bool is_complete(){
        return is_complete(root , 0 , tree_hieght());
    }
    bool is_complete(node *temp , int level , int last_level ){
        if(level == last_level)return 1;
        if(level != last_level - 1 && (!temp->right || !temp->left)) return 0;
        if(level == last_level - 1 && !temp->left)return 0;
        return is_complete(temp->left , level + 1 , last_level) & is_complete(temp->right , level + 1 , last_level);
    }


};

int main() {
    wageeh;
    int t = 1;
    //cin >> t;
    while (t--) {
        BinaryTree bt(1);
        cout << bt.is_perfect() << " " << endl;
//        bt.add_node({2} , "L");
//        bt.add_node({2,8,7} , "LRL");
//        bt.add_node({4,7,12,5} , "RRLL");
//        bt.add_node({4,6,9 , 15} , "RLRL");
        bt.add_node({2,4} , "LL");
        bt.add_node({2,5,98} , "LRR");
        bt.add_node({3} , "R");
        bt.add_node({3,7} , "RR");
        //bt.add_node({4,7,12,5} , "RRLL");
        //bt.add_node({4,6,9 , 15} , "RLRL");
        bt.print_in_order();
        bt.print_inorder_iterative();
        cout << bt.diameter() << " " << endl;
        bt.print_level_traversal();
        bt.print_level_spiral();
        cout << bt.is_complete() << endl;



    }
}

