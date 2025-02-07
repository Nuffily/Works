/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1992

  Все данные о клонах хранятся в неизменяемых узлах - при любом действии с ботом, если нужно поменять узел - вместо этого он копируется
  Таким образом копировать всю историю клона не нужно, клоны используют узлы своих предков.
  Каждое действие с клоном создает ровно один новый узел, так что суммарное количество узлов - не более 500000
*/
  
#pragma comment(linker, "/STACK:4007772")
#include <iostream>
#include <string>

#define MAX_CLONES 500000

using namespace std;

struct cloneInfo {
    int programm;
    cloneInfo* back;
    cloneInfo* reverse;
};

cloneInfo* create(int p = -1, cloneInfo* b = 0, cloneInfo* r = 0) {

    cloneInfo* node = new cloneInfo;

    node->programm = p;
    node->back = b;
    node->reverse = r;

    return node;
};

void learn(int prog, cloneInfo*& clone) {
    cloneInfo* updated = create(prog, clone, nullptr);
    clone = updated;
}

void rollback(cloneInfo*& clone) {
    cloneInfo* updated = create(clone->back->programm, clone->back->back, clone);
    clone = updated;
}

void relearn(cloneInfo*& clone) {
    cloneInfo* updated = create(clone->reverse->programm, clone, clone->reverse->reverse);
    clone = updated;
}

cloneInfo* clone(cloneInfo* clone) {
    cloneInfo* reflection = create(clone->programm, clone->back, clone->reverse);
    return reflection;
}

void check(cloneInfo* clone) {
    cout << clone->programm << endl;
}

int main() {

    int n, m, nextClone = 2;
    cin >> n >> m;

    cloneInfo* army[MAX_CLONES];

    army[1] = create();
    string task;
    int index, WhatToLearn;

    for (int i = 0; i < n; i++) {

        cin >> task;

        if (task == "learn") {

            cin >> index >> WhatToLearn;
            learn(WhatToLearn, army[index]);

        } else if (task == "rollback") {

            cin >> index;
            rollback(army[index]);

        } else if (task == "relearn") {

            cin >> index;
            relearn(army[index]);

        } else if (task == "clone") {

            cin >> index;
            army[nextClone] = clone(army[index]);
            nextClone++;

        } else if (task == "check") {

            cin >> index;
            if ((army[index])->programm == -1) cout << "basic" << endl;
            else cout << (army[index])->programm << endl;
        };
    }

    return 0;
}

