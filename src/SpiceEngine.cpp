#include "SpiceEngine.hpp"

#include "Types.hpp"
#include <algorithm>
#include <cassert>
#include <set>
#include <tuple>

#if not defined NDEBUG or defined _DEBUG
#include <iostream>
#endif

namespace spice {

std::vector<std::vector<size_t>> SpiceEngine::netlist_cycles(const std::vector<Net> netlist) const {
    std::vector<std::vector<size_t>> cycles;
    std::set<std::tuple<size_t, size_t>> processed;

    // TODO need a better way of tracking processed nodes (maybe)
    auto simple_hash = [](const std::vector<size_t>& vec, bool reverse) -> std::tuple<size_t, size_t> {
        size_t val = 0, pos = 0;
        for (size_t i = 0; i != vec.size(); i++) {
            auto n = reverse ? vec.size() - 1 - i : i;
            pos += n << vec[i];
            val += size_t(1) << vec[i];
        }
        return std::tuple(val, pos);
    };

    // explicit vector copies, rec allows for recursive lambda call
    auto find_cycles =
        [&](size_t node, size_t start, std::vector<bool> seen, std::vector<size_t> nodes, auto& rec) -> void {
        assert(seen.size() >= node);

        nodes.push_back(node);
        seen[node] = true;

        for (size_t neighbor : netlist[node].adjacent) {
            if (neighbor < start) { // avoid needless/ambiguous repeats
                continue;
            } else if (!seen[neighbor]) {
                rec(neighbor, start, seen, nodes, rec);
            } else if (neighbor == start && nodes.size() > 1 && neighbor != nodes.end()[-2]) {
                std::vector cycle(std::ranges::find(nodes, neighbor), nodes.end());

                std::ranges::rotate(cycle, std::ranges::min_element(cycle) + 1);
                auto h0 = simple_hash(cycle, true);
                if (processed.contains(h0))
                    continue;

                std::ranges::rotate(cycle, cycle.end() - 1);
                auto h1 = simple_hash(cycle, false);
                if (processed.contains(h1))
                    continue;

                processed.insert({h0, h1});
                cycles.push_back(cycle);
            }
        }
    };

    std::vector<bool> seen(netlist.size(), false);

    for (size_t i = 0; i < netlist.size(); i++) {
        find_cycles(i, i, seen, {}, find_cycles);
    }

    return cycles;
}

} // namespace spice