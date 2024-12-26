#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *left = NULL, *right = NULL;
    int height = 0;
    int data = 0;
    int number_children = 0;

    Node(int d) {
        data = d;
    }

    int cal_height(Node *node) {
        if (!node)return -1;
        return node->height;
    }

    int cal_children(Node *node) {
        if (!node)return 0;
        return node->number_children;
    }

    int get_height() {
        return height = 1 + max(cal_height(left), cal_height(right));
    }

    int get_children() {
        return number_children = cal_children(left) + cal_children(right) + (left != nullptr) + (right != nullptr);
    }

    int balance_factor() {
        return cal_height(left) - cal_height(right);
    }
};

class AVL {
private:
    Node *root = nullptr;
    int size = 0;
public:

    Node *left_rotation(Node *tree) {
        auto *it = tree->right->left;
        auto x = tree->right;
        x->left = tree;
        tree->right = it;
        tree->get_height();
        x->get_height();
        tree->get_children();
        x->get_children();
        return x;
    }

    Node *right_rotation(Node *tree) {
        auto it = tree->left;
        auto x = it->right;
        tree->left = x;
        it->right = tree;
        tree->get_height();
        it->get_height();
        tree->get_children();
        it->get_children();
        return it;
    }

    Node *balance(Node *node) {
        int b = node->balance_factor();
        if (b == 2) {// left
            if (node->left->balance_factor() == -1)// left right
                node->left = left_rotation(node->left);// to make it left left
            node = right_rotation(node);
        } else if (b == -2) {// right
            if (node->right->balance_factor() == 1)// right left
                node->right = right_rotation(node->right); // to ,ake it right right
            node = left_rotation(node);
        }
        return node;
    }

    Node *insert(int x, Node *tree) {
        if (x < tree->data) {
            if (!tree->left) tree->left = new Node(x);
            else
                tree->left = insert(x, tree->left);
        } else {
            if (!tree->right) {
                tree->right = new Node(x);
            } else
                tree->right = insert(x, tree->right);
        }
        tree->get_height();
        tree->get_children();
        return balance(tree);
    }

    void insert(int x) {
        if (root) {
            root = insert(x, root);
        } else {
            root = new Node(x);
        }
        size++;
    }

    Node *delete_node(int x, Node *node) {
        if (x < node->data && node->left) {
            node->left = delete_node(x, node->left);
        } else if (x > node->data && node->right) {
            node->right = delete_node(x, node->right);
        } else {// arrive to the target
            Node *temp = node;
            if (!temp->left && !temp->right) {
                node = nullptr;
            } else if (!temp->left) {
                node = temp->right;
            } else if (!temp->right) {
                node = temp->left;
            } else {// has 2 children
                Node *successor = temp->right;
                while (successor && successor->left)successor = successor->left;
                node->data = successor->data;
                node->right = delete_node(successor->data, node->right);
                temp = nullptr; // don't delete the node , the successor wil be delteted
            }
            if (temp)delete temp;
        }
        if (node) {
            node->get_height();
            node->get_children();
            node = balance(node);
        }
        return node;
    }

    void delete_node(int x) {
        if (root)root = delete_node(x, root);
    }

    void print() {
        print(root);
    }

    void print(Node *node) {
        if (!node)return;
        print(node->left);
        cout << node->data << ' ' << node->get_height() << " ";
        if (node->left)
            cout << "left =  " << node->left->height << " ";
        if (node->right)
            cout << "right =   " << node->right->height;
        cout << endl;
        print(node->right);
    }

    int lower_bound(int x) {
        return lower_bound(x, root);
    }

    int lower_bound(int x, Node *node) {
        if (!node)return 2e9;
        if (x <= node->data) return min(node->data, lower_bound(x, node->left));
        else return lower_bound(x, node->right);
    }

    int upper_bound(int x) {
        return upper_bound(x, root);
    }

    int upper_bound(int x, Node *node) {
        if (!node)return 2e9;
        if (x < node->data) return min(node->data, upper_bound(x, node->left));
        else return upper_bound(x, node->right);
    }

    bool count(int x) {
        return count(x, root);
    }

    bool count(int x, Node *node) {
        return lower_bound(x) == x;
    }
    int calculate(int x){
        return calculate(x , root);
    }
    int calculate(int x , Node *node){
        if(x == node->data)return  (node->right->cal_children(node->right) + (node->right != nullptr));
        if(x < node->data)
            return calculate(x , node->left) + (node->right->cal_children(node->right) + 1 + (node->right != nullptr));
        else
            return calculate(x , node->right);
    }

    int count_inversions(int arr[] , int n){
        Node *temp = root;
        root = NULL;
        int sz = size;
        size = 0;
        int ans = count_inversions(arr , n ,root );
        root = temp;
        size = sz;
        return ans;
    }

    int count_inversions(int arr[] ,int n , Node *node){
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            insert(arr[i]);
            cout << arr[i] << " " << calculate(arr[i]) << " " << size <<  endl;
            ans += calculate(arr[i]);
        }
        print();
        return ans;
    }
};

int main() {
    AVL tree;
    vector<int> v{3, 5, 1, 0, 2, 6, 10, 7, 4, 8};
    int arr[] = {10,5,8,2,12,6};
    vector<int> s{3, 5, 9, 1, 0, 2, 6, 10, 7, 4, 8, 1354, 456, 45, 16, 54, 0, 54, 6, 9};
    for (int i = 0; i < v.size(); ++i) {
        tree.insert(v[i]);
    }
    cout << tree.count_inversions(arr, 6) << endl;
//    for (int i = 0; i <s.size() ; ++i) {
//        cout << tree.upper_bound(s[i]) << " " << tree.count(s[i]) <<endl;
//    }

//    tree.insert(5);
//    tree.print();
//    cout << endl;
}