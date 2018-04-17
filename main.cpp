#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "headers/Automata.h"
#include "headers/State.h"
#include "libs/JSON/json.hpp"
#include "libs/TestLibrary/tester.h"
#include "test.h"

using json = nlohmann::json;

//Function to make automata from JSON-info
//:param json& j: A nlohmann::json object containing the parser
//:return automata: Automata created based on the JSON-info
Automata* FromJSONToAutomata(const json& j) {
    Automata* am = new Automata;

    //Setting automatatype
    std::string j_type = j.at("type");
    if (j_type == "DFA") am->setType(Automata::AutomataType::DFA);
    if (j_type == "NFA") am->setType(Automata::AutomataType::NFA);
    if (j_type == "eNFA") am->setType(Automata::AutomataType::E_NFA);

    //Setting alphabet
    auto j_alphabet = j.at("alphabet");
    for (auto symbol : j_alphabet) {
        am->addAlphabet(symbol);
    }

    //Setting states in automata
    auto j_states = j.at("states");
    for (auto& state : j_states) {
        //Defining state
        State* s = new State;
        
        //Setting state-name (string)
        s->setName(state.at("name"));
        //Set if accepting state (bool)
        s->setAcceptState(state.at("accepting"));
        //Set if starting state (bool)
        s->setStartState(state.at("starting"));

        //Adding state to automate
        am->addState(s);
    }

    //Setting transitions in the automata
    auto j_transitions = j.at("transitions");
    for (auto& transition : j_transitions) {
        //Define transition
        Transition* t = new Transition;
        
        //Set transition input-symbol
        t->input = transition.at("input");
        //Set To-State of transition
        std::string j_to = transition.at("to");
        t->nextState = am->retrieveState(j_to);
        //Assign this transition to state it's coming from
        std::string j_from = transition.at("from");
        am->retrieveState(j_from)->setTransition(t);
    }

    //Returning the automata
    return am;
}

//Function to add the powerset of NFA into DFA
//:param NFA: The NFA
//:param DFA: The DFA
void getSubsets(Automata& NFA, Automata& DFA) {
    int n = NFA.getAmountOfStates();
    int nSub = 1 << n;
    
    for(int i = 0; i < nSub; i++){
        std::cout << "{";
        State* newState = new State;
        std::string name = "{";
        for(int k = 0; k < n; k++){
            if ((1 << k) & i) {
                    State* S = NFA.retrieveState(k); 
                    
                    std::cout << S->getName() << ",";
                    name += S->getName() + ",";
                    //Fd = {S : S e Qd and S n Fn != 0}
                    if (S->isAccepting()) newState->setAcceptState(true);
                    
                    //Set transitions
                    //For every symbol in the alphabet
          /*          for (auto a : NFA.getAlphabet()) {
                        int n = S.amountOfTransitions(a);
                        
                        if (n > 0) {
                            for (int i = 0; i < n; i++) {
                                newState.setTransition(S.getTransition(a, i));
        //                        std::cout << S.getName() << " -> " << S.getTransition(a, i).nextState->getName() << " with symbol " << a << std::endl;
                            }
                        }
                    } */
            }
        }

        if (name != "{") name.pop_back();
        name += "}";
        
        newState->setName(name);
        DFA.addState(newState);
        std::cout << "}\n";
    }

    //Set start state
    for (auto& S : NFA.getAllStates()) {
        if (S->isStarting()) {
            std::string name = "{" + S->getName() + "}";
            DFA.retrieveState(name)->setStartState(true);
        }
    }
}

/*
//Function to set transitions of automata
//:param NFA: The NFA
//:param DFA: The DFA
void setTransitions(Automata& NFA, Automata& DFA) {
    //For every state in the DFA
    for (State S : NFA.getAllStates()) {
        std::string tPointerBuffer = "";
        //For every symbol in the alphabet
        for (auto a : DFA.getAlphabet()) {
            //If it's a single state (e.g not {q1,q2})
            if (S.hasTransition(a)) {
                auto t = S.getTransition(a);
                tPointerBuffer = t.nextState->getName();
                std::cout << tPointerBuffer << std::endl;
            }
        }
    }
}
*/

std::vector<std::string> splitStateByComma(State& S) {
    std::vector<std::string> v;

    std::string name = S.getName();
    std::stringstream ss(name);
    std::string segment;

    while (std::getline(ss, segment, ',')) {
        segment.erase(std::remove(segment.begin(), segment.end(), '{'), segment.end());
        segment.erase(std::remove(segment.begin(), segment.end(), '}'), segment.end());
        v.push_back(segment);
    }

    return v;
}

void setTransitions(Automata& NFA, Automata& DFA) {
    std::cout << "My states" << std::endl;
    for (auto& S : DFA.getAllStates()) {
        std::cout << S->getName() << std::endl;

        //If it's not single state e.g {Q0,Q1}
        if (contains(',', S->getName())) {
            for(auto StateName : splitStateByComma(*S)) {
                State* state = NFA.retrieveState(StateName);
                for (std::string symbol : NFA.getAlphabet()) {
                    int n = state->amountOfTransitions(symbol);
                    std::cout << "n " << n << std::endl; 
                    if (n == 1) {    
                        std::cout << symbol << ": " << state->getName() << " -> " << state->getTransition(symbol)->nextState->getName() << std::endl;

                        Transition* t = new Transition;
                        t->input = symbol;
                        t->nextState = state->getTransition(symbol)->nextState;
                        state->setTransition(t);

                    } else if (n > 1) {
                        static std::string nextState = "{";
                        for (int i = 0; i < n; i++) { 
                            //std::cout << symbol << ": " << state->getName() << " -> " << state->getTransition(symbol, i).nextState->getName() << std::endl;
                            
                            if (state->getTransition(symbol, i)->nextState != nullptr) { 
                            nextState += state->getTransition(symbol, i)->nextState->getName() + ",";
                            std::cout << "rofl" << std::endl;
                        
                        nextState.pop_back();
                        nextState += "}";
                        
                        std::cout << "next " << nextState << std::endl;

                        Transition* t = new Transition;
                        t->input = symbol;
                        t->nextState = DFA.retrieveState(nextState);

                        state->setTransition(t);
                        std::cout << "rolf ";
                        std::cout << state->amountOfTransitions() << std::endl;
                            }
                        }

                    } 
                }
            }
        }
    
        /*for (auto symbol : DFA.getAlphabet()) {
            int n = S.amountOfTransitions(symbol);
            
            std::cout << n << " with " << symbol << std::endl;

            if (n > 1) {
                std::string name = "{";
                for (int i = 0; i < n; i++) {
                    name += S.getTransition(symbol, i).nextState->getName() + ",";
                }
                name.pop_back();
                name += "}";

                std::cout << "TEST " << name << " with symbol " << symbol << std::endl;
            }
        }*/
    }
}

//Function to do subsetconstruction on an NFA to get the DFA
//:param Automata& NFA: Reference to the NFA-Automata to do SSC on
//:return Automata: The constructed DFA
Automata SubsetConstruction(Automata& NFA) {
    //Creating empty result DFA
    Automata DFA;

    //Setting alphabet
    for (auto a : NFA.getAlphabet()) {
        DFA.addAlphabet(a);
    }

    getSubsets(NFA, DFA);       //Qd = {S : S c Qn}
    setTransitions(NFA, DFA);   //&D(S, a) = U{p e S} &N(p, a)

    

    return DFA;
}

void output(Automata& FA) {
    std::string output = R"VOGON(digraph finite_state_machine { 
    rankdir=LR;
    size="8,5"
    )VOGON";

    //Setting all the nodes
    for (auto& S : FA.getAllStates()) {
        //Garbage state
        if (S->getName() == "{" ||
            S->getName() == "}" ||
            S->getName() == "{}") S->setName("{GC}");

        //Outputting all nodes
        std::string outputName = S->getName();
        outputName.erase(std::remove(outputName.begin(), outputName.end(), ','), outputName.end());
        if (S->isAccepting()) {
            output += "node [shape = doublecircle, label=\"" + S->getName() + "\", fontsize=16] " + outputName + ";\n";
        } else {
           output += "node [shape = circle, label=\"" + S->getName() +  "\", fontsize=18] " + outputName + ";\n";
        }
    }
   
    output += "\n";
    //Start arrow
    output += "node [shape = point ]; qi \n";

    //Set start state with arrow
    for (auto& S : FA.getAllStates()) {
        std::string outputName = S->getName();
        outputName.erase(std::remove(outputName.begin(), outputName.end(), ','), outputName.end());
        
        if (S->isStarting()) {
            output += "qi -> " + outputName + ";\n";
        }
    }

    //Display transitions
    for (auto& S : FA.getAllStates()) {
        for (auto a : FA.getAlphabet()) {
            if (S->hasTransition(a)) {
        std::cout << "lol" << std::endl;
                output += S->getName() + " -> " + S->getTransition(a)->nextState->getName() + " [ label = \"" + a + "\" ]";
            }
        }
    }

    //End
    output += "}\n";

    std::cout << "\n\n\n";
    std::cout << output << std::endl;
    
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string timestr(buffer);
  
    std::ofstream file;
    file.open(timestr + ".gv");
    file << output;
    file.close();

    system(("dot -Tpng \"" + timestr+".gv\"" + " -o \"" + timestr+".png\"").c_str());
}

int main(int argc, char* argv[]) {
    //Launch tests
    LaunchTest();

    //Check if argument given
    if (argc <= 1) {
        std::cerr << "Argument missing!" << std::endl;
        std::cout << "You should give an input file\nExample: ";
        std::cout << "./main myFile.json\nSee the test-folder for basic input-files" << std::endl;
        return -1;
    }

    //Parsing file
    std::ifstream ifs(argv[1]);
    json j = json::parse(ifs);
    
    //Make NFA-automata
    Automata* NFA = FromJSONToAutomata(j);

    //Construct DFA with SSC on NFA
    Automata DFA = SubsetConstruction(*NFA);
   
    //Output the DFA
    output(DFA);

    return 0;
}
