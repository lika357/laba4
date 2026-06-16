#pragma once
#include "button.hpp"
#include "config.hpp"
#include "horizontal_layout.hpp"
#include "vertical_layout.hpp"

class DoublingLayout : public VerticalLayout
{
   public:
    HorizontalLayout buttons{LayoutPositions::WORK_X, LayoutPositions::FUNC_Y,
                             LayoutPositions::FUNC_GAP};
    Button dbGenerate{"GENERATE N", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbGetIndex{"GET INDEX", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbSearch{"SEARCH", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbAuto{"AUTO", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbStop{"STOP", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbClear{"CLEAR", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbBack{"BACK", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbSave{"SAVE", ButtonSizes::STACK_W, ButtonSizes::STACK_H};
    Button dbStats{"STATS", ButtonSizes::STACK_W, ButtonSizes::STACK_H};

    DoublingLayout()
        : VerticalLayout(LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                         LayoutPositions::WORK_GAP)
    {
        buttons.append(dbGenerate);
        buttons.append(dbGetIndex);
        buttons.append(dbSearch);
        buttons.append(dbAuto);
        buttons.append(dbStop);
        buttons.append(dbClear);
        buttons.append(dbBack);
        buttons.append(dbSave);
        buttons.append(dbStats);
        this->append(buttons);
    }
};