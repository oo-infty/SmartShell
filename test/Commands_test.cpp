#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Commands.h"
#include "Processer.h"
#include "make.hpp"

using namespace std;

void output(ArgumentsType& vec) {
    copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, " "));
}

int main() {
    Processer proc;
    CommandsTree tree(
        makeCommandsTree("tree1",
            makeTask("cmd1", [&](ArgumentsType args) {
                cout << "Tree1 - Command1 ";
                output(args);
                cout << endl;
                return done();
            }),
            makeCommandsTree("tree2",
                makeTask("cmd1", [&](ArgumentsType args) {
                    cout << "Tree1 - Tree2 - Command1 ";
                    output(args);
                    cout << endl;
                    return done();
                }),
                makeTask("cmd2", [&](ArgumentsType args) {
                    cout << "Tree1 - Tree2 - Command2 ";
                    output(args);
                    cout << endl;
                    return done();
                })
            )
        ),
        makeCommandsTree("tree2",
            makeTask("cmd1", [&](ArgumentsType args) {
                cout << "Tree2 - Command1 ";
                output(args);
                cout << endl;
                return done();
            }),
            makeTask("cmd2", [&](ArgumentsType args) {
                cout << "Tree2 - Command2 ";
                output(args);
                cout << endl;
                return done();
            })
        )
    );
    ArgumentsType args1 = { "tree1","tree2","cmd2","Hello World 3nd" };
    tree.exec(args1, 0);

    return 0;
}

