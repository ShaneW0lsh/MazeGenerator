#include <Engine.h>

Engine::Engine() { 
    onInitVariables();
    onCreateWindow();
	onCreateCells();
}

Engine::~Engine() {

}

void Engine::run() { 
    while (getRunning()) { 
        onUpdate();
        onRender();
    }
}

void Engine::onCreateWindow() { 
    m_cs.antialiasingLevel = 6;
    m_window = new sf::RenderWindow(m_vidMode, "Maze Generator", 
									sf::Style::Close, m_cs);
    m_window->setVerticalSyncEnabled(true);
}

void Engine::onInitVariables() {
	m_vidMode = sf::VideoMode(900, 900);
	m_cellSize = 20;

	m_rowCellQuantity = m_vidMode.width / m_cellSize;
	m_totalCellQuantity = m_vidMode.width / m_cellSize
		* m_vidMode.width / m_cellSize;

    m_cellContainer.assign(m_rowCellQuantity, std::vector<Cell>(m_rowCellQuantity));

    std::srand(std::time(nullptr));
}

const bool Engine::getRunning() {
    return m_window->isOpen();
}

void Engine::onEventPolling() {
    while (m_window->pollEvent(m_ev)) {
        switch (m_ev.type) { 
            case sf::Event::Closed:
                m_window->close();
                break;
        }
    }
}

void Engine::onCreateCells() { 
    Cell tmp(m_window, sf::Vector2f(0, 0), m_cellSize);
    tmp.setVisited(true);

    m_cellContainer[0][0] = tmp;
    m_cellStack.push(tmp);

    for (int i = 0; i < m_rowCellQuantity; ++i) {
        for (int u = 1; u < m_rowCellQuantity; ++u) {
            sf::Vector2f pos(u*m_cellSize, i*m_cellSize);

            Cell tmpCell(m_window, pos, m_cellSize);
            m_cellContainer[i][u] = tmpCell;
            m_cellStack.push(tmpCell);
			std::cerr << tmpCell.getVisited() << '\n';
        }
    }
}

void Engine::onRenderCells() {
    for (int i = 0; i < m_cellContainer.size(); ++i) {
        for (int u = 0; u < m_cellContainer.size(); ++u) {
            m_cellContainer[i][u].render();
        }
    }
}

void Engine::onUpdateCurrentCell() { 
    if (!m_cellStack.empty()) {
        Cell currentCell = m_cellStack.pop();

        std::vector<sf::Vector2f> neighbours =
            checkNeightbours(currentCell);

        cerr << neighbours.size() << '\n';
        cerr <<"Number of neighbours :" << neighbours << '\n';

        uint16_t rd_n = rand() % neighbours.size();
        cerr <<"rd_n :" << rd_n << '\n';

        //onRemoveWallsBetween( 
        // don't forget how to solve this, use references, pointers, etc...

        neighbours[rd_n].setVisited(true);
        m_cellStack.push(neighbours[rd_n]);
    }
}

void Engine::onUpdate() {
    onEventPolling();
}

void Engine::onRender() { 
    m_window->clear(sf::Color(120, 120, 119));

    onRenderCells();

    m_window->display();
}
