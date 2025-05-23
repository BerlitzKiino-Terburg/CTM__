#include "../include/TuringMachinePp.hpp"

#include <iostream>
#include <map>
#include <string>
#include <utility>
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
    TuringMachinePp(const int dims, State startState) : dimensions(dims), state(std::move(startState))
    {
        head = vector(dims, 0);
        tape[head] = blankSymbol;
    }

    void addTransition(const State& currState, Symbol readSym, const State& newState, Symbol writeSym, const vector<int>& movement) {
        deltas[{currState, readSym}] = make_tuple(newState, writeSym, movement);
    }

    void step() {
        Symbol currentSymbol = tape.contains(head) ? tape[head] : blankSymbol;
        const auto key = make_pair(state, currentSymbol);

        if (!deltas.contains(key)) {
            cout << "TMPP:: Halting, no transition for (" << state << ", '" << currentSymbol << "')\n";
            state = "HALT";
            return;
        }

        auto [newState, writeSym, movement] = deltas[key];
        tape[head] = writeSym;
        state = newState;

        for (int i = 0; i < dimensions; i++) {
            head[i] += movement[i];
        }

        if (!tape.contains(head)) {
            tape[head] = blankSymbol;
        }
    }

    void run()
    {
        while(state != "HALT")
        {
            printTape();
            step();
        }
    }

    void printTape() {
        cout << "State: " << state << ", Head Position: [";
        for (const int i : head) cout << i << " ";
        cout << "], Symbol under head: '" << tape[head] << "'\n";
    }
};

int main()
{
    TuringMachinePp tm(2, "q0");

    tm.addTransition("q0", '0', "q1", '1', {1, 0});
    tm.addTransition("q1", '0', "q0", '0', {-1, 0});

    tm.run();

    return 0;
}