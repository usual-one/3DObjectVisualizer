#ifndef FIGURESESSIONSTATE_H
#define FIGURESESSIONSTATE_H

#include "logic/include/obj3d/figure/components/state.h"

class FigureSessionState {
public:
    FigureSessionState();

    std::shared_ptr<State> getState();

    bool isHidden();

    bool isSurface();

    void setHidden(bool hidden);

    void setState(std::shared_ptr<State> state);

    void setSurface(bool surface);

private:
    bool hidden_;

    bool is_surface_;

    std::shared_ptr<State> state_;

};

#endif // FIGURESESSIONSTATE_H
