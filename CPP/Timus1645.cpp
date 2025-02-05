/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1645

  Как считаем возможные места каждого лыжника:
    Если раньше него пришел лыжника, который стартовал позже, значит, он определенно прошел дистанцию за большее время,
    а значит, точно находится сзади него в итоговой таблице
    И наоборот, если позже него пришел лыжник, который стартовал позже, он точно прошел дистанцию быстрее,
    соответственно, его место выше
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int* finished = new int[n + 1];

    for (int i = 1; i <= n; i++)
        cin >> finished[i];

    int maxPlace, minPlace, currentFinished = 0;

    for (int i = 1; i <= n; i++) {

        maxPlace = 1;
        minPlace = n;

        for (int j = 1; j <= n; j++) {

            if (finished[j] > i) maxPlace++;

            else if (finished[j] == i) {
                currentFinished = j;
                break;
            }
        }

        for (int j = currentFinished + 1; j <= n; j++)
            if (finished[j] < i) minPlace--;

        cout << maxPlace << " " << minPlace << endl;
        
    }

}
