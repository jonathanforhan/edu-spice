#pragma once

#include "SpiceComponent.hpp"
#include <vector>

namespace spice {

class SpiceEngine {
public:
    /**
     * @brief Uses graph traversal to find N unique cycles in undirected graph (netlist).
     * Time complexity is O(E, V)
     * @param netlist
     * @return List of cycles
     */
    std::vector<std::vector<size_t>> netlist_cycles(const std::vector<Net> netlist) const;

private:
};

} // namespace spice