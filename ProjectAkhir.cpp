#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>

using namespace std;

// fungsi
void CariBuku();
void TambahAnggota();
void TampilAnggota();
void CariAnggota();
void TambahPinjaman();
void CariPinjaman();
void PengembalianBuku();
void HapusBuku();
void UpdateStok();
void PinjamBuku();

// Manajemen petugas
string inputPassword();
bool usernameSudahAda(string userCari);
int getLastID();
void tambahPetugas();
void tampilPetugas();


string inputPassword() {
    string pass = "";
    char ch;

    while (true) {
        pass = "";
        cout << "Masukkan Password (6 karakter): ";

        while ((ch = _getch())) {
            if (ch == 13) break;
            else if (ch == 8) {
                if (!pass.empty()) { cout << "\b \b"; pass.pop_back(); }
            } else if (pass.length() < 6) {
                pass.push_back(ch);
                cout << "*";
            }
        }

        cout << endl;
        if (pass.length() == 6) break;
        cout << "Password harus 6 karakter!\n";
    }
    return pass;
}

bool usernameSudahAda(string userCari) {
    ifstream file("petugas.txt");
    if (!file.is_open()) return false;
    string line, id, username;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, username, '|');
        if (username == userCari) return true;
    }
    return false;
}

int getLastID() {
    ifstream file("petugas.txt");
    string line, id;
    int lastID = 181924;

    while (getline(file, line)) {
        stringstream ss(line);
        if (!getline(ss, id, '|')) continue;
        try {
            int numID = stoi(id);
            if (numID > lastID) lastID = numID;
        } catch (...) {}
    }
    return lastID;
}

void tambahPetugas() {
    string username, password, nama;
    int idBaru = getLastID() + 1;

    cout << "\nID Petugas otomatis: " << idBaru << endl;

    do {
        cout << "Masukkan Username   : ";
        cin >> username;
        if (usernameSudahAda(username)) cout << "  Username sudah digunakan!\n";
    } while (usernameSudahAda(username));

    password = inputPassword();

    cout << "Masukkan Nama       : ";
    cin.ignore();
    getline(cin, nama);

    ofstream file("petugas.txt", ios::app);
    file << idBaru << "|" << username << "|" << password << "|" << nama << endl;
    file.close();

    cout << "\nData petugas berhasil disimpan!\n";
}

void tampilPetugas() {
    ifstream file("petugas.txt");
    if (!file.is_open()) {
        cout << "Tidak ada data petugas.\n";
        return;
    }
    string line;
    cout << "\n=== DAFTAR PETUGAS ===\n";
    cout << "ID\tUsername\tPassword\tNama\n";
    cout << "-------------------------------------------\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string id, username, password, nama;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, nama, '|');
        string mask(6, '*');
        cout << id << "\t" << username << "\t\t" << mask << "\t\t" << nama << endl;
    }
}

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

vector<Anggota> daftarAnggota;

//membuat id 6 digit otomatis
int getLastIDAnggota() {
    ifstream file("anggota.txt");
    string line, id;
    int lastID = 262518;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');

        try {
            int numID = stoi(id);
            if (numID > lastID) lastID = numID;
        } catch (...) {}
    }
    return lastID + 1; // BUKAN memanggil dirinya sendiri
}

//MENAMBAHKAN ANGGOTA
void TambahAnggota(){
    Anggota u;
    cin.ignore();

    cout << "===== MENAMBAHKAN ANGGOTA =====\n";

    u.id = to_string(getLastIDAnggota()); // FIX

    cout << "Masukkan nama lengkap: ";
    getline(cin, u.nama);

    cout << "Masukkan alamat: ";
    getline(cin, u.alamat);

    cout << "Masukkan ttl (Tempat, YYYY-MM-DD): ";
    getline(cin, u.ttl);

    cout << "Masukkan email: ";
    getline(cin, u.email);

    cout << "Status (1,0): ";
    cin >> u.status;

    // Generate kode anggota (YYYYMMDD + urut 3 digit)
    string tanggalOnly = u.ttl.substr(u.ttl.find(",") + 2);
    string baseKode = tanggalOnly.substr(0,4) + tanggalOnly.substr(5,2) + tanggalOnly.substr(8,2);

    int nomor = rand() % 999 + 1;
    string urut = (nomor < 10 ? "00" : nomor < 100 ? "0" : "") + to_string(nomor);
    u.kode = baseKode + urut;

    // SIMPAN KE FILE
    ofstream file("anggota.txt", ios::app);
    if(!file){
        cout << "Gagal membuka file!\n"; return;
    }

    file << u.id << "|" << u.kode << "|" << u.nama << "|" << u.alamat << "|"
         << u.ttl << "|" << u.email << "|" << u.status << endl;

    file.close();

    cout << "Anggota berhasil ditambahkan!\n";
};

void TampilAnggota() {
    ifstream file("anggota.txt");
    if (!file.is_open()) {
        cout << "Tidak ada data anggota.\n";
        return;
    }

    daftarAnggota.clear(); // pastikan kosong sebelum diisi

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Anggota u;
        string statusSTR;

        getline(ss, u.id, '|');
        getline(ss, u.kode, '|');
        getline(ss, u.nama, '|');
        getline(ss, u.alamat, '|');
        getline(ss, u.ttl, '|');
        getline(ss, u.email, '|');
        getline(ss, statusSTR, '|');

        u.status = (statusSTR == "1");
        daftarAnggota.push_back(u); // simpan semua anggota
    }
    file.close();

    // Sort setelah semua data masuk daftarAnggota
    sort(daftarAnggota.begin(), daftarAnggota.end(), [](const Anggota &a, const Anggota &b) {
        return a.nama < b.nama; // ascending
    });

    cout << "\n===== DATA ANGGOTA =====\n";
    for (auto &u : daftarAnggota) {
        cout << "\nID        : " << u.id
             << "\nKode      : " << u.kode
             << "\nNama      : " << u.nama
             << "\nAlamat    : " << u.alamat
             << "\nTTL       : " << u.ttl
             << "\nEmail     : " << u.email
             << "\nStatus    : " << (u.status ? "Aktif" : "Nonaktif")
             << "\n----------------------------------------";
    }
}
struct Buku{
    string judul;
    string penerbit;
    string tahunterbit;
    string pengarang;
    string id;
    string isbn;
    int stok;
};

void TambahBuku()
{
    while(true) {
    Buku a;
    cin.ignore();
    cout<<"Masukkan judul buku: ";
    getline(cin,a. judul);
    cout<<"Masukkan pengarang : ";
    getline(cin,a.pengarang);
    cout<<"Masukkan penerbit : ";
    getline(cin,a.penerbit);
    cout<<"Tahun terbit : ";
    getline(cin,a.tahunterbit);
    cout<<"Masukkan ISBN : ";
    cin>> a.isbn;

    //pengecekkan isbn harus 13 digit
    while (a.isbn.length() != 13) {
        cout << "ISBN harus tepat 13 digit, coba lagi: ";
        cin >> a.isbn;
    }

    cout<<"Masukan stok buku awal : ";
    cin>>a.stok;
    cin.ignore();

    //======================= ID BUKU ====================

    //ambil ID terakhir
    string lastId = " "; // default

// baca baris terakhir
string lastLine, baris;
ifstream baca("buku.txt");
while (getline(baca, baris)) {
    lastLine = baris;
}
baca.close();

// kalau file tidak kosong, ambil ID
if (!lastLine.empty()) {
    size_t p1 = lastLine.find('|');           // posisi pemisah pertama
    size_t p2 = lastLine.find('|', p1 + 1);   // posisi pemisah kedua

    lastId = lastLine.substr(p1 + 1, p2 - p1 - 1);
}
    // naikkan ID
    int angka = stoi(lastId);
    angka++;
    string idBaru = to_string(angka);
    while (idBaru.length() < 6) idBaru = "0" + idBaru;
    a.id = idBaru;

    //simpan ke file
    ofstream file("buku.txt", ios :: app);
    if (file.is_open()){
        //judul, id, isbn, pengarang, penerbit, tahun terbit, stok
        file << a.judul << "|";
        file << a.id << "|";
        file << a.isbn << "|";
        file << a.pengarang << "|";
        file << a.penerbit << "|";
        file << a.tahunterbit << "|";
        file << a.stok << endl;
    } else {
        cout<<"Gagal membuka file";
    }

char ulang;
cout << "Tambah buku lagi??(y/n)";
cin >> ulang;
 if (ulang != 'y' || ulang != 'Y'){
    break;
 }
 }
}

void TampilBuku() {
    ifstream file("buku.txt");
    string baris;

    if (!file) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    cout << "\n========== DAFTAR BUKU ==========\n\n";

    while (getline(file, baris)) {
        if (baris.empty()) continue;

        stringstream ss(baris);
        string judul, id, isbn, pengarang, penerbit, tahun, stok;

        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, pengarang, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stok, '|');

        cout << "ID       : " << id << endl;
        cout << "Judul    : " << judul << endl;
        cout << "Pengarang: " << pengarang << endl;
        cout << "Penerbit : " << penerbit << endl;
        cout << "Tahun    : " << tahun << endl;
        cout << "ISBN     : " << isbn << endl;
        cout << "Stok     : " << stok << endl;
        cout << "---------------------------------\n";
    }

    file.close();
}

    //=====Cari buku=====

void CariBuku() {
    string key;
    cout << "Masukkan kata kunci: ";
    getline(cin, key);

    ifstream cari("buku.txt");
    string baris; //membaca baris
    bool ketemu = false;

    if (!cari.is_open()) {
        cout << "File tidak bisa dibuka.\n";
        return;
    }

    while (getline(cari, baris)) {
        if (baris.find(key) != string::npos) {

            // Baca detail dari baris
            stringstream ss(baris);
            string judul, id, isbn, pengarang, penerbit, tahun, stok;

            getline(ss, judul, '|');
            getline(ss, id, '|');
            getline(ss, isbn, '|');
            getline(ss, pengarang, '|');
            getline(ss, penerbit, '|');
            getline(ss, tahun, '|');
            getline(ss, stok, '|');

            cout << "\n=== Buku Ditemukan ===\n";
            cout << "Judul     : " << judul << "\n";
            cout << "ID        : " << id << "\n";
            cout << "ISBN      : " << isbn << "\n";
            cout << "Pengarang : " << pengarang << "\n";
            cout << "Penerbit  : " << penerbit << "\n";
            cout << "Tahun     : " << tahun << "\n";
            cout << "Stok      : " << stok << "\n";

            ketemu = true;
        }
    }

    cari.close();

    if (!ketemu) {
        cout << "Kata kunci tidak ditemukan.\n";
    }
}

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

void TambahPinjaman(){ 
    string ID_anggota;
    cout << "\n=== TAMBAHKAN PINJAMAN! ===\n";
    cout << "Masukkan ID anggota: ";
    cin >> ID_anggota;

    //=== CEK ID ANGGOTA DAN STATUS ===
    ifstream file("data/anggota.txt");
    if(!file.is_open()){
        cout << "\nFILE TIDAK BISA DIBUKA!\n";
        return;
    }
    
    string baris;
    bool aktif = false;

    while(getline(file, baris)){
        if(baris.empty()) continue;

        stringstream ss (baris);
        vector<string> kolom;
        string isi;

        // pisahkan
        while(getline(ss, isi, '|')){
            kolom.push_back(isi);
        }

        if(kolom.size() < 7) continue;

        string ID = kolom[0];
        string status = kolom[6];

        if(ID == ID_anggota) {
            if(status == "1") {
                cout << "Anggota valid dan aktif!\n";
                aktif = true; //simpan status
                break;
            } else {
                cout << "Anggota nonaktif!\n";
                return;
            }
        }
    }
    file.close();

    //=== cek apakah ketemu ===
    if(!aktif){
        cout << "ID anggota tidak ditemukan!\n";
        return;
    }

    // ===== PEMINJAMAN BUKU =====
    string ID_buku;
    cout << "\nMasukkan ID buku yang ingin dipinjam: ";
    cin >> ID_buku;
    //  buke file buku.txt
    ifstream buku("data/buku.txt");
    if(!buku.is_open()){
        cout << "\nFile tidak ditemukan!\n";
        return;
    }
    bool temukanbuku = false;
    int stok = 0;
    string line;

    //  simpan semua buku untuk ditulis ulang
    vector<string> semuaBaris;
    int barisTarget = -1;   //baris buku yang ingin diedit
    int noBaris = 0;    //penghitung baris saat loop

    while(getline(buku, line)) {
        semuaBaris.push_back(line);
    
        if(line.empty()) {
            noBaris++;
            continue;
        }

        stringstream ss(line);
        vector<string> kolom;
        string isi;

        while(getline(ss, isi, '|')){
            kolom.push_back(isi);
        }

        if(kolom.size() < 7){
            noBaris++;
            continue;
        }

        string ID = kolom[1]; //kolom 1 = ID buku
        if(ID == ID_buku){
            temukanbuku = true;
            stok = stoi(kolom[6]); //kolom 6 = stok
            barisTarget = noBaris; //simpan baris mana yang harus di update
        }
        noBaris++;
    }
    buku.close();

    if(!temukanbuku){
        cout << "\nID buku tidak ditemukan!\n";
        return;
    }

    if(stok <= 0){
        cout << "\nStok buku kosong!\n";
        return;
    }

    // ===== KURANGI STOK =====
    stringstream s(semuaBaris[barisTarget]);
    vector<string> kolomm;
    string isii;

    while(getline(s, isii, '|')) {
        kolomm.push_back(isii);
    }

    int stokBaru = stok - 1;
    kolomm[6] = to_string(stokBaru);

    string barisBaru = kolomm[0];
    for (int i = 1; i < kolomm.size(); i++){
        barisBaru += "|" + kolomm[i];
    }

    semuaBaris[barisTarget] = barisBaru;

    ofstream out("data/buku.txt"); //tulis ulang baris
    for(string &b : semuaBaris){
        out << b << "\n";
    }
    out.close();
 };
 
void CariPinjaman(){ cout<<"[belum dibuat]\n"; }
void PengembalianBuku(){ 
    const int batasHari = 7;       // Batas peminjaman buku (hari)
    const int dendaPerHari = 1000; // Denda per hari (Rp)

    string nama, judul, status, ID;
    int hariPinjam;

    // Ambil tanggal sekarang
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int tanggalHariIni = ltm->tm_mday;
    int bulan = 1 + ltm->tm_mon;
    int tahun = 1900 + ltm->tm_year;

    cout << "Tanggal hari ini: " << tanggalHariIni << "/" << bulan << "/" << tahun << endl;

    // Input data peminjam
    cout << "Masukkan ID peminjaman : ";
    getline(cin, ID);
    cout << "Nama Peminjam          : ";
    getline(cin, nama);
    cout << "Judul buku             : ";
    getline(cin, judul);
    cout << "Berapa hari buku dipinjam : ";
    cin >> hariPinjam;
    cin.ignore();
    cout << "Apakah buku akan dikembalikan? (ya/tidak): ";
    getline(cin, status);

    // Hitung tanggal pengembalian otomatis
    int tanggalKembali = tanggalHariIni + hariPinjam;

    cout << "\n=== DATA PENGEMBALIAN BUKU ===" << endl;
    cout << "ID Peminjaman   : " << ID << endl;
    cout << "Nama Peminjam   : " << nama << endl;
    cout << "Judul Buku      : " << judul << endl;
    cout << "Tanggal Pinjam  : " << tanggalHariIni << "/" << bulan << "/" << tahun << endl;
    cout << "Lama Dipinjam   : " << hariPinjam << " hari" << endl;
    cout << "Tanggal Kembali : " << tanggalKembali << "/" << bulan << "/" << tahun << endl;

    if (status == "ya" || status == "Ya") {
        if (hariPinjam > batasHari) {
            int terlambat = hariPinjam - batasHari;
            int denda = terlambat * dendaPerHari;
            cout << "Terlambat     : " << terlambat << " hari" << endl;
            cout << "Denda         : Rp" << denda << endl;
        } else {
            cout << "Tepat waktu   : tidak ada denda" << endl;
        }
            cout << "Status        : Dikembalikan" << endl;
    } else {
            cout << "Status        : Belum dikembalikan" << endl;
    }
 }
void HapusBuku(){ cout<<"[ belum dibuat]\n"; }
void UpdateStok(){ cout<<"[ belum dibuat]\n"; }
void PinjamBuku(){ cout<<"[belum dibuat]\n"; }

int main (){
    system("chcp 65001 >nul");
    int pilihan1, pilihan, pilihan2;

    cout << "\033[36m";     //cyan
    cout << R"(                                                                                                                                
█████▄ ▄▄▄▄▄ ▄▄▄▄  ▄▄▄▄  ▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄  ▄▄ ▄▄  ▄▄▄   ▄▄▄  ▄▄  ▄▄ 
██▄▄█▀ ██▄▄  ██▄█▄ ██▄█▀ ██ ██ ███▄▄   ██  ██▀██ ██▄█▀ ██▀██ ██▀██ ███▄██ 
██     ██▄▄▄ ██ ██ ██    ▀███▀ ▄▄██▀   ██  ██▀██ ██ ██ ██▀██ ██▀██ ██ ▀██ 
                                                                           )" << endl;
    cout << "═════════════════════════════════════════════════════════════════════════\n" << "\033[0m";
    cout << "===== LOGIN =====\n";
    cout << "1. PETUGAS\n";
    cout << "2. ANGGOTA\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan1;

    if (pilihan1 == 1) {
        do {
            cout << "\n\n=============================\n";
            cout << "      MENU PERPUSTAKAAN      \n";
            cout << "-----------------------------\n";
            cout << "1. Tambah Buku\n";
            cout << "2. Cari Buku\n";
            cout << "3. Tambah Anggota\n";
            cout << "4. Cari Anggota\n";
            cout << "5. Tampil Anggota\n";
            cout << "6. Tambah Pinjaman\n";
            cout << "7. Tampil Data Buku\n";
            cout << "8. Pengembalian Buku\n";
            cout << "9. Hapus Buku\n";
            cout << "10. Update Stok Buku\n";
            cout << "11. Manajemen Petugas\n";
            cout << "0. Keluar\n";
            cout << "=============================\n\n";
            cout << "PILIH MENU: ";
            cin >> pilihan;

            switch(pilihan) {
                case 1: TambahBuku(); break;
                case 2: CariBuku(); break;
                case 3: TambahAnggota(); break;
                case 4: CariAnggota(); break;
                case 5: TampilAnggota(); break;
                case 6: TambahPinjaman(); break;
                case 7: CariPinjaman(); break;
                case 8: PengembalianBuku(); break;
                case 9: HapusBuku(); break;
                case 10: UpdateStok(); break;
                case 11: {
                    int p2;
                    cout << "\n=== Manajemen Petugas ===\n1. Tambah Petugas\n2. Tampil Petugas\n0. Kembali\nPilihan: ";
                    cin >> p2;
                    if(p2==1) tambahPetugas();
                    else if(p2==2) tampilPetugas();
                    break;
                }
                case 0: cout << "Keluar...\n"; break;
                default: cout << "Pilihan tidak valid!\n";
            }

        } while(pilihan != 12);
    }

    else if (pilihan1 == 2) {
        do{
            cout << "\n\n========================\n";
            cout << "      MENU ANGGOTA      \n";
            cout << "------------------------\n";
            cout << "1. Cari Buku\n";
            cout << "2. Tampil Buku\n";
            cout << "0. Keluar\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihan2;

            switch(pilihan2){
                case 1: CariBuku(); break;
                case 2: TampilBuku(); break;
                case 0: cout<<"Keluar...\n"; break;
                default: cout<<"Pilihan tidak valid!\n";
            }

        }while(pilihan2 != 3);
    }

    return 0;
}

