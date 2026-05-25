# ProjectLab
Lab for Final Project for CISC187

### Task 1: Both Sports Function
#### Struct formatting:
```cpp
struct Player{
    string first_name;
    string last_name;
    string team;
};
```
#### Function:
```cpp
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
```
#### Reasoning:
The structure provided by the problem for the player arrays clearly had a hash-like personality with key-value pairs. My function takes in two parameters being two different vectors of different sports and their athletes. Due to this I decided to make a vector that contained a struct that provided the traits of first name, last name, and team to match the given format. I first elected to create a temporary hashtable that contained the key-value pairs being a players name as a string and a boolean value marking true, indicating the person exists. By doing so I can ensure I have O(1) lookup since hashing provides direct access, preventing us from having to use a nested loop. I then iterate through every player on the second list, conjoining their first and last name, if they are in the hashtable I created then they are a player in both sports, and thus are added to the vector 'both', returning multi-sport athletes. This process has two independent for loops in which the first for loop iterates through every element in the first array (N), and the second loop every element in the second array (M). In doing so I meet the requested time complexity O(N+M).

### Task 2: Return The Missing Integer Function
#### Function:
```cpp
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
```
#### Reasoning:
Knowing that the provided array is intended to value from 0 to n we can utilize this to ensure an extremely simple and efficient way to find the missing integer. The classical summation formula relies on an iteration beginning at 1 and ending at n since adding 0 would contribute nothing. Since we start at 0 we can look at our array as always having the correct "size" since 0 isn't actually considered in summation. An example being an array [0, 1, 2, 4], using the formula n(n+1)/2 where n is the size of array (4) and gives an expected sum of 10. Our actual sum is 7, subtracting the two gives 3, which is our missing value. Similarly, if the missing value is 0, we will return 0 because that is what the difference will be. By using this logic we only ever have to iterate through our passed in vector once to calculate the actual sum, maintaining our goal time complexity of O(N). Of note, if utilzing large integers I would change the data type to long long, however, given the examples I assumed smaller values would be used and stuck with int.

### Task 3: Stock Prediction Function
#### Function:
```cpp
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
```
#### Reasoning:
For this function we want to find the most profitable time to buy and sell stocks based off a predicted/forseen array of daily trade values. By setting 2 placeholder values we can utilize a single for loop to find the answer for this problem. The potential profit is calculated by subtracting our lowest found stock price from our current iteration. We compare this potential profit to our currently tracked highest profit and the greater of the two decides which is more profitable, we track our lowest stock price through each iteration as well. Further, by performing our low variable check after the profit is checked we ensure that buying and selling on the same day does not occur. In such a case, imagine we have the array [5, 6, 8, 11, 2], while 2 is the lowest stock price, we cannot retroactively buy it at 2 after selling at 11, since it appears later in the array/the next day. We can track that our lowest and initial/buy price is 5, and each iteration we will replace our profit with the next difference between i and 5 until we eventually see that 11 is the best time to sell and 5 remains the lowest price to buy at. This prediction function could be further improved by looking at adverse effects of trading as well, such as cases where profit is not possible, however, given the structure of the problem I stuck with finding the most profit only. The function tracks this properly and gives us an O(N) time complexity. 

### Task 4: Highest Product of Any 2 Numbers
#### Function:
```cpp
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
```
#### Reasoning:
For this function rather than making nested loops for O(N^2) time complexity, we can make use of variable trackers that a single for loop can compare to. In this case, since negative numbers are considered, I do not only want to track my two most positive numbers, but potentially my two most negative as well. The initial variable are declared in such a way that they can still accurately reflect what the greatest, lowest, and second of each are in even a 2 element array. Due to this consideration our for loop begins at index 2. The current element in the for loop is compared to each of these variables to see if it meets any of the criteria to be the new greatest or lowest value. The two separate if statements ensures a value that is the new second greatest can also be evaluated for being the new lowest. Much like previous problems, I use the max function to return the greatest product between the two greatest and two lowest values, in the case that the two most negative values do indeed have a positive product greater than the two most positive. Any other combinations of values would provide a product between these two, and rather than checking all of the possible products utilizing this method ensures the desired O(N) time complexity.

### Task 5: Sorting Temp Low -> High Function
#### Function:
```cpp
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
```
#### Reasoning:
Noting the wording of this task allows a unique approach to it. We are told that only healthy temps are taken, ranging from 97.0 to 99.0, and that any difference between temps only varies by one tenth. This will give us 21 different temperatures total, which means we can use a counting sort styled algorithm due to having a known domain of values. Due to this I can make a hash table that hashes the occurrences of a temperature to itself. In my for loop you may note that I multiply my iteration var i, by .1, and that it's max val will be 20, this is to translate the iteration of i to the current (degree + it's tenth) that I'm searching for. I then use my hash table and see if that value resides in it, and if it does I push it onto my ordered vector j amount of times, where j is the number of occurrences it has in the value portion of the table. This allows for some dynamic cases, that all maintain O(N) time complexity. For example, lets say only 1 temperature happens, well my first for loop just marks it in the table as the only key and its occurrences as the value. The outer for loop runs a fixed 21 times and the inner loop run N times total through all outer iterations, since the sum of occurrences must equal the size of the input array giving a complexity O(21 + N). Mixing and matching temp results should always give a simplified time complexity of O(N), be that one of every temp or one temp multiple times.

### Task 6: Longest Consecutive Sequence Function
#### Function:
```cpp
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
```

#### Reasoning:
For this task the goal was to add every value from our vector into an unordered set, allowing us to utilize the count function. The count function returns a 0 or 1 which for our use case allows us to see if a value exists. Since we only need to return the longest sequence and not the actual values we can just verify if the next value in the sequence exist which is utilized in our (i + len) line. We also take care of niche cases, such as making sure the number we are starting at is indeed the first in the sequence, if it is not, or if a value exists that is 1 less than it, we need to move on to our next iteration of the for loop as we are not at the beginning. In this case our outer for loop hits that case and skips because i-1 exists, and will later be considered through the true starts while loop process If our sequence is longer than our prior tracked one we simply reassign our tracked sequence to the new longest one, again using max(). Each value is visited at most twice, once when skipped for not being a starting point and once during the while loop of the sequences actual start, which allows for linear time complexity. By using loops in this way we are able to maintain the desired O(N) time complexity.

### Main Unit Tests:
```cpp
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
```
### Example Terminal Output of Provided Cases:
<img width="1052" height="446" alt="Screenshot 2026-05-23 212218" src="https://github.com/user-attachments/assets/0f94a794-9591-43cb-bf16-ae62fbc6ddab" />
