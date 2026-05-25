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

//Task 1 Function Goal O(N+M) two diff for loops
//We are given what looks like a struct inside a vector, which Im using as the foundation for this problem 
// Solution made on given assumption that first and last name combos are unique
vector<string> bothSports(const vector<Player>& sport1, const vector<Player>& sport2){
    unordered_map<string, bool> athletes;
    //Iterate through entire sport1 arr mapping every full name to true (or present) O(N)
    //provides basis to compare with
    for (const auto& player : sport1){
        athletes[player.first_name + " " +player.last_name] = true;
    };

    vector<string> both;
    //using a new vector for our desired cases, we iterate through the 2nd arr and form a string of the full name based on the Player struct
    //if already in basis arr, athlete/player has appeared twice, add to our return arr
    for(const auto& player: sport2){
        string name = player.first_name + " " + player.last_name;
        if(athletes[name])
            both.push_back(name);
    }
    return both;
}

//Task 2 Function Goal O(N),  0->N elements
//Missing only one integer
int missingInt(const vector<int>& nums){

    int n = nums.size();
    //summation formula, utilizing passed in vector size
    //since vector includes 0, we know that the summation of n elements will be correct as 0 will not contribute to the sum
    //and the summation formula is considering an index starting from 1, making it easier to identify our missing val
    int expectedSum = (n * (n+1)) / 2;
    int sum  = 0;
    //only iterating through nums once to find summation
    for (int i =0; i < (int)nums.size(); i++){
        sum += nums[i];
    }
    //The difference between our supposed sum and actual will be the missing val
    return (expectedSum - sum);
}

//Task 3 Function Goal O(N)
int greatestProfit(const vector<int>& stockPredictions){

    if (stockPredictions.empty()) return 0;
    //starting vals/placeholders
    int low = stockPredictions[0];
    int profit = 0;

    for (int i = 1; i < (int)stockPredictions.size(); i++){
        //Var to hold the difference between our buy and sell point, if our potential is lower than our current calculated profit
        // then we dont change our curr profit margin
        int potential = stockPredictions[i] - low;
        //can use max and min function to find our lowest buy point and highest sell point by comparing through iteration over n
        profit = max(profit, potential);
        low = min(low, stockPredictions[i]);
    }
    return profit;
}

//Task 4 Goal O(N) Potentially two highest positive vals or two most negative vals
//can use max and min again
int highestProduct(const vector<int>& vals){
    //set placeholder/basis for highest, second highest, lowest, second lowest.
    if (vals.empty()) return 0;
    if (vals.size() < 2) return 0;

    int greatest = max(vals[0], vals[1]);
    int second_greatest = min(vals[0], vals[1]);
    int lowest = min(vals[0], vals[1]);
    int second_lowest =  max(vals[0], vals[1]);

    //iterate through vector for what might be the next highest or lowest and shift accordingly
    //start at 2 due to our placeholder intialization choice, which was chose in the case of a 2 integer arr
    for (int i = 2; i < (int)vals.size(); i++){
        if (vals[i] > greatest) {
            second_greatest = greatest;
            greatest = vals[i];
        }
        else if (vals[i] > second_greatest) second_greatest=vals[i];
        //need two different if statements, with initialization process second_greatest and lowest may be same for earlier iterations
        //have to ensure both cases are handled
        if (vals[i] < lowest){
            second_lowest = lowest;
            lowest = vals[i];
        } 
        else if (vals[i] < second_lowest) second_lowest = vals[i];    
    }
    //return the max between highest*second highest and lowest*secondlowest to consider negatives
    return max(greatest * second_greatest, lowest * second_lowest);
}

//Task 5 Goal O(N), Healthy range 97.0 to 99.0
vector<float> orderTemp(const vector<float> temps){
    //Because vals only range from 97.0 to 99.0 in .1 (tenths) increments we can conclude there are 21 different possible temps
    // because of this we can use a hash table that simply hashes occurences to each individual temp
    //We then use this map to insert our occuring vals into our output array using an incrementing for loop, incrementing for #of occurences

    //If present in the map insert it for as many occurences as it has, ie) in the example given 98.0 would have an occurence rate of 2 and would need to be inserted twice
    unordered_map<float, int> occurences;
    for (float temp : temps) occurences[temp]++;

    vector<float> order;
    order.reserve(temps.size());

    for (int i = 0; i <= 20; i++){
        //make our i into tenth form
        float temp = 97.0 + (i * .1);

        //iterate and find all occurences of a specific temp
        auto it = occurences.find(temp);
        if(it != occurences.end())
        //j is compared to the second part of the map pair, in this case occurences
        //does not break out time complexity because we arent iterating through n occurences, just occurences of the temperature
            for (int j=0; j < it->second; j++)
                order.push_back(temp);
    }
    return order;
}

//Task 6 Goal O(N)
int longSeq(const vector<int>& vals){
    //needs to be consecutive, difference of one
    //using count algorithm function we can use it as a boolean that is true if a val is contained

    //add in all ints from vals
    unordered_set<int> nums(vals.begin(), vals.end());

    //tracker var
    int longest_seq = 0;

    for(int i : nums){
        //check if our current value is the true "starting point"
        //if it is then our curr length is 1, and we can increment our length to try and find if the next val exists
        //if true our len increments again... and so on
        if (!nums.count(i - 1)){
            int len = 1;
            while(nums.count(i + len))
                ++len;
            //see if current tracked sequence is longer than last longest
            longest_seq = max(longest_seq, len);
        }
    }
    return longest_seq;
}


int main(){
//How Im declaring the Player arrays as type/example given is most likely written in Ruby
    vector<Player> basketball_players = {
        {"Jill",  "Huang",     "Gators"},
        {"Janko", "Barton",    "Sharks"},
        {"Wanda", "Vakulskas", "Sharks"},
        {"Jill",  "Moloney",   "Gators"},
        {"Luuk",  "Watkins",   "Gators"}
    };

    vector<Player> football_players = {
        {"Hanzla", "Radosti",   "32ers"},
        {"Tina",   "Watkins",   "Barleycorns"},
        {"Alex",   "Patel",     "32ers"},
        {"Jill",   "Huang",     "Barleycorns"},
        {"Wanda",  "Vakulskas", "Barleycorns"}
    };

    vector<string> multiple_sports = bothSports(basketball_players, football_players);

    cout << "Multi-Sport Athletes: ";
    for (int i = 0; i < (int)multiple_sports.size(); i++){
        cout << multiple_sports[i] << " ";
    }

    cout << endl;

    vector<int> nums = {2, 3, 0, 6, 1, 5};
    vector<int> nums2 = {8, 2, 3, 9, 4, 7, 5, 0, 6};

    cout << "Missing Value of First Example: " << missingInt(nums) << endl;

    cout << "Missing Value of Second Example: " << missingInt(nums2) << endl;

    vector<int> stocks = {10, 7, 5, 8, 11, 2, 6};
    //correct return of 6 can add $ for formatting, but test niche cases and other options as well
    cout << "The greatest profit is: $ " << greatestProfit(stocks) << endl;

    //task 4 both cases of highestproduct being negative and being positive work
    vector<int> product = {5, -10, -6, 8 ,4};
    cout<< "Highest Product with Negative Case: " <<  highestProduct(product) << endl;

    vector<int> products = {5, -10, -6, 20 ,4};
    cout<< "Highest Product with Positive Case: " << highestProduct(products) << endl;

    vector<float> temperatures = {98.6, 98.0, 97.1, 99.0, 98.9, 97.8, 98.5, 98.2, 98.0, 97.1};

    vector<float> ordered_temps = orderTemp(temperatures);
    cout << "The ordered temperatures are: ";
    for (int i=0; i < (int)ordered_temps.size(); i++){
        cout << ordered_temps[i] << " ";
    }

    cout << endl;


    vector<int> sequence = {10, 5, 12, 3, 55, 30, 4, 11, 2};
    vector<int> sequence2 = {19, 13, 15, 12, 18, 14, 17, 11};
    cout << "The first example longest sequence is: " << longSeq(sequence) << endl 
    << "The second example longest sequence is: " << longSeq(sequence2) << endl;

    return 0;
}