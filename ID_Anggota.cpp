#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Anggota
{
    string id;
    string nama;
};

vector<Anggota> daftarAnggota;

//membuat id 6 digit otomatis
string generateID6() {
    string id = " ";
    for (int i = 0; i < 6; i++) {
        id += to_string(rand() % 10); // mengambil angka random 0-9, ubah jadi string lalu di gabung ke id
    }
    return id;
}

//tambah anggota
void tambahAnggota() {
    string nama;
    cout << "Masukkan nama anggota : ";
    getline(cin, nama);

    string id = generateID6();
    daftarAnggota.push_back({id, nama}); //simpan anggota baru di daftar

    cout << "Anggota \"" << nama << "\" berhasil ditambahkan dan IDnya: " << id << endl;
}

//menampilkan semua anggota
void tampilkanAnggota(){
    cout << "\n === DAFTAR ANGGOTA ===" << endl;
    for (auto a : daftarAnggota){
        cout << "Nama: " << a.nama << " | ID: " << a.id << endl;
        }
}

int main() {
    srand(time(0)); // agar id yang di berikan berbeda setiap di run

    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
            tambahAnggota();

    cout << "Tambah anggota lagi? (y/n): ";
    cin >> lagi;
    cin.ignore();
    }
    tampilkanAnggota();

    return 0;
}
