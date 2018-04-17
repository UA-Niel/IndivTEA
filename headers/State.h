//Header-file for state

#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

class State;

//Transition
struct Transition {
    std::string input; //Input symbol
    State* nextState = nullptr;
};


//State-class
class State {
    public:
    //Accessors and mutators
    void setStartState(const bool start);
    void setAcceptState(const bool accept);
    void setName(const std::string& name);
    void setTransition(Transition* transition);

    bool isStarting();
    bool isAccepting();
    const std::string& getName() const;
    Transition* getTransition(const std::string& input);
    Transition* getTransition(const std::string& input, const int i);
    bool hasTransition(const std::string& input);
    const int amountOfTransitions();
    const int amountOfTransitions(const std::string& input);

    private:
    //Properties
    bool accept_state = false;
    bool start_state = false;
    std::string name = "";
    std::vector<Transition*> myTransition;
};

#endif //STATE_H
