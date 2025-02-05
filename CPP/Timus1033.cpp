/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1033

  Представляем лабиринт ввиде boolean матрицы, где каждая ячейка false, если в ней стена, а иначе - пустота 
  Матрица имеет на две ячейки больше в ширину и длинну выполняющая роль рамки, все ячейки которой считаем стенами (для удобства)

  Запускаем поиск в ширину с обоих входом, и считаем стены. Если ячейка сверху пустая, то добавляем в очередь, иначе - сумма стен++

  Так как на входах нет стен (суммарно 4), заранее вычитаем их из результата
*/

#include <iostream>
#include <queue>

#define SQUARE_OF_WALL_CELL 9
#define COUNT_OF_ENTER_CELLS 4

using namespace std;

struct cell {
    int column;
    int row;

    cell() {}

    cell(int c, int r) {
        column = c;
        row = r;
    }

    cell& operator = (cell other) {
        column = other.column;
        row = other.row;

        return *this;
    }
};

bool** createTwoDimMatrix(int n) {
    bool** matrix = new bool* [n];

    for (int i = 0; i < n; i++)
        matrix[i] = new bool[n] { false };
    
    return matrix;
}

int wallComputingBFS(bool** matrix, bool** visited, cell start) {

    int result = 0;

    queue<cell> que;

    if (!visited[start.column][start.row]) {
        que.push(start);
        visited[start.column][start.row] = true;
    }

    cell current;

    while (!que.empty()) {

        current = que.front();
        que.pop();

        if (matrix[current.column + 1][current.row]) {
            if (!visited[current.column + 1][current.row]) {
                que.push(cell(current.column + 1, current.row));
                visited[current.column + 1][current.row] = true;
            }
        }
        else
            result++;

        if (matrix[current.column - 1][current.row]) {
            if (!visited[current.column - 1][current.row]) {
                que.push(cell(current.column - 1, current.row));
                visited[current.column - 1][current.row] = true;
            }
        }
        else
            result++;

        if (matrix[current.column][current.row + 1]) {
            if (!visited[current.column][current.row + 1]) {
                que.push(cell(current.column, current.row + 1));
                visited[current.column][current.row + 1] = true;
            }
        }
        else
            result++;

        if (matrix[current.column][current.row - 1]) {
            if (!visited[current.column][current.row - 1]) {
                que.push(cell(current.column, current.row - 1));
                visited[current.column][current.row - 1] = true;
            }
        }
        else
            result++;
    }

    return (result) * SQUARE_OF_WALL_CELL;
}

int main() {

    int n, answer = - COUNT_OF_ENTER_CELLS * SQUARE_OF_WALL_CELL;
    cin >> n;

    bool** matrix = createTwoDimMatrix(n + 2);
    bool** visited = createTwoDimMatrix(n + 2);

    char curCell;


    for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < n + 1; j++) {
            cin >> curCell;
            if (curCell == '.') 
                matrix[j][i] = true;
        }

    answer += wallComputingBFS(matrix, visited, cell(1, 1));
    answer += wallComputingBFS(matrix, visited, cell(n, n));

    cout << answer << endl;

    return 0;
}
