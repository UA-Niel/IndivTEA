//Implementation file for Automata

#include "../headers/Automata.h"
#include <string>
#include <vector>

//Methods
void Automata::addState(State* state) {
    this->states.push_back(state);
}
State* Automata::retrieveState(const int i) {
    return this->states[i];
}
State* Automata::retrieveState(std::string& name) {
    /*for (auto& i : this->states) {
        if (i.getName() == name) return i;
    }*/
    for (int i = 0; i < this->states.size(); i++) {
        if (this->states[i]->getName() == name) return this->states[i];
    }
}
std::vector<State*> Automata::getAllStates() {
    return this->states;
}
const int Automata::getAmountOfStates() {
    return this->states.size();
}
void Automata::setType(const AutomataType& type) {
    this->type = type;
}
const Automata::AutomataType& Automata::getType() const {
    return this->type;
}

void Automata::addAlphabet(const std::string& symbol) {
    this->alphabet.push_back(symbol);
}
const std::vector<std::string> Automata::getAlphabet() const {
    return this->alphabet;
}
