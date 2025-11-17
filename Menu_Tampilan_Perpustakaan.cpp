#include <iostream>
#include <string>
using namespace std;

struct Anggota {
    string kode;
    string nama;
    string alamat;
    string ttl;
    string email;
    bool status;
};

void TambahBuku();
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

void TampilAnggota();
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
        cout << "3.Tampil Anggota" << endl;
        cout << "4.Tambah Pinjaman" << endl;
        cout << "5.Tampil Data" << endl;
        cout << "6.Cari Data" << endl;
        cout << "7.Pengembalian Buku" << endl;
        cout << "8.Hapus Buku" << endl;
        cout << "9.Update Stok Buku" << endl;
        cout << "10.Keluar" << endl;
        cout << "=====================================" << endl;
        cout << "Pilih Menu (1-10) : " << endl;
        cin >> pilihan;

        switch(pilihan) {
            case 1: TambahBuku(); break;
            case 2: TambahAnggota(); break;
            case 3: TampilAnggota(); break;
            case 4: TambahPinjaman(); break;
            case 5: TampilData(); break;
            case 6: CariData(); break;
            case 7: PengembalianBuku(); break;
            case 8: HapusBuku(); break;
            case 9: UpdateStok();break;
            case 10: cout << "TERIMAKASIH TELAH MENGGUNAKAN SISTEM PERPUSTAKAAN!\n"; break;
            default: cout << "Pilihan Tidak Tersedia!\n";
             }

        } while (pilihan !=10);

             return 0;
