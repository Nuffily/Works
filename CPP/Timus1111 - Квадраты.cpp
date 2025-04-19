/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1111
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define EPSILON 0.0000001

using namespace std;

struct Point {
    double x;
    double y;

    Point() {}

    Point(double xx, double yy) {
        x = xx;
        y = yy;
    }

    // по теорема Пифагора
    double findRange(Point second) {
        return sqrt((second.x - x) * (second.x - x) + (second.y - y) * (second.y - y));
    }
};

template <typename T>
void Swap(T& r1, T& r2) {
    T swapChar = r1;
    r1 = r2; r2 = swapChar;
}

class Square {

    Point point[5];
    double diametr;

public:

    void pointsFill(double firstPointX, double firstPointY, double thirdPointX, double thirdPointY) {

        point[1] = Point(firstPointX, firstPointY);
        point[3] = Point(thirdPointX, thirdPointY);

        double x = (point[3].x - point[1].x) / 2;
        double y = (point[3].y - point[1].y) / 2;

        point[2].x = point[1].x + x + y;
        point[2].y = point[1].y - x + y;
        point[4].x = point[1].x + x - y;
        point[4].y = point[1].y + x + y;
    }

    pair<Point, Point> findTwoNearestPoints(Point p) {

        double current;

        pair<double, double> ranges = pair(INFINITY, INFINITY);
        pair<Point, Point> answer;

        for (int i = 1; i < 5; i++) {
            current = sqrt((p.x - point[i].x) * (p.x - point[i].x) + (p.y - point[i].y) * (p.y - point[i].y));

            if (ranges.first > current) {
                answer.first = point[i];
                ranges.first = current;
            }

            else if (ranges.second > current) {
                answer.second = point[i];
                ranges.second = current;
            }
        }

        return answer;
    }

    double findDiametr() {
        return sqrt((point[3].x - point[1].x) * (point[3].x - point[1].x) + (point[3].y - point[1].y) * (point[3].y - point[1].y));
    }

    bool isPointInside(Point p) {

        double rangeToFirst = p.findRange(point[1]);
        double rangeToThird = p.findRange(point[3]);
        double diametr = findDiametr();

        return (diametr * diametr + EPSILON > rangeToFirst * rangeToFirst + rangeToThird * rangeToThird);
    }

    double findHeight(Point p, Point first, Point second) {

        double mainSide = first.findRange(second);
        double firstSide = p.findRange(first);
        double secondSide = p.findRange(second);

        double halfPerimetr = (firstSide + secondSide + mainSide) / 2;

        if (!isHeightExist(mainSide, firstSide, secondSide))
            return -1;

        // По формуле Герона
        return (2 * sqrt(halfPerimetr * (halfPerimetr - firstSide) * 
            (halfPerimetr - secondSide) * (halfPerimetr - mainSide))) / mainSide;
    }

    bool isHeightExist(double mainSide, double firstSide, double secondSide) {
        return !(((firstSide * firstSide + mainSide * mainSide - secondSide * secondSide) / (2 * firstSide * mainSide) < 0)
            || ((secondSide * secondSide + mainSide * mainSide - firstSide * firstSide) / (2 * secondSide * mainSide) < 0));
    }

};

void printAnswer(double* array, int n) {

    double minimum;
    int index;

    for (int f = 0; f < n; f++) {

        minimum = INFINITY;

        for (int j = 0; j < n; j++) {

            if (array[j] < minimum - EPSILON) {
                minimum = array[j];
                index = j;
            }
        }

        cout << index + 1 << " ";

        array[index] = INFINITY;
    }

    cout << endl;
}

int main() {

    cout.precision(8);

    int n;
    cin >> n;

    double* ans = new double[n];
    Square* sqrs = new Square[n];

    double firstPointX, firstPointY, thirdPointX, thirdPointY;

    for (int i = 0; i < n; i++) {
        cin >> firstPointX >> firstPointY >> thirdPointX >> thirdPointY;

        sqrs[i].pointsFill(firstPointX, firstPointY, thirdPointX, thirdPointY);
    }

    Point p;
    cin >> p.x >> p.y;

    pair<Point, Point> nearestPoints;

    double heightLength;

    for (int i = 0; i < n; i++) {

        nearestPoints = sqrs[i].findTwoNearestPoints(p);

        if (!sqrs[i].findDiametr()) {
            ans[i] = p.findRange(nearestPoints.first);
            continue;
        }

        if (sqrs[i].isPointInside(p)) {
            ans[i] = 0;
            continue;
        }

        heightLength = sqrs[i].findHeight(p, nearestPoints.first, nearestPoints.second);

        if (heightLength < 0)
            ans[i] = p.findRange(nearestPoints.first);
        else
            ans[i] = heightLength;
    
    }

    printAnswer(ans, n);

    return 0;

}

