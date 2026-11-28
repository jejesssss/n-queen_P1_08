#include "nqueens.h"
#include <string>
#include <vector>

std::vector<std::vector<int>> solveHoles(int n, const std::vector<std::string>& grid) {
    const int MAKS_N = 12;                  
    std::vector<std::vector<int>> hasil;

    const unsigned semua = (1u << n) - 1; 

    unsigned bolong[MAKS_N];
    for (int r = 0; r < n; r++) {
        bolong[r] = 0;
        for (int c = 0; c < n; c++)
            if (grid[r][c] == 'H') bolong[r] |= (1u << c);
    }

    unsigned kolomPakai[MAKS_N + 1]; 
    unsigned diagKiri[MAKS_N + 1];   
    unsigned diagKanan[MAKS_N + 1];
    unsigned sisa[MAKS_N + 1];      
    int kolom[MAKS_N];     

    int baris = 0;
    kolomPakai[0] = 0;
    diagKiri[0] = 0;
    diagKanan[0] = 0;
    sisa[0] = semua & ~bolong[0];

    while (baris >= 0) {
        if (sisa[baris] == 0) {
            baris--;
            continue;
        }

        unsigned bit = sisa[baris] & (~sisa[baris] + 1);
        sisa[baris] ^= bit;
        kolom[baris] = __builtin_ctz(bit);  

        if (baris == n - 1) {
            hasil.push_back(std::vector<int>(kolom, kolom + n));
            continue;
        }

        kolomPakai[baris + 1] = kolomPakai[baris] | bit;
        diagKiri[baris + 1] = ((diagKiri[baris] | bit) << 1) & semua;  
        diagKanan[baris + 1] = (diagKanan[baris] | bit) >> 1;           
        baris++;
        sisa[baris] = semua & ~(kolomPakai[baris] | diagKiri[baris] | diagKanan[baris] | bolong[baris]);
    }

    return hasil; 
}