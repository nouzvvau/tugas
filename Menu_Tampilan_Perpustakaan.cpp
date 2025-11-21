#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Anggota {
    string kode;
    string nama;
    string alamat;
    string ttl;
    string email;
    bool status;
};
struct Buku{
    string judul;
    string penerbit;
    string tahunterbit;
    string pengarang;
    string id;
    string isbn;
};

void TambahBuku(){}

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
void TambahPinjaman();
void TampilData();
void CariData();
void PengembalianBuku();
void HapusBuku();
void UpdateStok();

int main()
{
    int pilihan;
    do {
        cout << "\n=====MENU PERPUSTAKAAN=====" << endl;
        cout << "1.Tambah Buku" << endl;
        cout << "2.Tambah Anggota" << endl;
        cout << "3.Tambah Pinjaman" << endl;
        cout << "4.Tampil Data" << endl;
        cout << "5.Cari Data" << endl;
        cout << "6.Pengembalian Buku" << endl;
        cout << "7.Hapus Buku" << endl;
        cout << "8.Update Stok Buku" << endl;
        cout << "9.Keluar" << endl;
        cout << "=====================================" << endl;
        cout << "Pilih Menu (1-9) : " << endl;
        cin >> pilihan;

        switch(pilihan) {
            case 1: TambahBuku(); break;
            case 2: TambahAnggota(); break;
            case 3: TambahPinjaman(); break;
            case 4: TampilData(); break;
            case 5: CariData(); break;
            case 6: PengembalianBuku(); break;
            case 7: HapusBuku(); break;
            case 8: UpdateStok();break;
            case 9: cout << "TERIMAKASIH TELAH MENGGUNAKAN SISTEM PERPUSTAKAAN!\n"; break;
            default: cout << "Pilihan Tidak Tersedia!\n";
             }

        } while (pilihan !=9);

             return 0;
}