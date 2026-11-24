// Memakai metode backtracking + bitmasking

#include "nqueens.h"
#include <string>
#include <vector>

namespace {

void backtrack(int row, int n, unsigned int allCols, unsigned int cols,
               unsigned int diag1, unsigned int diag2, std::vector<int> &board,
               std::vector<std::vector<int>> &solutions) {
  // Base case: seluruh N queen telah ditempatkan dengan aman
  if (row == n) {
    solutions.push_back(board);
    NQ_SNAPSHOT(nq::queensOf(board),
                "solution " + std::to_string(solutions.size()));
    return;
  }

  // Cari semua bit kolom yang aman di baris saat ini
  unsigned int available = allCols & ~(cols | diag1 | diag2);

  while (available != 0) {
    // Ambil bit paling kanan yang bernilai 1 (kolom aman pertama)
    unsigned int bit = available & (~available + 1);
    // Hapus bit tersebut dari kandidat
    available &= (available - 1);

    // Konversi posisi bit menjadi indeks kolom 0-based
    int col = __builtin_ctz(bit);
    board[row] = col;

    // Lanjut ke baris berikutnya sambil menggeser mask diagonal
    backtrack(row + 1, n, allCols, cols | bit, (diag1 | bit) << 1,
              (diag2 | bit) >> 1, board, solutions);
  }
}

} // namespace

std::vector<std::vector<int>> solveNQueens(int n) {
  std::vector<std::vector<int>> solutions;
  if (n <= 0) {
    return solutions;
  }

  std::vector<int> board(n, 0);
  unsigned int allCols = (1u << n) - 1u;

  backtrack(0, n, allCols, 0u, 0u, 0u, board, solutions);
  return solutions;
}