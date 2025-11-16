#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//struktur petugas
struct Petugas {
    string id;
    string nama;
};

vector <Petugas> daftarPetugas;

//membuat ID 6 digit otomatis
string generateID6() {
    string id = "";
    for (int i = 0; i < 6; i++) {
        id += to_string(rand() % 10);
    }
    return id;
}
//tambah petugas
void tambahPetugas() {
    string nama;
    cout << "Masukkan nama petugas: ";
    getline(cin, nama);

    string id = generateID6();
    daftarPetugas.push_back({id, nama});

    cout << "Petugaas \"" << nama << "\" berhasil ditambahkan dan IDnya: " << id << endl;
}
//tampilkan semua petugas
void tampilkanPetugas() {
    cout << "\n === DAFTAR PETUGAS ===" << endl;
    cout << "NO | Nama             | ID" << endl;
    cout << "---------------------------" << endl;


int n0 =1;
for (auto p : daftarPetugas) {
    cout << n0 << " | "
         << p.nama << " | "
         << p.id << endl;
    n0++;
   }
}

int main()
{
    srand(time(0));

    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
        tambahPetugas();

        cout << "Tambah petugas lain? (y/n): ";
        cin >> lagi;
        cin.ignore();
    }
    tampilkanPetugas();
    return 0;
