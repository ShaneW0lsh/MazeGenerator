#include <Cell.h>

Cell::Cell(sf::RenderWindow* arg_window, sf::Vector2f arg_pos, uint32_t arg_size) { 
    m_window = arg_window;
    m_pos = arg_pos;
    m_size = arg_size;

	onInitVariables();
}

Cell::Cell() {};

void Cell::onInitVariables() { 
    m_walls = {true, true, true, true};

    m_bVisited = false;
}

void Cell::render() { 
//{{{
    sf::Vector2f st, ed;

    if (m_walls[0]) { //{{{
        st = sf::Vector2f(m_pos.x, m_pos.y);
        ed = sf::Vector2f(m_pos.x + m_size, m_pos.y);
        
        sf::Vertex f(st), s(ed);
        f.color = sf::Color::White;
        s.color = sf::Color::White;
		sf::Vertex wall[] =
		{
            f, s
		};

        m_window->draw(wall, 2, sf::Lines);
    } //}}} 
    if (m_walls[1]) { //{{{
        st = sf::Vector2f(m_pos.x + m_size, m_pos.y);
        ed = sf::Vector2f(m_pos.x + m_size, m_pos.y + m_size);

        sf::Vertex f(st), s(ed);
        f.color = sf::Color::White;
        s.color = sf::Color::White;
		sf::Vertex wall[] =
		{
            f, s
		};

        m_window->draw(wall, 2, sf::Lines);
    } //}}} 
    if (m_walls[2]) { //{{{
        st = sf::Vector2f(m_pos.x + m_size, m_pos.y + m_size);
        ed = sf::Vector2f(m_pos.x, m_pos.y + m_size);


        sf::Vertex f(st), s(ed);
        f.color = sf::Color::White;
        s.color = sf::Color::White;
		sf::Vertex wall[] =
		{
            f, s
		};


        m_window->draw(wall, 2, sf::Lines);
    } //}}}
    if (m_walls[3]) { //{{{
        st = sf::Vector2f(m_pos.x, m_pos.y + m_size);
        ed = sf::Vector2f(m_pos.x, m_pos.y);

        sf::Vertex f(st), s(ed);
        f.color = sf::Color::White;
        s.color = sf::Color::White;
		sf::Vertex wall[] =
		{
            f, s
		};

        m_window->draw(wall, 2, sf::Lines);
    } //}}}
} //}}}

void Cell::setWallState(uint16_t id, bool val) { 
    m_walls[id] = val;
}

bool Cell::getWallState(uint16_t id) { 
    return m_walls[id];
}

void Cell::setVisited(bool val) {
    m_bVisited = val;
}

bool Cell::getVisited() {
    return m_bVisited;
}
