#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H

#pragma once

#include <iostream>
#include <fstream>
#include "sequence.h"
#include <chrono>
#include <listsequence.h>
#include <listsequence.cpp>
#include <fstream>
#include <extrafunctions.h>
#include <string.h>
#include <ntree.h>
#include <ntree.cpp>
#include "game.h"
#include <time.h>
#include "game.cpp"

void makeData(int zeros) {
    srand(time(NULL));
    string str = "";
    for (int i = 0; i < zeros; ++i)
        str += "0 ";
    for (int i = 0; i < 100 - zeros; ++i) {
        if (rand() % 2 == 0) str += "X ";
        else str += "O ";
    }
    std::ofstream outField;
    outField.open("field.txt");
    outField << str;
    outField.close();
}

void testGame() {
    std::ofstream outInit;
    std::ofstream outMakeTree;
    std::ofstream outStep;
    std::ofstream outChances;
    outInit.open("test_init.txt");
    outMakeTree.open("test_tree.txt");
    outStep.open("test_step.txt");
    outChances.open("test_chances.txt");

    for (int i = 0; i < 100; ++i) {
        cout << i << " ";
        makeData(i + 1);

        Game g(10);
        auto timeStamp_1 = std::chrono::high_resolution_clock::now();
        g.Init();
        auto timeStamp_2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStamp_2 - timeStamp_1).count();
        outInit << duration << endl;

        timeStamp_1 = std::chrono::high_resolution_clock::now();
        g.MakeTree();
        timeStamp_2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStamp_2 - timeStamp_1).count();
        outMakeTree << duration << endl;

        timeStamp_1 = std::chrono::high_resolution_clock::now();
        g.SaveStepInFile("field.txt");
        timeStamp_2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStamp_2 - timeStamp_1).count();
        outStep << duration << endl;

        timeStamp_1 = std::chrono::high_resolution_clock::now();
        g.CountChances();
        g.SaveChancesInFile();
        timeStamp_2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStamp_2 - timeStamp_1).count();
        outChances << duration << endl;
    }



    outInit.close();
    outMakeTree.close();
    outStep.close();
    outChances.close();
}

#endif // EXTRA_FUNCTIONS_H
