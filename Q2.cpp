#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;


vector<long long> genPhones(int n) { //random phone numbers generator
    vector<long long> nums;
    for (int i = 0; i < n; ++i) {
        // Generate a random 10-digit phone number
        long long num = 1000000000LL + rand() % 9000000000LL; 
        nums.push_back(num);
    }
    return nums;
}

//h(x) = x mod 50
int h1(long long x) {
    return x % 50;
}

//h(x) = ((ax + b) mod p) mod 50
int h2(long long x, int a, int b, int p) {
    return ((a * x + b) % p) % 50;
}

//Correlation coefficient
double calcCorr(const vector<long long>& data, const vector<int>& hOuts) {
    int n = data.size();
    long long sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;

    
    for (int i = 0; i < n; ++i) {
        sumX += data[i];
        sumY += hOuts[i];
        sumXY += data[i] * hOuts[i];
        sumX2 += data[i] * data[i];
        sumY2 += hOuts[i] * hOuts[i];
    }

    
    double num = n * sumXY - sumX * sumY;
    double denom = sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

    return denom == 0 ? 0 : num / denom; 
}

int main() {
    srand(static_cast<unsigned int>(time(0))); //Seed for random numbers

    const int nPhones = 1000; //No. of phone numbers
    vector<long long> phones = genPhones(nPhones); //Generate phone numbers
    vector<int> hOut1(nPhones); //Hash outputs for h1
    vector<int> hOut2(nPhones); //Hash outputs for h2

    
    const int p = 10091; //Large prime number
    const int a = 2468;  
    const int b = 1357;  

    //Using the hash functions
    for (int i = 0; i < nPhones; ++i) {
        hOut1[i] = h1(phones[i]); //h1
        hOut2[i] = h2(phones[i], a, b, p); //h2
    }

    //Frequency
    unordered_map<int, int> freq1, freq2;

    //h1 freq
    for (const auto& output : hOut1) {
        freq1[output]++;
    }

    //h2 freq
    for (const auto& output : hOut2) {
        freq2[output]++;
    }

    
    cout << "h1: (h(x) = x mod 50):\n";
    for (const auto& entry : freq1) {
        cout << "Hash Value: " << entry.first << ", Freq: " << entry.second << endl;
    }

    // Display frequency of hash outputs for function 2
    cout << "\nh2: (h(x) = ((ax + b) mod p) mod 50):\n";
    for (const auto& entry : freq2) {
        cout << "Hash Value: " << entry.first << ", Freq: " << entry.second << endl;
    }

    // Calculate and display correlation coefficients for independence evaluation
    double corr1 = calcCorr(phones, hOut1); // Correlation for function 1
    double corr2 = calcCorr(phones, hOut2); // Correlation for function 2

    cout << "\nCorrelation Coefficient for h1: " << corr1 << endl;
    cout << "Correlation Coefficient for h2: " << corr2 << endl;

    return 0;
}
