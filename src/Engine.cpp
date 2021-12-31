#include <Engine.h>

Engine::Engine() { 
    onInitVariables();
    onCreateWindow();
	onCreateCells();
    onMazeGenerate();
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
	m_cellSize = 45;

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
	for (int i = 0; i < m_rowCellQuantity; ++i) {
        for (int u = 0; u < m_rowCellQuantity; ++u) {
            sf::Vector2f pos(u*m_cellSize, i*m_cellSize);
			Cell tmpCell(m_window, pos, m_cellSize);
        
			if (i == 0 && u == 0) {
				tmpCell.setVisited(true);
				m_cellStack.push(tmpCell);
			}

			m_cellContainer[i][u] = tmpCell;
           // m_cellStack.push(tmpCell);
			std::cerr << "is visited: " << tmpCell.getVisited() << '\n';
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

//gets called from onUpdateCurrentCell
//
//there is a mistake
const std::vector<Cell*> Engine::onCheckNeighbours(Cell& c) {
    std::vector<Cell*> nb;

    int cx = (int)c.getPos().x / m_cellSize;
	int cy = (int)c.getPos().y / m_cellSize;
	std::cerr << "cx: " << cx << ' ' << "cy: " << cy << '\n';

    //top row
    if (cy == 0) { 
        //{{{ 
		std::cerr << "m_rowCellQuantity: " << m_rowCellQuantity << '\n';
        if (cx == 0) { 
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
        }
        else if (cx != 0 && cx != m_rowCellQuantity-1) {
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
        }
        else { 
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
        }
    } ///}}}
    //bottom row
    else if (cy == m_rowCellQuantity-1) {
        //{{{
        if (cx == 0) {
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
        }
        else if (cx == m_rowCellQuantity-1) {
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx-1][cy]);
            }
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
        }
        else {
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx-1][cy]);
            }
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
        }
    } //}}}
    //middle row
    else { 
        //{{{
        if (cx == 0) {
			std::cerr << cx << ' ' << cy - 1 << '\n';
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
        }
        else if (cx == m_rowCellQuantity-1) {
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx-1][cy]);
            }
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
        }
        else { 
            if (!m_cellContainer[cx][cy-1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy-1]);
            }
            if (!m_cellContainer[cx+1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx+1][cy]);
            }
            if (!m_cellContainer[cx][cy+1].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx][cy+1]);
            }
            if (!m_cellContainer[cx-1][cy].getVisited()) {
                std::cerr << "an nb was found!\n"; 
                nb.push_back(&m_cellContainer[cx-1][cy]);
            }
        }
    } //}}}
        
	std::cerr << nb.size() << '\n';
    return nb;
}

void Engine::onRemoveWallsBetween(Cell& f, Cell& s) {
    //on the right
    if (f.getPos().x > s.getPos().x) {
        f.setWallState(3, false);
        s.setWallState(1, false);
    }

    //on the left
    else if (f.getPos().x < s.getPos().x) { 
        f.setWallState(1, false);
        s.setWallState(3, false);
    }

    //lower
    else if (f.getPos().y > s.getPos().y) {
        f.setWallState(0, false);
        s.setWallState(2, false);
    }

    //above
    else if (f.getPos().y < s.getPos().y) {
        f.setWallState(2, false);
        s.setWallState(0, false);
    }
}

/* void Engine::onUpdateCurrentCell() { */ 
/* } */

void Engine::onMazeGenerate() { 
	while (!m_cellStack.empty()) {
        // Place where a bug can occur easily, because of pointer syntax
		Cell* currentCell = &(m_cellStack.top());
		m_cellStack.pop();

        // it might be better to do this in the Cell class somewhere
        sf::RectangleShape cShape(sf::Vector2f(m_cellSize, m_cellSize));
        cShape.setPosition(sf::Vector2f(currentCell->getPos().x, currentCell->getPos().y));
        cShape.setFillColor(sf::Color::Red);

        m_window->draw(cShape);

		// A strange moment here, take your time in the 
		// future to make sure you understan r/lvalues
        const std::vector<Cell*>& nb =
            onCheckNeighbours(*currentCell);

        std::cerr <<"Number of neighbours :" << nb.size() << '\n';

        if (nb.size() > 0) {
            uint16_t rd_n = rand() % nb.size();
            std::cerr <<"rd_n :" << rd_n << '\n';

            onRemoveWallsBetween(*currentCell, *nb[rd_n]);

            nb[rd_n]->setVisited(true);
            m_cellStack.push(*nb[rd_n]);
        }
		m_window->clear(sf::Color(120, 120, 119));
		m_window->display();
    }
    std::cerr << "Finished maze generation\n";
}

void Engine::onUpdate() {
    onEventPolling();
}

void Engine::onRender() { 
    m_window->clear(sf::Color(120, 120, 119));

    onRenderCells();

    m_window->display();
}
