#include <iostream>
#include <sequence.h>
#include <listsequence.h>
#include <listsequence.cpp>
#include <fstream>
#include <extrafunctions.h>
#include <string.h>
#include <ntree.h>
#include <ntree.cpp>
#include "game.h"
#include "game.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    //testGame();


 /*   Game g(3);
    g.Init();
    g.MakeTree();
    //cout << g;
    g.CountChances();
    g.SaveChancesInFile();
    return 0;
*/
/*
    Game g(3);
    g.Init();
    g.MakeTree();
    g.SaveStepInFile("field.txt");
    g.CountChances();
    g.SaveChancesInFile();
    return 0;
*/
    if (argc < 3) return 0;
    int n = atoi(argv[1]);
    string action = argv[2];
    Game game(n);
    game.Init();
    game.MakeTree();
    if (action == "init_chances") {
        game.CountChances();
        game.SaveChancesInFile();
    }
    if (action == "make_step") {
        game.SaveStepInFile("field.txt");
        game.CountChances();
        game.SaveChancesInFile();
    }
    return 0;

}
