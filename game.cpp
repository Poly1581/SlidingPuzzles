#include "game.hpp"
#include <cmath>
using std::abs;
#include <cstdlib>
using std::rand;


//		INITIALIZE ALL GAMES TO SOLVED STATE
game::game(int size) {
	this->size = size;
	for(int row = 0; row < size; row++) {
		board.push_back({});
		for(int col = 0; col < size; col++) {
			board.back().push_back((size*row)+col+1);
		}
	}
	emptySpace = {size-1, size-1};
	board.at(emptySpace.row).at(emptySpace.col) = 0;
}

void game::display(void) { 
	for(int row = 0; row < board.size(); row++) {
		for(int col = 0; col < board.size(); col++) {
			cout << board.at(row).at(col) << "\t";
		}
		cout << endl << endl;
	}
	cout << endl << endl;
};

vector<position> game::getValidMoves(void) {
	vector<position> moves = {};
	if(-1 < emptySpace+UP && emptySpace+UP < size) {
		moves.push_back(UP);
	}
	if(-1 < emptySpace+RIGHT && emptySpace+RIGHT < size) {
		moves.push_back(RIGHT);
	}
	if(-1 < emptySpace+DOWN && emptySpace+DOWN < size) {
		moves.push_back(DOWN);
	}
	if(-1 < emptySpace+LEFT && emptySpace+LEFT < size) {
		moves.push_back(LEFT);
	}
	return moves;
};

void game::applyMove(position& move) {
	position newEmptySpace = emptySpace+move;
	board.at(emptySpace.row).at(emptySpace.col) = board.at(newEmptySpace.row).at(newEmptySpace.col);
	emptySpace = newEmptySpace;
	board.at(emptySpace.row).at(emptySpace.col) = 0;
}

game game::getChild(position& move) {
	game child = *this;
	child.applyMove(move);
	child.depth++;
	return child;
}

vector<game> game::getChildren(void) {
	vector<game> children = {};
	vector<position> moves = getValidMoves();
	for(position move:moves) {
		children.push_back(getChild(move));
	}
	return children;
}

position game::find(int tile) {
	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			if(board.at(row).at(col) == tile) {
				position found = {row,col};
				return found;
			}
		}
	}
	position notFound = {-1,-1};
	return notFound;
}

string game::getHash(void) {
	string hash = "";
	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			hash+= board.at(row).at(col);
			hash+= "*";
		}
	}
	return hash;
}

void game::randomize(void) {
	for(int r = 0; r < 4*size*size; r++) {
		vector<position> moves = getValidMoves();
		applyMove(moves.at(rand()%moves.size()));
	}
}

int game::uniformCost(game& compGame) {
	return 0;
}

int game::misplacedTile(game& compGame) {
	int misplacedTileCount = 0;
	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			if(board.at(row).at(col) != 0) {
				if(board.at(row).at(col) != compGame.board.at(row).at(col)) {
					misplacedTileCount++;
				}
			}
		}
	}
	return misplacedTileCount;
}

int game::manhattanDistance(game& compGame) {
	int totalManhattanDistance = 0;
	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			if(board.at(row).at(col) != 0) {
				position found = compGame.find(board.at(row).at(col));
				int drow = abs(row-found.row);
				int dcol = abs(col-found.col);
				totalManhattanDistance+= drow+dcol;
			}
		}
	}
	return totalManhattanDistance;
}