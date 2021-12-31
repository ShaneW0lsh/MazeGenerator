#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Cell { 
public:
    Cell(sf::RenderWindow* arg_window, 
        sf::Vector2f arg_pos, uint32_t arg_size);
	Cell();

    void render();
	static const uint8_t m_WALL_NUM = 4;

    void setWallState(uint16_t id, bool val);
    bool getWallState(uint16_t id);

    void setVisited(bool val);
    bool getVisited();

private:
    sf::RenderWindow* m_window;

    uint32_t m_size;
    sf::Vector2f m_pos;

    bool m_bVisited;

    std::vector<bool> m_walls;

    void onInitVariables();
};
