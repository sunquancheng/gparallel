#include <iostream>
#include <gtest/gtest.h>
#include <stdio.h>
#include "node_deduce.h"
#include "util.h"
#include "meta.h"
#include "node_container.h"
using namespace galois::gparallel;

struct base {};
DECL_DATA_META(MetaB, base) {};

DECL_DATA_META(MetaC, base) {};

DECL_DATA_META(MetaA, base, MetaC) {};

DECL_DATA_META(MetaD, base) {};

DECL_DATA_META(MetaE, base, MetaD) {};

struct NodeA
{
    int process(output<MetaA> b) { return 0; }
};

struct NodeB
{
    int process(input<MetaA> a, output<MetaB> b) { return 0; }
};

struct NodeC
{
    int process(output<MetaC> c) { return 0; }
};

struct NodeD
{
    int process(input<MetaB> b, input<MetaC> c, output<MetaD> d) { return 0; }
};

struct NodeE
{
    int process(output<MetaE> e) { return 0; }
};

TEST(Test, register_node) {
    using namespace galois::gparallel;
    node_container nodes;
    register_node<NodeA, NodeB, NodeC, NodeD, NodeE>::reg(nodes);
}