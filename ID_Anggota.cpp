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
void TambahAnggota(){
    Anggota u;

    cout << "\nMasukkan nama lengkap: ";
    getline(cin, u.nama);

    cout << "\nMasukkan alamat (Kab, Kec, Ds): ";
    getline(cin, u.alamat);
    
    cout << "\nMasukkan tempat tanggal lahir (Tempat, YYYY-MM-DD): ";
    getline(cin, u.ttl);
    int pos = u.ttl.find(" ");

    cout << "\nMasukkan email: ";
    getline(cin, u.email);

string inputStatus;
    cout << "\nStatus (aktif/nonaktif): ";
    getline(cin, inputStatus);
    u.status = (inputStatus == "aktif");

    cout << "\n=====DATA ANGGOTA=====\n"; //OUTPUT
    cout << "KODE = " << endl;
    cout << "Nama: " << u.nama;
    cout << "\nAlamat: " << u.alamat;
    cout << "\nTTL: " << u.ttl;
    cout << "\nEmail: " << u.email;
    cout << "\nStatus: " << (u.status ? "aktif" : "nonaktif") << endl;
};


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


