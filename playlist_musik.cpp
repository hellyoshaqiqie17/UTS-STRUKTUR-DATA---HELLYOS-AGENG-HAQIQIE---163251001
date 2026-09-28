
//UTS Struktur Data - Hellyos Ageng Haqiqie -163251001  

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Struktur data untuk Lagu
struct Lagu {
    string judul;
    string penyanyi;
    string durasi; // ini menggunakan Format: MM:SS, contoh "03:45"
};

// Node untuk Singly Linked List (Playlist)
struct NodeLagu {
    Lagu data;
    NodeLagu* next;

    NodeLagu(const Lagu& l) : data(l), next(nullptr) {}
};

// Node untuk Stack (History Pemutaran Lagu)
struct NodeStack {
    Lagu data;
    NodeStack* next;

    NodeStack(const Lagu& l, NodeStack* n = nullptr) : data(l), next(n) {}
};

// Implementasi Stack History menggunakan Linked List
class StackHistory {
private:
    NodeStack* topNode;
    int count;

public:
    StackHistory() : topNode(nullptr), count(0) {}

    ~StackHistory() {
        while (!isEmpty()) {
            Lagu temp;
            pop(temp);
        }
    }

    // Memeriksa apakah stack kosong
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Operasi PUSH: menambahkan lagu yang diputar ke atas stack
    void push(const Lagu& l) {
        NodeStack* baru = new NodeStack(l, topNode);
        topNode = baru;
        count++;
    }

    // Operasi POP: menghapus riwayat lagu terakhir dari atas stack
    bool pop(Lagu& laguDihapus) {
        if (isEmpty()) {
            cout << "\n[PERINGATAN] Stack Underflow: Riwayat pemutaran kosong! Tidak ada history yang bisa dihapus.\n";
            return false;
        }

        NodeStack* temp = topNode;
        laguDihapus = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return true;
    }

    // Operasi PEEK: melihat lagu terakhir yang diputar tanpa menghapusnya
    bool peek(Lagu& laguTerakhir) const {
        if (isEmpty()) {
            cout << "\n[INFO] Riwayat pemutaran masih kosong. Belum ada lagu yang diputar.\n";
            return false;
        }

        laguTerakhir = topNode->data;
        return true;
    }

    // Menampilkan seluruh isi riwayat stack dari TOP ke BOTTOM
    void displayAll() const {
        if (isEmpty()) {
            cout << "\n[INFO] Riwayat pemutaran kosong (Stack kosong).\n";
            return;
        }

        cout << "\n======================================================================\n";
        cout << "                 RIWAYAT PEMUTARAN LAGU (STACK - LIFO)                \n";
        cout << "======================================================================\n";
        cout << left << setw(6)  << "Pos"
             << setw(30) << "Judul Lagu"
             << setw(24) << "Penyanyi"
             << setw(10) << "Durasi" << "\n";
        cout << "----------------------------------------------------------------------\n";

        NodeStack* curr = topNode;
        int idx = 1;
        while (curr != nullptr) {
            string posLabel = (curr == topNode) ? "TOP" : to_string(idx);
            cout << left << setw(6)  << posLabel
                 << setw(30) << curr->data.judul
                 << setw(24) << curr->data.penyanyi
                 << setw(10) << curr->data.durasi << "\n";
            curr = curr->next;
            idx++;
        }
        cout << "======================================================================\n";
        cout << "Total lagu dalam riwayat: " << count << "\n";
    }

    int getCount() const {
        return count;
    }
};

// Implementasi Singly Linked List untuk Playlist Musik
class PlaylistMusik {
private:
    NodeLagu* head;
    int totalLagu;

public:
    PlaylistMusik() : head(nullptr), totalLagu(0) {}

    ~PlaylistMusik() {
        NodeLagu* curr = head;
        while (curr != nullptr) {
            NodeLagu* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getTotal() const {
        return totalLagu;
    }

    // 1. Tambah lagu ke playlist (Insert at End / Tail)
    void tambahLagu(const Lagu& l) {
        NodeLagu* baru = new NodeLagu(l);

        if (head == nullptr) {
            head = baru;
        } else {
            NodeLagu* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = baru;
        }
        totalLagu++;
        cout << "\n[SUKSES] Lagu \"" << l.judul << "\" oleh " << l.penyanyi 
             << " berhasil ditambahkan ke playlist!\n";
    }

    // 2. Hapus lagu dari playlist berdasarkan nomor urutan
    bool hapusLaguByNomor(int nomor, Lagu& laguDihapus) {
        if (isEmpty() || nomor < 1 || nomor > totalLagu) {
            return false;
        }

        NodeLagu* hapus = nullptr;

        if (nomor == 1) {
            // Hapus di head
            hapus = head;
            head = head->next;
        } else {
            // Hapus di posisi ke-nomor
            NodeLagu* curr = head;
            for (int i = 1; i < nomor - 1; ++i) {
                curr = curr->next;
            }
            hapus = curr->next;
            curr->next = hapus->next;
        }

        laguDihapus = hapus->data;
        delete hapus;
        totalLagu--;
        return true;
    }

    // 2 (Alternatif). Hapus lagu berdasarkan judul
    bool hapusLaguByJudul(const string& judul, Lagu& laguDihapus) {
        if (isEmpty()) return false;

        NodeLagu* curr = head;
        NodeLagu* prev = nullptr;

        while (curr != nullptr) {
            if (curr->data.judul == judul) {
                if (prev == nullptr) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                laguDihapus = curr->data;
                delete curr;
                totalLagu--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // 3. Tampilkan seluruh isi playlist (Traversal Singly Linked List)
    void tampilkanPlaylist() const {
        cout << "\n======================================================================\n";
        cout << "                    DAFTAR PLAYLIST MUSIK                            \n";
        cout << "======================================================================\n";

        if (isEmpty()) {
            cout << "                 [ Playlist masih kosong ]                           \n";
            cout << "======================================================================\n";
            return;
        }

        cout << left << setw(5)  << "No"
             << setw(32) << "Judul Lagu"
             << setw(25) << "Penyanyi"
             << setw(10) << "Durasi" << "\n";
        cout << "----------------------------------------------------------------------\n";

        NodeLagu* curr = head;
        int no = 1;
        while (curr != nullptr) {
            cout << left << setw(5)  << no
                 << setw(32) << curr->data.judul
                 << setw(25) << curr->data.penyanyi
                 << setw(10) << curr->data.durasi << "\n";
            curr = curr->next;
            no++;
        }

        cout << "======================================================================\n";
        cout << "Total lagu: " << totalLagu << "\n";
    }

    // 4. Ambil data lagu berdasarkan nomor urutan (1-based index)
    bool getLaguByNomor(int nomor, Lagu& outLagu) const {
        if (isEmpty() || nomor < 1 || nomor > totalLagu) {
            return false;
        }

        NodeLagu* curr = head;
        for (int i = 1; i < nomor; ++i) {
            curr = curr->next;
        }

        outLagu = curr->data;
        return true;
    }
};

// Fungsi pembantu untuk membersihkan buffer input
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Objek global
PlaylistMusik playlist;
StackHistory history;

// 1. Menu Tambah Lagu
void menuTambahLagu() {
    cout << "\n--- TAMBAH LAGU KE PLAYLIST ---\n";
    Lagu l;

    cout << "Masukkan Judul Lagu   : ";
    cin >> ws;
    getline(cin, l.judul);

    cout << "Masukkan Nama Penyanyi: ";
    getline(cin, l.penyanyi);

    cout << "Masukkan Durasi (MM:SS): ";
    getline(cin, l.durasi);

    playlist.tambahLagu(l);
}

// 2. Menu Hapus Lagu
void menuHapusLagu() {
    cout << "\n--- HAPUS LAGU DARI PLAYLIST ---\n";
    if (playlist.isEmpty()) {
        cout << "[INFO] Playlist masih kosong. Tidak ada lagu yang bisa dihapus.\n";
        return;
    }

    playlist.tampilkanPlaylist();

    cout << "\nPilihan metode hapus:\n";
    cout << "1. Hapus berdasarkan Nomor Urut\n";
    cout << "2. Hapus berdasarkan Judul Lagu\n";
    cout << "Pilih metode (1/2): ";
    int metode;
    if (!(cin >> metode)) {
        cout << "[ERROR] Input invalid!\n";
        bersihkanInput();
        return;
    }

    Lagu laguDihapus;
    if (metode == 1) {
        int nomor;
        cout << "Masukkan Nomor Urut lagu yang ingin dihapus (1 - " << playlist.getTotal() << "): ";
        if (!(cin >> nomor)) {
            cout << "[ERROR] Input nomor harus berupa angka!\n";
            bersihkanInput();
            return;
        }

        if (playlist.hapusLaguByNomor(nomor, laguDihapus)) {
            cout << "\n[SUKSES] Lagu \"" << laguDihapus.judul << "\" oleh " 
                 << laguDihapus.penyanyi << " berhasil dihapus dari playlist.\n";
        } else {
            cout << "[ERROR] Nomor lagu tidak valid! Silakan cek nomor urut playlist.\n";
        }
    } else if (metode == 2) {
        string judul;
        cout << "Masukkan Judul Lagu yang ingin dihapus: ";
        cin >> ws;
        getline(cin, judul);

        if (playlist.hapusLaguByJudul(judul, laguDihapus)) {
            cout << "\n[SUKSES] Lagu \"" << laguDihapus.judul << "\" oleh " 
                 << laguDihapus.penyanyi << " berhasil dihapus dari playlist.\n";
        } else {
            cout << "[ERROR] Lagu dengan judul \"" << judul << "\" tidak ditemukan di playlist.\n";
        }
    } else {
        cout << "[ERROR] Pilihan metode tidak valid.\n";
    }
}

// 3. Menu Tampilkan Playlist
void menuTampilkanPlaylist() {
    playlist.tampilkanPlaylist();
}

// 4. Menu Putar Lagu Berdasarkan Urutan
void menuPutarLagu() {
    cout << "\n--- PUTAR LAGU BERDASARKAN URUTAN ---\n";
    if (playlist.isEmpty()) {
        cout << "[INFO] Playlist kosong. Tambahkan lagu terlebih dahulu sebelum memutar.\n";
        return;
    }

    playlist.tampilkanPlaylist();

    int nomor;
    cout << "\nMasukkan nomor urut lagu yang ingin diputar (1 - " << playlist.getTotal() << "): ";
    if (!(cin >> nomor)) {
        cout << "[ERROR] Input nomor harus berupa angka!\n";
        bersihkanInput();
        return;
    }

    Lagu laguDiputar;
    if (playlist.getLaguByNomor(nomor, laguDiputar)) {
        cout << "\n======================================================\n";
        cout << "  ▶ SEDANG MEMUTAR LAGU                              \n";
        cout << "======================================================\n";
        cout << "Judul Lagu : " << laguDiputar.judul << "\n";
        cout << "Penyanyi   : " << laguDiputar.penyanyi << "\n";
        cout << "Durasi     : " << laguDiputar.durasi << "\n";
        cout << "======================================================\n";

        // Setiap lagu yang diputar dimasukkan ke Stack History (PUSH)
        history.push(laguDiputar);
        cout << "[INFO] Lagu berhasil ditambahkan ke riwayat pemutaran (Stack History).\n";
    } else {
        cout << "[ERROR] Nomor lagu tidak valid! Silakan masukkan nomor antara 1 hingga " 
             << playlist.getTotal() << ".\n";
    }
}

// 5. Menu Lihat Lagu Terakhir Diputar (Stack Peek)
void menuLihatLaguTerakhir() {
    cout << "\n--- LIHAT LAGU TERAKHIR DIPUTAR (STACK PEEK) ---\n";
    Lagu laguTerakhir;

    if (history.peek(laguTerakhir)) {
        cout << "\n======================================================\n";
        cout << "  ⏮ LAGU TERAKHIR DIPUTAR (TOP OF STACK)              \n";
        cout << "======================================================\n";
        cout << "Judul Lagu : " << laguTerakhir.judul << "\n";
        cout << "Penyanyi   : " << laguTerakhir.penyanyi << "\n";
        cout << "Durasi     : " << laguTerakhir.durasi << "\n";
        cout << "======================================================\n";

        // Tanyakan apakah ingin melihat seluruh riwayat
        char lihatSemua;
        cout << "Tampilkan seluruh riwayat pemutaran? (y/n): ";
        cin >> lihatSemua;
        if (lihatSemua == 'y' || lihatSemua == 'Y') {
            history.displayAll();
        }
    }
}

// 6. Menu Hapus History Terakhir (Pop)
void menuHapusHistoryTerakhir() {
    cout << "\n--- HAPUS HISTORY TERAKHIR (POP STACK) ---\n";
    Lagu laguDihapus;

    if (history.pop(laguDihapus)) {
        cout << "\n[SUKSES] Riwayat pemutaran terakhir berhasil di-POP!\n";
        cout << "------------------------------------------------------\n";
        cout << "Judul Lagu : " << laguDihapus.judul << "\n";
        cout << "Penyanyi   : " << laguDihapus.penyanyi << "\n";
        cout << "Durasi     : " << laguDihapus.durasi << "\n";
        cout << "------------------------------------------------------\n";
        cout << "Sisa lagu dalam riwayat: " << history.getCount() << "\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n==================================================\n";
        cout << "      MANAJEMEN PLAYLIST MUSIK                    \n";
        cout << "     (Materi: Singly Linked List + Stack)         \n";
        cout << "==================================================\n";
        cout << "1. Tambah Lagu ke Playlist\n";
        cout << "2. Hapus Lagu dari Playlist\n";
        cout << "3. Tampilkan Playlist\n";
        cout << "4. Putar Lagu Berdasarkan Urutan\n";
        cout << "5. Lihat Lagu Terakhir Diputar (Stack)\n";
        cout << "6. Hapus History Terakhir (Pop)\n";
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
                menuTambahLagu();
                break;
            case 2:
                menuHapusLagu();
                break;
            case 3:
                menuTampilkanPlaylist();
                break;
            case 4:
                menuPutarLagu();
                break;
            case 5:
                menuLihatLaguTerakhir();
                break;
            case 6:
                menuHapusHistoryTerakhir();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan Aplikasi Playlist Musik!\n";
                break;
            default:
                cout << "\n[ERROR] Menu tidak valid! Silakan pilih angka antara 0 hingga 6.\n";
                break;
        }

    } while (pilihan != 0);

    return 0;
}
