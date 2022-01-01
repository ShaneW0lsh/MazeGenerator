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
	m_cellSize = 45;

    m_isGenerating = true;

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
			Cell tmpCell(pos, m_cellSize);
        
			if (i == 0 && u == 0) {
				tmpCell.setVisited(true);
				tmpCell.setCurrent(true);
				m_cellStack.push(tmpCell);
			}

			m_cellContainer[i][u] = tmpCell;
           // m_cellStack.push(tmpCell);
        }
    }
}

void Engine::onRenderCells() {
    for (int i = 0; i < m_cellContainer.size(); ++i) {
        for (int u = 0; u < m_cellContainer.size(); ++u) {
			m_cellContainer[i][u].render(m_window);
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

/* void Engine::onMazeGenerate() { */ 
/* 	/1* while (!m_cellStack.empty()) { *1/ */
/*         /1* // Place where a bug can occur easily, because of pointer syntax *1/ */
/* 	/1* 	Cell* currentCell = &(m_cellStack.top()); *1/ */
/* 	/1* 	m_cellStack.pop(); *1/ */

/*         /1* // it might be better to do this in the Cell class somewhere *1/ */
/*         /1* sf::RectangleShape cShape(sf::Vector2f(m_cellSize, m_cellSize)); *1/ */
/*         /1* cShape.setPosition(sf::Vector2f(currentCell->getPos().x, currentCell->getPos().y)); *1/ */
/*         /1* cShape.setFillColor(sf::Color::Red); *1/ */

/*         /1* m_window->draw(cShape); *1/ */

/* 	/1* 	// A strange moment here, take your time in the *1/ */ 
/* 	/1* 	// future to make sure you understan r/lvalues *1/ */
/*         /1* const std::vector<Cell*>& nb = *1/ */
/*             /1* onCheckNeighbours(*currentCell); *1/ */

/*         /1* std::cerr <<"Number of neighbours :" << nb.size() << '\n'; *1/ */

/*         /1* if (nb.size() > 0) { *1/ */
/*             /1* uint16_t rd_n = rand() % nb.size(); *1/ */
/*             /1* std::cerr <<"rd_n :" << rd_n << '\n'; *1/ */

/*             /1* onRemoveWallsBetween(*currentCell, *nb[rd_n]); *1/ */

/*             /1* nb[rd_n]->setVisited(true); *1/ */
/*             /1* m_cellStack.push(*(nb[rd_n])); *1/ */
/*         /1* } *1/ */
/* 		//m_window->clear(sf::Color(120, 120, 119)); */
/* 		/1* onRenderCells(); *1/ */
/* 		/1* m_window->display(); *1/ */
/*     } */
/*     std::cerr << "Finished maze generation\n"; */
/* } */



void Engine::step() { 
    if (!m_cellStack.empty()) { 
        // Place where a bug can occur easily, because of pointer syntax
		Cell* currentCell = &(m_cellStack.top());
		currentCell->setCurrent(true);
		m_cellStack.pop();


        /* // it might be better to do this in the Cell class somewhere */
        /* sf::RectangleShape cShape(sf::Vector2f(m_cellSize, m_cellSize)); */
        /* cShape.setPosition(sf::Vector2f(currentCell->getPos().x, currentCell->getPos().y)); */
        /* cShape.setFillColor(sf::Color::Red); */

        /* m_window->draw(cShape); */

		// A strange moment here, take your time in the 
		// future to make sure you understan r/lvalues
        const std::vector<Cell*>& nb =
            onCheckNeighbours(*currentCell);

        std::cerr <<"Number of neighbours :" << nb.size() << '\n';

        if (nb.size() > 0) {
            uint16_t rd_n = rand() % nb.size();

            onRemoveWallsBetween(*currentCell, *nb[rd_n]);

            nb[rd_n]->setVisited(true);
            m_cellStack.push(*(nb[rd_n]));
        }
    // the code above 
    } else {
        std::cerr << "Finished generating!\n";
		m_isGenerating = false;
    }
}

void Engine::onUpdate() {
    onEventPolling();

    if (m_isGenerating) {
        step();
    }
}

void Engine::onRender() { 
    m_window->clear(sf::Color(120, 120, 119));

    onRenderCells();

    m_window->display();
}
