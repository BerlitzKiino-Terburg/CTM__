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
    using Position = map<int, int>; //dimensions, position
    using Movement = map<int, int>;
    using Transition = tuple<State, Symbol, Movement>;

private:
    map<pair<State, Symbol>, Transition> deltas;
    map<Position, Symbol> tape;
    Position head;
    State state;
    int dimensions;
    Symbol blankSymbol = '_';

public:
    TuringMachinePp(const int dims, State startState) : state(std::move(startState)), dimensions(dims)
    {
        tape[head] = blankSymbol;
    }

    void addTransition(const State& currState, Symbol readSym, const State& newState, Symbol writeSym, const Movement& movement) {
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
        if (writeSym == blankSymbol) {
            tape.erase(head);
        } else {
            tape[head] = writeSym;
        }

        state = newState;

        for (int i = 0; i < dimensions; i++) {
            if (const int newVal = head[i] + movement[i]; newVal == 0) {
                head.erase(i);
            } else {
                head[i] = newVal;
            }
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

    static void printPosition(const Position& pos) {
        cout << "{ ";
        for (const auto& [dim, val] : pos) {
            cout << dim << ":" << val << " ";
        }
        cout << "}";
    }

    void printTape() {
        cout << "State: " << state << ", Head Position: ";
        printPosition(head);
        cout << ", Symbol under head: '" << tape[head] << "'\n";

        cout << "Tape contents:\n";
        for (const auto& [pos, sym] : tape) {
            printPosition(pos);
            cout << " -> '" << sym << "'";
            if (pos == head) cout << " <- head";
            cout << "\n";
        }
        cout << endl;
    }
};

int main()
{
    TuringMachinePp tm(10, "q0");

    tm.addTransition("q0", '_', "q1", '_', {{1, 1}, {9, -1}}); //Movement is Dimension : movement
    tm.addTransition("q1", '_', "q2", 'a', {{1, -1}});

    tm.run();

    return 0;
}