#include <iostream>
#include <string>
using namespace std;

void TambahBuku();
void TambahAnggota();
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
