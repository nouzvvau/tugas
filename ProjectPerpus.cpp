#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>

using namespace std;

// fungsi
void TambahPetugas();
void TampilPetugas();
void TambahAnggota();
void TampilAnggota();
void CariAnggota();
void TambahBuku();
void TampilBuku();
void CariBuku();
void TambahPinjaman();
void PinjamBuku();
void cariPeminjaman();
void PengembalianBuku();
void BukuYangBelumKembali();
void HapusBuku();
void UpdateStok();


void loginPetugas() {
    string us, pw;
    string id, user, passw, nama;

    cout << "\n===== Login Petugas =====\n";
    cout << "Masukkan username: ";
    cin >> us;
    cout << "Masukkan password: ";
    pw = "";
    char ch;
    while (true) {
        ch = _getch(); // baca karakter tanpa menampilkan di layar
        if (ch == 13) break; // enter
        else if (ch == 8) { // backspace
            if (!pw.empty()) {
                pw.pop_back();
                cout << "\b \b"; // hapus * di layar
            }
        } else {
            pw.push_back(ch);
            cout << "*";
        }
    }
    ifstream file("petugas.txt");
    if (!file.is_open()) {
        cout << "\nFile tidak bisa dibuka!\n";
        return;
    }

    string baris;
    bool temu = false;

    while (getline(file, baris)) {
        if(baris.empty()) continue;
        stringstream ss(baris);

        getline(ss, id, '|');
        getline(ss, user, '|');
        getline(ss, passw, '|');
        getline(ss, nama, '|');

        if (us == user && pw == passw) {
            temu = true;
            break;
        }
    }

    if (temu) {
        cout << "\nLogin berhasil! Selamat datang, " << nama << "!\n";
    } else {
        cout << "\nLogin gagal, silakan coba lagi!\n";
        loginPetugas();
    }
}

    void loginAnggota() {
    string jeneng, pw, cek;
    string id, kode, nama, alamat, ttl, email;
    bool status;

    while (true) {
        cout << "\n===== Login Anggota =====\n";

        cout << "Masukkan nama: ";
        cin.ignore();
        getline(cin, jeneng);

        cout << "Masukkan email: ";
        cin >> pw;

        bool berhasil = false;

        ifstream in("anggota.txt");
        if (!in.is_open()) {
            cout << "\nFile tidak bisa dibuka!\n";
            return;
        }

        while (getline(in, cek)) {
            if (cek.empty()) continue;

            stringstream ss(cek);
            getline(ss, id, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, alamat, '|');
            getline(ss, ttl, '|');
            getline(ss, email, '|');

            string statusSTR;
            getline(ss, statusSTR, '|');
            status = (statusSTR == "1");

            if (jeneng == nama && pw == email) {
                berhasil = true;
                break;
            }
        }

        if (berhasil) {
            cout << "\nLogin berhasil!\n";
            break; //
        } else {
            cout << "\nNama atau email salah, coba lagi!\n";
        }
    }
}

// Manajemen petugas//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string inputPassword();
bool usernameSudahAda(string userCari);
int getLastID();

// Password petugas
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
// Cek Username
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

// ID otomtis awalan 181925
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

// Tambah petugas
void TambahPetugas() {
    string username, password, nama;
    int idBaru = getLastID() + 1;

    cout << "\nID Petugas otomatis: " << idBaru << endl;

    // Validasi Username
    bool taken;
    do {
        cout << "Masukkan Username   : ";
        cin >> username;
        taken = usernameSudahAda(username);

        if (taken)
            cout << "  Username sudah digunakan! Coba lagi.\n";

    } while (taken);

    // Password input aman (disembunyikan)
    password = inputPassword();

    cout << "Masukkan Nama lengkap: ";
    cin >> ws;
    getline(cin, nama);

    // Simpan ke file
  ofstream file("petugas.txt", ios::app);  file << idBaru << "|" << username << "|" << password << "|" << nama << endl;
  file.close();

  cout << "\nData petugas berhasil di simpan!\n";

}
// Tampil Petugas
void TampilPetugas() {
    ifstream file("petugas.txt");

    if (!file.is_open()) {
        cout << "Tidak ada data petugas.\n";
        return;
    }

    string line;
    cout << "\n=== DAFTAR PETUGAS ===\n";
    cout << "ID\tUsername\tPassword\tNama\n";
    cout << "---------------------------------------------";

    while (getline(file, line)) {
        stringstream ss(line);
        string id, username, password, nama;

        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, nama, '|');

        // Buat password jadi **** sebanyak panjang password
        string mask(password.length(), '*');

        cout << id << "\t" << username << "\t\t" << mask << "\t\t" << nama << endl;
    }

    file.close();
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

//ID otomatis awalan 262519
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

//Manajemen Anggota
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

    // Kode berdasarkan TTL + no urut berdasarkan nama
string tanggal = u.ttl.substr(u.ttl.find(",") + 2);
string baseKode = tanggal.substr(0,4) + tanggal.substr(5,2) + tanggal.substr(8,2);

// Vector untuk menyimpan nama nama yang memiliki tanggal sama
vector<string> namaSama;

ifstream cek("anggota.txt");
string line;

while(getline(cek, line)){
    size_t pos1 = line.find("|");
    size_t pos2 = line.find("|", pos1 + 1);
    size_t pos3 = line.find("|", pos2 + 1);

    if(pos1 != string::npos && pos2 != string::npos && pos3 != string::npos){
        string kodeFile = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string namaFile = line.substr(pos2 + 1, pos3 - pos2 - 1);

        // Ambil hanya yang tanggal lahir sama
        if(kodeFile.substr(0, 8) == baseKode){
            namaSama.push_back(namaFile);
        }
    }
}
cek.close();

// Masukkan nama anggota baru
namaSama.push_back(u.nama);

// Sort supaya urutan berdasarkan abjad
sort(namaSama.begin(), namaSama.end());

// Cari posisi anggota baru di vector sorted
int posisi = 1;
for(int i = 0; i < namaSama.size(); i++){
    if(namaSama[i] == u.nama){
        posisi = i + 1;
        break;
    }
}

// Format nomor urut (001, 002, ...)
string nomor = (posisi < 10 ? "00" : posisi < 100 ? "0" : "") + to_string(posisi);

u.kode = baseKode + nomor;

// Simpan ke file
ofstream file("anggota.txt", ios::app);
if(!file){
    cout << "Gagal membuka file!\n";
    return;
}

file << u.id << "|" << u.kode << "|" << u.nama << "|" << u.alamat << "|"
     << u.ttl << "|" << u.email << "|" << u.status << endl;

file.close();

cout << "\nAnggota berhasil ditambahkan!\n";

}

// Tampil anggota
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

//Cari anggota
void CariAnggota() {
    ifstream file("anggota.txt");
    if (!file.is_open()) {
        cout << "Tidak ada data anggota.\n";
        return;
    }

    string kodeCari;
    cout << "Masukkan kode anggota yang dicari: ";
    cin >> kodeCari;

    bool ditemukan = false;
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

        if (u.kode == kodeCari) {
            ditemukan = true;
            cout << "\n===== DATA ANGGOTA =====\n";
            cout << "\nID        : " << u.id
                 << "\nKode      : " << u.kode
                 << "\nNama      : " << u.nama
                 << "\nAlamat    : " << u.alamat
                 << "\nTTL       : " << u.ttl
                 << "\nEmail     : " << u.email
                 << "\nStatus    : " << (u.status ? "Aktif" : "Nonaktif")
                 << "\n----------------------------------------\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Anggota dengan kode " << kodeCari << " tidak ditemukan.\n";
    }

    file.close();
}


// Buku
struct Buku{
    string judul;
    string penerbit;
    string tahunterbit;
    string pengarang;
    string id;
    string isbn;
    int stok;
    bool status;
};

// Tambah buku
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
    cout<<"Status: ";
    cin >> a.status;
    cin.ignore();
cout<<endl;
    //ID Buku

    //ambil ID terakhir
    string lastId = "000000 "; // default

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
        file << a.stok << "|";
        file << a.status<< endl;
    } else {
        cout<<"Gagal membuka file";
    }

char ulang;
cout << "Tambah buku lagi??(y/n) : ";
cin >> ulang;
 if (ulang != 'y' && ulang != 'Y'){
break;
 }
 }
}

// Tampil buku
void TampilBuku() {

    ifstream file("buku.txt");
    string baris;

    if (!file.is_open()) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    vector<string> data;

    // ambil semua baris
    while (getline(file, baris)) {
        if (baris != "") {
            data.push_back(baris);
        }
    }
    file.close();

    // bubble sort
    for (int i = 0; i < data.size(); i++) {
        for (int j = i + 1; j < data.size(); j++) {
            string a = data[i];
            string b = data[j];

            stringstream sa(a), sb(b);
            string judulA, judulB;

            getline(sa, judulA, '|');
            getline(sb, judulB, '|');

            if (judulA > judulB) {
                string temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    cout << "\n===== DAFTAR BUKU =====\n\n";

    // tampilkan
    for (int i = 0; i < data.size(); i++) {
        stringstream ss(data[i]);
        string judul, id, isbn, pengarang, penerbit, tahun, stok, status;

        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, pengarang, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stok, '|');
        getline(ss, status, '|');

        if (status == "0") {
            continue;  // skip yang tidak aktif
        }

        cout << "ID       : " << id << endl;
        cout << "Judul    : " << judul << endl;
        cout << "Pengarang: " << pengarang << endl;
        cout << "Penerbit : " << penerbit << endl;
        cout << "Tahun    : " << tahun << endl;
        cout << "ISBN     : " << isbn << endl;
        cout << "Stok     : " << stok << endl;
        cout << "---------------------------\n";
    }
}
    // Cari buku

void CariBuku() {
    string key, baris;
    bool ketemu = false;

    cout << "Masukkan judul atau ID buku: ";
    cin.ignore();
    getline(cin, key);

    ifstream file("buku.txt");
    if (!file.is_open()) {
        cout << "File tidak bisa dibuka!\n";
        return;
    }

    cout << "\n=== HASIL PENCARIAN ===\n";

    while (getline(file, baris)) {
        stringstream ss(baris);
        string judul, id, isbn, pengarang, penerbit, tahun, stok, status;

        // pisahkan semua field berdasarkan '|'
        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, pengarang, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stok, '|');
        getline(ss, status, '|');

        if (status == "1"){

        // cek keyword cuma di judul atau ID
        if (judul.find(key) != string::npos || id.find(key) != string::npos) {
            cout << "Judul     : " << judul << endl;
            cout << "ID        : " << id << endl;
            cout << "ISBN      : " << isbn << endl;
            cout << "Pengarang : " << pengarang << endl;
            cout << "Penerbit  : " << penerbit << endl;
            cout << "Tahun     : " << tahun << endl;
            cout << "Stok      : " << stok << endl;
            cout << "-----------------------------\n";
            ketemu = true;
        }
        }
    }

    if (!ketemu) {
        cout << "Buku tidak ditemukan\n";
    }

    file.close();

}
void UpdateStok() {
    string idBuku;
    cout << "Masukkan ID Buku yang ingin diupdate: ";
    cin >> idBuku;

    ifstream in("buku.txt");
    if (!in.is_open()) {
        cout << "File buku tidak ditemukan!\n";
        return;
    }

    string line, semuaData = "";
    bool ketemu = false;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string judul, id, isbn, pengarang, penerbit, tahun, stok;

        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, pengarang, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stok, '|');

        if (id == idBuku) {
            ketemu = true;

            int stokLama = stoi(stok);
            int tambah;

            cout << "Stok saat ini: " << stokLama << endl;
            cout << "Tambah berapa stok?: ";
            cin >> tambah;

            int stokBaru = stokLama + tambah;

            semuaData += judul + "|" + id + "|" + isbn + "|"
                       + pengarang + "|" + penerbit + "|" + tahun + "|"
                       + to_string(stokBaru) + "\n";
        }
        else {
            semuaData += line + "\n";
        }
    }

    in.close();

    ofstream out("buku.txt");
    out << semuaData;
    out.close();

    if (ketemu) {
        cout << "Stok berhasil ditambahkan!\n";
    } else {
        cout << "ID buku tidak ditemukan!\n";
    }
}



   void HapusBuku() {
    string idBuku;
    cout << "Masukkan ID Buku yang ingin dihapus: ";
    cin >> idBuku;

    ifstream in("buku.txt");
    if (!in.is_open()) {
        cout << "File buku tidak ditemukan!\n";
        return;
    }

    string line, semuaData = "";
    bool ketemu = false;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string judul, id, isbn, pengarang, penerbit, tahun, stok, status;

        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, pengarang, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stok, '|');
        if (!getline(ss, status, '|')) status = "aktif"; // default

        if (id == idBuku && status == "1") {
            status = "0"; // soft delete
            ketemu = true;
        }

        semuaData += judul + "|" + id + "|" + isbn + "|" + pengarang + "|" + penerbit + "|" + tahun + "|" + stok + "|" + status + "\n";
    }

    in.close();

    ofstream out("buku.txt");
    out << semuaData;
    out.close();

    if (ketemu) cout << "Buku berhasil dihapus!!!\n";
    else cout << "Buku tidak ditemukan atau sudah dihapus.\n";
}

    //===============================================================================PEMINJAMAN=================================================
    //Stok buku
    void kurangiStok(string idBuku) {
    ifstream file("buku.txt");
    string line, hasil = "";

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string judul, id, isbn, peng, penerbit, tahun, stokStr;
        getline(ss, judul, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, peng, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stokStr, '|');

        int stok = stoi(stokStr);
        if (id == idBuku) stok--;

        hasil += judul + "|" + id + "|" + isbn + "|" + peng + "|" + penerbit + "|" + tahun + "|" + to_string(stok) + "\n";
    }
    file.close();

    ofstream out("buku.txt");
    out << hasil;
}

//Cari anggota
bool cariAnggota(string id) {
    ifstream file("anggota.txt");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idFile, kode, nama, alamat, ttl, email, statusSTR;
        getline(ss, idFile, '|');
        getline(ss, kode, '|'); // skip kode
        getline(ss, nama, '|'); // skip nama
        getline(ss, alamat, '|');
        getline(ss, ttl, '|');
        getline(ss, email, '|');
        getline(ss, statusSTR, '|');

        if (idFile == id) return true;
    }
    return false;
}

//Cari buku peminjaman
bool cariBuku(string idBuku, string &judul, int &stok) {
    ifstream file("buku.txt");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string j, id, isbn, peng, penerbit, tahun, stokStr;
        getline(ss, j, '|');
        getline(ss, id, '|');
        getline(ss, isbn, '|');
        getline(ss, peng, '|');
        getline(ss, penerbit, '|');
        getline(ss, tahun, '|');
        getline(ss, stokStr, '|');

        if (id == idBuku) {
            judul = j;
            stok = stoi(stokStr);
            return true;
        }
    }
    return false;
}


// HITUNG DENDA (TELAT)
// telat > 7 hari = (telat - 7) * 1000
int hitungDenda(int hariPinjam) {
    if (hariPinjam > 7) {
        return (hariPinjam - 7) * 1000;
    }
    return 0;
}

// ID otomatis peminjaman di mulai 182619
int getLastIDPinjaman() {
    ifstream file("peminjaman.txt");
    string line, id;
    int lastID = 182618; // sebelum ID pertama

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        getline(ss, id, '|'); // asumsikan ID peminjaman ada di kolom pertama

        try {
            int numID = stoi(id);
            if (numID > lastID) lastID = numID;
        } catch (...) {}
    }

    file.close();
    return lastID;
}

string generateIDPinjaman() {
    int nextID = getLastIDPinjaman() + 1;
    string id = to_string(nextID);

    // pastikan 6 digit
    while (id.length() < 6) id = "0" + id;

    return id;
    cout<<id;
}

// FUNGSI PINJAM BUKU (UTAMA)
void pinjamBuku() {
    string idAnggota, idBuku, judul;
    int stok;

    cout << "\n=== MENU PINJAM BUKU ===\n";

    // ID peminjaman
    string idPinjam = generateIDPinjaman();
    cout << "ID Peminjaman: " << idPinjam << endl;

    // Cari anggota
    while (true) {
        cout << "Masukkan ID Anggota: ";
        cin >> idAnggota;

        if (cariAnggota(idAnggota)) {
            cout << "Anggota ditemukan!\n";
            break;
        } else {
            cout << "Anggota TIDAK ADA, ulangi!\n";
        }
    }

    // Cari buku
    while (true) {
        cout << "Masukkan ID Buku: ";
        cin >> idBuku;

        if (!cariBuku(idBuku, judul, stok)) {
            cout << "Buku tidak ditemukan!\n";
        }
        else if (stok == 0) {
            cout << "STOK HABIS ! Cari buku lain!\n";
        }
        else {
            cout << "Buku ditemukan: " << judul << " (stok: " << stok << ")\n";
            break;
        }
    }

    // Kurangi stok
    kurangiStok(idBuku);

    //Input durasi jam
    string tanggalpnjam;
    cin.ignore();
     cout << " Masukkan tanggal pinjam(YYYY-MM-DD) : ";
     getline(cin,tanggalpnjam);


    // Simpan data peminjaman
    ofstream out("peminjaman.txt", ios::app);
    out<< idPinjam << "|" << idAnggota << "|" << idBuku << "|" << judul<< "|" << tanggalpnjam << "|" <<  "0" << "|" << "Belum dikembalikan"<<"|"<<"Tanggal pengembalian"<<endl; // denda nanti dihitung saat pengembalian
    out.close();

    cout << "\n=== PEMINJAMAN BERHASIL ===\n";
    cout << "ID Peminjaman: " << idPinjam << endl;
    cout << "Anggota       : " << idAnggota << endl;
    cout << "Buku          : " << judul << endl;
    cout << "Tanggal Pinjam: " << tanggalpnjam<< endl;

}

// Pengembalian buku

void PengembalianBuku() {
    string idPinjam;
    cout << "Masukkan ID Peminjaman: ";
    cin >> idPinjam;

    ifstream in("peminjaman.txt");
    if (!in.is_open()) {
        cout << "File peminjaman tidak ditemukan!\n";
        return;
    }

    string line, semuaData = "";
    bool ketemu = false;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string curID, idAnggota, idBuku, judul, tglpjm, dendaStr, status, tglKembali;
        getline(ss, curID, '|'); //IDPEMINJAMAN
        getline(ss, idAnggota, '|');
        getline(ss, idBuku, '|');
        getline(ss, judul, '|');
        getline(ss, tglpjm, '|');
        getline(ss, dendaStr, '|');
        getline(ss, status, '|');
        getline(ss, tglKembali, '|');

        if (curID == idPinjam) {
            ketemu = true;

            if (status == "Sudah Dikembalikan") {
                cout << "Buku ini sudah dikembalikan sebelumnya!\n";
                semuaData += line + "\n";
                continue;
            }

            cout << "\n=== Data Peminjaman ===\n";
            cout << "ID Peminjaman  : " << curID << "\n";
            cout << "ID Anggota     : " << idAnggota << "\n";
            cout << "ID Buku        : " << idBuku << "\n";
            cout << "Judul Buku     : " << judul << "\n";
            cout << "Tanggal Pinjam : " << tglpjm << "\n";

            string tglPengembalian;
            cout << "Masukkan tanggal pengembalian (YYYY-MM-DD): ";
            cin >> tglPengembalian;
            int lamaPinjam;
            cout<<"Berapa lama dipinjam? ";
            cin>> lamaPinjam;


            int denda = hitungDenda(lamaPinjam);

            // Update line: tambahkan tanggal pengembalian, denda, status
            stringstream updated;
            updated << curID << "|" << idAnggota << "|" << idBuku << "|" << judul
                    << "|" << tglpjm << "|" << denda << "|Sudah Dikembalikan|" << tglPengembalian;

            semuaData += updated.str() + "\n";

            cout << "\nBuku berhasil dikembalikan!\n";
            cout << "Denda: Rp " << denda << "\n";
        } else {
            semuaData += line + "\n";
        }
    }
    in.close();

    if (!ketemu) {
        cout << "ID Peminjaman tidak ditemukan!\n";
        return;
    }

    ofstream out("peminjaman.txt");
    out << semuaData;
    out.close();
}


void BukuYangBelumKembali () {
ifstream file("peminjaman.txt");
    if(!file.is_open()) {
    cout << "Tidak bisa dibuka" << endl;

}
string baris;
bool ada = false;
cout<< "BUKU YANG BELUM DIKEMBALIKAN "<< endl ;
while (getline(file,baris)){

    stringstream ss(baris);
string idpeminjaman, idanggota, idbuku, nama, tangglpinjam, denda, status;

    getline(ss, idpeminjaman, '|');
    getline(ss, idanggota, '|');
    getline(ss, idbuku, '|');
    getline(ss, nama, '|');
    getline(ss, tangglpinjam, '|');
    getline(ss, denda, '|');
    getline(ss, status, '|');

        if(status == "Belum dikembalikan"){

            cout<<"Id Peminjaman: "<<idpeminjaman <<endl;
            cout << "Id Anggota : "<< idanggota << endl;
            cout << "Id Buku : " << idbuku<<endl;
            cout << "Nama Peminjam : "<< nama << endl;
            cout << "Tanggal Pinjam :"<< tangglpinjam << endl;
            cout<< "Status : "<< status<< endl;
            cout<<"-------------------------------------------\n";
            ada = true;

        }
}
        if(!ada){
            cout<<"TIDAK ADA BUKU YANG BELUM DIKEMBALIKAN";
        }
        file.close();
}
//caripmnjmn
void cariPeminjaman() {
string key;
cout << "Masukkan key (ID Peminjaman atau Judul Buku): ";
cin.ignore();
getline(cin, key);

ifstream file("peminjaman.txt");
if (!file.is_open()) {
    cout << "File peminjaman tidak ditemukan!\n";
    return;
}

string baris;
bool ketemu = false;
while (getline(file, baris)) {
    if (baris.empty()) continue;

    stringstream ss(baris);
    string idpeminjaman, idanggota, idbuku, judulbuku, tanggalpinjam, denda, status, tglpengembalian;

    getline(ss, idpeminjaman, '|');
    getline(ss, idanggota, '|');
    getline(ss, idbuku, '|');
    getline(ss, judulbuku, '|');
    getline(ss, tanggalpinjam, '|');
    getline(ss, denda, '|');
    getline(ss, status, '|');
    getline(ss, tglpengembalian, '|');

    if (idpeminjaman == key || judulbuku == key||idanggota==key) {
        ketemu = true;
        cout << "\n=== Peminjaman Ditemukan ===\n";
        cout << "ID Peminjaman        : " << idpeminjaman << "\n";
        cout << "ID Anggota           : " << idanggota << "\n";
        cout << "ID Buku              : " << idbuku << "\n";
        cout << "Judul Buku           : " << judulbuku << "\n";
        cout << "Tanggal Pinjam       : " << tanggalpinjam << "\n";
        cout << "Denda                : " << denda << "\n";
        cout << "Status               : " << status << "\n";
        cout << "Tanggal Pengembalian : " << tglpengembalian << "\n";
    }
}

if (!ketemu) cout << "Peminjaman tidak ditemukan.\n";
file.close();

}

int main() {
    system("chcp 65001 >nul");
    int pilihan1;

    while (true) { // loop utama untuk menu login
        cout << "\033[36m";
        cout << R"(
█████▄ ▄▄▄▄▄ ▄▄▄▄  ▄▄▄▄  ▄▄ ▄▄  ▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄  ▄▄ ▄▄  ▄▄▄   ▄▄▄  ▄▄  ▄▄
██▄▄█▀ ██▄▄  ██▄█▄ ██▄█▀ ██ ██ ███▄▄   ██  ██▀██ ██▄█▀ ██▀██ ██▀██ ███▄██
██     ██▄▄▄ ██ ██ ██    ▀███▀ ▄▄██▀   ██  ██▀██ ██ ██ ██▀██ ██▀██ ██ ▀██
                                                                           )" << endl;
        cout << "═════════════════════════════════════════════════════════════════════════\n" << "\033[0m";
        cout << "===== LOGIN =====\n";
        cout << "1. PETUGAS\n";
        cout << "2. ANGGOTA\n";
        cout << "0. KELUAR\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan1;

        if (pilihan1 == 1) {
            loginPetugas();
            int pilihan;

            do {
                cout << "\n===== MENU PERPUSTAKAAN =====\n";
                cout << "1. Manajemen Petugas\n";
                cout << "2. Manajemen Anggota\n";
                cout << "3. Manajemen Buku\n";
                cout << "4. Manajemen Peminjaman Dan Pengembalian\n";
                cout << "5. Keluar\n";
                cout << "=====================================\n";
                cout << "Pilih Menu (1-5): ";
                cin >> pilihan;

                switch(pilihan) {
                                    //================ MENUPETUGAS ================
                case 1: {
                    int p2;
                    do {
                        cout << "\n=== Manajemen Petugas ===\n";
                        cout << "1. Tambah Petugas\n";
                        cout << "2. Tampil Petugas\n";
                        cout << "0. Kembali\n";
                        cout << "Pilihan: ";
                        cin >> p2;

                        switch(p2) {
                            case 1: TambahPetugas(); break;
                            case 2: TampilPetugas(); break;
                            case 0: cout << "Kembali ke menu utama...\n"; break;
                            default: cout << "Pilihan tidak valid!\n";
                        }
                    } while(p2 != 0);
                    break;
                }
                                case 2: {
                    int p2;
                    do {
                        cout << "\n=== Manajemen Anggota ===\n";
                        cout << "1. Tambah Anggota\n";
                        cout << "2. Tampil Anggota\n";
                        cout << "3. Cari Anggota\n";
                        cout << "0. Kembali\n";
                        cout << "Pilihan: ";
                        cin >> p2;

                        switch(p2) {
                            case 1: TambahAnggota(); break;
                            case 2: TampilAnggota(); break;
                            case 3: CariAnggota(); break;
                            case 0: cout << "Kembali ke menu utama...\n"; break;
                            default: cout << "Pilihan tidak valid!\n";
                        }
                    } while(p2 != 0);
                    break;
                }

                //================ MENU BUKU ================
                case 3: {
                    int p2;
                    do {
                        cout << "\n=== Manajemen Buku ===\n";
                        cout << "1. Tambah Buku\n";
                        cout << "2. Tampil Buku\n";
                        cout << "3. Cari Buku\n";
                        cout << "4. Hapus Buku\n";
                        cout << "5. Update Stok\n";
                        cout << "0. Kembali\n";
                        cout << "Pilihan: ";
                        cin >> p2;

                        switch(p2) {
                            case 1: TambahBuku(); break;
                            case 2: TampilBuku(); break;
                            case 3: CariBuku(); break;
                            case 4: HapusBuku(); break;
                            case 5: UpdateStok(); break;
                            case 0: cout << "Kembali ke menu utama...\n"; break;
                            default: cout << "Pilihan tidak valid!\n";
                        }
                    } while(p2 != 0);
                    break;
                }

                //================ MENU PINJAM ================
                case 4: {
                    int p2;
                    do {
                        cout << "\n=== Manajemen Peminjaman Dan Pengembalian ===\n";
                        cout << "1. Tambah Pinjaman\n";
                        cout << "2. Cari Pinjaman\n";
                        cout << "3. Pengembalian Buku\n";
                        cout << "4. Tampil Buku Yang Belum Dikembalikan\n";
                        cout << "0. Kembali\n";
                        cout << "Pilihan: ";
                        cin >> p2;

                        switch(p2) {
                            case 1: pinjamBuku(); break;
                            case 2: cariPeminjaman(); break;
                            case 3: PengembalianBuku(); break;
                            case 4: BukuYangBelumKembali(); break;
                            case 0: cout << "Kembali ke menu utama...\n"; break;
                            default: cout << "Pilihan tidak valid!\n";
                        }
                    } while(p2 != 0);
                    break;
                }


                }

            } while (pilihan != 5); // Logout akan kembali ke menu login
        }
        else if (pilihan1 == 2) {
            loginAnggota();
            int pilihan2;

            do {
                cout << "\n===== MENU ANGGOTA =====\n";
                cout << "1. Cari Buku\n";
                cout << "2. Tampil Buku\n";
                cout << "3. Keluar\n";
                cout << "Masukkan pilihan: ";
                cin >> pilihan2;

                switch(pilihan2) {
                    case 1: CariBuku(); break;
                    case 2: TampilBuku(); break;
                    case 3: cout << "Logout berhasil, kembali ke menu login...\n"; break;
                    default: cout << "Pilihan tidak valid!\n";
                }

            } while(pilihan2 != 3); // Logout akan kembali ke menu login
        }
        else if (pilihan1 == 0) {
            cout << "Terima kasih! Program selesai.\n";
            break;
            }
        else {
            cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    }

    return 0;
}
