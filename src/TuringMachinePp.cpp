//
// Created by berlitzeop on 2/4/25.
//

#include "../include/TuringMachinePp.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class TuringMachinePp
{
public:
    using State = string;
    using Symbol = char;
    using Position = vector<int>;
    using Transition = tuple<State, Symbol, vector<int>>;

private:
    map<pair<State, Symbol>, Transition> deltas;
    map<Position, Symbol> tape;
    Position head;
    State state;
    int dimensions;
    Symbol blankSymbol = '0';

public:
    TuringMachinePp(int dims, State startState) : dimensions(dims), state(startState)
    {
        head = vector<int>(dims, 0);
        tape[head] = blankSymbol;
    }

    void addTransition(State currState, Symbol readSym, State newState, Symbol writeSym, vector<int> movement) {
        deltas[{currState, readSym}] = make_tuple(newState, writeSym, movement);
    }

    void step() {
        Symbol currentSymbol = tape.count(head) ? tape[head] : blankSymbol; // Read from tape or use blank
        auto key = make_pair(state, currentSymbol);

        if (deltas.find(key) == deltas.end()) {
            cout << "TMPP:: Halting, no transition for (" << state << ", '" << currentSymbol << "')\n";
            return;
        }

        auto [newState, writeSym, movement] = deltas[key];
        tape[head] = writeSym;
        state = newState;

        for (int i = 0; i < dimensions; i++) {
            head[i] += movement[i];
        }

        if (tape.find(head) == tape.end()) {
            tape[head] = blankSymbol;
        }
    }

    void printTape() {
        cout << "State: " << state << ", Head Position: [";
        for (int i : head) cout << i << " ";
        cout << "], Symbol under head: '" << tape[head] << "'\n";
    }
};

int main()
{
    TuringMachinePp tm(2, "q0");

    tm.addTransition("q0", '0', "q1", '1', {1, 0});
    tm.addTransition("q1", '0', "q0", '0', {-1, 0});

    for (int i = 0; i < 5; i++) {
        tm.printTape();
        tm.step();
    }

    return 0;
}
