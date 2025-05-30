#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Koruptor {
    string nama;
    string jabatan;
    int jumlahKorupsi;
};

struct Node {
    Koruptor data;
    Node* left;
    Node* right;
};

Node* insert(Node* root, Koruptor data) {
    if (root == nullptr) { // masih kosong
        Node* newNode = new Node{data, nullptr};
        return newNode;
    }
    if (data.nama < root->data.nama) { // geser ke kiri
        root->left = insert(root->left, data);
    } else { // geser ke kanan
        root->right = insert(root->right, data);
    }
    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Nama: " << root->data.nama << ", Jabatan: " << root->data.jabatan
             << ", Jumlah Korupsi: " << root->data.jumlahKorupsi << endl;
        inorder(root->right);
    }
}

Node* findMin(Node* root) {
    while (root && root->left != nullptr)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, string nama, stack<Koruptor>& deletedStack) {
    if (root == nullptr) return root;
    if (nama < root->data.nama) {
        root->left = deleteNode(root->left, nama, deletedStack);
    } else if (nama > root->data.nama) {
        root->right = deleteNode(root->right, nama, deletedStack);
    } else {
        deletedStack.push(root->data);
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.nama, deletedStack);
    }
    return root;
}

int main() {
    Node* root = nullptr;
    stack<Koruptor> deletedStack;
    int pilihan;
    do {
        cout << "\nMenu:\n1. Tambah Data\n2. Tampilkan Data\n3. Hapus Data\n4. Undo Hapus Terakhir\n5. Tampilkan Stack Hapus\n0. Keluar\nPilih: ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 1) {
            int n;
            cout << "Berapa data yang ingin dimasukkan? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; ++i) {
                Koruptor k;
                cout << "\nData ke-" << (i + 1) << endl;
                cout << "Nama: "; getline(cin, k.nama);
                cout << "Jabatan: "; getline(cin, k.jabatan);
                cout << "Jumlah Korupsi: "; cin >> k.jumlahKorupsi; cin.ignore();
                root = insert(root, k);
            }
        } else if (pilihan == 2) {
            cout << "Data Koruptor (Inorder):\n";
            inorder(root);
        } else if (pilihan == 3) {
            int n;
            cout << "Berapa data yang ingin dihapus? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; ++i) {
                string nama;
                cout << "Nama yang akan dihapus ke-" << (i + 1) << ": ";
                getline(cin, nama);
                root = deleteNode(root, nama, deletedStack);
            }
        } else if (pilihan == 4) {
            if (!deletedStack.empty()) {
                Koruptor k = deletedStack.top();
                deletedStack.pop();
                root = insert(root, k);
                cout << "Undo berhasil. Data dikembalikan ke BST.\n";
            } else {
                cout << "Stack kosong, tidak ada yang bisa di-undo.\n";
            }
        } else if (pilihan == 5) {
            cout << "Data yang sudah dihapus (dari stack):\n";
            stack<Koruptor> temp = deletedStack;
            while (!temp.empty()) {
                Koruptor k = temp.top();
                cout << "Nama: " << k.nama << ", Jabatan: " << k.jabatan
                     << ", Jumlah Korupsi: " << k.jumlahKorupsi << endl;
                temp.pop();
            }
        } else if (pilihan == 6) {
            cout << "Keluar dari program.\n";
            break;
        }
    } while (pilihan != 0);
    return 0;
}