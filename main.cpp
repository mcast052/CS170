/* 

Melissa Castillo, mcast052
861157259 
CS170 WINTER17, Project 1: 
8-Puzzle using 
1. Uniform Cost Search
2. A* w/ Manhattan Distance Heuristic
3. A* w/ Missing Tile Heuristic

*/

#include <iostream> 
#include <vector> 
#include <queue> 
#include <utility>
#include <sstream>
#include <functional> 
#include <algorithm> 
#include <cmath> 

using namespace std; 

//Comparator for priority queue
class Node {
	public: 
	Node* parent; 
	int f_n; 
	int g_n; 
	int h_n; 
	int heuristic; 
	vector< vector<int> > curr_state; 
	pair<int, int> curr_blank_index; 
	
	//Constructor 
	Node(Node* p, int cost, vector< vector<int> > c_state, pair<int, int> c_b_i, int h) 
		: parent(p), g_n(cost), curr_state(c_state), curr_blank_index(c_b_i), heuristic(h) 
	{ 
		calcFn(); 
	}; 
	
	void calcFn() { 
		if(heuristic == 1) { h_n = 0; }
		else if(heuristic == 2) { 
			h_n = 0; 
			int numToCheck = 1; 
			for(unsigned int x = 0; x < 3; x++) {
				for(unsigned int y = 0; y < 3; y++) { 
					if(numToCheck < 9 && curr_state.at(x).at(y) != numToCheck) { h_n++; }
					numToCheck++; 
				}
			} 
		} 
		else if(heuristic == 3) {
			h_n = 0; 
			int numToCheck = 1;
			
			for(unsigned x = 0; x < 3; x++) { 
				for(unsigned y = 0; y < 3; y++) {
					
					int currNum = curr_state.at(x).at(y);
					int tmp = 0; 
					//cout << currNum << endl; 
					
					
					if(currNum != numToCheck) { 
						cout << "Coordinate: " << x << ", " << y << endl; 
						if(currNum == 1) { tmp = x + y; } 
						else if(currNum == 2) { tmp = x + abs( (int)(1 - y) ); } 
						else if(currNum == 3) { tmp = x + abs( (int)(2 - y) ); } 
						else if(currNum == 4) { tmp = abs( (int)(1 - x) ) + y; }
						else if(currNum == 5) { tmp = abs( (int)(1 - x) ) + abs( (int)(1 - y) ); }
						else if(currNum == 6) { tmp = abs( (int)(1 - x) ) + abs( (int)(2 - y) ); }
						else if(currNum == 7) { tmp = abs( (int)(2 - x ) ) + y; }
						else if(currNum == 8) { tmp = abs( (int)(2 - x) ) + abs( (int)(1 - y) ); }
						else { tmp = 0; } 
						cout << "currNum: " << currNum << endl; 
						cout << "Distance: " << tmp << endl; 
						h_n += tmp;
					} 
					numToCheck++; 
				} 
			} 
			
		}
		f_n = g_n + h_n; 
		return; 
	} 
	
	vector<Node*> createChildren(vector<Node*> f, vector<Node*> e) { 
		vector<Node*> children;
		
		//Check which operators are possible to do
		int x = this->curr_blank_index.first; 
		int y = this->curr_blank_index.second; 
		Node* child; 
		bool check = true; 
		
		
		if(x < 2) { //down
			int x = curr_blank_index.first + 1; 
			int y = curr_blank_index.second;
			pair<int, int> index(x, y); 
			child = new Node(this, g_n + 1, operationAction(x, y), index, heuristic); 
			
			for(unsigned int i = 0; i < f.size(); i++) { 
				if(f.at(i)->curr_state == child->curr_state) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < e.size(); j++) {	
				if(e.at(j)->curr_state == child->curr_state) {check = false; break; } 
			}
			if(check) { 
				cout << "f_n = " << child->f_n << endl; 
				children.push_back(child); 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
						//cout << "(" << x << ", " << y << ")";
					} 
					cout << endl; 
				}
			}
				
		} 
		
		check = true; 
		if(x > 0) { //up
			int x = curr_blank_index.first - 1; 
			int y = curr_blank_index.second;
			pair<int, int> index(x, y); 
			child = new Node(this, g_n + 1, operationAction(x, y), index, heuristic); 
			
			for(unsigned int i = 0; i < f.size(); i++) { 
				if(f.at(i)->curr_state == child->curr_state) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < e.size(); j++) {	
				if(e.at(j)->curr_state == child->curr_state) {check = false; break; } 
			}
			if(check) { 
				cout << "f_n = " << child->f_n << endl; 
				children.push_back(child); 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
						//cout << "(" << x << ", " << y << ")";
					} 
					cout << endl; 
				}
			}
		}
		
		check = true; 
		if(y < 2) { //right
			int x = curr_blank_index.first; 
			int y = curr_blank_index.second + 1;
			pair<int, int> index(x, y); 
			child = new Node(this, g_n + 1, operationAction(x, y), index, heuristic); 
			
			for(unsigned int i = 0; i < f.size(); i++) { 
				if(f.at(i)->curr_state == child->curr_state) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < e.size(); j++) {	
				if(e.at(j)->curr_state == child->curr_state) {check = false; break; } 
			}
			if(check) { 
				children.push_back(child); 
				cout << "f_n = " << child->f_n << endl; 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
						//cout << "(" << x << ", " << y << ")";
					} 
					cout << endl; 
				}
			}
		}
		
		check = true; 	
		if(y > 0) { //left 
			int x = curr_blank_index.first; 
			int y = curr_blank_index.second - 1;
			pair<int, int> index(x, y); 
			child = new Node(this, g_n + 1, operationAction(x, y), index, heuristic); 
			
			for(unsigned int i = 0; i < f.size(); i++) { 
				if(f.at(i)->curr_state == child->curr_state) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < e.size(); j++) {	
				if(e.at(j)->curr_state == child->curr_state) {check = false; break; } 
			}
			if(check) { 
				children.push_back(child); 
				cout << "f_n = " << child->f_n << endl;
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
					} 
					cout << endl; 
				}
			}
		}
		
		cout << "NUM CHILDREN: " << children.size() << endl; 
		return children; 
	} 
	
	vector< vector<int> > operationAction(const int x, const int y) {

		pair<int, int> new_blank(x, y); 
		int tmp = this->curr_state.at(x).at(y); 
		
		vector< vector<int> > new_state = this->curr_state; 
		new_state.at(x).at(y) = 0; 
		new_state.at(this->curr_blank_index.first).at(this->curr_blank_index.second) = tmp; 
		
		return new_state;
	}

	
	bool goalTest(const vector< vector<int> > goal) { 
		return this->curr_state == goal; 
	} 
}; 

struct Compare : public std::binary_function<Node*, Node*, bool> { 
	bool operator() (const Node* a, const Node* b) const { 
		return a->f_n > b->f_n; 
	} 
}; 

class Problem { 
	public: 
	vector< vector<int> > initial_state; 
	const vector< vector<int> > goal_state{ {1, 2, 3},
									        {4, 5, 6}, 
									        {7, 8, 0} };
	pair<int, int> blank_index;
	int heuristic; 
	
	Problem(vector< vector <int> > init_state, int heuristicFunc, pair<int, int> index) 
		: initial_state(init_state), heuristic(heuristicFunc), blank_index(index)
	{ } 

}; 


void GRAPH_SEARCH(Problem prob) { 
	priority_queue<Node*, vector<Node*>, Compare> frontier;  
	vector<Node*> explored;
	vector<Node*> frontierCheck; 
	
	Node* init = new Node(NULL, 0, prob.initial_state, prob.blank_index, prob.heuristic); 
	frontier.push(init); //frontier has only initial state
	frontierCheck.push_back(init); 
	
	long maxFrontierSize = frontier.size(); 
	long maxExploredSize = explored.size(); 
	
	while(!frontier.empty()) {
		
		Node* tmp = frontier.top();
		frontier.pop(); 
		cout << "The best state to expand is..." << endl; 
		for(unsigned int x = 0; x < 3; x++) { 
			for(unsigned int y = 0; y <3; y++) { 
			cout << tmp->curr_state.at(x).at(y) << " ";
			} 
			cout << endl; 
		}
		cout << endl;
		
		if(tmp->g_n > 31) {cout << "PAST DEPTH 31" << endl; return;}
		if(tmp->goalTest(prob.goal_state)) { 
			cout << "FINISHED:" << endl; 
			cout << "Max Frontier size: " << maxFrontierSize << endl;
			cout << "Final Frontier size: " << frontier.size() << endl; 
			cout << "Explored size: " << maxExploredSize << endl; 
			cout << "Depth: " << tmp->g_n << endl; 
			return; 
		} 
		
		explored.push_back(tmp); 
		
		/*vector<Node*> children = tmp->createChildren(frontierCheck, explored); 
		for(unsigned int i = 0; i < children.size(); i++) { 
			frontier.push(children.at(i));
			frontierCheck.push_back(children.at(i)); 
		}*/
		
		const int x = tmp->curr_blank_index.first; 
		const int y = tmp->curr_blank_index.second; 
		Node* child; 
		vector< vector<int> > tmpState; 
		bool check = true; 
		
		
		if(x < 2) { //down
			pair<int, int> index(x + 1, y);
			tmpState = tmp->operationAction(x + 1, y); 

			for(unsigned int i = 0; i < frontierCheck.size(); i++) { 
				if(frontierCheck.at(i)->curr_state == tmpState) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < explored.size(); j++) {	
				if(explored.at(j)->curr_state == tmpState) {check = false; break; } 
			}
			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic); 
				cout << "f_n = " << child->f_n << endl; 
				frontier.push(child);
				frontierCheck.push_back(child); 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
					} 
					cout << endl; 
				}
			}
				
		} 
		
		check = true; tmpState.clear(); 
		if(x > 0) { //up
			pair<int, int> index(x - 1, y); 
			tmpState = tmp->operationAction(x - 1, y); 
			
			for(unsigned int i = 0; i < frontierCheck.size(); i++) { 
				if(frontierCheck.at(i)->curr_state == tmpState) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < explored.size(); j++) {	
				if(explored.at(j)->curr_state == tmpState) {check = false; break; } 
			}
			if(check) { 
				cout << "f_n = " << child->f_n << endl; 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic); 
			
				frontier.push(child); 
				frontierCheck.push_back(child); 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
					} 
					cout << endl; 
				}
			}
		}
		
		check = true; tmpState.clear(); 
		if(y < 2) { //right
			pair<int, int> index(x, y + 1); 
			tmpState = tmp->operationAction(x, y + 1); 

			for(unsigned int i = 0; i < frontierCheck.size(); i++) { 
				if(frontierCheck.at(i)->curr_state == tmpState) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < explored.size(); j++) {	
				if(explored.at(j)->curr_state == tmpState) {check = false; break; } 
			}
			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic); 

				frontier.push(child); 
				frontierCheck.push_back(child); 
				cout << "f_n = " << child->f_n << endl; 
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
					} 
					cout << endl; 
				}
			}
		}
		
		check = true; tmpState.clear(); 
		if(y > 0) { //left 
			pair<int, int> index(x, y - 1); 
			tmpState = tmp->operationAction(x, y - 1); 
			
			for(unsigned int i = 0; i < frontierCheck.size(); i++) { 
				if(frontierCheck.at(i)->curr_state == tmpState) { check = false; break; } 
			} 
			for(unsigned int j = 0; j < explored.size(); j++) {	
				if(explored.at(j)->curr_state == tmpState) {check = false; break; } 
			}
			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic); 
				frontier.push(child); 
				frontierCheck.push_back(child); 
				cout << "f_n = " << child->f_n << endl;
				for(unsigned int x = 0; x < 3; x++) { 
					for(unsigned int y = 0; y <3; y++) { 
						cout << child->curr_state.at(x).at(y) << " ";
					} 
					cout << endl; 
				}
			}
		}
		
		
		maxFrontierSize = max(maxFrontierSize, (long)frontier.size()); 
		maxExploredSize = max(maxExploredSize, (long)explored.size()); 
	}

	cout << "Failed to find solution" << endl; 
	return; 
} 


int main() { 

	vector< vector<int> > initial_state; 
	int puzzle_type = 0;  
	pair<int, int> blank_index; 
	
	cout << "Welcome to 861157259's 8-puzzle solver." << endl; 
	cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl; 
	cin >> puzzle_type;
	
	if(puzzle_type == 1) { 
		vector<int> tmp1{1, 2, 3}; 
		vector<int> tmp2{4, 8, 0}; 
		vector<int> tmp3{7, 6, 5}; 
		
		initial_state.push_back(tmp1); 
		initial_state.push_back(tmp2); 
		initial_state.push_back(tmp3); 
		
		blank_index.first = 1; 
		blank_index.second = 2; 
	} 
	else if(puzzle_type == 2) { 
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		cout << "Enter the first row, use space or tabs between numbers" << endl; 
		int input;
		vector<int> tmp; 
		for(unsigned int i = 0; i < 3; i++) {
			cin >> input; 
			if(input == 0) { blank_index.first = 0; blank_index.second = i; } 
			tmp.push_back(input); 
		} 
		initial_state.push_back(tmp); 
		
		cout << "Enter the second row, use space or tabs between numbers" << endl; 
		tmp.clear(); 
		for(unsigned int i = 0; i < 3; i++) {  
			cin >> input; 
			if(input == 0) { blank_index.first = 1; blank_index.second = i; } 
			tmp.push_back(input); 
		} 
		initial_state.push_back(tmp); 
		
		cout << "Enter the third row, use space or tabs between numbers" << endl; 
		tmp.clear(); 
		for(unsigned int i = 0; i < 3; i++) {
			cin >> input; 
			if(input == 0) { blank_index.first = 2; blank_index.second = i; } 
			tmp.push_back(input); 
		} 
		initial_state.push_back(tmp); 
	} 
	
	int alg_choice; 
	cout << "Enter your choice of algorithm \n 1. Uniform Cost Search \n 2. A* with the Misplaced Tile heurisitc. \n 3. A* with the Manhattan distance heuristic." << endl; 
	cin >> alg_choice; 
	
	Problem prob(initial_state, alg_choice, blank_index); 
	GRAPH_SEARCH(prob); 
	
	return 0; 	
} 