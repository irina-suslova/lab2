#pragma once
#include "game.h"

Game::Game(int dimension) {
    _dimension = dimension;
    _win_chances = new ArraySequence<int>;
    _lose_chances = new ArraySequence<int>;
    _nextStep = new GameState;
    _tree = new NTree<GameState>();
    _tree->GetRoot()->_data._field->_dimension = dimension;
}

void Game::LoadInitStateGameByFile(string name_of_file) {
    _tree->GetRoot()->_data.ReadFieldFromFile(name_of_file);
}

void Game::InitMode(string name_of_file) {
    ifstream in(name_of_file);
    if (in.is_open()) {
        in >> _mode;
        in.close();
    }
}

void Game::Init(string name_of_state_file = "field.txt", string name_of_mode_file = "mode.txt") {
    InitMode(name_of_mode_file);
    LoadInitStateGameByFile(name_of_state_file);
}

void Game::MakeTree(TreeItem<GameState> *root = nullptr, char mode = 'O') {
    bool checker = true;
    if (!root) {
        root = _tree->GetRoot();
    }

    TreeItem<GameState>* it = root;

    Sequence<int> *indexes = new ArraySequence<int>;
    indexes->Append(0);

    while(checker) {
        if (it->_chilgren->GetLength() == 0) {
            if (it == root)
                checker = MakeBranch(it, mode);
            else
                checker = MakeBranch(it, mode);
            if (!checker) {
                checker = true;
                it = it->_parent;
                mode = (mode == 'O') ? 'X' : 'O';
                indexes->DelByIndex(indexes->GetLength() - 1);
                if (it) indexes->GetLast() += 1;
                if (!it) break;
                continue;
            }
        }
        if (indexes->GetLast() >= it->_chilgren->GetLength()) {
            it = it->_parent;
            mode = (mode == 'O') ? 'X' : 'O';
            indexes->DelByIndex(indexes->GetLength() - 1);
            if (indexes->GetLength() != 0)
                indexes->GetLast() += 1;
            else
                checker = false;
            continue;
        }
        it = (*it->_chilgren)[indexes->GetLast()];
        mode = (mode == 'O') ? 'X' : 'O';
        indexes->Append(0);
    }
}

bool Game::MakeBranch(TreeItem<GameState> *it = nullptr, char mode = 'O') {
    bool checker = false;
    if (!it) {
        it = _tree->GetRoot();
    }
    if (it->_data.GetState() != '0') return false;
    for (int i = 0; i < _dimension; ++i) {
        for (int j = 0; j < _dimension; ++j) {
            if (it->_data.Get({j, i}) == '0') {
                checker = true;
                GameState* gS = new GameState(it->_data);
                gS->ChangeField({j, i}, mode);
                gS->SetState();
                _tree->Add(it, *gS);
            }
        }
    }
    return checker;
}

bool IsXWin(GameState gS) {
    return gS.GetState() == 'X';
}

bool IsOWin(GameState gS) {
    return gS.GetState() == 'O';
}

int Game::FindBestStep() {
    int best_i = 0;
    int best_chance = 0;

    for (int i = 0; i < _tree->GetRoot()->_chilgren->GetLength(); ++i) {
        int all_ends = _tree->CountAllLeaves(_tree->GetRoot()->_chilgren->Get(i));
        int o_win = _tree->GetLeavesByCondition(_tree->GetRoot()->_chilgren->Get(i), IsOWin)->GetLength();
        int chance = -1;
        if (all_ends != 0)
            chance = o_win * 100 / (all_ends);
        if (best_chance < chance) {
            best_i = i;
            best_chance = chance;
        }
    }
    _index_nextStep = best_i;
    return best_i;
}

GameState Game::GetBestStep() {
    _index_nextStep = FindBestStep();
    *_nextStep = _tree->GetRoot()->_chilgren->Get(_index_nextStep)->_data;
    return *_nextStep;
}

GameState Game::GetStep() {
    srand(time(NULL));
    _index_nextStep = rand() % _tree->GetRoot()->_chilgren->GetLength();
    *_nextStep = _tree->GetRoot()->_chilgren->Get(_index_nextStep)->_data;
    return *_nextStep;
}

void Game::CountChances() {
    while(_win_chances->GetLength() > 0) {
        _win_chances->DelByIndex(0);
        _lose_chances->DelByIndex(0);
    }
    for (int i = 0; i < _dimension * _dimension; ++i) {
        _win_chances->Append(0);
        _lose_chances->Append(0);
    }
    int x_win, o_win, all_ends;
    int n;
    if (_index_nextStep == -1)
        n = _tree->GetRoot()->_chilgren->GetLength();
    else {
        n = _tree->GetRoot()->_chilgren->Get(_index_nextStep)->_chilgren->GetLength();
    }

    for (int i = 0; i < n; ++i) {
        if (_index_nextStep == -1) {
            x_win = _tree->CountLeavesByCondition(_tree->GetRoot()->_chilgren->Get(i), IsOWin);
            o_win = _tree->CountLeavesByCondition(_tree->GetRoot()->_chilgren->Get(i), IsXWin);
            all_ends = _tree->CountAllLeaves(_tree->GetRoot()->_chilgren->Get(i));
        }
        else {
            x_win = _tree->CountLeavesByCondition(_tree->GetRoot()->_chilgren->Get(_index_nextStep)->_chilgren->Get(i), IsXWin);
            o_win = _tree->CountLeavesByCondition(_tree->GetRoot()->_chilgren->Get(_index_nextStep)->_chilgren->Get(i), IsOWin);
            all_ends = _tree->CountAllLeaves(_tree->GetRoot()->_chilgren->Get(_index_nextStep)->_chilgren->Get(i));
        }
        //cout << x_win << " " << o_win << " " << x_win + o_win << " " << x_win * 100 / (x_win + o_win) << endl;
        int win_chance = 0;
        int lose_chance = 0;
        if (all_ends != 0) {
            win_chance = x_win * 100 / (all_ends);
            lose_chance = o_win * 100 / (all_ends);
        }
        Point lastStep;
        if (_index_nextStep == -1) {
            lastStep = _tree->GetRoot()->_chilgren->Get(i)->_data._lastStep;
        }
        else {
           lastStep = _tree->GetRoot()->_chilgren->Get(_index_nextStep)->_chilgren->Get(i)->_data._lastStep;
        }
        //cout << lastStep.x << " " << lastStep.y << endl;
        (*_win_chances)[lastStep.x + lastStep.y * _dimension] = win_chance;
        (*_lose_chances)[lastStep.x + lastStep.y * _dimension] = lose_chance;
    }
}

void Game::SaveChancesInFile(string name_of_file = "chances.txt") {
    ofstream out(name_of_file);
    if (out.is_open()) {
        for (int i = 0; i < _win_chances->GetLength(); ++i) {
            out << (*_win_chances)[i] << " " << (*_lose_chances)[i] << endl;
        }
        out.close();
    }
}

void Game::SaveStepInFile(string name_of_file = "field.txt") {
    if (_mode == 1)
        GetBestStep().WriteFieldInFile(name_of_file);
    else if (_mode == 0)
        GetStep().WriteFieldInFile(name_of_file);
}
