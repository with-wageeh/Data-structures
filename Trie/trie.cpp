#include <bits/stdc++.h>
using namespace std;
//struct node{
//    int data = -1;
//    bool leaf = 0;
//    node* arr[26] = {};
//    node(int d){
//        data = d;
//        for (int i = 0; i < 26 ; ++i) {
//            arr[i] = nullptr;
//        }
//    }
//};
//struct Trie{
//private:
//    node *root = new node (-1);
//public:
//    void set(string word){
//        set(0 , word , root);
//    }
//    void set(int idx , string s , node *temp){
//        if(idx == s.size()){
//            temp->leaf = 1;
//            return;
//        }
//        if(!temp->arr[s[idx] - 'a']) temp->arr[s[idx] - 'a'] = new node (s[idx] - 'a');
//        set(idx + 1 , s , temp -> arr[s[idx] - 'a']);
//    }
//    void insert_iterative(string x){
//        node *temp = root;
//        int idx = 0;
//        while (idx != x.size()){
//            if(!temp->arr[x[idx] - 'a']) temp->arr[x[idx] - 'a'] = new node(x[idx] - 'a');
//            temp = temp->arr[x[idx] - 'a'];
//            idx++;
//        }
//        temp->leaf = 1;
//    }
//    void print_all_prefix(){
//        print_all_prefix(root , "" );
//    }
//    void print_all_prefix(node *temp , string res){
//        for (int i = 0; i < 26 ; ++i) {
//            if(temp->arr[i])print_all_prefix(temp->arr[i] , res + char(i + 'a'));
//        }
//        if(res.size()) cout << res << endl;
//    }
//    void print_all_words(){
//        print_all_words(root , "" );
//    }
//    void print_all_words(node *temp , string res){
//        if(temp->leaf) cout << res << endl;
//        for (int i = 0; i < 26 ; ++i) {
//            if(temp->arr[i])print_all_words(temp->arr[i] , res + char(i + 'a')) ;
//        }
//    }
//    bool word_exist(string s){
//        return word_exist(0 ,s , root);
//    }
//    bool word_exist(int idx , string s , node* temp){
//        if(idx == s.size()) return temp->leaf;
//
//        if(temp->arr[s[idx] - 'a']) return word_exist(idx + 1 , s , temp->arr[s[idx] - 'a']);
//        else return 0;
//    }
//    bool prefix_exist(string s){
//        return prefix_exist(0 ,s , root);
//    }
//    bool prefix_exist(int idx , string s , node* temp){
//        if(idx == s.size()) return 1;
//
//        if(temp->arr[s[idx] - 'a']) return prefix_exist(idx + 1 , s , temp->arr[s[idx] - 'a']);
//        else return 0;
//    }
//    string minimal_prefix(string s){
//        return minimal_prefix(0 , s , root);
//    }
//    string minimal_prefix(int i , string s , node*temp){
//        if (i == s.size())return s;
//        if(temp->leaf)return s.substr(0 , i);
//        int nxt = s[i] - 'a';
//        if(temp->arr[nxt]) return minimal_prefix(i + 1 , s , temp->arr[nxt]);
//        else return s;
//    }
//    void auto_complete(string s){
//        auto_complete( s , root);
//    }
//    void auto_complete(string s , node*temp , string ans = "" , int idx = 0){
//        if(!temp)return;
//        if(idx>= s.size() && temp->leaf) cout << ans << endl;
//        if(idx < s.size()){
//            auto_complete(s , temp->arr[s[idx] - 'a'] , ans + s[idx] , idx + 1);
//        }
//        else
//        for (int i = 0; i < 26; ++i) {
//            if(temp->arr[i]) auto_complete(s , temp->arr[i] , ans + (char) (i + 'a') , idx + 1);
//        }
//    }
//    bool exist_with_one_change(string s){
//        return exist_with_one_change(0 , s , root ,0);
//    }
//    bool exist_with_one_change(int i , string s , node *temp , int num_of_changes){
//        if(num_of_changes > 1) return 0;
//        if(i == s.size()) return num_of_changes;
//        bool ans = 0;
//        for (int j = 0; j < 26; ++j) {
//            if(temp->arr[j]) ans |= exist_with_one_change(i + 1 , s , temp->arr[j] , num_of_changes + (j != s[i] - 'a'));
//        }
//        return ans;
//    }
//};
//struct Node{
//    string data = "";
//    bool leaf = 0;
//    map<string ,Node*>mp;
//    Node(string s){
//        data = s;
//    }
//};
//struct Trie_strings{
//private:
//    Node *root = new Node ("");
//public:
//    void set(vector<string> v){
//        set(0 , v , root);
//    }
//    void set(int idx , vector<string>v , Node *temp){
//        if(idx == v.size()){
//            temp->leaf = 1;
//            return;
//        }
//      if(!temp->mp.count(v[idx]))temp->mp[v[idx]] = new Node(v[idx]);
//      set(idx + 1 , v , temp->mp[v[idx]]);
//    }
//   bool path_exist(vector<string>v){
//       return path_exist(0 , v , root);
//    }
//    bool path_exist(int i , vector<string>v , Node *temp){
//        if(i == v.size())return 1;
//        if(!temp->mp.count(v[i])) return 0;
//        return path_exist(i + 1 , v , temp->mp[v[i]]);
//    }
//
//};
struct node{
    int data = -1;
    bool leaf = 0;
    map<pair<int,int>, node*> mp;
    node(int i ){
        data = i;
    }
};
struct Trie{
private:
    node *root = new node (-1);
public:
    void set(string word , int id){
        set(0 ,word.size() - 1 ,  word , root , id);
    }
    void set(int idx , int end ,  string s , node *temp , int id){
        if(idx == s.size()){
            temp->leaf = 1;
            return;
        }
        int pre = s[idx]  - 'a' , suf = s[end] - 'a';
        if(!temp->mp.count({pre , suf})) temp->mp[{pre , suf}] = new node (id);
        set(idx + 1 , end - 1 , s , temp -> mp[{pre , suf}] , id);
    }
    int search( string pre , string suf){
        return search(0 , 0 , pre , suf , root);
    }
    int search (int st , int end , string pre  , string suf , node *temp){
        if(!temp) return -1;
        if(st == pre.size() && end == suf.size() && temp->leaf) return temp->data;

        if(st < pre.size() && end < suf.size()){
            int p = pre[st] - 'a' , s = suf[end] - 'a';
            if(temp->mp.count({p,s}))
            return search(st + 1  , end + 1  , pre , suf , temp-> mp[{p , s}]);
            else return -1;
        }
        else if (st < pre.size()){
            int p = pre[st] - 'a' ;
            int ans = -1;
            for (int i = 0; i < 26 ; ++i) {
                if(temp->mp.count({p,i}))
                ans = max(ans , search(st + 1 , end , pre, suf , temp->mp[{p , i}]));
            }
            return ans;
        }
        else if (end < suf.size()){
            int  s = suf[end] - 'a';
            int ans = -1;
            for (int i = 0; i < 26 ; ++i) {
                if(temp->mp.count({i,s}))
                    ans = max(ans , search(st , end + 1 , pre, suf , temp->mp[{i , s}]));
            }
            return ans;
        }
        else{
            int ans = -1;
            for (int i = 0; i < 26 ; ++i) {
                for (int j = 0; j < 26 ; ++j) {
                    if(temp->mp.count({i,j})){
                        ans = max(ans , search(st  , end  , pre, suf , temp->mp[{i , j}]));
                    }

                }
            }
            return ans;
        }
    }

};
int main(){
//    Trie t;
//    t.set("abcd");
//    t.set("xyz");
//    t.insert_iterative("abvc");
//    t.set("dfgmkdjgdfkgdfkifd");
//    t.set("dfgmkdjgdfkgdfkifdd");
//   // t.print_all_prefix();
//   // cout << endl;
//    //t.print_all_words();
//    //cout << endl;
//    t.set("ab");
//    cout << endl;
//    cout << t.exist_with_one_change("absd ");
//   // t.print_all_words();
//    //cout << t.prefix_exist("dfgmkdjgdf");
//   // cout << t.word_exist("abvc");
//    cout << t.minimal_prefix("xyzfdf");
Trie t;
vector<string> v = {"aae" , "apple" , "bannana" , "akldfjgdisorfgdsfdfdfgfg" , "aplicationae"} ;
vector<pair<string,string>> q = {{"a" , "e"} , {"a" , "x"} , {"app" ,"le"} , {"a","fd"}};
    for (int i = 0; i <v.size() ; ++i) {
        t.set(v[i] , i);
    }
    for (int i = 0; i <q.size() ; ++i) {
        reverse(q[i].second.begin() , q[i].second.end());
            cout << t.search(q[i].first , q[i].second) << endl;


    }

}