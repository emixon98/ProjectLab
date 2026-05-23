#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


struct Player{
    string first_name;
    string last_name;
    string team;
};

//Task 1 Function Goal O(N+M) two diff for loops?
//We are given what looks like a struct inside a vector, which Im using as the foundation for this problem 
vector<string> bothSports(const vector<Player>& sport1, const vector<Player>& sport2){
    unordered_map<string, bool> athletes;
    //Iterate through entire sport1 arr mapping every full name to true (or present) O(N)
    //provides basis to compare with
    for (const auto& player : sport1){
        athletes[player.first_name + " " +player.last_name] = true;
    };

    vector<string> both;
    //using a new vector for our desired cases, we iterate through the 2nd arr and form a string of the full name
    //if it is already in our basis arr then we can add it to our both arr, knowing the name appears in both
    //assuming given case that first and last name combos are unique
    for(const auto& player: sport2){
        string name = player.first_name + " " + player.last_name;
        if(athletes[name])
            both.push_back(name);
    }
    return both;
}

//Task 2 Function Goal O(N)
int missingInt(const vector<int>& nums){

}

//Task 3 Function Goal O(N)
int greatestProfit(const vector<int>& stockPredictions){

}

//Task 4 Goal O(N)
int highestProduct(const vector<int>& vals){

}

//Task 5 (use double for 10 places) Goal O(N)
vector<double> orderTemp(const vector<double>& temps){

}

//Task 6 Goal O(N)
int longSeq(const vector<int>& vals){

}