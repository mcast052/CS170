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
#include <unordered_map>
#include <stack> 

using namespace std; 

class Node {
	public: 
	Node* parent; 
	int f_n; 
	int g_n; 
	int h_n; 
	int heuristic; 
	string key; 
	vector< vector<int> > curr_state; 
	pair<int, int> curr_blank_index; 
	
	//Constructor 
	Node(Node* p, int cost, vector< vector<int> > c_state, pair<int, int> c_b_i, int h, string k) 
		: parent(p), g_n(cost), curr_state(c_state), curr_blank_index(c_b_i), heuristic(h), key(k) 
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
					
					
					if(currNum != numToCheck) { 
						if(currNum == 1) { tmp = x + y; } 
						else if(currNum == 2) { tmp = x + abs( (int)(1 - y) ); } 
						else if(currNum == 3) { tmp = x + abs( (int)(2 - y) ); } 
						else if(currNum == 4) { tmp = abs( (int)(1 - x) ) + y; }
						else if(currNum == 5) { tmp = abs( (int)(1 - x) ) + abs( (int)(1 - y) ); }
						else if(currNum == 6) { tmp = abs( (int)(1 - x) ) + abs( (int)(2 - y) ); }
						else if(currNum == 7) { tmp = abs( (int)(2 - x ) ) + y; }
						else if(currNum == 8) { tmp = abs( (int)(2 - x) ) + abs( (int)(1 - y) ); }
						else { tmp = 0; } 
						h_n += tmp;
					} 
					numToCheck++; 
				} 
			} 
			
		}
		f_n = g_n + h_n; 
		return; 
	} 
	
	vector< vector<int> > operationAction(const int x, const int y) {

		pair<int, int> new_blank(x, y); 
		int tmp = this->curr_state.at(x).at(y); 
		
		vector< vector<int> > new_state = this->curr_state; 
		new_state.at(x).at(y) = 0; 
		new_state.at(this->curr_blank_index.first).at(this->curr_blank_index.second) = tmp; 
		
		return new_state;
	}
}; 

//Comparator for the priority queue
struct Compare { 
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

//Generates keys for the unordered map, changing 2D vectors into a string
string keyGen(vector< vector<int> > v) { 
	string key; 
	
	for(unsigned int x = 0; x < 3; x++) { 
		for(unsigned int y = 0; y < 3; y++) { 
			key += to_string(v.at(x).at(y)); 
		} 
	} 
	return key; 
} 

void displayPath(Node* g) { 
	cout << "The solution path is: " << endl; 
	Node* curr = g; 
	stack<Node*> path; 
	while(curr != NULL) { 
		path.push(curr); 
		curr = curr->parent; 
	} 
	
	while(path.size() > 0) { 
		for(unsigned int x = 0; x < 3; x++) { 
			for(unsigned int y = 0; y < 3; y++) { 
				cout << path.top()->curr_state.at(x).at(y) << " "; 
			} 
			cout << endl; 
		} 
		cout << endl; 
		path.pop(); 
	} 
} 

void GRAPH_SEARCH(Problem prob) { 
	priority_queue<Node*, vector<Node*>, Compare> frontier;  

	unordered_map<string, bool> explored; 
	
	string key = keyGen(prob.initial_state); 
	Node* init = new Node(NULL, 0, prob.initial_state, prob.blank_index, prob.heuristic, key); 
	frontier.push(init); //frontier has only initial state
	
	
	explored.insert(make_pair(key, false)); 
	long maxFrontierSize = frontier.size(); 
	
	while(!frontier.empty()) {
		
		Node* tmp = frontier.top();
		frontier.pop(); 
		cout << "The best state to expand with a g(n) = " << tmp->g_n << " and h(n) = " << tmp->h_n << "..." << endl; 
		for(unsigned int x = 0; x < 3; x++) { 
			for(unsigned int y = 0; y <3; y++) { 
			cout << tmp->curr_state.at(x).at(y) << " ";
			} 
			cout << endl; 
		}
		cout << endl;
		
		if(tmp->curr_state == prob.goal_state) {
			int exploredSize = 0; 
			for(auto it = explored.begin(); it != explored.end(); it++) { 
				if(it->second == true) { exploredSize++; }
			} 
	
			cout << "GOAL!!" << endl; 
			cout << "To solve this problem the search algorithm expanded a total of " << exploredSize << " nodes." << endl; 
			cout << "The maximum number of nodes in the queue at any one time was " << maxFrontierSize << endl; 
			cout << "The depth of the goal node was " << tmp->g_n << endl << endl << endl; 
			
			displayPath(tmp); 
			return; 
		} 
		
		explored.at(tmp->key) = true; 
		
		const int x = tmp->curr_blank_index.first; 
		const int y = tmp->curr_blank_index.second; 
		Node* child; 
		vector< vector<int> > tmpState; 
		bool check = true; 
		
		if(x < 2) { //down
			pair<int, int> index(x + 1, y);
			tmpState = tmp->operationAction(x + 1, y); 
			string key = keyGen(tmpState); 

			if(explored.find(key) != explored.end()) { check = false; } 

			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic, key);
				
				explored.insert(make_pair(key, false));  
				frontier.push(child);
			}
				
		} 
		
		check = true; tmpState.clear(); 
		if(x > 0) { //up
			pair<int, int> index(x - 1, y); 
			tmpState = tmp->operationAction(x - 1, y); 
			string key = keyGen(tmpState); 
			
			if(explored.find(key) != explored.end()) {check = false;} 
			
			if(check) {  
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic, key); 
			
				explored.insert(make_pair(key, false)); 
				frontier.push(child); 
				
			}
		}
		
		check = true; tmpState.clear(); 
		if(y < 2) { //right
			pair<int, int> index(x, y + 1); 
			tmpState = tmp->operationAction(x, y + 1); 
			string key = keyGen(tmpState); 

			if(explored.find(key) != explored.end()) { check = false; } 
			
			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic, key); 
				explored.insert(make_pair(key, false)); 
				frontier.push(child);
			}
		}
		
		check = true; tmpState.clear(); 
		if(y > 0) { //left 
			pair<int, int> index(x, y - 1); 
			tmpState = tmp->operationAction(x, y - 1); 
			string key = keyGen(tmpState); 
			
			if(explored.find(key) != explored.end()) { check = false; } 
			
			if(check) { 
				child = new Node(tmp, tmp->g_n + 1, tmpState, index, tmp->heuristic, key); 
				explored.insert(make_pair(key, false)); 
				frontier.push(child); 
			}
		}
		
		maxFrontierSize = max(maxFrontierSize, (long)frontier.size()); 
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