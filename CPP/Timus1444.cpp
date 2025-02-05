/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1444

  Для каждой тыквы, кроме первой, находим угол между прямыми (Текущая тыква, первая тыква) и (первая тыква, Ox)
  Сортируем тыквы по этому углу и выводим в том же порядке

  1* Если несколько тыкв имеют один угол, идем от ближней к дальней (относительно первой тыквы)
  
  2* Обход идет по часовой стрелки начиная с -180 градусов от первой тыквы
  Если угол между какими-либо двумя последующими тыквами в полученом ответе будет >=180, то обход скорее всего будет неверным

  В таком случае к углу всех тыкв с углом <0 добавляем 360 и заново сортируем, в таком случае обход начнется с 0 градусов относительно первой тыквы

  Поскольку к круге всего 360 градусов и по условию все тыквы не лежат на одной прямой, такой разрыв может быть только один, и с новой точкой старта, он не будет уччавствовать в обходе 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define EPSILON 0.0000001
#define PI 3.141592654

using namespace std;

template <typename T>
void heapify(T arr[], int N, int i) {

    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, N, largest);
    }
}

template <typename T>
void heapSort(T arr[], int N) {

    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    for (int i = N - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

class Point;

class Vector {

public:
    double x;
    double y;

    Vector(Point from, Point to);

    double len() {
        return sqrt(x * x + y * y);
    }
};

class Point {

public:
    double x;
    double y;

    Point(double xx, double yy) {
        x = xx;
        y = yy;
    }

    Point(const Point& s) {
        x = s.x;
        y = s.y;
    }

    Point() {}

    Point operator = (const Point& s) {
        x = s.x;
        y = s.y;
        return *this;
    }

    double findRange(Point to) {
        Vector coords = Vector(*this, to);
        return coords.len();
    }

    // Высчитывает угол между прямой, заданой двумя точками (a и b) и осью Ox
    double findAngle(Point a) {

        Point c = Point(this->x + 1, this->y);

        Vector bc = Vector(*this, c);
        Vector ba = Vector(*this, a);

        double bcLen = bc.len();
        double baLen = ba.len();

        if (!baLen || !bcLen) return 0;

        double answer = (180 / PI) * acos((bc.x * ba.x + bc.y * ba.y) / (bcLen * baLen));

        if (a.y < this->y)
            return answer * -1;
        else
            return answer;
    }

};

Vector::Vector(Point from, Point to) {
        x = to.x - from.x;
        y = to.y - from.y;
}

class Pumpkin {

public:

    int num;
    Point point;

    double angle;
    double range;

    Pumpkin() {}

    Pumpkin(int num, Point point) {
        this->num = num;
        this->point = point;
    }

    void locateOver(Pumpkin p) {
        angle = p.point.findAngle(point);
        range = p.point.findRange(point);
    }

    bool operator > (Pumpkin p) {

        if (this->angle - p.angle > EPSILON) {
            return true;
        }

        else if (this->angle - p.angle < -1 * EPSILON) {

            return false;
        }
        
        else {

            return (this->range - p.range > 0);
        }
    }

};

void printAnswer(Pumpkin arr[], int N) {

    for (int i = 0; i < N; ++i)
        cout << arr[i].num  << endl;

    cout << "\n";
}

int main() {

    int n, curX, curY;
    cin >> n;

    Pumpkin* pumpkin = new Pumpkin[n];

    for (int i = 0; i < n; i++) {
        cin >> curX >> curY;
        pumpkin[i] = Pumpkin(i + 1, Point(curX, curY));
    }

    pumpkin[0].angle = -181;

    for (int i = 1; i < n; i++) 
        pumpkin[i].locateOver(pumpkin[0]);
    
    heapSort(pumpkin, n);

    for (int i = 2; i < n; i++) 
        if (abs(pumpkin[i - 1].angle - pumpkin[i].angle) + EPSILON > 180) {

            for (int j = 1; j < n; j++)
                if (pumpkin[j].angle + EPSILON < 0) pumpkin[j].angle += 360;

            heapSort(pumpkin, n);
            break;
        }

    cout << n << endl;

    printAnswer(pumpkin, n);

	return 0;
}
