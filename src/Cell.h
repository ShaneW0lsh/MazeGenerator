#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Cell { 
public:
    Cell(sf::Vector2f arg_pos, uint32_t arg_size);
	Cell();

    void render(sf::RenderWindow* arg_window);
	static const uint8_t m_WALL_NUM = 4;

    void setWallState(uint16_t id, bool val);
    bool getWallState(uint16_t id);

    void setVisited(bool val);
    bool getVisited();
    
    bool getCurrent();
    void setCurrent(bool val);

    sf::Vector2f getPos();

private:
    uint32_t m_size;
    sf::Vector2f m_pos;

    bool m_bVisited;
    bool m_bCurrent;

    //std::vector<bool> m_walls;
	bool* m_walls;

    void onInitVariables();
};
