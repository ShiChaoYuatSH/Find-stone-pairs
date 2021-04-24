// There are N number of stones, labeled as [0, N-1]. We know the weight of each of those stones.
// We want to find a stone pair whose weight difference is weightDiff.

#include<cassert>                   // for assert
#include<utility>                   // for std::pair
#include<cmath>                     // for std::fabs
#include<unordered_map>             // for std::unordered_map
#include<boost/functional/hash.hpp> // for boost::hash

// Input
//     stoneWeights : the pointer which points to the stone weights
//     N            : the number of stones
//     weightDiff   : the diff to be searched
//     stonePair    : the stone pair whose difference is weightDiff
// Output
//     find valid pair or not
// Synopsis
//     store the stoneWeights + weightDiff into hashtable and loop the stoneWeights to find one pair
bool findStonePair(double* const stoneWeights, int N, double weightDiff, std::pair<int, int>& stonePair) {
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
            stonePair = std::minmax(iter->second, i);
            return true;
        }
    }

    return false;
}

// This case will cover odd stones weights with successful result
void testOddStoneWeights1() {
    constexpr int N = 7;
    constexpr double diffWeight = 0.39;
    double stoneWeights[N] = {1.23, 5.39, 5.0, 14560.465, 45613.78, 963.25, 8742.5};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(result && (stonePair.first == 1) && (stonePair.second == 2));
}

// This case will cover odd stones weights with failed result
void testOddStoneWeights2() {
    constexpr int N = 7;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 963.25, 8742.5};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(!result);
}

// This case will cover even stones weights with successful result
void testEvenStoneWeights1() {
    constexpr int N = 6;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 0.23};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(result && (stonePair.first == 0) && (stonePair.second == 5));
}

// This case will cover even stones weights with failed result
void testEvenStoneWeights2() {
    constexpr int N = 6;
    constexpr double diffWeight = 9.9;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 14560.465, 45613.78, 0.23};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(!result);
}

// This case will cover the weight difference is 0
void testWeightDiffZero() {
    constexpr int N = 7;
    constexpr double diffWeight = 0.0;
    double stoneWeights[N] = {1.23, 5.39, 81742.5, 14560.465, 45613.78, 0.23, 8742.5};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(!result);
}

// This case will cover one pair matched in multiple pairs
void testOnePairMatchedFromMultiPairs() {
    constexpr int N = 6;
    constexpr double diffWeight = 1.0;
    double stoneWeights[N] = {1.23, 5.39, 456.369, 2.23, 45613.78, 0.23};
    std::pair<int, int> stonePair;
    
    bool result = findStonePair(stoneWeights, N, diffWeight, stonePair);
    assert(result && (((stonePair.first == 0) && (stonePair.second == 3)) || ((stonePair.first == 0) && (stonePair.second == 5))));
}

int main() {
    testOddStoneWeights1();  // one pair expected
    testOddStoneWeights2();  // no  pair expected
    testEvenStoneWeights1(); // one pair expected
    testEvenStoneWeights2(); // no  pair expected
    testWeightDiffZero();    // no  pair expected
    testOnePairMatchedFromMultiPairs(); // one pair expected
    
    return 0;
}
