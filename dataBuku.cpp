#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
    Buku a;
    cout<<"Masukkan judul buku: ";
    getline(cin,a.judul);
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
}



    void TampilBuku() {
    ifstream file("buku.txt");

    const int max = 500;
    string data[max];
    int n = 0;

    // baca file
    while (n < max && getline(file, data[n])) {
        n++;
    }

    file.close();

  // bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                string temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // tampilkan
    for (int i = 0; i < n; i++) {
        cout << data[i] << endl;
    }
    }


int main (){
    TambahBuku();
    TampilBuku();

    return 0;
}
