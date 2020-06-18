#ifndef FIGURESTATEDTO_H
#define FIGURESTATEDTO_H

#include "logic/include/obj3d/figure/components/state.h"

class FigureStateDTO {
public:
    FigureStateDTO(std::shared_ptr<State> state);

    State &getState();

    void setState(std::shared_ptr<State> state);

private:
    State state_;

};

#endif // FIGURESTATEDTO_H
