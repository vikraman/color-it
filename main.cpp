#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Game.h"

using namespace std;

int main()
{
    string t[] = {
        "YSPSYGPSYSRPPS",
        "SYBYYBYGPBBGYG",
        "PSYYBYYGPYRBPB",
        "SSGYGPYRGGYSGY",
        "PYYGPRBBGRBBBB",
        "RSYSYRRRPBSSPP",
        "BYRPGSSSPBPYRS",
        "PRRYGYSGPPSYSP",
        "YGSPRSYPGSPRBP",
        "RPPSYGRGPBGPYB",
        "GRYPBYSSSRGPPS",
        "YYPGBPSGBSBPSR",
        "RYYGRBSRPBSRBP",
        "SRGGYRBRSBBGBS"
    };
    string s[] = {
        "ABCD",
        "BCDA",
        "CDAB",
        "DCBA"
    };
    vector<string> v;
    string str;
    while (cin >> str)
        v.push_back(str);
    vector<string> board(v.begin(), v.end());
    Game * g = new Game(board);
    string sol = g->solve();
    cout << sol << endl;
    return 0;
}
