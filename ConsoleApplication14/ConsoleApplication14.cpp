#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;
const int SIZE = 20;
enum TrenchType { FAULT, RIDGE, GUTTER };
struct Location {
    char ocean[50];
};

struct Trench {
    char name[100];
    int depth;
    Location loc;
    TrenchType type;
};

Trench trenches[SIZE] = {
    {"Марианская", 11022, {"Pacific"}, GUTTER},
    {"Тонга", 10882, {"Pacific"}, GUTTER},
    {"Филиппинская", 10540, {"Pacific"}, GUTTER},
    {"Кермадек", 10047, {"Pacific"}, GUTTER},
    {"Пуэрто-Рико", 8376, {"Atlantic"}, GUTTER},
    {"Южно-Сандвичев", 8428, {"Atlantic"}, GUTTER},
    {"Романш", 7760, {"Atlantic"}, FAULT},
    {"Кайман", 7686, {"Atlantic"}, FAULT},
    {"Яванская", 7725, {"Indian"}, GUTTER},
    {"Диамантина", 8047, {"Indian"}, FAULT},
    {"Перуанская", 8065, {"Pacific"}, GUTTER},
    {"Алеутская", 7679, {"Pacific"}, GUTTER},
    {"Рюкю", 7507, {"Pacific"}, GUTTER},
    {"Идзу-Бонин", 9810, {"Pacific"}, GUTTER},
    {"Яп", 8527, {"Pacific"}, GUTTER},
    {"Палау", 8138, {"Pacific"}, GUTTER},
    {"Центральноамериканская", 6669, {"Pacific"}, GUTTER},
    {"Сан-Кристобаль", 9165, {"Pacific"}, GUTTER},
    {"Милуоки", 8380, {"Atlantic"}, GUTTER},
    {"Витязь", 6150, {"Pacific"}, RIDGE}
};
void print(Trench t) {
    cout << t.name << ", " << t.depth << " м, ";
    if (strcmp(t.loc.ocean, "Pacific") == 0) cout << "Тихий";
    else if (strcmp(t.loc.ocean, "Atlantic") == 0) cout << "Атлантический";
    else cout << "Индийский";
    cout << ", ";
    if (t.type == FAULT) cout << "разломная";
    else if (t.type == RIDGE) cout << "хребет";
    else cout << "желоб";
    cout << endl;
}
int cntDeep() {
    int cnt = 0;
    for (int i = 0; i < SIZE; i++)
        if (trenches[i].depth > 7000) cnt++;
    return cnt;
}

void sortGutters() {
    Trench gutters[SIZE];
    int gcnt = 0;
    for (int i = 0; i < SIZE; i++)
        if (trenches[i].type == GUTTER)
            gutters[gcnt++] = trenches[i];
    for (int i = 0; i < gcnt - 1; i++)
        for (int j = 0; j < gcnt - i - 1; j++)
            if (strcmp(gutters[j].loc.ocean, gutters[j + 1].loc.ocean) > 0)
                swap(gutters[j], gutters[j + 1]);
    cout << "\nЖелобы, отсортированные по океанам:\n";
    for (int i = 0; i < gcnt; i++)
        print(gutters[i]);
}

void top3deep() {
    Trench copy[SIZE];
    for (int i = 0; i < SIZE; i++) copy[i] = trenches[i];
    for (int i = 0; i < SIZE - 1; i++)
        for (int j = 0; j < SIZE - i - 1; j++)
            if (copy[j].depth < copy[j + 1].depth)
                swap(copy[j], copy[j + 1]);
    cout << "\nТип 3 глубочайших впадин: \n";
    for (int i = 0; i < 3; i++) {
        cout << copy[i].name << ", глубина " << copy[i].depth << "м: ";
        if (copy[i].type == FAULT) cout << "разломная";
        else if (copy[i].type == RIDGE) cout << "хребет";
        else cout << "желоб";
        cout << endl;
    }
}
void change(int d, const char* n, const char* o, TrenchType t) {
    for (int i = 0; i < SIZE; i++)
        if (trenches[i].depth == d) {
            strcpy_s(trenches[i].name, n);
            strcpy_s(trenches[i].loc.ocean, o);
            trenches[i].type = t;
            return;
        }
    cout << "Не найдено\n";
}
void filter(const char* ocean, Trench*& arr, int& cnt) {
    arr = new Trench[SIZE];
    cnt = 0;
    for (int i = 0; i < SIZE; i++) {
        if (strcmp(trenches[i].loc.ocean, ocean) == 0) {
            arr[cnt++] = trenches[i];
        }
    }
}

void show(Trench* arr, int cnt) {
    if (cnt == 0) {
        cout << "Нет данных\n";
        return;
    }
    for (int i = 0; i < cnt; i++)
        print(arr[i]);
}
//Задание 1
void file() {
    ifstream fin("myfile.txt");
    if (fin.is_open()) {
        char name[100];
        int val;
        while (fin >> name >> val) {
            for (int i = 0; i < SIZE; i++) {
                if (strcmp(trenches[i].name, name) == 0) {
                    trenches[i].depth = val;
                }
            }
        }
        fin.close();
    }
    cout << "\nОбновлёенные данные после считывания из файла:\n";
    for (int i = 0; i < SIZE; i++) {
        print(trenches[i]);
    }
}
//Задание 2
void SaveBin(Trench t, const char* filename) {
    ofstream out(filename, ios::binary | ios::out);
    if (out.is_open()) {
        out.write((char*)&t, sizeof(Trench));
        out.close();
        cout << "\nДанные записаны в бинарный файл\n";
    }
}

void LoadBin(const char* filename) {
    Trench t;
    ifstream in(filename, ios::binary | ios::in);
    if (in.is_open()) {
        in.read((char*)&t, sizeof(Trench));
        in.close();
        cout << "\nДанные из бинарного файла " << filename << ":\n";
        print(t);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Количество впадин глубже 7 тысяч метров: " << cntDeep() << endl;
    sortGutters();
    top3deep();
    cout << "\nИзменение названия и океана впадины по глубине 8376:\n";
    change(8376, "Новая", "Atlantic", RIDGE);
    for (int i = 0; i < SIZE; i++)
        if (trenches[i].depth == 8376) print(trenches[i]);
    char ocean[50];
    cout << "\nВведите название океана по английски(Pacific, Atlantic, Indian):";
    cin >> ocean;
    Trench* filtered;
    int fcnt;
    filter(ocean, filtered, fcnt);
    cout << "\nРезультат:\n";
    show(filtered, fcnt);

    cout << "\n\nЗадание 1\n";
    file();

    cout << "\n\nЗадание 2\n";
    SaveBin(trenches[0], "trench.bin");
    LoadBin("trench.bin");

    delete[] filtered;
    return 0;
}