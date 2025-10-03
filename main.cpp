//game leaderboard project (trying to implement what I learnt in DS course)
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string n;
    int s;
    Node* l;
    Node* r;

    Node(string name, int score) : n(name), s(score), l(nullptr), r(nullptr) {}
};

Node* minNode(Node* root) {
    while (root && root->l) root = root->l;
    return root;
}

Node* del(Node* root, string name) {
    if (!root) return nullptr;

    if (name < root->n)
        root->l = del(root->l, name);
    else if (name > root->n)
        root->r = del(root->r, name);
    else {
        if (!root->l) {
            Node* temp = root->r;
            delete root;
            return temp;
        }
        else if (!root->r) {
            Node* temp = root->l;
            delete root;
            return temp;
        }
        else {
            Node* temp = minNode(root->r);
            root->n = temp->n;
            root->s = temp->s;
            root->r = del(root->r, temp->n);
        }
    }
    return root;
}

Node* insert(Node* root, string name, int score) {
    if (!root) return new Node(name, score);

    if (score < root->s)
        root->l = insert(root->l, name, score);
    else if (score > root->s)
        root->r = insert(root->r, name, score);
    else {
        if (name < root->n) root->l = insert(root->l, name, score);
        else root->r = insert(root->r, name, score);
    }

    return root;
}

void printBoard(Node* root) {
    if (!root) return;
    printBoard(root->r); 
    cout << root->n << " : " << root->s << endl;
    printBoard(root->l);
}

Node* find(Node* root, string name) {
    if (!root || root->n == name) return root;
    
    Node* left = find(root->l, name);
    return left ? left : find(root->r, name);
}

Node* update(Node* root, string name, int newScore) {
    if (!find(root, name)) {
        cout << "Player not found!\n";
        return root;
    }

    root = del(root, name);       
    return insert(root, name, newScore);
}

int main() {
    Node* root = nullptr;

    root = insert(root, "Jacob", 100);
    root = insert(root, "Bella", 150);
    root = insert(root, "Edward", 120);

    cout << "Leaderboard:\n";
    printBoard(root);

    root = update(root, "Jacob", 160);

    cout << "\nUpdated Leaderboard:\n";
    printBoard(root);

    return 0;
}