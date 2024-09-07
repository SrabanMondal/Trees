#include<iostream>
using namespace std;
struct Node{
    int data;
    struct Node* right;
    struct Node* left;
    struct Node* parent;
};
class SplayTree{
    Node* root;
    public:
    SplayTree(){
        root=nullptr;
    }
    void insert(int data);
    void deletetopdown(int data);
    void deletebottomup(int data);
    Node* findmax(Node* n);
    bool search(int data);
    void splay(Node *n);
    void zig(Node* n);
    void zag(Node* n);
    void print(Node* node){
        if(node->left!=nullptr) print(node->left);
        cout<<node->data<<" ";
        if(node->right!=nullptr) print(node->right);
    }
    void print_tree(){
        Node* cur = root;
        if(cur==nullptr){
            return;
        }
        print(cur);
    }
};
void SplayTree::insert(int value){
    if (root == nullptr) {
        root = new Node;
        root->data = value;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
    }  
    Node* cur = root;
    Node* prev = nullptr;
    while(cur!=nullptr){
        prev=cur;
        if(cur->data>value) cur = cur->left;
        else if(cur->data<value) cur= cur->right;
        else{
            splay(cur); return;
        }
    }
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr; 
    newNode->parent = prev;
    if(prev->data > value) prev->left = newNode;
    else prev->right = newNode;
    splay(newNode);
}
void SplayTree::splay(Node* n){
    while(n!=root){
    if(n->parent->parent==nullptr){
        if(n->parent->data < n->data) zig(n->parent);
        else zag(n->parent);
    }
    else{
        Node* par = n->parent;
        Node* grandpar = n->parent->parent;
        if(grandpar->left==par && par->left==n){
            zag(grandpar); zag(par);
        }
        else if(grandpar->right==par && par->right==n) {
            zig(grandpar); zig(par);
        }
        else if(grandpar->left == par && par->right == n){
            zig(par);
            zag(grandpar);
        }
        else {
            zag(par); 
            zig(grandpar);
        }
    }}
}
void SplayTree::zig(Node* n){
    Node* x = n->right;
    Node* y = x->left;
    n->right = y;
    x->parent = n->parent;
    if(y!=nullptr){ y->parent = n; }
    if(n->parent==nullptr) {root=x; x->parent = nullptr;}
    else if(n->parent->left == n) n->parent->left = x;
    else n->parent->right = x;
    x->left = n;
    n->parent = x;
}
void SplayTree::zag(Node* n){
    Node* x = n->left;
    Node* y = x->right;
    n->left = y;
    x->parent = n->parent;
    if(y!=nullptr) y->parent = n;
    if(n->parent == nullptr) {root=x; x->parent = nullptr;}
    else if(n->parent->left == n) n->parent->left=x;
    else n->parent->right=x;
    x->right = n;
    n->parent = x;
}
bool SplayTree::search(int value){
    Node* current = root;
    Node* prev = nullptr;
    while(current!=nullptr){
        if(current->data==value) break;
        prev=current;
        if(current->data<value){
            current = current->right;
        }else{
            current = current->left;
        }
    }
    if(current==nullptr){
        splay(prev);
        return false;
    }
    else{
        splay(current);
        return true;
    }
}
void SplayTree::deletetopdown(int data){
    if(!search(data)) return;
    Node *temp = root;
    Node* lefttree = temp->left;
    Node* righttree = temp->right;
    delete temp;
    if(lefttree==nullptr){
        root = righttree;
        if (righttree != nullptr)
            righttree->parent = nullptr;
    }
    else{
        lefttree->parent = nullptr;
        Node* maxNode = lefttree;
        while (maxNode->right != nullptr)
            maxNode = maxNode->right;
        splay(maxNode);
        root->right = righttree;
        if (righttree != nullptr)
            righttree->parent = root;
    }
    delete lefttree;
}
void SplayTree::deletebottomup(int value){
    if(root==nullptr) return;
    Node* current = root;
    Node* prev = nullptr;
    while(current!=nullptr){
        if(current->data==value) break;
        prev=current;
        if(current->data<value){
            current = current->right;
        }else if(current->data>value){
            current = current->left;
        }
    }
    if(current==nullptr){
        splay(prev); return;
    }
    if(current->left==nullptr && current->right==nullptr){
        Node* temp=current;
        if(current->parent!=nullptr){
            if(temp->data < prev->data) {
                prev->left = nullptr;
            }else{
                prev->right = nullptr;
            }
        }
        current=nullptr;
        delete temp;
    }
    else if(current->left==nullptr){
        Node* temp=current;
        if(current->parent!=nullptr){
            if(temp->data < prev->data)  {
                prev->left = current->right;
            }else{
                prev->right = current->right;
            }
        }
        else{
            current->right->parent = current->parent;
            current->right = nullptr;
        }
        current = nullptr;
        delete temp;
    }
    else if (current->right==nullptr)
    {
        Node* temp=current;
        if(current->parent!=nullptr){
            if(temp->data < prev->data)  {
                prev->left = current->left;
            }else{
                prev->right = current->left;
            }
        }
        else{
            current->left->parent = current->parent;
            root=current->left;
        }
        current=nullptr;
        delete temp;
    }
    else{
        Node* temp= findmax(current->left);
        int a=temp->data;
        deletebottomup(temp->data);
        current->data=a;
        prev = current;
    }
    if(prev!=nullptr)
    {
    splay(prev);
    }
}
Node* SplayTree::findmax(Node* n){
    while(n->right != nullptr)
        n = n->right;
    return n;
}
int main(){
    SplayTree st;
    int arr[]={12,34,56,33,10,16};
    for(int i=0; i<6; i++){
    }
    st.insert(arr[0]);
    st.insert(arr[1]);
    st.insert(arr[2]);
    st.insert(arr[3]);
    st.insert(arr[4]);
    st.insert(arr[5]);
    //if(st.search(46)) cout<<"56 found\n";
    //else cout<<"fail\n";
    st.print_tree();
    cout<<endl;
    st.deletebottomup(46);
    //st.deletetopdown(56);
    st.print_tree();
}