#include "logic/include/obj3d/figure/components/edge.h"

obj3d::Edge::Edge(size_t begin_id, size_t end_id) :
    begin_id_(begin_id),
    end_id_(end_id) {}

size_t obj3d::Edge::getBegin() const {
    return begin_id_;
}

size_t obj3d::Edge::getEnd() const {
    return end_id_;
}

bool obj3d::Edge::isEqualTo(const obj3d::Edge &other) const {
    return (getBegin() == other.getBegin() && getEnd() == other.getEnd()) ||
            (getEnd() == other.getBegin() && getBegin() == other.getEnd());
}

bool obj3d::Edge::operator==(const obj3d::Edge &other) const {
    return isEqualTo(other);
}

bool obj3d::Edge::operator!=(const obj3d::Edge &other) const {
    return !isEqualTo(other);
}
