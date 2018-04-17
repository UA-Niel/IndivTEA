//Header file for automata

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "State.h"
#include <string>
#include <vector>

class Automata {
    public:
    //Allowed types of automata
    enum AutomataType {
        DFA,
        NFA,
        E_NFA
    };
        
    //Accessors and mutators
    void addState(const State& state);
    void addState(State* state);
    State* retrieveState(const int i);
    State* retrieveState(std::string& name);
    std::vector<State*> getAllStates();
    const int getAmountOfStates();

    void setType(const AutomataType& type);
    const AutomataType& getType() const;

    void addAlphabet(const std::string& symbol);
    const std::vector<std::string> getAlphabet() const;

    private:
    //Properties
    AutomataType type;
    std::vector<State*> states;
    std::vector<std::string> alphabet;
};

#endif //AUTOMATA_H
