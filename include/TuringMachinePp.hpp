#ifndef TURINGMACHINEPP_HPP
#define TURINGMACHINEPP_HPP
#include <map>
#include <string>
#include <vector>

using namespace std;

class TuringMachinePP {
public:
    using State = string;
    using Symbol = char;
    using Position = vector<int>;
    using Transition = tuple<State, Symbol, vector<int>>;

private:
    map<pair<State, Symbol>, Transition> deltas;
    std::map<Position, Symbol> tape;
    Position head;
    State state;
    int dimensions;
    Symbol blankSymbol = '0';
public:
    TuringMachinePP(int dims, State startState);
    void addTransition(State currState, Symbol readSym, State newState, Symbol writeSym, vector<int> movement);
    void step();
    void printTape();
};



#endif //TURINGMACHINEPP_HPP