#ifndef RULE_HPP
#define RULE_HPP

#include "CellularAutomata.hpp"

class RuleBase {
public:
    virtual CellState apply(const std::vector<CellState>& neighbors) const = 0;
};

int applyRule(int ruleNumber, const std::vector<CellState>& neighborhood) {
    int neighbors = (neighborhood[0] << 2) | (neighborhood[1] << 1) | neighborhood[2];
    return (ruleNumber >> neighbors) & 1;
}
#endif



