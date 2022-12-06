// Membuat Hash Dan Tree dengan SIZE 10
#include <iostream>
#include <list>
#include <string>
#define sizee 10
using namespace std;
//=================================HASH TABLE=========================================//
class Hash {
	int SIZE;
	list <string>* table;
public:
	Hash(int V); //constructor
	void insertItem(int x,string y, string z);
	int hashFunction(int x) {
		return (x % SIZE);
	}
	void printHash();
	void PrintTree();

};

Hash::Hash(int b) {
	this->SIZE = b;
	table = new list<string>[SIZE];
}

void Hash::insertItem(int key,string kode, string nama) {
	// jika index != null maka index+1
	int index = hashFunction(key);
	if (table[index].empty()) {
		table[index].push_back(kode);
		table[index].push_back(nama);
	}
	else {
		key++;
		insertItem(key, kode, nama);
	}
}

void Hash::printHash() {
	cout << "\n\tIndex\t| Kode\t| Nama Barang" << endl;
	cout << "\t-----------------------------" << endl;
	for (int i = 0; i < SIZE; i++) {
		cout <<"\t"<< i;
		if (table[i].empty()) {
			cout << "\t|\t|" << endl;
		}
		else {
			for (auto x : table[i]) {
				cout << "\t| " << x;
			}
			cout << endl;
		}
	}
	
}
//=======================TREE==========================//
struct node {
	int index;
	string kode;
	node* left;
	node* right;
};

class tree {
public:
	tree();
	void insert(int index, string kode);
	void insert(int index, string kode, node* leaf);
	void print();
	void printInorder(node* leaf);
	void printPreorder(node* leaf);
	void printPostOrder(node* leaf);
	node* root;
};

tree::tree() {
	root = NULL;
}

void tree::insert(int index, string kode, node* leaf) {
	if (index < leaf->index) {
		if (leaf->left != NULL) {
			insert(index, kode, leaf->left);
		}
		else {
			leaf->left = new node;
			leaf->left->index = index;
			leaf->left->kode = kode;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
	else if (index >= leaf->index) {
		if (leaf->right != NULL) {
			insert(index, kode, leaf->right);
		}
		else {
			leaf->right = new node;
			leaf->right->index = index;
			leaf->right->kode = kode;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}

void tree::insert(int index, string kode) {
	if (root != NULL) {
		insert(index, kode, root);
	}
	else {
		root = new node;
		root->index = index;
		root->kode = kode;
		root->left = NULL;
		root->right = NULL;
	}

}

void tree::printInorder(node* leaf) {
	if (leaf != NULL) {
		printInorder(leaf->left);
		cout << leaf->index << "-->" << leaf->kode << ", ";
		printInorder(leaf->right);
	}
}

void tree::printPreorder(node* leaf) {
	if (leaf != NULL) {
		cout << leaf->index << "-->" << leaf->kode << ", ";
		printPreorder(leaf->left);
		printPreorder(leaf->right);
	}
}

void tree::printPostOrder(node* leaf) {
	if (leaf != NULL) {
		printPostOrder(leaf->left);
		printPostOrder(leaf->right);
		cout << leaf->index << "-->" << leaf->kode << ", ";
	}
}

void tree::print() {
	cout << "\nTREE INORDER" << endl;
	printInorder(root);
	cout << "\nTREE Preorder" << endl;
	printPreorder(root);
	cout << "\nTREE PostOrder" << endl;
	printPostOrder(root);
}
//==============================Hash to tree=====================//
void Hash::PrintTree() {
	tree* btree = new tree();
	for (int i = 0; i < SIZE; i++) {
		for (auto item : table[i]) {
			btree->insert(i, item);
			break;
		}
	}
	btree->print();
}

int main() {
	int jml, number, inp;
	string kode[sizee], nama[sizee];
	cout << "Masukkan jumlah data yang ingin diinput = ";
	cin >> inp;
	
	for (int i = 0; i < inp; i++) {
		cout << "masukkan data kode = "; //input user kode
		cin >> kode[i];
		cout << "masukkan data nama barang = "; //input user nama
		cin >> nama[i];
	}
	
	Hash hs(sizee); //ukuran table hash 

	for (int i = 0; i < inp; i++) {
		hs.insertItem(stoi(kode[i]),kode[i], nama[i]); //input table hash
	}

	cout << "\nHASH TABLE:" << endl;
	hs.printHash(); //print table hash
	cout << "\nBinary Tree:" << endl;
	hs.PrintTree(); //print tree
	return 0;
}
