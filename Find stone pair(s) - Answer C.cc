// There are N number of stones, labeled as [0, N-1]. We know the weight of each of those stones.
// We want to find all stone pairs whose weight difference is weightDiff.

#include<cassert>                   // for assert
#include<utility>                   // for std::pair
#include<cmath>                     // for std::fabs
#include<unordered_map>             // for std::unordered_map
#include<vector>                    // for std::vector
#include<boost/functional/hash.hpp> // for boost::hash
#include<iostream>                  // for std::cout

// Input
//     stoneName    : the name of stones
//     stoneWeights : the pointer which points to the stone weights
//     N            : the number of stones
//     weightDiff   : the diff to be searched
//     stonePairs   : all stone pairs whose difference is weightDiff
// Output
//     number of valid pairs
// Synopsis
//     store the stoneWeights + weightDiff into hashtable and loop the stoneWeights to find all pairs
int findStonePairs(const char * stoneName, double* const stoneWeights, int N, double weightDiff, std::vector<std::pair<int, int>>& stonePairs) {
    assert(N > 0);
    assert(weightDiff >= 0.0);
    for(int i = 0; i < N; i++) {
        assert(stoneWeights[i] > 0.0);
    }
    
    std::unordered_map<double, int> stoneWeightsAddDiff(N);
    for(int i = 0; i < N; i++) {
        stoneWeightsAddDiff.emplace(std::make_pair(stoneWeights[i] + weightDiff, i));
    }
    
    for(int i = 0; i < N; i++) {
        auto iter = stoneWeightsAddDiff.find(stoneWeights[i]);
        if((iter != stoneWeightsAddDiff.end()) && (i != iter->second)) {
            stonePairs.push_back(std::minmax(iter->second, i));
        }
    }

    if(stonePairs.size() > 0) {
        std::cout << stoneName << ": ";
        for(auto pair : stonePairs) {
            std::cout << pair.first << " " << pair.second << "; ";
        }
        std::cout << std::endl;
    }
    
    return stonePairs.size();
}

// This case will cover odd stones weights with successful result
void testOddStoneWeights1() {
    constexpr int N = 7;
    constexpr double diffWeight = 0.39;
    double stoneWeights[N] = {1.23, 5.39, 5.0, 14560.465, 45613.78, 963.25, 8742.5};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(result == 1);
}

// This case will cover odd stones weights with failed result
void testOddStoneWeights2() {
    constexpr int N = 7;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 963.25, 8742.5};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(!result);
}

// This case will cover even stones weights with successful result
void testEvenStoneWeights1() {
    constexpr int N = 6;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 0.23};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(result == 1);
}

// This case will cover even stones weights with failed result
void testEvenStoneWeights2() {
    constexpr int N = 6;
    constexpr double diffWeight = 9.9;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 0.23};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(!result);
}

// This case will cover the weight difference is 0
void testWeightDiffZero() {
    constexpr int N = 7;
    constexpr double diffWeight = 0.0;
    double stoneWeights[N] = {1.23, 5.39, 81742.5, 14560.465, 45613.78, 0.23, 8742.5};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(!result);
}

// This case will cover two pairs found
void testTwoPairsFound1() {
    constexpr int N = 6;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 2.23, 45613.78, 0.23};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(result == 2);
}

// This case will cover two pairs found
void testTwoPairsFound2() {
    constexpr int N = 6;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 45614.78, 45613.78, 0.23};
    std::vector<std::pair<int, int>> stonePairs;
    
    int result = findStonePairs(__FUNCTION__, stoneWeights, N, diffWeight, stonePairs);
    assert(result == 2);
}

int main() {
    testOddStoneWeights1();  // one pair expected
    testOddStoneWeights2();  // no  pair expected
    testEvenStoneWeights1(); // one pair expected
    testEvenStoneWeights2(); // no  pair expected
    testWeightDiffZero();    // no  pair expected
    testTwoPairsFound1();    // two pairs expected
    testTwoPairsFound2();    // two pairs expected
    return 0;
}
