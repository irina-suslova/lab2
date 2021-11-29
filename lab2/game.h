#ifndef GAME_H
#define GAME_H

#pragma once

#include "gamestate.h"
#include "ntree.h"
#include <time.h>

class Game {
    NTree<GameState> *_tree;
    int _dimension;
    Sequence<int> *_win_chances;
    Sequence<int> *_lose_chances;
    int _mode;
    int _index_nextStep = -1;
    GameState *_nextStep = nullptr;
public:
    Game(int dimension);

    void LoadInitStateGameByFile(string name_of_file);
    void InitMode(string name_of_file);
    void Init(string name_of_state_file, string name_of_mode_file);

    void MakeTree(TreeItem<GameState> *root, char mode);
    bool MakeBranch(TreeItem<GameState> *it, char mode);

    int FindBestStep();
    void CountChances();

    GameState GetBestStep();
    GameState GetStep();

    void SaveStepInFile(string name_of_file);
    void SaveChancesInFile(string name_of_file);

    friend std::ostream& operator << (std::ostream& out, Game& g) {
        out << *(g._tree->GetRoot()->_data.GetField());
        out << endl;
        for (int i = 0; i < g._tree->GetAllLeaves(g._tree->GetRoot())->GetLength(); ++i)
            out << *(g._tree->GetAllLeaves(g._tree->GetRoot())->Get(i)->_data.GetField());
        return out;
    }
};

#endif // GAME_H
