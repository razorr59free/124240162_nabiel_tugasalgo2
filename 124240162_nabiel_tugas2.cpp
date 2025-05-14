#include <iostream>
#include <string>

using namespace std;

// Struktur data buku dengan double linked list
struct Buku {
    string judul;
    int harga;
    Buku* prev;
    Buku* next;
};

// Pointer awal dan akhir dari linked list
Buku* head = NULL;
Buku* tail = NULL;

// Fungsi menambahkan buku di akhir list
void tambahBuku(string judul, int harga) {
    Buku* baru = new Buku;
    baru->judul = judul;
    baru->harga = harga;
    baru->prev = NULL;
    baru->next = NULL;

    if (head == NULL) {
        head = tail = baru; // jika list kosong
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }

    cout << "Buku berhasil ditambahkan.\n";
}

// Fungsi menampilkan semua buku
void tampilkanBuku() {
    if (head == NULL) {
        cout << "Data buku kosong.\n";
        return;
    }

    Buku* bantu = head;
    cout << "Daftar Buku:\n";
    while (bantu != NULL) {
        cout << "- Judul: " << bantu->judul << ", Harga: SAR " << bantu->harga << endl;
        bantu = bantu->next;
    }
}

// Fungsi mencari buku berdasarkan judul
void cariBuku(string target) {
    Buku* cari = head;
    bool ketemu = false;

    while (cari != NULL) {
        if (cari->judul == target) {
            cout << "Buku ditemukan: " << cari->judul << ", Harga: SAR " << cari->harga << endl;
            ketemu = true;
            break;
        }
        cari = cari->next;
    }

    if (!ketemu)
        cout << "Buku tidak ditemukan.\n";
}

// Menyisip buku di depan
void sisipDepan(string judul, int harga) {
    Buku* baru = new Buku{judul, harga, NULL, head};

    if (head != NULL)
        head->prev = baru;
    else
        tail = baru;

    head = baru;
    cout << "Buku disisip di depan.\n";
}

// Menyisip buku di belakang (sama seperti tambah biasa)
void sisipBelakang(string judul, int harga) {
    tambahBuku(judul, harga);
}

// Menyisip buku di tengah (setelah buku tertentu)
void sisipTengah(string judul, int harga, string setelahJudul) {
    Buku* bantu = head;

    while (bantu != NULL && bantu->judul != setelahJudul)
        bantu = bantu->next;

    if (bantu == NULL) {
        cout << "Judul buku untuk referensi tidak ditemukan.\n";
        return;
    }

    Buku* baru = new Buku{judul, harga, bantu, bantu->next};

    if (bantu->next != NULL)
        bantu->next->prev = baru;
    else
        tail = baru;

    bantu->next = baru;
    cout << "Buku disisip setelah " << setelahJudul << ".\n";
}

// Fungsi untuk menghapus buku berdasarkan judul
void hapusBuku(string judul) {
    Buku* hapus = head;

    while (hapus != NULL && hapus->judul != judul)
        hapus = hapus->next;

    if (hapus == NULL) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    if (hapus->prev != NULL)
        hapus->prev->next = hapus->next;
    else
        head = hapus->next;

    if (hapus->next != NULL)
        hapus->next->prev = hapus->prev;
    else
        tail = hapus->prev;

    delete hapus;
    cout << "Buku berhasil dihapus.\n";
}

// Fungsi utama (main menu)
int main() {
    int pilih;
    string judul, setelahJudul;
    int harga;

    do {
        cout << "\n=== Menu ===\n";
        cout << "1. Tambahkan Buku\n";
        cout << "2. Tampilkan Seluruh Data Buku\n";
        cout << "3. Cari Data Buku\n";
        cout << "4. Sisip Buku\n";
        cout << "5. Hapus Buku\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                cout << "Judul Buku: ";
                getline(cin, judul);
                cout << "Harga Buku (dalam angka): ";
                cin >> harga;
                tambahBuku(judul, harga);
                break;

            case 2:
                tampilkanBuku();
                break;

            case 3:
                cout << "Masukkan judul buku yang dicari: ";
                getline(cin, judul);
                cariBuku(judul);
                break;

            case 4:
                int sub;
                cout << "1. Sisip Depan\n2. Sisip Tengah\n3. Sisip Belakang\nPilih: ";
                cin >> sub;
                cin.ignore();

                cout << "Judul Buku: ";
                getline(cin, judul);
                cout << "Harga Buku: ";
                cin >> harga;
                cin.ignore();

                if (sub == 1)
                    sisipDepan(judul, harga);
                else if (sub == 2) {
                    cout << "Sisip setelah buku berjudul: ";
                    getline(cin, setelahJudul);
                    sisipTengah(judul, harga, setelahJudul);
                } else if (sub == 3)
                    sisipBelakang(judul, harga);
                else
                    cout << "Pilihan tidak valid.\n";
                break;

            case 5:
                cout << "Judul buku yang ingin dihapus: ";
                getline(cin, judul);
                hapusBuku(judul);
                break;

            case 6:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Menu tidak valid.\n";
        }
    } while (pilih != 6);

    return 0;
}
