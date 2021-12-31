#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Cell.h>

#include <iostream>
#include <ctime>
#include <vector>
#include <stack>

class Engine {
public:
    Engine();
    ~Engine();

	void run();

private:
    sf::RenderWindow* m_window;
    sf::ContextSettings m_cs;
    sf::VideoMode m_vidMode;
    sf::Event m_ev;

    uint32_t m_cellSize; 
    uint32_t m_rowCellQuantity;
    uint32_t m_totalCellQuantity;

    //references are a must here
    std::vector<std::vector<Cell>> m_cellContainer;
    std::stack<Cell> m_cellStack;

    void onCreateWindow();
    void onInitVariables();
    const bool getRunning();

    void onEventPolling();

	void onCreateCells();
    void onRenderCells();

    void onUpdate();
    void onRender();
};
