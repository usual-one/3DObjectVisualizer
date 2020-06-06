#include "logic/include/obj3d/figure/edge.h"

obj3d::Edge::Edge(std::string begin, std::string end) :
    begin_(std::make_shared<std::string>(begin)),
    end_(std::make_shared<std::string>(end)) {}

std::shared_ptr<std::string> obj3d::Edge::getBegin() {
    return begin_;
}

std::shared_ptr<std::string> obj3d::Edge::getEnd() {
    return end_;
}

bool obj3d::Edge::operator==(const obj3d::Edge &other) {
    return (*begin_ == *other.begin_ && *end_ == *other.end_) ||
            (*end_ == *other.begin_ && *begin_ == *other.end_);
}

bool obj3d::Edge::operator!=(const obj3d::Edge &other) {
    return !(*this == other);
}
