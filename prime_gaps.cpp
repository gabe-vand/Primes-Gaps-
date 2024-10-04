#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>

const double TARGET = 50000000000;

void generate_primes_below(double target, std::vector<double> &primes) {
    if (target < 2) return;
    std::vector<bool> is_prime(target, true);
    is_prime[0] = false; // 0 is not prime
    is_prime[1] = false; // 1 is not prime
    for (double i = 2; i * i < target; ++i) {
        if (is_prime[i]) {
            for (double j = i * i; j < target; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (double i = 2; i < target; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

void prime_gaps(const std::vector<double> &primes, std::vector<double> &gaps) {
    if (primes.empty()) return;
    gaps.push_back(0); // First gap is 0
    for (size_t i = 1; i < primes.size(); ++i) {
        gaps.push_back(primes[i] - primes[i - 1]);
    }
}

void elim_dupes(const std::vector<double> &gaps, std::vector<double> &no_dupes) {
    std::set<double> unique_gaps(gaps.begin(), gaps.end());
    no_dupes.assign(unique_gaps.begin(), unique_gaps.end());
}

void get_freq(const std::vector<double> &gaps, const std::vector<double> &no_dupes, std::vector<double> &freq) {
    std::map<double, double> gap_counts;
    for (double gap : gaps) {
        gap_counts[gap]++;
    }
    for (double gap : no_dupes) {
        freq.push_back(gap_counts[gap]);
    }
}

int main() {
    std::cout << "\n";
    std::cout << "THINKING... hunting for data for under " << TARGET << "\n";

    clock_t start_time = clock();

    std::vector<double> primes;
    generate_primes_below(TARGET, primes);

    std::vector<double> gaps;
    prime_gaps(primes, gaps);

    std::vector<double> no_dupes;
    elim_dupes(gaps, no_dupes);

    std::vector<double> freq;
    get_freq(gaps, no_dupes, freq);

    // Output to CSV file
    std::ofstream outfile("prime_gaps.csv");
    outfile << "Gaps,Frequencies\n";

    for (size_t i = 0; i < no_dupes.size(); ++i) {
        outfile << no_dupes[i] << "," << freq[i] << "\n";
    }
    outfile.close();

    clock_t end_time = clock();
    double execution = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Found data for values up to " << TARGET << " in " << std::fixed << std::setprecision(3) << execution << " seconds\n";
    std::cout << "\n";

    return 0;
}
