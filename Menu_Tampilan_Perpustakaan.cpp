#include <iostream>
using namespace std;

void TambahBuku();
void TambahAnggota();
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
        cout << "PIlih Menu (1-9) : " << endl;
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
