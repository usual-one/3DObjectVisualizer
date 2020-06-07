#ifndef EDGE_H
#define EDGE_H

#include "logic/include/obj3d/figure/components/vertex3d.h"

namespace obj3d {
    class Edge;
}

class obj3d::Edge {
public:
    Edge() = delete;

    Edge(size_t begin, size_t end);

    size_t getBegin() const;

    size_t getEnd() const;

    bool operator==(const obj3d::Edge &other) const;

    bool operator!=(const obj3d::Edge &other) const;

private:
    bool isEqualTo(const obj3d::Edge &other) const;

    size_t begin_id_;

    size_t end_id_;
};

#endif // EDGE_H
