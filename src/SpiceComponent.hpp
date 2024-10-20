#pragma once

#include "Types.hpp"

namespace spice {

/**
 * @brief Nets are used to define the nodes of a circuit
 */
struct Net {
    Net() = delete;

    /**
     * @brief Construct a Net from a vector or adjacent nodes
     * @param adjacent Adjacency neighbors from graph theory, these are indices of other nodes in netlist
     * @param ground Is the Net grounded?
     */
    Net(const std::vector<size_t>& adjacent, bool ground = false)
        : adjacent(adjacent),
          ground(ground) {}

    const std::vector<size_t> adjacent;
    const bool ground;
};

struct Component {
    Component() = delete;

    /**
     * @brief Construct circuit component by defined nets and value.
     * The circuit component can represent any basic component e.g. RLC.
     * @param net_in Input net
     * @param net_out Output net
     * @param value Complex component value
     */
    Component(size_t net_in, size_t net_out, complex_t value = {})
        : net_in(net_in),
          net_out(net_out),
          value(value) {}

    // TODO make these port vectors to support subckts like opamps
    const size_t net_in;
    const size_t net_out;
    complex_t value;
};

} // namespace spice