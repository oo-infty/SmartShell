#include "stdafx.h"
#include <iostream>
#include <string>
#include "Commands.h"
#include "Processer.h"
#include "make.hpp"
#include "Extension.h"

using namespace std;

int main(){
    CommandsTree tree(
        makeTask("exit", [](ArgumentsType args) {
            cout << "Logout" << endl;
            exit(0);
            return done();
        }),
        makeTask("hello", [](ArgumentsType args) {
            cout << "Hello World!!!" << endl;
            return done();
        })
    );

    tree.insert("load", [&](ArgumentsType args) {
        if (args[0] == "message") {
            ArgumentsType rawargs;
            copy(args.begin() + 2, args.end(), back_inserter(rawargs));
            tree.load(rawargs, 0, makeExtension<MessageExtension>(ref(cout), args[1]));
        }
        return done();
    });
    Processer processer;
    
    while (1) {
        cout << "SmartShell >>> ";
        tree.exec(processer.split(processer.read(cin), " "), 0);
    }
}