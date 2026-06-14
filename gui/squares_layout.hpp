#pragma once
#include "button.hpp"
#include "config.hpp"
#include "horizontal_layout.hpp"
#include "vertical_layout.hpp"

class SquaresLayout : public VerticalLayout
{
public:
    HorizontalLayout buttons{LayoutPositions::WORK_X, LayoutPositions::FUNC_Y,
                             LayoutPositions::FUNC_GAP};
    Button sqGenerate{"GENERATE N", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqGetIndex{"GET INDEX", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqSearch{"SEARCH", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqAuto{"AUTO", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqStop{"STOP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqClear{"CLEAR", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button sqBack{"BACK", ButtonSizes::STACK_W, ButtonSizes::STACK_H};

    SquaresLayout()
        : VerticalLayout(LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                         LayoutPositions::WORK_GAP)
    {
        buttons.append(sqGenerate);
        buttons.append(sqGetIndex);
        buttons.append(sqSearch);
        buttons.append(sqAuto);
        buttons.append(sqStop);
        buttons.append(sqClear);
        buttons.append(sqBack);
        this->append(buttons);
    }
};