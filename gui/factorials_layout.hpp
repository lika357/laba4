#pragma once
#include "button.hpp"
#include "config.hpp"
#include "horizontal_layout.hpp"
#include "vertical_layout.hpp"

class FactorialsLayout : public VerticalLayout
{
   public:
    HorizontalLayout buttons{LayoutPositions::WORK_X, LayoutPositions::FUNC_Y,
                             LayoutPositions::FUNC_GAP};
    Button fcGenerate{"GENERATE N", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcGetIndex{"GET INDEX", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcSearch{"SEARCH", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcAuto{"AUTO", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcStop{"STOP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcClear{"CLEAR", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fcBack{"BACK", ButtonSizes::STACK_W, ButtonSizes::STACK_H};

    FactorialsLayout()
        : VerticalLayout(LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                         LayoutPositions::WORK_GAP)
    {
        buttons.append(fcGenerate);
        buttons.append(fcGetIndex);
        buttons.append(fcSearch);
        buttons.append(fcAuto);
        buttons.append(fcStop);
        buttons.append(fcClear);
        buttons.append(fcBack);
        this->append(buttons);
    }
};