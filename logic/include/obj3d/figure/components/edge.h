#ifndef EDGE_H
#define EDGE_H

#include "logic/include/obj3d/figure/components/vertex3d.h"

namespace obj3d {
    class Edge;
}

class obj3d::Edge {
public:
    Edge() = delete;

    Edge(std::string begin, std::string end);

    std::shared_ptr<std::string> getBegin();

    std::shared_ptr<std::string> getEnd();

    bool operator==(const obj3d::Edge &other);

    bool operator!=(const obj3d::Edge &other);

private:
    std::shared_ptr<std::string> begin_;

    std::shared_ptr<std::string> end_;
};

#endif // EDGE_H
