#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int findState(char state, char tuples[][5], int stateNum);

void useTuple(char tuples[][5], int state, string &tape, bool &direc, int &tapePos, char &cState);

void tapeEdit(string &tape, char instruct[], bool &direc, int &tapePos, char &cState);

int main(){
    //current state
    char state;

    //maximum number of iterations
    int maxIters;

    //the tape 
    string tape;

    //check terminate
    int terminate = 0;

    //left(0) or right(1)
    bool direc = 1;

    //tape position
    int tapePos = 0;

    //setting up tuples
    string userIn;
    char tuples[100][5];
    int stateNum = 0;
    bool inputs = 1;

    cout << "Enter 5-Tuples. Enter a '.' by itself to end." << endl;
    while(inputs == 1){
        getline(cin, userIn);
        if(userIn == "."){
            inputs = 0;
            cout << "Enter the initial tape and press enter." << endl;
        }
        else{
            //always assumes correct input
            for(int i = 0; i < 5; i++)
                tuples[stateNum][i] = char(userIn[i]);
            stateNum++;
        }
    }

    string initState;
    getline(cin, initState, '}');
    state = initState[1];

    cout << "Maximum Iterations: ";
    cin >> maxIters;
 
    for(int i = 0; i < maxIters; i++){
        if(findState(state, tuples, stateNum) == -1){
            terminate == -1;
            state = state;
        }
        else{
            useTuple(tuples, findState(state, tuples, stateNum), tape, direc, tapePos, state);
            cout << tape << "{" << state << "}" << endl;
        }
    }

    if(terminate == -1){
        cout << "HALTED \nFinal State:" << state;
    }
    else{
        cout << "Max Iterations Reached \nFinal State: " << state;
    }
}

int findState(char state, char tuples[][5], int stateNum){
    int statePos = 0;
    while (statePos < stateNum){
    if(tuples[statePos][0] == state)
        return statePos;
    else
        statePos++;
    }
    return -1;
}

void useTuple(char tuples[][5], int state, string &tape, bool &direc, int &tapePos, char &cState){
    char instructions[3];
    for(int i = 0; i < 3; i++){
        instructions[i] == tuples[state][i+2]; 
    }
    tapeEdit(tape, instructions, direc, tapePos, cState);
}

void tapeEdit(string &tape, char instruct[], bool &direc, int &tapePos, char &cState){
    int size;
    if(!tape.empty())
        size = tape.length();
    else 
        size = 0;
    vector<char> copyTape;
    vector<char>::iterator it;
    it = copyTape.begin();

    if(!tape.empty()){
        for(int i = 0; i < size; i++)
            copyTape.push_back(tape[i]);
    }

    if(tape.empty()){
        copyTape.push_back(instruct[0]);
    }
    else if(direc == 0 && tapePos == 0){
        //left and beginning of tape
        copyTape.insert(copyTape.begin(), instruct[0]);
    }
    else if(direc == 1 && tapePos == size-1){
        copyTape.push_back(instruct[0]);
    }
    else if(direc == 0){
        it += tapePos;
        copyTape.insert(it, instruct[0]);
    }
    else{
        it += tapePos;
        it++;
        copyTape.insert(it, instruct[0]);
    }

    //rewrite tape string
    tape = copyTape[0];
    for(int i = 1; i < size; i++){
        tape += copyTape[i];
    }

    //change direction
    if(toupper(instruct[1]) == 'L')
    direc = 0;
    else
    direc = 1;

    //change position
    if(direc == 0 && tapePos == 0)
        tapePos = 0;
    else if(direc == 0)
        tapePos--;
    else if(direc == 1 && tapePos < size)
        tapePos++;
    else
        tapePos = tapePos;

    //change state
    cState = instruct[2];
}