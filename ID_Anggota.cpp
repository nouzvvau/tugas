#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

struct Anggota
{
    string id;
    string nama;
    string alamat;
    string ttl;
    string email;
    bool status;
};

vector<Anggota> daftarAnggota;

//membuat id 6 digit otomatis
string generateID6() {
    string id = "";
    for (int i = 0; i < 6; i++) {
        id += to_string(rand() % 10); // mengambil angka random 0-9, ubah jadi string lalu di gabung ke id
    }
    return id;
}

//menambahkan anggota
void TambahAnggota(){
    Anggota u;

    u.id = generateID6();

    cout << "Masukkan nama lengkap: ";
    getline(cin, u.nama);

    cout << "Masukkan alamat: ";
    getline(cin, u.alamat);
    
    cout << "Masukkan tempat tanggal lahir (Tempat, YYYY-MM-DD): ";
    getline(cin, u.ttl); 

    cout << "Masukkan email: ";
    getline(cin, u.email);

    string inputStatus;
    cout << "Status (aktif/nonaktif): ";
    getline(cin, inputStatus);
    u.status = (inputStatus == "aktif");

    //MENULIS DATA ANGGOTA KE DALAM FILE anggota.txt
    //isine mek percobaan tok cah hehe
    ofstream file("anggota.txt", ios::app);
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }

    file << u.id << " | ";
    file << u.nama << " | ";
    file << u.alamat << " | ";
    file << u.ttl << " | ";
    file << u.email << " | ";
    file << (u.status ? "aktif" : "nonaktif");
    file << endl;
    file.close();

    //OUTPUT
    cout << "\n=====DATA ANGGOTA=====\n";
    cout << "Kode = " ;
    cout << "\nNama: " << u.nama;
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
            TambahAnggota();

    cout << "\nTambah anggota lagi? (y/n): ";
    cin >> lagi;
    cin.ignore();
    }
    tampilkanAnggota();

    return 0;
}