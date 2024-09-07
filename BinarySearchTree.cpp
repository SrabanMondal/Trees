#include<iostream>
using namespace std;

class BST{
    public:
    int data;
    BST* left;
    BST* right;
    BST(int value) : data(value), left(nullptr), right(nullptr) {};

    BST* insert(int value){
        if(this==nullptr){
            BST* node= new BST(value);
            return node;
        }
        else{
            if(data>value){
                left=left->insert(value);
            }
            else if(data<value) {
                right=right->insert(value);
            }
            return this;
        }
    }
    void inorder(){
        if(left!=nullptr) left->inorder();
        cout<<data<<" ";
        if(right!=nullptr) right->inorder();
    }
    void postorder(){
        if(left!=nullptr) left->inorder();
        if(right!=nullptr) right->inorder();
        cout<<data<<" ";
    }
    void preorder(){
        cout<<data<<" ";
        if(left!=nullptr) left->inorder();
        if(right!=nullptr) right->inorder();
    }
    BST* deleteNode(int value) {
        if (value < data) {
            if (left != nullptr) {
                left = left->deleteNode(value);
            }
        } else if (value > data) {
            if (right != nullptr) {
                right = right->deleteNode(value);
            }
        } else {
            if (left == nullptr && right == nullptr) {
                delete this;
                return nullptr;
            } else if (left == nullptr) {
                BST* temp = right;
                delete this;
                return temp;
            } else if (right == nullptr) {
                BST* temp = left;
                delete this;
                return temp;
            } else {
                BST* successor = findMinNode(left);
                data = successor->data;
                left = left->deleteNode(successor->data);
            }
        }
        return this;
    }

    BST* findMinNode(BST* node) {
        BST* current = node;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }
    bool search(int value){
        if(value==data) return true;
        else if(value<data && left!=nullptr) return left->search(value);
        else if(value>data && right!=nullptr) return right->search(value);
        return false;
    }
};
int main(){
    BST *btree = new BST(5);
    btree->insert(3);
    btree->insert(2);
    btree->insert(4);
    btree->insert(15);
    btree->insert(17);
    btree->insert(12);
    btree->insert(10);
    cout<<"inorder-"; btree->inorder(); cout<<endl;
    cout<<"preorder-"; btree->preorder(); cout<<endl;
    cout<<"postorder-"; btree->postorder(); cout<<endl;
    btree->deleteNode(5);
    cout<<"inorder-"; btree->inorder(); cout<<endl;
    int n=10;
    if(btree->search(n)) {cout<<n<<" found";}
    else {cout<<n<<" not found";}
}