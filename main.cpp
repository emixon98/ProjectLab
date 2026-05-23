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

//Task 2 Function Goal O(N),  0->N
//Missing only one integer
int missingInt(const vector<int>& nums){
    //since start at 0 we can just utilize size since our summation formula is considering starting from index 1
    //If the difference is 0 then we are simply missing 0 and can just return it
    int n = nums.size();
    //summation formula
    int expectedSum = (n * (n+1)) / 2;
    int sum  = 0;
    //only iterating once to find summation
    for (int i =0; i < nums.size(); i++){
        sum += nums[i];
    }
    return (expectedSum - sum);
}

//Task 3 Function Goal O(N)
int greatestProfit(const vector<int>& stockPredictions){
    //starting vals/placeholders
    int low = stockPredictions[0];
    int profit = 0;

    for (int i = 1; i < stockPredictions.size(); i++){
        //Var to hold the difference between our buy and sell point, if our potential is lower than our current calculated profit
        // then we dont change our curr profit margin
        int potential = stockPredictions[i] - low;
        //can use max and min function to find our lowest buy point and highest sell point by comparing through iteration over n
        profit = max(profit, potential);
        low = min(low, stockPredictions[i]);
    }
    return profit;
}

//Task 4 Goal O(N)
//int highestProduct(const vector<int>& vals){

//}

//Task 5 (use double for 10 places) Goal O(N)
//vector<double> orderTemp(const vector<double>& temps){

//}

//Task 6 Goal O(N)
//int longSeq(const vector<int>& vals){

//}



int main(){
    vector<int> nums = {2, 3, 4, 5, 6, 0, 1};

    cout << missingInt(nums) << endl;

    //write test for task1, kind of dont want to atm, could copy paste from lab just ensuring I implement struct datatype

    vector<int> stocks = {10, 7, 5, 8, 11, 2, 6};
    //correct return of 6 can add $ for formatting, but test niche cases and other options as well
    cout << greatestProfit(stocks) << endl;

    return 0;
}