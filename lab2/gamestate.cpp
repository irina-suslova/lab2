#include "gamestate.h"

Field::Field(int dimension) {
    this->_dimension = dimension;
    _field = new ArraySequence<char>;
    for (int i = 0; i < dimension * dimension; ++i) {
        char ch = '0';
        _field->Append(ch);
    }
}

Field::Field(const Field &field) {
    _dimension = field._dimension;
    _field = new ArraySequence<char>;
    for (int i = 0; i < field._field->GetLength(); ++i)
        _field->Append((*field._field)[i]);
}

Field::Field(string name_of_input_file, int dimension) {
    this->_dimension = dimension;
    ifstream in(name_of_input_file);
    if (in.is_open()) {
        for (int i = 0; i < dimension * dimension; ++i) {
            in >> (*_field)[i];
        }
        in.close();
    }
}

char Field::Get(Point p) {
    return (*_field)[p.x + p.y * _dimension];
}

char Field::operator[](Point p) {
    return this->Get(p);
}

void Field::ReadFieldFromFile(string name_of_input_file) {
    ifstream in(name_of_input_file);
    while(_field->GetLength()) _field->DelByIndex(_field->GetLength() - 1);
    if (in.is_open()) {
        for (int i = 0; i < _dimension * _dimension; ++i) {
                char c;
                in >> c;
                _field->Append(c);
        }
        in.close();
    }
}

void Field::WriteFieldInFile(string name_of_output_file) {
    ofstream out(name_of_output_file);
    if (out.is_open()) {
        for (int i = 0; i < _dimension; ++i) {
            for (int j = 0; j < _dimension; ++j) {
                out << _field->Get(j + i * _dimension) << " ";
            }
            out << endl;
        }
        out.close();
    }
}

char Field::CheckFinishState() {
    return CheckFinishStateBigField();
/*
    int dimension = this->_dimension;
    bool checker;
    for (int i = 0; i < dimension; ++i) {   // horizontal
        checker = true;
        for (int j = 0; j < dimension - 1; ++j) {
            if ((*_field)[j + i * dimension] != (*_field)[j + 1 + i * dimension]) {
                checker = false;
                break;
            }
        }
        if (checker && (*_field)[i * dimension] != '0') return (*_field)[i * dimension];
    }
    for (int i = 0; i < dimension; ++i) {   // vertical
        checker = true;
        for (int j = 0; j < dimension - 1; ++j) {
            if ((*_field)[i + j * dimension] != (*_field)[i + (j + 1) * dimension]) {
                checker = false;
                break;
            }
        }
        if (checker && (*_field)[i] != '0') return (*_field)[i];
    }
    checker = true;
    for (int i = 0; i < dimension - 1; ++i) {
        if ((*_field)[i + i * dimension] != (*_field)[i + 1 + (i + 1) * _dimension]) {
            checker = false;
            break;
        }
    }
    if (checker && (*_field)[0] != '0') return (*_field)[0];
    checker = true;
    for (int i = 0; i < dimension - 1; ++i) {
        if ((*_field)[(dimension - i - 1) + i * _dimension] != (*_field)[(dimension - i - 2) + (i + 1) * dimension]) {
            checker = false;
            break;
        }
    }
    if (checker && (*_field)[dimension - 1] != '0') return (*_field)[dimension - 1];
    return '0';
*/

}

char Field::CheckFinishStateBigField() {
    int dimension;
    if (_dimension <= 3)
        dimension = _dimension;
    else
        dimension = min(this->_dimension - 1, 5);
    bool checker;
    for (int i = 0; i < _dimension; ++i) {   // horizontal
        for (int k = 0; k < _dimension - dimension + 1; ++k) {
            checker = true;
            for (int j = 0; j < _dimension - 1; ++j) {
                if ((*_field)[j + i * _dimension + k] != (*_field)[j + 1 + i * _dimension]) {
                    checker = false;
                    break;
                }
            }
            if (checker && (*_field)[i * _dimension + k] != '0') return (*_field)[i * _dimension];
        }
    }

    for (int i = 0; i < _dimension; ++i) {   // vertical
        for (int k = 0; k < _dimension - dimension + 1; ++k) {
            checker = true;
            for (int j = 0; j < _dimension - 1; ++j) {
                if ((*_field)[i + (j + k) * _dimension] != (*_field)[i + (j + 1 + k) * _dimension]) {
                    checker = false;
                    break;
                }
            }
            if (checker && (*_field)[i + k * _dimension] != '0') return (*_field)[i + k * _dimension];
        }
    }

    for (int y = 0; y < _dimension - dimension + 1; ++y) {
        for (int x = 0; x < _dimension - dimension + 1; ++x) {
            checker = true;
            for (int i = 0; i < dimension - 1; ++i) {
                if ((*_field)[(i + x) + (i + y) * dimension] != (*_field)[(i + 1 + x) + (i + 1 + y) * _dimension]) {
                    checker = false;
                    break;
                }
            }
            if (checker && (*_field)[x + y * dimension] != '0') return (*_field)[x + y * dimension];
        }
    }

    for (int y = 0; y < _dimension - dimension + 1; ++y) {
        for (int x = 0; x < _dimension - dimension + 1; ++x) {
            checker = true;
            for (int i = 0; i < dimension - 1; ++i) {
                if ((*_field)[(dimension - i - 1 + x) + (i + y) * _dimension] != (*_field)[(dimension - i - 2 + x) + (i + 1 + y) * dimension]) {
                    checker = false;
                    break;
                }
            }
            if (checker && (*_field)[dimension - 1 + y * _dimension] != '0') return (*_field)[dimension - 1 + y * _dimension];
        }
    }
    return '0';
}

void Field::ChangeField(Point p, char value) {
    (*_field)[p.x + p.y * _dimension] = value;
}

bool Field::operator==(Field field) {
    if (_dimension != field._dimension) return false;
    for (int i = 0; i < _dimension * _dimension; ++i)
        if ((*_field)[i] != (*field._field)[i]) return false;
    return true;
}


GameState::GameState() {
    _field = new Field(0);
    _lastStep = {-1, -1};
    _state = '0';
}

GameState::GameState(const GameState &gameState) {
    _lastStep = gameState._lastStep;
    _state = gameState._state;
    _field = new Field(*gameState._field);
}

GameState::GameState(int dimension, Point lastStep = {-1 , -1}) {
    _field = new Field(dimension);
    _lastStep = lastStep;
    _state = '0';
}

GameState::GameState(Field *field, Point lastStep, char state = '1') {
    _field = field;
    _lastStep = lastStep;
    if (state != '1') _state = state;
    else _state = (*_field).CheckFinishState();
}

char GameState::Get(Point p) {
    return _field->Get(p);
}

Field *GameState::GetField() {
    return _field;
}

char GameState::operator[](Point p) {
    return _field->Get(p);
}

void GameState::ReadFieldFromFile(string name_of_input_file) {
    _field->ReadFieldFromFile(name_of_input_file);
}

void GameState::WriteFieldInFile(string name_of_output_file) {
    _field->WriteFieldInFile(name_of_output_file);
}

void GameState::SetState() {
    _state = _field->CheckFinishState();
}

char GameState::GetState() {
    return _state;
}

char GameState::CheckFinishState() {
    _state = _field->CheckFinishState();
    return _state;
}

bool GameState::CheckFillField() {
    for (int i = 0; i < _field->_dimension; ++i) {
        for (int j = 0; j < _field->_dimension; ++j) {
            if (_field->Get({i, j}) == '0')
                return false;
        }
    }
    return true;
}

void GameState::ChangeField(Point p, char value) {
    _field->ChangeField(p, value);
    _lastStep = p;
}

GameState &GameState::operator=(GameState &gameState) {
    if (this == &gameState)
           return *this;
    _lastStep = gameState._lastStep;
    _state = gameState._state;
    *_field = *gameState._field;
    return *this;
}

bool GameState::operator==(GameState gameState) {
    return ((*_field) == (*gameState._field)) & (_lastStep.x == gameState._lastStep.x) & (_lastStep.y == gameState._lastStep.y);
}
