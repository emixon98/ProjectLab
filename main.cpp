#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
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

//Task 4 Goal O(N) Potentially two highest pos vals or two most neg vals, can check if abs val function
//can use max and min again
int highestProduct(const vector<int>& vals){
    //set placeholder for highest, second highest, lowest, second lowest.
    //iterate through vector for what might be the next highest or lowest and shift accordingly
    //return the max between highest*second highest and lowest*secondlowest
    int greatest = vals[0];
    int second_greatest = vals[0];
    int lowest = vals[0];
    int second_lowest = vals[0];

    for (int i =1; i < vals.size(); i++){
        if (vals[i] > greatest) {
            second_greatest = greatest;
            greatest = vals[i];
        }
        else if (vals[i] > second_greatest) second_greatest=vals[i];
        else if (vals[i] < lowest){
            second_lowest = lowest;
            lowest = vals[i];
        } 
        else if (vals[i] < second_lowest) second_lowest = vals[i];    
    }
    return max(greatest * second_greatest, lowest * second_lowest);
}

//Task 5 (use double for 10 places) Goal O(N)
vector<double> orderTemp(const vector<double>& temps){
//Healthy range 97.0 to 99.0
    //How are multiple cases meant to be handled, just listed out consecutively?
    //Because vals only range from 97.0 to 99.0 in .1 increments we can conclude there are 21 different possible temps
    // because of this we can use a hash table that simply marks occurences of each individual temp
    //We then use this map to insert our occuring vals into our output array using an incrementing for loop
    //If present in the map insert it for as many occurences as it has, ie in the example given 98.0 would have an occurence rate of 2 and would need to be inserted twice
    unordered_map<double, int> occurences;
    for (double temp : temps) occurences[temp]++;

    vector<double> order;
    //couldnt declare size in one line, added extra 0 vals
    order.reserve(temps.size());
    //maybe error was here in loop, error with iteration was present here
    for (int i = 0; i <= 20; i++){
        double temp = 97.0 + (i * .1);
        auto it = occurences.find(temp);
        if(it != occurences.end())
        //j is compared to the second part of the map pair, in this case occurences
        //does not break out time complexity because we arent iterating through n occurences, just occurences of the temperature
        //in the case our only temperature is 97.5 for example, we are using our unordered_map for iteration, which would only have one temp in such a case
        // so our iteration in that case would be O(1 + n) n being occurence, either way we even out between these loops to simplify to O(n) time complexity
            for (int j=0; j < it->second; j++)
                order.push_back(temp);
    }
    return order;
}

//Task 6 Goal O(N)
int longSeq(const vector<int>& vals){
    //needs to be consecutive, difference of one
    //first thought is a process that is a time complexity of O(n*(n-1)) need to simplify
    //can potentially sort them into a new vector, then can check if next val is +1 from last val
    //if so add to a running vector, but if run into a longer one later will need to change vector...
    //nvm only returning length of sequence, that makes it much easier
    //using count algorithm function we can basically use it as a boolean that is true if a val is contained

    unordered_set<int> nums(vals.begin(), vals.end());

    int longest_seq = 0;

    for(int i : nums){
        //check if our current value is the true "starting point"
        if (!nums.count(i - 1)){
            int len = 1;
            while(nums.count(i + len))
                ++len;
            longest_seq = max(longest_seq, len);
        }
    }
    return longest_seq;
}



int main(){
    vector<int> nums = {2, 3, 4, 5, 6, 0, 1};

    cout << missingInt(nums) << endl;

    //write test for task1, kind of dont want to atm, could copy paste from lab just ensuring I implement struct datatype

    vector<int> stocks = {10, 7, 5, 8, 11, 2, 6};
    //correct return of 6 can add $ for formatting, but test niche cases and other options as well
    cout << greatestProfit(stocks) << endl;

    //task 4 both cases of highestproduct being negative and being positive work
    vector<int> product = {5, -10, -6, 8 ,4};
    cout<< highestProduct(product) << endl;

    vector<int> products = {5, -10, -6, 20 ,4};
    cout<< highestProduct(products) << endl;

    vector<double> temperatures = {98.6, 98.0, 97.1, 99.0, 98.9, 97.8, 98.5, 98.2, 98.0, 97.1};

    vector<double> ordered_temps = orderTemp(temperatures);
    for (int i=0; i < ordered_temps.size(); i++){
        cout << ordered_temps[i] << " ";
    }

    cout << endl;


    vector<int> sequence = {10, 5, 12, 3, 55, 30, 4, 11, 2};
    vector<int> sequence2 = {19, 13, 15, 12, 18, 14, 17, 11};
    cout << longSeq(sequence) << endl << longSeq(sequence2) << endl;

    return 0;
}