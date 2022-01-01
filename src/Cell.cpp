#include <Cell.h>

Cell::Cell(sf::Vector2f arg_pos, uint32_t arg_size) { 
    m_pos = arg_pos;
    m_size = arg_size;

	onInitVariables();
}

Cell::Cell() {};

void Cell::onInitVariables() { 
    m_walls = new bool[4];
    m_walls[0] = true;
    m_walls[1] = true;
    m_walls[2] = true;
    m_walls[3] = true;

    m_bVisited = false;
    m_bCurrent = false;
}

void Cell::render(sf::RenderWindow* arg_window) { 
//{{{
    if (m_bCurrent) { 
		std::cerr << "YEAh it defenitely is a current cell!\n";
        sf::RectangleShape c(sf::Vector2f(m_size, m_size));
        c.setPosition(m_pos.x, m_pos.y);
        c.setFillColor(sf::Color::Red);
        arg_window->draw(c);
    }

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

        arg_window->draw(wall, 2, sf::Lines);
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

		arg_window->draw(wall, 2, sf::Lines);
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


		arg_window->draw(wall, 2, sf::Lines);
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

		arg_window->draw(wall, 2, sf::Lines);
    } //}}}
} //}}}

void Cell::setWallState(uint16_t id, bool val) { 
	if (id > 3) {
		std::cerr << "Index is too big\n";
		return;
	}
	std::cerr << "value: " << val << '\n'; ///
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

bool Cell::getCurrent() {
    return m_bCurrent;
}

void Cell::setCurrent(bool val) {
	m_bCurrent = val;
}

sf::Vector2f Cell::getPos() {
    return m_pos;
}
