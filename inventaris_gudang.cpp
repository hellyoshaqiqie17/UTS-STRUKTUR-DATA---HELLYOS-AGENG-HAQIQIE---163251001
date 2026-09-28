
//UTS STRUKTUR DATA - HELLYOS AGENG HAQIQIE - 163251001

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Konstanta kapasitas maksimal
const int MAX_BARANG = 100;
const int MAX_STACK = 100;

// Struktur data untuk Barang dalam Inventaris (Array)
struct Barang {
    string kode;
    string nama;
    int stok;
};

// Struktur data untuk Riwayat Perubahan Stok (Stack)
struct Transaksi {
    string kodeBarang;
    string namaBarang;
    int jumlahTambah;
};

// Implementasi Stack menggunakan Array untuk Riwayat Transaksi
struct StackRiwayat {
    Transaksi data[MAX_STACK];
    int top;

    StackRiwayat() {
        top = -1; // Stack kosong diawali dengan top = -1
    }

    // Memeriksa apakah Stack penuh
    bool isFull() const {
        return top == MAX_STACK - 1;
    }

    // Memeriksa apakah Stack kosong
    bool isEmpty() const {
        return top == -1;
    }

    // Operasi Push dengan validasi Stack Overflow
    bool push(const Transaksi& t) {
        if (isFull()) {
            cout << "\n[PERINGATAN] Stack Overflow: Riwayat transaksi sudah penuh (Maksimal " 
                 << MAX_STACK << " transaksi)!\n";
            return false;
        }
        data[++top] = t;
        return true;
    }

    // Operasi Pop dengan validasi Stack Underflow
    bool pop(Transaksi& t) {
        if (isEmpty()) {
            cout << "\n[PERINGATAN] Stack Underflow: Tidak ada riwayat transaksi yang dapat dibatalkan (Stack Kosong)!\n";
            return false;
        }
        t = data[top--];
        return true;
    }

    // Menampilkan isi Stack dari elemen teratas (TOP/LIFO)
    void display() const {
        if (isEmpty()) {
            cout << "\n[INFO] Riwayat transaksi kosong (Belum ada perubahan stok).\n";
            return;
        }

        cout << "\n======================================================================\n";
        cout << "               RIWAYAT TRANSAKSI TERAKHIR (STACK - LIFO)             \n";
        cout << "======================================================================\n";
        cout << left << setw(6)  << "Pos"
             << setw(16) << "Kode Barang"
             << setw(32) << "Nama Barang"
             << setw(14) << "Perubahan" << "\n";
        cout << "----------------------------------------------------------------------\n";

        for (int i = top; i >= 0; --i) {
            string posLabel = (i == top) ? "TOP" : to_string(i + 1);
            cout << left << setw(6)  << posLabel
                 << setw(16) << data[i].kodeBarang
                 << setw(32) << data[i].namaBarang
                 << "+" + to_string(data[i].jumlahTambah) << "\n";
        }
        cout << "======================================================================\n";
        cout << "Total riwayat tersimpan: " << (top + 1) << " dari kapasitas " << MAX_STACK << "\n";
    }
};

// Variabel global / state inventaris
Barang daftarBarang[MAX_BARANG];
int jumlahBarang = 0;
StackRiwayat riwayatTransaksi;

// Fungsi pembantu untuk membersihkan buffer input jika terjadi error
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fungsi untuk mencari indeks barang berdasarkan kode (Linear Search)
int cariIndeksBarang(const string& kode) {
    for (int i = 0; i < jumlahBarang; ++i) {
        if (daftarBarang[i].kode == kode) {
            return i;
        }
    }
    return -1; // Tidak ditemukan
}

// 1. Fitur Tambah Barang (Array)
void tambahBarang() {
    cout << "\n--- TAMBAH BARANG BARU ---\n";
    if (jumlahBarang >= MAX_BARANG) {
        cout << "[ERROR] Gudang penuh! Tidak dapat menambahkan barang baru (Maksimal " 
             << MAX_BARANG << " barang).\n";
        return;
    }

    string kode, nama;
    int stok;

    cout << "Masukkan Kode Barang: ";
    cin >> ws;
    getline(cin, kode);

    // Cek apakah kode barang sudah terdaftar
    if (cariIndeksBarang(kode) != -1) {
        cout << "[ERROR] Barang dengan kode '" << kode << "' sudah terdaftar! Gunakan kode lain.\n";
        return;
    }

    cout << "Masukkan Nama Barang: ";
    getline(cin, nama);

    cout << "Masukkan Jumlah Stok Awal: ";
    while (!(cin >> stok) || stok < 0) {
        cout << "[INPUT INVALID] Masukkan angka stok yang valid (>= 0): ";
        bersihkanInput();
    }

    // Simpan ke dalam array inventaris
    daftarBarang[jumlahBarang].kode = kode;
    daftarBarang[jumlahBarang].nama = nama;
    daftarBarang[jumlahBarang].stok = stok;
    jumlahBarang++;

    cout << "[SUKSES] Barang '" << nama << "' berhasil ditambahkan ke inventaris!\n";
}

// 2. Fitur Tampilkan Seluruh Barang
void tampilkanSeluruhBarang() {
    cout << "\n======================================================================\n";
    cout << "                       DAFTAR BARANG DI GUDANG                        \n";
    cout << "======================================================================\n";

    if (jumlahBarang == 0) {
        cout << "                 [ Belum ada data barang di gudang ]                  \n";
        cout << "======================================================================\n";
        return;
    }

    cout << left << setw(5)  << "No"
         << setw(16) << "Kode Barang"
         << setw(35) << "Nama Barang"
         << right << setw(10) << "Stok" << "\n";
    cout << "----------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahBarang; ++i) {
        cout << left << setw(5)  << (i + 1)
             << setw(16) << daftarBarang[i].kode
             << setw(35) << daftarBarang[i].nama
             << right << setw(10) << daftarBarang[i].stok << "\n";
    }

    cout << "======================================================================\n";
    cout << "Total jenis barang: " << jumlahBarang << " / " << MAX_BARANG << "\n";
}

// 3. Fitur Cari Barang Berdasarkan Kode
void cariBarang() {
    cout << "\n--- CARI BARANG BERDASARKAN KODE ---\n";
    if (jumlahBarang == 0) {
        cout << "[INFO] Inventaris masih kosong.\n";
        return;
    }

    string kode;
    cout << "Masukkan Kode Barang yang dicari: ";
    cin >> ws;
    getline(cin, kode);

    int idx = cariIndeksBarang(kode);
    if (idx != -1) {
        cout << "\n[HASIL DITEMUKAN]\n";
        cout << "--------------------------------------\n";
        cout << "Kode Barang : " << daftarBarang[idx].kode << "\n";
        cout << "Nama Barang : " << daftarBarang[idx].nama << "\n";
        cout << "Jumlah Stok : " << daftarBarang[idx].stok << " unit\n";
        cout << "--------------------------------------\n";
    } else {
        cout << "[INFO] Barang dengan kode '" << kode << "' tidak ditemukan!\n";
    }
}

// 4. Fitur Tambah Stok (Push ke Stack)
void tambahStok() {
    cout << "\n--- TAMBAH STOK BARANG (PUSH KE STACK) ---\n";
    if (jumlahBarang == 0) {
        cout << "[INFO] Belum ada barang di inventaris. Silakan tambahkan barang terlebih dahulu.\n";
        return;
    }

    string kode;
    cout << "Masukkan Kode Barang yang ingin ditambah stoknya: ";
    cin >> ws;
    getline(cin, kode);

    int idx = cariIndeksBarang(kode);
    if (idx == -1) {
        cout << "[ERROR] Barang dengan kode '" << kode << "' tidak ditemukan!\n";
        return;
    }

    // Validasi apakah stack riwayat penuh (Stack Overflow)
    if (riwayatTransaksi.isFull()) {
        cout << "[PERINGATAN] Stack Overflow: Riwayat transaksi sudah mencapai batas maksimum ("
             << MAX_STACK << ")!\n";
        cout << "Perubahan stok tidak dapat dicatat ke riwayat transaksi.\n";
        return;
    }

    int jumlahTambah;
    cout << "Barang ditemukan: " << daftarBarang[idx].nama << " (Stok saat ini: " << daftarBarang[idx].stok << ")\n";
    cout << "Masukkan jumlah stok yang ditambahkan: ";
    while (!(cin >> jumlahTambah) || jumlahTambah <= 0) {
        cout << "[INPUT INVALID] Jumlah tambahan stok harus berupa angka lebih dari 0: ";
        bersihkanInput();
    }

    // Tambah stok pada array barang
    daftarBarang[idx].stok += jumlahTambah;

    // Catat ke Stack Riwayat Transaksi (Push)
    Transaksi t;
    t.kodeBarang = daftarBarang[idx].kode;
    t.namaBarang = daftarBarang[idx].nama;
    t.jumlahTambah = jumlahTambah;

    riwayatTransaksi.push(t);

    cout << "\n[SUKSES] Stok berhasil ditambahkan!\n";
    cout << "Barang       : " << daftarBarang[idx].nama << "\n";
    cout << "Tambah Stok  : +" << jumlahTambah << "\n";
    cout << "Stok Sekarang: " << daftarBarang[idx].stok << "\n";
    cout << "[INFO] Transaksi berhasil di-PUSH ke Stack riwayat transaksi.\n";
}

// 5. Fitur Batalkan Transaksi Terakhir (Pop)
void batalkanTransaksiTerakhir() {
    cout << "\n--- BATALKAN TRANSAKSI TERAKHIR (POP STACK) ---\n";

    Transaksi tTerakhir;
    // Lakukan operasi POP dari stack
    if (!riwayatTransaksi.pop(tTerakhir)) {
        // Jika pop gagal karena stack kosong, pesan Underflow sudah ditampilkan oleh method pop
        return;
    }

    // Cari barang yang bersangkutan di array
    int idx = cariIndeksBarang(tTerakhir.kodeBarang);
    if (idx != -1) {
        // Rollback stok: kurangi stok kembali sebesar jumlah yang pernah ditambahkan
        daftarBarang[idx].stok -= tTerakhir.jumlahTambah;
        if (daftarBarang[idx].stok < 0) {
            daftarBarang[idx].stok = 0; // Menjaga batas bawah stok
        }

        cout << "\n[SUKSES] Transaksi terakhir berhasil dibatalkan (POP)!\n";
        cout << "--------------------------------------------------------\n";
        cout << "Kode Barang     : " << tTerakhir.kodeBarang << "\n";
        cout << "Nama Barang     : " << tTerakhir.namaBarang << "\n";
        cout << "Stok Dikurangkan: -" << tTerakhir.jumlahTambah << " (Pembatalan)\n";
        cout << "Stok Sekarang   : " << daftarBarang[idx].stok << "\n";
        cout << "--------------------------------------------------------\n";
    } else {
        cout << "[PERINGATAN] Data barang dengan kode '" << tTerakhir.kodeBarang 
             << "' tidak lagi ada di inventaris, namun transaksi telah di-POP dari stack.\n";
    }
}

// 6. Fitur Tampilkan Riwayat Transaksi Stack
void tampilkanRiwayat() {
    riwayatTransaksi.display();
}

int main() {
    int pilihan;

    do {
        cout << "\n==================================================\n";
        cout << "     SISTEM INVENTARIS BARANG GUDANG             \n";
        cout << "             (Materi: Array + Stack)              \n";
        cout << "==================================================\n";
        cout << "1. Tambah Barang Baru (Array)\n";
        cout << "2. Tampilkan Seluruh Barang\n";
        cout << "3. Cari Barang Berdasarkan Kode\n";
        cout << "4. Tambah Stok Barang (Push ke Stack)\n";
        cout << "5. Batalkan Transaksi Terakhir (Pop Stack)\n";
        cout << "6. Tampilkan Riwayat Transaksi (Stack)\n";
        cout << "0. Keluar\n";
        cout << "==================================================\n";
        cout << "Pilih menu (0-6): ";

        if (!(cin >> pilihan)) {
            cout << "\n[ERROR] Pilihan harus berupa angka 0 - 6!\n";
            bersihkanInput();
            continue;
        }

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanSeluruhBarang();
                break;
            case 3:
                cariBarang();
                break;
            case 4:
                tambahStok();
                break;
            case 5:
                batalkanTransaksiTerakhir();
                break;
            case 6:
                tampilkanRiwayat();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan Sistem Inventaris Gudang!\n";
                break;
            default:
                cout << "\n[ERROR] Menu tidak valid! Silakan pilih angka antara 0 hingga 6.\n";
                break;
        }

    } while (pilihan != 0);

    return 0;
}
