#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
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

    cout << "Status (1/0): "; //(1) jika aktif, (0) jika nonaktif
    cin >> u.status;
    
    //.....===== MENULIS DATA ANGGOTA KE DALAM FILE anggota.txt =====.....
    ofstream file("data/anggota.txt", ios::app);
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }
    file << u.id << "|";
    file << u.nama << "|";
    file << u.alamat << "|";
    file << u.ttl << "|";
    file << u.email << "|";
    file << u.status << endl;
    file.close();

    cout << "Anggota berhasil ditambahkan!" << endl;
};

//.....===== MENAMPILKAN SEMUA ANGGOTA =====.....
void tampilkanAnggota(){
    ifstream file;
    string baris;

    file.open("data/anggota.txt");
    if(!file){
        cout << "File tidak bisa dibuka!" << endl;
    }

    cout << "\n===== DAFTAR ANGGOTA =====\n";

    string ttlSebelumnya = "";
    int noUrut = 0;

    while (getline(file, baris))
    {
        //jika baris kosong maka lewati
        if(baris.empty()){continue;}

        stringstream ss(baris);
        string id, nama, alamat, ttl, email;
        bool status;

        getline(ss, id, '|');
        getline(ss, nama, '|');
        getline(ss, alamat, '|');
        getline(ss, ttl, '|');
        getline(ss, email, '|');
        string statusSTR;
        getline(ss, statusSTR, '|');
        status = (statusSTR == "1");

        //yyyymmdd
        string tanggalAsli = ttl.substr(ttl.find(",")+2);
        string tahun = tanggalAsli.substr(0, 4);
        string bulan = tanggalAsli.substr(5, 2);
        string tanggal = tanggalAsli.substr(8, 2);

        string baseKode = tahun + bulan + tanggal;

        //...nomor urut...
        if (tanggalAsli == ttlSebelumnya) {noUrut++;}
        else {
            ttlSebelumnya = tanggalAsli;
            noUrut = 1;
        }

        //...3 digit...
        string urut;
        if (noUrut < 10) urut = "00" + to_string(noUrut);
        else if (noUrut < 100) urut = "0" + to_string(noUrut);
        else urut = to_string(noUrut);

        string kode = baseKode + urut;

        //OUTPUT
        cout << "ID       : " << id << endl;
        cout << "Kode     : " << kode << endl;
        cout << "Nama     : " << nama << endl;
        cout << "Alamat   : " << alamat << endl;
        cout << "TTL      : " << ttl << endl;
        cout << "Email    : " << email << endl;
        cout << "Status   : " << (status ? "aktif" : "nonaktif") << endl;
        cout << "------------------------------------------------" << endl;    
    }
    file.close();
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