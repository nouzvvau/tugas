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

//MENAMBAHKAN ANGGOTA
void TambahAnggota(){
    Anggota u;

    cout << "===== MENAMBAHKAN ANGGOTA =====\n";

    u.id = generateID6();

    cout << "Masukkan nama lengkap: ";
    getline(cin, u.nama);

    cout << "Masukkan alamat: ";
    getline(cin, u.alamat);
    
    cout << "Masukkan ttl (Tempat, YYYY-MM-DD): ";
    getline(cin, u.ttl); 

    cout << "Masukkan email: ";
    getline(cin, u.email);

    string inputStatus;
    cout << "Status (aktif/nonaktif): ";
    getline(cin, inputStatus);
    u.status = (inputStatus == "aktif");

    //MENULIS DATA ANGGOTA KE DALAM FILE anggota.txt
    //isine mek percobaan tok cah hehe
    ofstream file;
    file.open("anggota.txt", ios::app);
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }
    file << u.id << " | ";
    file << u.nama << " | ";
    file << u.alamat << " | ";
    file << u.ttl << " | ";
    file << u.email << " | ";
    file << u.status;
    file << endl;
    file.close();

    cout << "Anggota berhasil ditambahkan!" << endl;
};

//MENAMPILKAN SEMUA ANGGOTA
void tampilkanAnggota(){
    cout << "\n===== DAFTAR ANGGOTA =====\n";
    ifstream file;
    string data [6];

    file.open("anggota.txt");

    file >> data[6];

    cout << data[0] << endl;
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