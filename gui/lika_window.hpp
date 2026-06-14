#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <memory>
#include <sstream>

#include "../include/array_sequence.hpp"
#include "../include/generators.hpp"
#include "../include/lazy_sequence.hpp"
#include "button.hpp"
#include "config.hpp"
#include "doubling_layout.hpp"
#include "edit.hpp"
#include "factorials_layout.hpp"
#include "fibonacci_layout.hpp"
#include "horizontal_layout.hpp"
#include "label.hpp"
#include "squares_layout.hpp"
#include "vertical_layout.hpp"

class LikaWindow
{
   private:
    sf::RenderWindow window;
    sf::Font font;
    Label titleLabel{"LAZY SEQUENCE TESTER"};

    VerticalLayout chooseLayout{LayoutPositions::CHOOSE_X, LayoutPositions::CHOOSE_Y,
                                LayoutPositions::CHOOSE_GAP};

    Button btnFib{"FIBONACCI", ButtonSizes::CHOOSE_W, ButtonSizes::CHOOSE_H};
    Button btnSquare{"SQUARES", ButtonSizes::CHOOSE_W, ButtonSizes::CHOOSE_H};
    Button btnDouble{"DOUBLING", ButtonSizes::CHOOSE_W, ButtonSizes::CHOOSE_H};
    Button btnFact{"FACTORIALS", ButtonSizes::CHOOSE_W, ButtonSizes::CHOOSE_H};

    VerticalLayout workLayout{LayoutPositions::WORK_X, LayoutPositions::WORK_Y,
                              LayoutPositions::WORK_GAP};

    std::unique_ptr<FibonacciLayout> fibLayout;
    std::unique_ptr<SquaresLayout> sqLayout;
    std::unique_ptr<DoublingLayout> dbLayout;
    std::unique_ptr<FactorialsLayout> fcLayout;

    Edit inputField;
    Label resultLabel{""};

    std::vector<HorizontalLayout*> elementRows;
    size_t currentRow = 0;

    std::unique_ptr<LazySequence<int>> lazySeq;

    std::string currentGeneratorName;

    bool inputMode = false;
    int inputType = 0;
    bool isAutoGenerating = false;
    int generatedCount = 0;

    static constexpr size_t MAX_ELEMENTS = 160;
    static constexpr int MAX_INDEX = 200;

    int activeGenerator = 0;

    void setupFibonacciLayout()
    {
        fibLayout = std::make_unique<FibonacciLayout>();

        fibLayout->fibGenerate.setOnClick(std::bind(&LikaWindow::onGenerateClick, this));
        fibLayout->fibGetIndex.setOnClick(std::bind(&LikaWindow::onGetByIndexClick, this));
        fibLayout->fibSearch.setOnClick(std::bind(&LikaWindow::onSearchClick, this));
        fibLayout->fibAuto.setOnClick(std::bind(&LikaWindow::onAutoClick, this));
        fibLayout->fibStop.setOnClick(std::bind(&LikaWindow::onStopClick, this));
        fibLayout->fibClear.setOnClick(std::bind(&LikaWindow::onClearClick, this));
        fibLayout->fibBack.setOnClick(std::bind(&LikaWindow::onBackClick, this));

        while (workLayout.getWidgetCount() > 0)
        {
            workLayout.removeLast();
        }

        workLayout.append(*fibLayout);
    }

    void setupSquaresLayout()
    {
        sqLayout = std::make_unique<SquaresLayout>();
        sqLayout->sqGenerate.setOnClick(std::bind(&LikaWindow::onGenerateClick, this));
        sqLayout->sqGetIndex.setOnClick(std::bind(&LikaWindow::onGetByIndexClick, this));
        sqLayout->sqSearch.setOnClick(std::bind(&LikaWindow::onSearchClick, this));
        sqLayout->sqAuto.setOnClick(std::bind(&LikaWindow::onAutoClick, this));
        sqLayout->sqStop.setOnClick(std::bind(&LikaWindow::onStopClick, this));
        sqLayout->sqClear.setOnClick(std::bind(&LikaWindow::onClearClick, this));
        sqLayout->sqBack.setOnClick(std::bind(&LikaWindow::onBackClick, this));
        while (workLayout.getWidgetCount() > 0)
        {
            workLayout.removeLast();
        }
        workLayout.append(*sqLayout);
    }

    void setupDoublingLayout()
    {
        dbLayout = std::make_unique<DoublingLayout>();
        dbLayout->dbGenerate.setOnClick(std::bind(&LikaWindow::onGenerateClick, this));
        dbLayout->dbGetIndex.setOnClick(std::bind(&LikaWindow::onGetByIndexClick, this));
        dbLayout->dbSearch.setOnClick(std::bind(&LikaWindow::onSearchClick, this));
        dbLayout->dbAuto.setOnClick(std::bind(&LikaWindow::onAutoClick, this));
        dbLayout->dbStop.setOnClick(std::bind(&LikaWindow::onStopClick, this));
        dbLayout->dbClear.setOnClick(std::bind(&LikaWindow::onClearClick, this));
        dbLayout->dbBack.setOnClick(std::bind(&LikaWindow::onBackClick, this));
        while (workLayout.getWidgetCount() > 0)
        {
            workLayout.removeLast();
        }
        workLayout.append(*dbLayout);
    }

    void setupFactorialsLayout()
    {
        fcLayout = std::make_unique<FactorialsLayout>();
        fcLayout->fcGenerate.setOnClick(std::bind(&LikaWindow::onGenerateClick, this));
        fcLayout->fcGetIndex.setOnClick(std::bind(&LikaWindow::onGetByIndexClick, this));
        fcLayout->fcSearch.setOnClick(std::bind(&LikaWindow::onSearchClick, this));
        fcLayout->fcAuto.setOnClick(std::bind(&LikaWindow::onAutoClick, this));
        fcLayout->fcStop.setOnClick(std::bind(&LikaWindow::onStopClick, this));
        fcLayout->fcClear.setOnClick(std::bind(&LikaWindow::onClearClick, this));
        fcLayout->fcBack.setOnClick(std::bind(&LikaWindow::onBackClick, this));
        while (workLayout.getWidgetCount() > 0)
        {
            workLayout.removeLast();
        }
        workLayout.append(*fcLayout);
    }

    void onFibClick()
    {
        chooseLayout.setVisible(false);
        workLayout.setVisible(true);
        titleLabel.setText("FIBONACCI");
        currentGeneratorName = "Fibonacci";
        activeGenerator = 1;
        clearElements();

        int initial[] = {1, 1};
        lazySeq = std::make_unique<LazySequence<int>>(fibGenerator, initial, 2);
        setupFibonacciLayout();
    }

    void onSquareClick()
    {
        chooseLayout.setVisible(false);
        workLayout.setVisible(true);
        titleLabel.setText("SQUARES");
        currentGeneratorName = "Squares";
        activeGenerator = 2;
        clearElements();

        int initial[] = {1};
        lazySeq = std::make_unique<LazySequence<int>>(squareGenerator, initial, 1);
        setupSquaresLayout();
    }

    void onDoubleClick()
    {
        chooseLayout.setVisible(false);
        workLayout.setVisible(true);
        titleLabel.setText("DOUBLING");
        currentGeneratorName = "Doubling";
        activeGenerator = 3;
        clearElements();

        int initial[] = {1};
        lazySeq = std::make_unique<LazySequence<int>>(doubleGenerator, initial, 1);
        setupDoublingLayout();
    }

    void onFactClick()
    {
        chooseLayout.setVisible(false);
        workLayout.setVisible(true);
        titleLabel.setText("FACTORIALS");
        currentGeneratorName = "Factorials";
        activeGenerator = 4;
        clearElements();

        int initial[] = {1};
        lazySeq = std::make_unique<LazySequence<int>>(factorialGenerator, initial, 1);
        setupFactorialsLayout();
    }

    void onGenerateClick()
    {
        if (generatedCount >= MAX_ELEMENTS)
        {
            resultLabel.setText("Max elements");
            resultLabel.setVisible(true);
            return;
        }

        inputMode = true;
        inputType = 1;
        inputField.clear();
        inputField.setVisible(true);
        inputField.setFocused(true);
        resultLabel.setVisible(false);
    }

    void onGetByIndexClick()
    {
        inputMode = true;
        inputType = 2;
        inputField.clear();
        inputField.setVisible(true);
        inputField.setFocused(true);
        resultLabel.setVisible(false);
    }

    void onSearchClick()
    {
        inputMode = true;
        inputType = 3;
        inputField.clear();
        inputField.setVisible(true);
        inputField.setFocused(true);
        resultLabel.setVisible(false);
    }

    void onAutoClick()
    {
        if (generatedCount >= MAX_ELEMENTS)
        {
            resultLabel.setText("Max elements");
            resultLabel.setVisible(true);
            return;
        }

        isAutoGenerating = true;
        inputField.setVisible(false);
        resultLabel.setVisible(false);
    }

    void onStopClick()
    {
        isAutoGenerating = false;
        resultLabel.setText("Stop. Generated: " + std::to_string(generatedCount));
        resultLabel.setVisible(true);
    }

    void onClearClick()
    {
        isAutoGenerating = false;
        clearElements();
        resultLabel.setText("Cleared");
        resultLabel.setVisible(true);
    }

    void onBackClick()
    {
        isAutoGenerating = false;
        workLayout.setVisible(false);
        chooseLayout.setVisible(true);
        titleLabel.setText("LAZY SEQUENCE TESTER");
        inputField.setVisible(false);
        resultLabel.setVisible(false);
        inputMode = false;
        clearElements();
    }

    std::string formatNumber(int value)
    {
        if (value < 0)
        {
            return std::to_string(value);
        }
        if (value <= 9999)
        {
            return std::to_string(value);
        }

        double d = static_cast<double>(value);
        int exp = 0;
        while (d >= 1000.0)
        {
            d /= 1000.0;
            exp++;
        }

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << d;
        if (exp == 1)
        {
            ss << "k";
        }
        else if (exp == 2)
        {
            ss << "M";
        }
        else if (exp == 3)
        {
            ss << "G";
        }
        return ss.str();
    }

    void addElement(int value)
    {
        if (elementRows.empty())
        {
            elementRows.push_back(new HorizontalLayout(
                LayoutPositions::WORK_X, LayoutPositions::ELEM_Y, LayoutPositions::ELEM_GAP));
            currentRow = 0;
        }

        float nextX =
            LayoutPositions::WORK_X + (elementRows[currentRow]->getWidgetCount() + 1) *
                                          (ButtonSizes::ELEMENT_W + LayoutPositions::ELEM_GAP);

        if (nextX > Window::WIDTH - 50.0f)
        {
            float newY =
                LayoutPositions::ELEM_Y +
                (elementRows.size()) * (ButtonSizes::ELEMENT_H + LayoutPositions::ELEM_GAP);
            elementRows.push_back(
                new HorizontalLayout(LayoutPositions::WORK_X, newY, LayoutPositions::ELEM_GAP));
            currentRow = elementRows.size() - 1;
        }

        Button* elem =
            new Button(formatNumber(value), ButtonSizes::ELEMENT_W, ButtonSizes::ELEMENT_H);
        elem->setColor(Colors::ELEMENT);
        elementRows[currentRow]->append(*elem);
        generatedCount++;
    }

    void handleGenerateInput(int count)
    {
        if (count <= 0)
        {
            resultLabel.setText("INCORRECT NUMBER");
            resultLabel.setVisible(true);
            return;
        }

        if (count > MAX_ELEMENTS)
        {
            count = MAX_ELEMENTS;
        }

        int spaceLeft = MAX_ELEMENTS - generatedCount;
        if (count > spaceLeft)
        {
            count = spaceLeft;
        }

        if (count == 0)
        {
            resultLabel.setText("Max elements");
            resultLabel.setVisible(true);
            return;
        }

        int startIndex = generatedCount;
        int generated = 0;

        for (int i = 0; i < count; i++)
        {
            int index = startIndex + i;

            if (index >= MAX_INDEX)
            {
                resultLabel.setText("Limit reached : Generated: " + std::to_string(generated));
                resultLabel.setVisible(true);
                return;
            }

            int value = (*lazySeq).Get(index);

            if (index > 10 && value <= 0)
            {
                resultLabel.setText("Overflow at index " + std::to_string(index));
                resultLabel.setVisible(true);
                return;
            }

            addElement(value);
            generated++;
        }

        resultLabel.setText("Generated " + std::to_string(generated) + " elements");
        resultLabel.setVisible(true);
    }

    void handleGetByIndex(int index)
    {
        if (index < 0)
        {
            resultLabel.setText("Index must be >= 0");
            resultLabel.setVisible(true);
            return;
        }

        if (index >= MAX_INDEX)
        {
            resultLabel.setText("Index too large : Max: " + std::to_string(MAX_INDEX - 1));
            resultLabel.setVisible(true);
            return;
        }

        int value = (*lazySeq).Get(index);
        resultLabel.setText("[" + std::to_string(index) + "] = " + std::to_string(value));
        resultLabel.setVisible(true);
    }

    void handleSearchInput(int target)
    {
        int index = 0;
        bool found = false;

        while (index < MAX_INDEX)
        {
            int value = (*lazySeq).Get(index);

            if (value == target)
            {
                found = true;
                break;
            }

            if (index > 10 && value <= 0)
            {
                break;
            }
            index++;
        }

        if (found)
        {
            resultLabel.setText("Found " + std::to_string(target) + " at [" +
                                std::to_string(index) + "]");
        }
        else
        {
            resultLabel.setText(std::to_string(target) + " not found");
        }
        resultLabel.setVisible(true);
    }

   public:
    LikaWindow(size_t width, size_t height, const std::string& title)
    {
        window.create(
            sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}),
            title);

        if (!font.openFromFile("arial.ttf")) throw std::runtime_error("Failed NOT open");

        Widget::getDefaultFont() = font;

        titleLabel.setPosition(ElementPositions::TITLE_X, ElementPositions::TITLE_Y);
        inputField.setPosition(ElementPositions::INPUT_X, ElementPositions::INPUT_Y);
        resultLabel.setPosition(ElementPositions::RESULT_X, ElementPositions::RESULT_Y);
        inputField.setVisible(false);
        resultLabel.setVisible(false);

        chooseLayout.append(btnFib);
        chooseLayout.append(btnSquare);
        chooseLayout.append(btnDouble);
        chooseLayout.append(btnFact);

        btnFib.setOnClick(std::bind(&LikaWindow::onFibClick, this));
        btnSquare.setOnClick(std::bind(&LikaWindow::onSquareClick, this));
        btnDouble.setOnClick(std::bind(&LikaWindow::onDoubleClick, this));
        btnFact.setOnClick(std::bind(&LikaWindow::onFactClick, this));

        workLayout.setVisible(false);
    }

    void clearElements()
    {
        for (auto* row : elementRows)
        {
            while (row->getWidgetCount() > 0) row->removeLast();
            delete row;
        }
        elementRows.clear();
        currentRow = 0;
        generatedCount = 0;
    }

    void run()
    {
        sf::Clock autoClock;

        while (window.isOpen())
        {
            if (isAutoGenerating && lazySeq && generatedCount < MAX_ELEMENTS &&
                generatedCount < MAX_INDEX)
            {
                if (autoClock.getElapsedTime().asSeconds() > 0.5f)
                {
                    autoClock.restart();

                    int value = (*lazySeq).Get(generatedCount);

                    if (generatedCount > 10 && value <= 0)
                    {
                        isAutoGenerating = false;
                        resultLabel.setText("Overflow : " + std::to_string(generatedCount));
                        resultLabel.setVisible(true);
                    }
                    else
                    {
                        addElement(value);
                    }
                }
            }

            while (auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) window.close();

                bool handled = false;

                if (inputField.isVisible()) handled = inputField.handleEvent(*event);

                if (!handled && chooseLayout.handleEvent(*event)) handled = true;

                if (!handled && workLayout.handleEvent(*event)) handled = true;

                for (auto* row : elementRows)
                {
                    if (row->handleEvent(*event))
                    {
                        handled = true;
                        break;
                    }
                }

                if (inputMode && !inputField.isFocused() && !inputField.getInput().empty())
                {
                    int value = std::stoi(inputField.getInput());
                    inputField.clear();
                    inputField.setVisible(false);
                    inputMode = false;

                    if (inputType == 1)
                        handleGenerateInput(value);
                    else if (inputType == 2)
                        handleGetByIndex(value);
                    else if (inputType == 3)
                        handleSearchInput(value);

                    resultLabel.setVisible(true);
                }
            }

            window.clear(Colors::BACKGROUND);
            titleLabel.draw(window);
            chooseLayout.draw(window);
            workLayout.draw(window);

            for (auto* row : elementRows) row->draw(window);

            if (inputField.isVisible()) inputField.draw(window);
            if (resultLabel.isVisible()) resultLabel.draw(window);

            window.display();
        }
    }
};