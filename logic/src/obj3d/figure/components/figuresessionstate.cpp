#include "logic/include/obj3d/figure/components/figuresessionstate.h"

FigureSessionState::FigureSessionState() :
    hidden_(false),
    is_surface_(false),
    state_(std::make_shared<State>()) {}

std::shared_ptr<State> FigureSessionState::getState() {
    return state_;
}

bool FigureSessionState::isHidden() {
    return hidden_;
}

bool FigureSessionState::isSurface() {
    return is_surface_;
}

void FigureSessionState::setHidden(bool hidden) {
    hidden_ = hidden;
}

void FigureSessionState::setState(std::shared_ptr<State> state) {
    state_->copy(*state);
}

void FigureSessionState::setSurface(bool surface) {
    is_surface_ = surface;
}
