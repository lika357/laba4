#pragma once
#include "button.hpp"
#include "config.hpp"
#include "horizontal_layout.hpp"
#include "vertical_layout.hpp"

class FibonacciLayout : public VerticalLayout
{
   public:
    HorizontalLayout buttons{LayoutPositions::WORK_X, LayoutPositions::FUNC_Y,
                             LayoutPositions::FUNC_GAP};
    Button fibGenerate{"GENERATE N", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibGetIndex{"GET INDEX", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibSearch{"SEARCH", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibAuto{"AUTO", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibStop{"STOP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibClear{"CLEAR", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibBack{"BACK", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibSave{"SAVE", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button fibStats{"STATS", ButtonSizes::STACK_W, ButtonSizes::STACK_H};

    FibonacciLayout()
        : VerticalLayout(LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                         LayoutPositions::WORK_GAP)
    {
        buttons.append(fibGenerate);
        buttons.append(fibGetIndex);
        buttons.append(fibSearch);
        buttons.append(fibAuto);
        buttons.append(fibStop);
        buttons.append(fibClear);
        buttons.append(fibBack);
        buttons.append(fibSave);
        buttons.append(fibStats);
        this->append(buttons);
    }
};