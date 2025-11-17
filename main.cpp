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

void pause()
{
    char lanjut;
    cout << "\nKetik huruf apapun lalu Enter untuk melanjutkan: ";
    cin >> lanjut;
}

int main()
{
    inisialisasiAkun();

    while (true)
    {
        cout << "\n\n*************************************" << endl;
        cout << "==   SELAMAT DATANG DI ATM MINI    ==" << endl;
        cout << "*************************************" << endl;

        int indexAkunAktif = login();

        if (indexAkunAktif != -1)
        {
            tampilkanMenu(indexAkunAktif);
        }
        else
        {
            cout << "Terima kasih telah menggunakan ATM kami." << endl;
            break;
        }
    }

    return 0;
}
