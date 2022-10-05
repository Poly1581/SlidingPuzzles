#include <vector>
using std::vector;


//		MATRIX DEFINITION FOR STORING BOARD STATE
#define matrix vector<vector<int>>

//		POSITION STRUCT FOR KEEPING TRACK OF AND ADDING POSITIONS
struct position {
	int row = 0;
	int col = 0;
	friend bool operator==(const position& a, const position& b) {
		return (a.row == b.row) && (a.col == b.col);
	}
	position operator+(const position& d) {
		position p;
		p.row = this->row + d.row;
		p.col = this->col + d.col;
		return p;
	}
};

const position UP = {-1,0};
const position RIGHT = {0,1};
const position DOWN = {1,0};
const position LEFT = {0,-1};

struct game{
	int size = 0;
	matrix board = {{}};
	position emptySpace = {0,0};
	friend bool operator==(const game& a, const game& b) {
		return (a.size == b.size) && (a.board == b.board);
	}
};



int main() {

}