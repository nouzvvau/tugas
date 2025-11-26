#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
using namespace std;

// masking password 6 karakter
string inputPassword() {
    string pass = "";
    char ch;

    while (true) {
        pass = "";
        cout << "Masukkan Password (6 karakter): ";
        while ((ch = _getch())) {
            if (ch == 13) { // Enter
                cout << endl;
                break;
            } else if (ch == 8) { // Backspace
                if (!pass.empty()) {
                    cout << "\b \b";
                    pass.pop_back();
                }
            } else {
                pass.push_back(ch);
                cout << "*";
            }
        }
        if (pass.length() != 6) {
            cout << "Password harus 6 karakter! Coba lagi.\n";
        } else {
            break;
        }
    }
    return pass;
}

// cek apakah username sudah ada
bool usernameSudahAda(string userCari) {
    ifstream file("petugas.txt");
    string line, id, username;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, username, '|');
        if (username == userCari)
            return true;
    }
    return false;
}

// dapatkan ID terakhir dari file, jika kosong mulai dari 181924
int getLastID() {
    ifstream file("petugas.txt");
    string line, id;
    int lastID = 181924; // supaya yang pertama 181925

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        int numID = stoi(id);
        if (numID > lastID) lastID = numID;
    }
    return lastID;
}

// tambah petugas
void tambahPetugas() {
    string username, password, nama;

    // ID otomatis urut
    int idBaru = getLastID() + 1;
    string idStr = to_string(idBaru);
    cout << "\nID Petugas otomatis: " << idStr << endl;

    // input Username
    do {
        cout << "Masukkan Username   : ";
        cin >> username;
        if (usernameSudahAda(username)) {
            cout << "  Username sudah digunakan! Masukkan username lain.\n";
        }
    } while (usernameSudahAda(username));

    // input Password
    password = inputPassword();

    // input Nama
    cout << "Masukkan Nama       : ";
    cin.ignore();
    getline(cin, nama);

    // smpan ke file
    ofstream file("petugas.txt", ios::app);
    file << idStr << "|" << username << "|" << password << "|" << nama << endl;
    file.close();

    cout << "\nData petugas berhasil disimpan!" << endl;
}

//tampil semua petugas
void tampilPetugas() {
    ifstream file("petugas.txt");
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

        //masking password selalu 6 *
        string passMasked(6, '*');

        cout << id << "\t" << username << "\t\t" << passMasked << "\t\t" << nama << endl;
    }

    file.close();
}

int main() {
    int pilihan;

    do {
        cout << "\n=== MENU PETUGAS ===\n";
        cout << "1. Tambah Petugas\n";
        cout << "2. Tampil Petugas\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPetugas();
                break;
            case 2:
                tampilPetugas();
                break;
            case 0:
                cout << "Keluar program...\n";
                break;
            default:
                cout << "Pilihan salah!\n";
        }
    } while (pilihan != 0);

    return 0;
}
