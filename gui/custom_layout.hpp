#pragma once
#include "button.hpp"
#include "config.hpp"
#include "horizontal_layout.hpp"
#include "vertical_layout.hpp"

class CustomLayout : public VerticalLayout
{
   public:
    HorizontalLayout buttons{LayoutPositions::WORK_X, LayoutPositions::FUNC_Y,
                             LayoutPositions::FUNC_GAP};
    Button btnStart{"START", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnStep{"STEP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnLimit{"LIMIT", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnGenerate{"GENERATE N", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnGetIndex{"GET INDEX", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnSearch{"SEARCH", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnAuto{"AUTO", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnStop{"STOP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnClear{"CLEAR", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnBack{"BACK", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnSave{"SAVE", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button btnStats{"STATS", ButtonSizes::STACK_W, ButtonSizes::STACK_H};

    CustomLayout()
        : VerticalLayout(LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                         LayoutPositions::WORK_GAP)
    {
        buttons.append(btnStart);
        buttons.append(btnStep);
        buttons.append(btnLimit);
        buttons.append(btnGenerate);
        buttons.append(btnGetIndex);
        buttons.append(btnSearch);
        buttons.append(btnAuto);
        buttons.append(btnStop);
        buttons.append(btnClear);
        buttons.append(btnBack);
        buttons.append(btnSave);
        buttons.append(btnStats);
        this->append(buttons);
    }
};