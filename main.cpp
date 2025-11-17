#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Transaksi
{
    string deskripsi;
    double jumlah;
};

struct Akun
{
    string nomorRekening;
    string pin;
    string nama;
    long long saldo;
    vector<Transaksi> history;
};
vector<Akun> g_semuaAkunBank;

void inisialisasiAkun();
void tambahHistory(int indexAkun, string deskripsi, double jumlah);
int login();
int cariAkun(string nomorRekening);
void tampilkanMenu(int indexAkun);
void cekSaldo(int indexAkun);
void tambahSaldo(int indexAkun);
void tarikSaldo(int indexAkun);
void transfer(int indexAkunPengirim);
void cekHistory(int indexAkun);
