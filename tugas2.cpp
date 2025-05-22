#include <iostream>
#include <string>
using namespace std;

struct Pesanan {
    string nama;
    string jenisRoti;
    int totalHarga;
    Pesanan* next;
};

struct Antrean {
    Pesanan* depan;
    Pesanan* belakang;

    Antrean() {
        depan = belakang = nullptr;
    }

    bool kosong() {
        return depan == nullptr;
    }

    void enqueue(string nama, string jenisRoti, int totalHarga) {
        Pesanan* baru = new Pesanan{nama, jenisRoti, totalHarga, nullptr};
        if (kosong()) {
            depan = belakang = baru;
        } else {
            belakang->next = baru;
            belakang = baru;
        }
        cout << " Pesanan berhasil ditambahkan ke antrean.\n";
    }

    void dequeue(Antrean& riwayat) {
        if (kosong()) {
            cout << " Antrean kosong, tidak ada yang bisa dilayani.\n";
            return;
        }
        Pesanan* keluar = depan;
        depan = depan->next;

        keluar->next = nullptr;
        if (riwayat.belakang == nullptr) {
            riwayat.depan = riwayat.belakang = keluar;
        } else {
            riwayat.belakang->next = keluar;
            riwayat.belakang = keluar;
        }

        cout << " Pesanan atas nama " << keluar->nama << " telah dilayani.\n";
    }

    void cetak() {
        if (kosong()) {
            cout << " Tidak ada pesanan dalam antrean.\n";
            return;
        }
        Pesanan* curr = depan;
        int i = 1;
        cout << "\n Daftar Pesanan dalam Antrean:\n";
        while (curr != nullptr) {
            cout << i++ << ". " << curr->nama << " - " << curr->jenisRoti << " - Rp" << curr->totalHarga << endl;
            curr = curr->next;
        }
    }

    void cancelLast() {
        if (kosong()) {
            cout << " Antrean kosong, tidak ada pesanan untuk dibatalkan.\n";
            return;
        }
        if (depan == belakang) {
            delete depan;
            depan = belakang = nullptr;
        } else {
            Pesanan* curr = depan;
            while (curr->next != belakang) {
                curr = curr->next;
            }
            delete belakang;
            belakang = curr;
            belakang->next = nullptr;
        }
        cout << " Pesanan terakhir telah dibatalkan.\n";
    }

    void displayHistory() {
        if (kosong()) {
            cout << "ℹ Belum ada pesanan yang pernah dilayani.\n";
            return;
        }
        Pesanan* curr = depan;
        int i = 1;
        cout << "\n Riwayat Pesanan yang Sudah Dilayani:\n";
        while (curr != nullptr) {
            cout << i++ << ". " << curr->nama << " - " << curr->jenisRoti << " - Rp" << curr->totalHarga << endl;
            curr = curr->next;
        }
    }
};

int main() {
    Antrean antrean;
    Antrean riwayat;
    int pilihan;

    do {
        cout << "\n====== SISTEM ANTREAN TOKO ROTI ======\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Layani Pesanan\n";
        cout << "3. Tampilkan Antrean\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Tampilkan Riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                string nama, jenis;
                int harga;
                cout << "Masukkan Nama Pembeli: "; getline(cin, nama);
                cout << "Masukkan Jenis Roti  : "; getline(cin, jenis);
                cout << "Masukkan Total Harga : "; cin >> harga;
                antrean.enqueue(nama, jenis, harga);
                break;
            }
            case 2:
                antrean.dequeue(riwayat);
                break;
            case 3:
                antrean.cetak();
                break;
            case 4:
                antrean.cancelLast();
                break;
            case 5:
                riwayat.displayHistory();
                break;
            case 0:
                cout << " Keluar dari program. Terima kasih!\n";
                break;
            default:
                cout << " Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
