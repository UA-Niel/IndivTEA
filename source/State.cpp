//Implementation file for State

#include <string>
#include <vector>
#include "../headers/State.h"

//Methods
void State::setStartState(const bool start) {
    this->start_state = start;
}
void State::setAcceptState(const bool accept) {
    this->accept_state = accept;
}
void State::setName(const std::string& name) {
    this->name = name;
}
void State::setTransition(Transition* transition) {
    this->myTransition.push_back(transition);
}

bool State::isStarting() {
    return this->start_state;
}
bool State::isAccepting() {
    return this->accept_state;
}
const std::string& State::getName() const {
    return this->name;
}
Transition* State::getTransition(const std::string& input) {
    for (int i = 0; i < this->myTransition.size(); i++) {
        if (this->myTransition[i]->input == input) return this->myTransition[i];
    }
}
Transition* State::getTransition(const std::string& input, const int i) {
    int counter = 0;

    for (int j = 0; j < this->myTransition.size(); j++) {
        if (this->myTransition[j]->input == input) {
            if (i == 0) return this->myTransition[j];
            counter++;
        }
        if (counter == i) return this->myTransition[j];
    }
    
}
    
bool State::hasTransition(const std::string& input) {
    for (auto t : this->myTransition) {
        if (t->input == input) return true;
    }
    
    return false;
}

const int State::amountOfTransitions() {
    return this->myTransition.size();
}
const int State::amountOfTransitions(const std::string& input) {
    int counter = 0;
    for (auto t : this->myTransition) {
        if (t->input == input) counter++;
    }

    return counter;
}
