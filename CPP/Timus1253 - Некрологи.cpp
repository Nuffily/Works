/*
    Problem - https://acm.timus.ru/problem.aspx?space=1&num=1253
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#define MAX_SYMBOLS 1000000

using namespace std;

string link[10];
int sizes[10];

string build(int blank) {

    string necrolog = "";
    stack<char> st;
    bool thisIsLink = false;
    int number;
    int amount = 0;

    for (int i = sizes[blank] - 1; i >= 0; i--) {
        st.push(link[blank][i]);
        amount++;
    }

    while (!(st.empty())) {

        if (amount > MAX_SYMBOLS) return "#";

        else if (st.top() == '*') {
            st.pop();
            thisIsLink = true;
            continue;
        }

        else if (thisIsLink) {
            number = st.top() - '0';
            st.pop();
            for (int i = sizes[number] - 1; i >= 0; i--) {
                st.push((link[number])[i]);
                amount++;
            }
            thisIsLink = false;
        }

        else {
            necrolog += st.top();
            st.pop();
        }
    }

    return necrolog;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i < n + 1; i++) { 
        getline(cin, link[i], '#');

        link[i].erase(0, 1);

        sizes[i] = link[i].length();
    }

    cout << build(1);

    return 0;
}
