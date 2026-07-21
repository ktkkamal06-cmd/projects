#ifndef BUDGET_CALCULATOR_H
#define BUDGET_CALCULATOR_H

#include <string>

class BudgetCalculator {
private:
    // Our crash-proof helper function from before!
    static double getSafeDouble(const std::string& prompt);

public:
    static void runCalculator();
};

#endif