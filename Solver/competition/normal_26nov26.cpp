#include <utility>
#include <vector>

#include "nqueens.h"

namespace {

void backtrackNormal(int row, int n, std::vector<int> &board,
                     std::vector<bool> &usedCol, std::vector<bool> &usedDiag1,
                     std::vector<bool> &usedDiag2,
                     std::vector<std::vector<int>> &solutions) {
  if (row == n) {
    solutions.push_back(board);
    return;
  }

  for (int col = 0; col < n; ++col) {
    int d1 = row - col + (n - 1);
    int d2 = row + col;

    if (usedCol[col] || usedDiag1[d1] || usedDiag2[d2]) {
      continue;
    }

    board[row] = col;
    usedCol[col] = true;
    usedDiag1[d1] = true;
    usedDiag2[d2] = true;

    backtrackNormal(row + 1, n, board, usedCol, usedDiag1, usedDiag2,
                    solutions);

    usedCol[col] = false;
    usedDiag1[d1] = false;
    usedDiag2[d2] = false;
  }
}

} // namespace

std::vector<std::vector<int>> solveNQueens(int n) {
  std::vector<std::vector<int>> solutions;
  if (n <= 0) {
    return solutions;
  }

  std::vector<int> board(n, -1);
  std::vector<bool> usedCol(n, false);
  std::vector<bool> usedDiag1(2 * n - 1, false);
  std::vector<bool> usedDiag2(2 * n - 1, false);

  backtrackNormal(0, n, board, usedCol, usedDiag1, usedDiag2, solutions);
  return solutions;
}