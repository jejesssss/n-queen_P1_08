#include <utility>
#include <vector>

#include "nqueens.h"

namespace {

void backtrackPreplaced(int row, int n, const std::vector<int> &fixedCol,
                        std::vector<int> &board, std::vector<bool> &usedCol,
                        std::vector<bool> &usedDiag1,
                        std::vector<bool> &usedDiag2,
                        std::vector<std::vector<int>> &solutions) {
  if (row == n) {
    solutions.push_back(board);
    return;
  }

  if (fixedCol[row] != -1) {
    backtrackPreplaced(row + 1, n, fixedCol, board, usedCol, usedDiag1,
                       usedDiag2, solutions);
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

    backtrackPreplaced(row + 1, n, fixedCol, board, usedCol, usedDiag1,
                       usedDiag2, solutions);

    usedCol[col] = false;
    usedDiag1[d1] = false;
    usedDiag2[d2] = false;
  }
}

} // namespace

std::vector<std::vector<int>>
solvePreplaced(int n, const std::vector<std::pair<int, int>> &preplaced) {
  std::vector<std::vector<int>> solutions;
  if (n <= 0) {
    return solutions;
  }

  std::vector<int> fixedCol(n, -1);
  std::vector<int> board(n, -1);
  std::vector<bool> usedCol(n, false);
  std::vector<bool> usedDiag1(2 * n - 1, false);
  std::vector<bool> usedDiag2(2 * n - 1, false);

  for (const std::pair<int, int> &pos : preplaced) {
    int r = pos.first;
    int c = pos.second;

    if (r < 0 || r >= n || c < 0 || c >= n) {
      return solutions;
    }
    if (fixedCol[r] != -1) {
      if (fixedCol[r] == c) {
        continue;
      }
      return solutions;
    }

    int d1 = r - c + (n - 1);
    int d2 = r + c;

    if (usedCol[c] || usedDiag1[d1] || usedDiag2[d2]) {
      return solutions;
    }

    fixedCol[r] = c;
    board[r] = c;
    usedCol[c] = true;
    usedDiag1[d1] = true;
    usedDiag2[d2] = true;
  }

  backtrackPreplaced(0, n, fixedCol, board, usedCol, usedDiag1, usedDiag2,
                     solutions);
  return solutions;
}