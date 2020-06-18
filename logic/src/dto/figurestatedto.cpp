#include "logic/include/dto/figurestatedto.h"

FigureStateDTO::FigureStateDTO(std::shared_ptr<State> state) {
    setState(state);
}

State &FigureStateDTO::getState() {
    return state_;
}

void FigureStateDTO::setState(std::shared_ptr<State> state) {
    state_.copy(*state);
}
