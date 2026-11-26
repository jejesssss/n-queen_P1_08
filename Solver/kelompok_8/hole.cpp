#include "nqueens.h"
#include <utility>
#include <vector>
#include <string>

struct HoleSearcher {
    int n;
    unsigned full;                       
    std::vector<unsigned> holeMask;     
    std::vector<int> cols;                 
    std::vector<std::vector<int>> found;    

    void place(int r, unsigned usedCols, unsigned diagL, unsigned diagR) {
        if (r == n) {
            found.push_back(cols);
            return;
        }
        unsigned avail = full & ~(usedCols | diagL | diagR) & ~holeMask[r];
        while (avail) {
            unsigned bit = avail & (~avail + 1); 
            avail ^= bit;                        
            cols[r] = __builtin_ctz(bit);         
            place(r + 1,
                  usedCols | bit,
                  ((diagL | bit) << 1) & full,    
                  (diagR | bit) >> 1);           
        }
    }
};

std::vector<std::vector<int>> solveHoles(int n, const std::vector<std::string>& grid) {
    HoleSearcher s;
    s.n = n;
    s.full = (1u << n) - 1;
    s.cols.assign(n, -1);
    s.holeMask.assign(n, 0);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c] == 'H') s.holeMask[r] |= (1u << c);

    s.place(0, 0, 0, 0);
    return std::move(s.found);  
}