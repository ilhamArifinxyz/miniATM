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

int cariAkun(string nomorRekening)
{
    for (int i = 0; i < g_semuaAkunBank.size(); i++)
    {
        if (g_semuaAkunBank[i].nomorRekening == nomorRekening)
        {
            return i;
        }
    }
    return -1;
}

void tampilkanMenu(int indexAkun)
{
    int pilihan = 0;

    while (pilihan != 6)
    {
        cout << "\n\n*************************************" << endl;
        cout << "==           MENU UTAMA ATM          ==" << endl;
        cout << "*************************************" << endl;

        cout << "Halo, " << g_semuaAkunBank[indexAkun].nama << endl;
        cout << "Rekening: " << g_semuaAkunBank[indexAkun].nomorRekening << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Cek Saldo" << endl;
        cout << "2. Tarik Saldo" << endl;
        cout << "3. Tambah Saldo (Setor Tunai)" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Cek History Transaksi" << endl;
        cout << "6. Logout" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Masukkan pilihan Anda (1-6): ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cekSaldo(indexAkun);
            break;
        case 2:
            tarikSaldo(indexAkun);
            break;
        case 3:
            tambahSaldo(indexAkun);
            break;
        case 4:
            transfer(indexAkun);
            break;
        case 5:
            cekHistory(indexAkun);
            break;
        case 6:
            cout << "\nLogout berhasil. Terima kasih." << endl;
            break;
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }

        if (pilihan != 6)
        {
            pause();
        }
    }
}

void cekSaldo(int indexAkun)
{
    cout << "\n--- CEK SALDO ---" << endl;

    cout << "Saldo Anda saat ini adalah: Rp " << formatRibuan(g_semuaAkunBank[indexAkun].saldo) << endl;
}

void tambahSaldo(int indexAkun)
{
    cout << "\n--- TAMBAH SALDO (SETOR TUNAI) ---" << endl;
    double jumlah;
    cout << "Masukkan jumlah yang ingin disetor: Rp ";
    cin >> jumlah;

    if (jumlah <= 0)
    {
        cout << "Jumlah tidak valid." << endl;
    }
    else
    {
        g_semuaAkunBank[indexAkun].saldo += jumlah;
        tambahHistory(indexAkun, "Setor Tunai", jumlah);

        cout << "Setor tunai berhasil." << endl;
        cout << "Saldo baru Anda: Rp " << g_semuaAkunBank[indexAkun].saldo << endl;
    }
}

void tarikSaldo(int indexAkun)
{
    cout << "\n--- TARIK SALDO ---" << endl;
    double jumlah;
    cout << "Masukkan jumlah yang ingin ditarik: Rp ";
    cin >> jumlah;

    if (jumlah <= 0)
    {
        cout << "Jumlah tidak valid." << endl;
    }
    else if (jumlah > g_semuaAkunBank[indexAkun].saldo)
    {
        cout << "Saldo tidak mencukupi." << endl;
        cout << "Saldo Anda saat ini: Rp " << formatRibuan(g_semuaAkunBank[indexAkun].saldo) << endl;
    }
    else
    {
        g_semuaAkunBank[indexAkun].saldo -= jumlah;
        tambahHistory(indexAkun, "Tarik Tunai", -jumlah);

        cout << "Tarik tunai berhasil." << endl;
        cout << "Saldo sisa Anda: Rp " << g_semuaAkunBank[indexAkun].saldo << endl;
    }
}

void transfer(int indexAkunPengirim)
{
    cout << "\n--- TRANSFER ANTAR AKUN ---" << endl;
    string noRekTujuan;
    double jumlah;

    cout << "Masukkan Nomor Rekening Tujuan: ";
    cin >> noRekTujuan;

    int indexAkunPenerima = cariAkun(noRekTujuan);

    if (indexAkunPenerima == -1)
    {
        cout << "Nomor Rekening Tujuan tidak ditemukan." << endl;
    }
    else if (indexAkunPenerima == indexAkunPengirim)
    {
        cout << "Anda tidak dapat transfer ke rekening Anda sendiri." << endl;
    }
    else
    {
        cout << "Anda akan transfer ke: " << g_semuaAkunBank[indexAkunPenerima].nama << endl;
        cout << "Masukkan jumlah transfer: Rp ";
        cin >> jumlah;

        if (jumlah <= 0)
        {
            cout << "Jumlah tidak valid." << endl;
        }
        else if (jumlah > g_semuaAkunBank[indexAkunPengirim].saldo)
        {
            cout << "Saldo tidak mencukupi untuk melakukan transfer." << endl;
        }
        else
        {
            g_semuaAkunBank[indexAkunPengirim].saldo -= jumlah;
            g_semuaAkunBank[indexAkunPenerima].saldo += jumlah;

            tambahHistory(indexAkunPengirim, "Transfer ke " + g_semuaAkunBank[indexAkunPenerima].nama, -jumlah);
            tambahHistory(indexAkunPenerima, "Transfer dari " + g_semuaAkunBank[indexAkunPengirim].nama, jumlah);

            cout << "Transfer berhasil." << endl;
            cout << "Saldo baru Anda: Rp " << g_semuaAkunBank[indexAkunPengirim].saldo << endl;
        }
    }
}

