#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include <iostream>
#include <sequence.h>
#include <arraysequence.h>
#include <arraysequence.cpp>
#include <fstream>
#include <string.h>
using namespace std;


struct Point {
    int x;
    int y;
};

class Field {
    int _dimension;
    Sequence<char> *_field;
public:
    Field(int dimension);
    Field(const Field& field);
    Field(string name_of_input_file, int dimension);

    char Get(Point p);
    char operator[](Point p);
    void ReadFieldFromFile(string name_of_input_file);
    void WriteFieldInFile(string name_of_output_file);
    char CheckFinishState();
    char CheckFinishStateBigField();
    void ChangeField(Point p, char value);
    bool operator==(Field field);

    friend class GameState;
    friend class Game;
    friend std::ostream& operator << (std::ostream& out, Field& f) {
        out << endl << "dim=" << f._dimension << " len=" << f._field->GetLength() << endl;
        for (int i = 0; i < f._dimension; ++i) {
            for (int j = 0; j < f._dimension; ++j)
                out << f._field->Get(j + i * f._dimension) << " ";
            out << endl;
        }
        out << endl;
        return out;
    }
};

class GameState {
    Field *_field;
    Point _lastStep;
    char _state;  // X/O/0 - system lose/win/game havent got finished
public:
    GameState();
    GameState(const GameState &gameState);
    GameState(int dimension, Point lastStep);
    GameState(Field *field, Point lastStep, char state);

    char Get(Point p);
    Field *GetField();
    char operator[](Point p);

    void ReadFieldFromFile(string name_of_input_file);
    void WriteFieldInFile(string name_of_output_file);

    void SetState();
    char GetState();

    char CheckFinishState();
    bool CheckFillField();
    void ChangeField(Point p, char value);

    GameState& operator=(GameState &gameState);

    bool operator==(GameState gameState);

    friend class Game;
    friend class Field;
    friend std::ostream& operator << (std::ostream& out, GameState& gs) {
        out << gs._field;
        return out;
    }

};
#endif // GAMESTATE_H
