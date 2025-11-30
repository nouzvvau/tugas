#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Anggota
{
    string id;
    string kode;
    string nama;
    string alamat;
    string ttl;
    string email;
    bool status;
};

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

    // ===== ... BUAT KODE 11 DIGIT ... =====
    // Mengambil tanggal asli: "YYYY-MM-DD"
    string tanggalAsli = u.ttl.substr(u.ttl.find(",") + 2);
    string tahun = tanggalAsli.substr(0, 4);
    string bulan = tanggalAsli.substr(5, 2);
    string tanggal = tanggalAsli.substr(8, 2);

    string baseKode = tahun + bulan + tanggal;

    // Hitung nomor urut untuk hari yang sama
    int noUrut = 1;
    ifstream cek("data/anggota.txt");
    string baris;
    while (getline(cek, baris)) {
        if (baris.find(baseKode) != string::npos) {
            noUrut++;
        }
    }
    cek.close();

    // Format nomor urut 3 digit
    string urut;
    if (noUrut < 10) urut = "00" + to_string(noUrut);
    else if (noUrut < 100) urut = "0" + to_string(noUrut);
    else urut = to_string(noUrut);

    u.kode = baseKode + urut;


    cout << "Masukkan email: ";
    getline(cin, u.email);

    cout << "Status (1/0): "; //(1) jika aktif, (0) jika nonaktif
    cin >> u.status;
    
    //.....===== MENULIS DATA ANGGOTA KE DALAM FILE anggota.txt =====.....
    ofstream file("data/anggota.txt", ios::app);
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }
    file << u.id << "|";
    file << u.kode << "|";
    file << u.nama << "|";
    file << u.alamat << "|";
    file << u.ttl << "|";
    file << u.email << "|";
    file << u.status << endl;
    file.close();

    cout << "Anggota berhasil ditambahkan!" << endl;
};

//.....===== MENAMPILKAN SEMUA ANGGOTA SECARA ASCENDING =====.....
void tampilkanAnggota(){
    ifstream file;
    string baris;
    string id, kode, nama, alamat, ttl, email;
    bool status;

    file.open("data/anggota.txt");
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }

    vector<Anggota> list;

    while (getline(file, baris))
    {
        //jika baris kosong maka lewati
        if(baris.empty()){continue;}

        stringstream ss(baris);
        Anggota u;

        getline(ss, u.id, '|');
        getline(ss, u.kode, '|');
        getline(ss, u.nama, '|');
        getline(ss, u.alamat, '|');
        getline(ss, u.ttl, '|');
        getline(ss, u.email, '|');
        string statusSTR;
        getline(ss, statusSTR, '|');
        u.status = (statusSTR == "1");

        list.push_back(u);
    }
    file.close();

    // SORTING ASCENDING BERDASARKAN NAMA
    sort(list.begin(), list.end(), [](const Anggota &a, const Anggota &b) {
        return a.nama < b.nama;
    });

    //OUTPUT
    cout << "\n===== DAFTAR ANGGOTA =====\n";
    for (auto &u : list){
        cout << "ID       : " << u.id << endl;
        cout << "Kode     : " << u.kode << endl;
        cout << "Nama     : " << u.nama << endl;
        cout << "Alamat   : " << u.alamat << endl;
        cout << "TTL      : " << u.ttl << endl;
        cout << "Email    : " << u.email << endl;
        cout << "Status   : " << (u.status ? "aktif" : "nonaktif") << endl;
        cout << "------------------------------------------------" << endl << endl;
    }  
}

//...=== CARI ANGGOTA === ...
void CariAnggota(){
    string cariKode;
    cout << "\n=====PENCARIAN ANGGOTA=====\n";
    cout << "\nMasukkan kode anggota : ";
    cin >> cariKode;
    cin.ignore();

    ifstream cari;
    string baris;
    bool ketemu = false;

    cari.open("data/anggota.txt");
    if(!cari){
        cout << "File tidak bisa dibuka!" << endl;
    }

    while (getline(cari, baris))
    {
        //jika baris kosong maka lewati
        if(baris.empty()){continue;}

        stringstream ss(baris);
        string id, kode, nama, alamat, ttl, email;
        bool status;

        getline(ss, id, '|');
        getline(ss, kode, '|');
        getline(ss, nama, '|');
        getline(ss, alamat, '|');
        getline(ss, ttl, '|');
        getline(ss, email, '|');
        string statusSTR;
        getline(ss, statusSTR, '|');
        status = (statusSTR == "1");

        if (kode == cariKode) {
            ketemu = true;
            cout << "\n===== DATA ANGGOTA DITEMUKAN =====\n";
            cout << "ID       : " << id << endl;
            cout << "Kode     : " << kode << endl;
            cout << "Nama     : " << nama << endl;
            cout << "Alamat   : " << alamat << endl;
            cout << "TTL      : " << ttl << endl;
            cout << "Email    : " << email << endl;
            cout << "Status   : " << (status ? "aktif" : "nonaktif") << endl;
            cout << "----------------------------------------------" << endl;
            break;
        }
    }

    if (!ketemu) {
        cout << "\nKode tidak ditemukan :(\n";
    }
    cari.close();
};

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
    CariAnggota();
    return 0;
}