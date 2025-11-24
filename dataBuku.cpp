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

//======================= ID BUKU ====================

//ambil ID terakhir
    string lastLine, baris;
    ifstream baca("buku.txt");
    while (getline(baca, baris)) {
        lastLine = baris; // simpan baris terakhir
    }
    baca.close();

    string lastId ; 
    if (!lastLine.empty()) {
        size_t pos1 = lastLine.find(" | ");//cari awal id
        size_t pos2 = lastLine.find(" | ", pos1 + 1);//cari akhir id
        lastId = lastLine.substr(pos1 + 1, pos2 - pos1 - 1);//ambil id awal dan akhir
    }

// naikkan ID
    int angka = stoi(lastId);
    angka++;
    string idBaru = to_string(angka);
    while (idBaru.length() < 6) idBaru = "0" + idBaru;
    a.id = idBaru;

//simpan ke file
ofstream file("buku.txt",ios :: app);
if (file.is_open()){
	//judul, id, isbn, pengarang, penerbit, tahun terbit, stok
	file<<a.judul<<" | "<<a.id<<" | "<<a.isbn<<" | "<<a.pengarang<<" | "<<a.penerbit<<" | "<<a.tahunterbit<<" | "<<a.stok<<endl;
    

} else {
	cout<<"Gagal membuka file";
}
}
void TampilBuku() {
    ifstream file("buku.txt");
    string baris;

    while (getline(file, baris)) {
        cout << baris << endl;
    }

    file.close();
}


    
int main (){
    TambahBuku();
    TampilBuku();

    return 0;
}