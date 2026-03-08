/*
===============================================================
[Touhou] Bad Apple!! - ASCII Animation Player
===============================================================

Description:
This program plays the Touhou "Bad Apple!!" animation in the
Windows console using ASCII frames.

Frames are stored as text files and loaded into memory before
playback. The program synchronizes frame rendering with time
to achieve a stable frame rate and plays the audio track
simultaneously.

How It Works:
1. The program reads the total number of frames from:
      res/numberOfFrames.txt
2. All frame files are loaded into memory:
      res/BA1.txt
      res/BA2.txt
      ...
3. The audio file (BA.wav) is played asynchronously.
4. Frames are rendered at 30 FPS using time-based calculation.

Directory Structure:
    res/
        BA1.txt
        BA2.txt
        ...
        numberOfFrames.txt
        BA.wav

Dependencies:
- Windows API (windows.h)
- Windows Multimedia API (winmm.lib)
- Standard C libraries

Platform:
Windows Console

Compile Example (GCC / MinGW):
    gcc main.c -o badapple -lwinmm

Author:
Bryan Alexander - 2802428665 [Mika Von Euphillia]

Notes:
- Console must support ANSI escape codes.
- Large animations may require significant memory since
  all frames are preloaded.

===============================================================
*/

#include <stdio.h>      // Library standar input/output (printf, fopen, dll)
#include <stdlib.h>     // Library untuk alokasi memori (malloc, free)
#include <string.h>     // Operasi string
#include <time.h>       // Digunakan untuk timing (clock)
#include <windows.h>    // Windows API (cursor console, Sleep, dll)
#include <mmsystem.h>   // Windows Multimedia API (PlaySound)


// ==========================
// Konfigurasi Program
// ==========================

#define PROJECTNAME "[Touhou]Bad Apple!!"  // Nama project yang ditampilkan
#define DIRECTORY "res"                    // Folder tempat semua frame disimpan
#define PREFIX "/BA"                       // Prefix nama file frame
#define FILETOT "/numberOfFrames.txt"      // File berisi jumlah total frame
#define FILEMUSIC "res/BA.wav"             // File audio yang diputar

#define FPS 30                             // Frame per second video
#define FRAME_TIME (1000 / FPS)            // Waktu per frame dalam milidetik

// Warna ANSI untuk tampilan console
#define COLOR_RESET "\033[0m"
#define COLOR_TITLE "\033[1;36m"
#define COLOR_LOAD  "\033[33m"
#define COLOR_READY "\033[32m"
#define COLOR_PINK	"\033[38;5;218m"

#define ALIAS "Mika Von Euphillia"

// =========================================
// Fungsi untuk memindahkan kursor console
// =========================================
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;  // posisi kolom
    coord.Y = y;  // posisi baris
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// =========================================
// Prototype fungsi
// =========================================
int getTotFrames(char *dir);                    // Membaca jumlah total frame
char *loadFrame(int i, char *dir);              // Load satu frame ASCII
char **loadFrames(char *dir, int totFrames);    // Load semua frame
void play(char **frames, int totFrames);        // Memainkan animasi


// =========================================
// Fungsi utama program
// =========================================
int main() {

    // Ambil jumlah total frame dari file konfigurasi
    int totFrames = getTotFrames(DIRECTORY);

    // Jika gagal membaca jumlah frame
    if (totFrames <= 0) {
        printf("Failed to read number of frames\n");
        return 1;
    }

    // Tampilan judul program
	printf(COLOR_TITLE "=== %s ===\n" COLOR_RESET, PROJECTNAME);
	printf(COLOR_PINK "BY : %s\n" COLOR_RESET, ALIAS);
    printf(COLOR_LOAD "Loading %d frames...\n" COLOR_RESET, totFrames);

    // Load semua frame ASCII ke memori
    char **frames = loadFrames(DIRECTORY, totFrames);

    // Tunggu user menekan ENTER
    printf(COLOR_READY "Press ENTER to play..." COLOR_RESET);
    getchar();

    // Putar musik secara asynchronous (tidak memblokir program)
	PlaySound(FILEMUSIC, NULL, SND_ASYNC);

    // Jalankan animasi
    play(frames, totFrames);

    return 0;
}


// =========================================
// Membaca jumlah total frame dari file
// res/numberOfFrames.txt
// =========================================
int getTotFrames(char *dir) {

    char fileName[200];

    // Membuat path file lengkap
    sprintf(fileName, "%s%s", dir, FILETOT);

    // Buka file
    FILE *fin = fopen(fileName, "r");
    if (!fin) return -1;  // jika gagal

    int tot;

    // Baca integer jumlah frame
    fscanf(fin, "%d", &tot);

    fclose(fin);

    return tot;
}

// =========================================
// Load satu frame ASCII dari file
// contoh: res/BA1.txt, res/BA2.txt, dst
// =========================================
char *loadFrame(int i, char *dir) {

    char fileName[200];
    
    // Membuat nama file frame
    sprintf(fileName, "%s%s%d.txt", dir, PREFIX, i + 1);
    
    // Buka file dalam mode binary
    FILE *f = fopen(fileName, "rb");
    if (!f) return NULL;

    // Cari ukuran file
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    // Alokasi memori untuk isi file
    char *buffer = malloc(size + 1);

    // Baca isi file ke buffer
    fread(buffer, 1, size, f);

    // Tambahkan null-terminator agar menjadi string
    buffer[size] = '\0';

    fclose(f);
    
    return buffer;
}


// =========================================
// Load seluruh frame ke dalam array
// =========================================
char **loadFrames(char *dir, int totFrames) {

    // Alokasi array pointer untuk semua frame
    char **frames = malloc(sizeof(char*) * totFrames);

    // Loop untuk membaca setiap frame
    for (int i = 0; i < totFrames; i++) {

        // Load frame ke-i
        frames[i] = loadFrame(i, dir);

        // Progress loading
        printf("\rLoading frame %d/%d", i + 1, totFrames);
        fflush(stdout);
    }

    printf("\n");

    return frames;
}


// =========================================
// Fungsi untuk memainkan animasi ASCII
// =========================================
void play(char **frames, int totFrames) {

    clock_t startTime = clock();   // waktu mulai animasi
    int currentFrame = 0;

    printf("\033[2J");  // clear screen menggunakan ANSI escape

    // Loop sampai semua frame selesai
    while (currentFrame < totFrames) {

        // Hitung waktu yang sudah berlalu (ms)
        double elapsedMs = (double)(clock() - startTime) * 1000.0 / CLOCKS_PER_SEC;

        // Hitung frame yang seharusnya ditampilkan
        int targetFrame = (int)(elapsedMs / FRAME_TIME);

        if (targetFrame > currentFrame && targetFrame < totFrames) {

            currentFrame = targetFrame;

            // 1. Pindahkan kursor ke pojok kiri atas
            gotoxy(0, 0);

            // 2. Gambar frame ASCII
            printf("%s", frames[currentFrame]);

            // 3. Hitung waktu berjalan
            int currentSeconds = currentFrame / FPS;
            int totalSeconds = totFrames / FPS;

            // 4. Tampilkan durasi playback
            // Format: [ 01:20 / 03:39 ]
            printf("\n  [ %02d:%02d / %02d:%02d ]  ", 
                    currentSeconds / 60, currentSeconds % 60, 
                    totalSeconds / 60, totalSeconds % 60);

            fflush(stdout);
        }

        // Sleep kecil agar CPU tidak 100%
        Sleep(1);
    }
}
