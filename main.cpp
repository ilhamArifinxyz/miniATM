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

void inisialisasiAkun()
{
    Akun a1 = {"12345", "1111", "Budi Santoso", 1500000};
    g_semuaAkunBank.push_back(a1);
    tambahHistory(0, "Setoran Awal", 1500000);

    Akun a2 = {"56789", "2222", "Citra Lestari", 500000};
    g_semuaAkunBank.push_back(a2);
    tambahHistory(1, "Setoran Awal", 500000);

    Akun a3 = {"10101", "3333", "Ahmad Dahlan", 10000000};
    g_semuaAkunBank.push_back(a3);
    tambahHistory(2, "Setoran Awal", 10000000);

    Akun a4 = {"20202", "4444", "Dewi Sartika", 250000};
    g_semuaAkunBank.push_back(a4);
    tambahHistory(3, "Setoran Awal", 250000);
}

void tambahHistory(int indexAkun, string deskripsi, double jumlah)
{
    Transaksi trxBaru;
    trxBaru.deskripsi = deskripsi;
    trxBaru.jumlah = jumlah;

    g_semuaAkunBank[indexAkun].history.push_back(trxBaru);
}

int login()
{
    string noRek, pin;

    for (int percobaan = 0; percobaan < 3; percobaan++)
    {
        cout << "\nSilakan login." << endl;
        cout << "(Ketik 'exit' di Nomor Rekening untuk keluar)\n";
        cout << "Masukkan Nomor Rekening : ";
        cin >> noRek;

        if (noRek == "exit")
        {
            return -1;
        }

        cout << "Masukkan PIN            : ";
        cin >> pin;

        for (int i = 0; i < g_semuaAkunBank.size(); i++)
        {
            if (g_semuaAkunBank[i].nomorRekening == noRek && g_semuaAkunBank[i].pin == pin)
            {
                cout << "\nLogin berhasil! Selamat datang, " << g_semuaAkunBank[i].nama << "." << endl;
                pause();
                return i;
            }
        }

        cout << "\nNomor Rekening atau PIN salah." << endl;
        cout << "Sisa percobaan login: " << 2 - percobaan << endl;
        pause();
    }

    cout << "\nBatas percobaan login telah habis." << endl;
    pause();
    return -1;
}
