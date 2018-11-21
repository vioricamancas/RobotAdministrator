/*
Copyright Mancas Viorica 311CA
Tema1 SD 2018
*/
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include "Deque.h"
#include "Stack.h"

#define e(i, j) std::get<j>(i)  // gets elem on pos j of tuple named i

#define tuple_type std::tuple<int, int, int, int, int>
#define stack_type Stack<std::tuple<std::string, tuple_type> >
#define out_ref std::ofstream&

typedef Deque<tuple_type> robot;

int ** read(int *n, int *lin, int *col, std::ifstream& f) {
	f >> *n >> *lin >> *col;
	// progressively allocates new elements
	int **A = new int*[*lin];
	for(int i = 0; i < *lin; i++)
		A[i] = new int[*col];
	for(int i = 0; i < *lin; i++)
		for(int j = 0; j < *col; j++)
			f >> A[i][j];
	// returns pointer so it can be deleted later
	return A;
}

void ADD_GET_BOX(robot* bots, tuple_type t, int time) {
	int id = e(t, 0), priority = e(t, 4);
	e(t, 0) = 1;  // type of command
	e(t, 4) = time;
	if (!priority){
		bots[id].push_front(t);
	} else {
		bots[id].push_back(t);
	}
}

void ADD_DROP_BOX(robot* bots, tuple_type t, int time) {
	int id = e(t, 0), priority = e(t, 4);
	e(t, 0) = 0;  // type of command
	e(t, 4) = time;
	if (!priority) {
		bots[id].push_front(t);
	} else {
		bots[id].push_back(t);
	}
}

void PRINT_COMMANDS(out_ref g, int id, robot *bots) {
	if (bots[id].isEmpty()) {
		g << "No command found\n";
	} else {
		g << id << ":";
		tuple_type t;
		// iterates the queue
		for (int i = 0; i < bots[id].size()-1; i++) {
			t = bots[id].pop_front();
			if (e(t, 0))
				g << " GET ";
			else
				g << " DROP ";
			g << e(t, 1) << " " << e(t, 2) << " " << e(t, 3) << ";";
			bots[id].push_back(t);
		}
		// last element has a different type of ending character
		// new line instead of ';'
		t = bots[id].pop_front();
		if (e(t, 0))
			g << " GET ";
		else
			g << " DROP ";
		g << e(t, 1) << " " << e(t, 2) << " " << e(t, 3) << "\n";
		bots[id].push_back(t);
	}
}

void EXECUTE(out_ref g, int **A, robot *bots, int *boxes_carried,
	  int id, stack_type * done, stack_type * exec, int time) {
	if (bots[id].isEmpty()){
		g << "EXECUTE: No command to execute\n";
	} else {
		tuple_type t = bots[id].pop_front();
		// removes top element
		int aux = e(t, 4);  // time
		e(t, 4) = id;
		done->push(std::forward_as_tuple("EXECUTE", t));
		e(t, 4) = time - aux;
		// last parameter becomes the time it has stayed in the queue
		if (e(t, 0)) {  // GET
				// nr_box > A[x][y]
			if(e(t, 3) > A[e(t, 1)][e(t, 2)]) {  // exception
				e(t, 3) = A[e(t, 1)][e(t, 2)];
			}
			// updating the map and the array of boxes
			A[e(t, 1)][e(t, 2)] -= e(t, 3);  // A[x][y] -= nr_box
			boxes_carried[id] += e(t, 3);
			e(t, 0) = id;
			exec->push(std::forward_as_tuple("GET", t));

		} else {  // DROP
			if (e(t, 3) > boxes_carried[id])  // exception
				e(t, 3) = boxes_carried[id];
			// updating the map and the array of boxes
			A[e(t, 1)][e(t, 2)] += e(t, 3);  // A[x][y] += nr_box
			boxes_carried[id] -= e(t, 3);
			e(t, 0) = id;
			exec->push(std::forward_as_tuple("DROP", t));
		}
	}
}

void UNDO(out_ref g, int **A, int *boxes_carried, robot *bots,
	  stack_type * done, stack_type *exec, int time) {
	std::tuple<std::string, tuple_type> aux;
	tuple_type t;
	if (!done->isEmpty()) {
		aux = done->pop();  // removes top element of stack done
		t = e(aux, 1);  // gets second element of pair aux
		if (e(aux, 0) == "EXECUTE") {
			if (!exec->isEmpty()) {
				aux = exec->pop();  // removes top element of stack done
				t = e(aux, 1);  // gets second element of pair aux
				int id = e(t, 0);  // keeps id
				e(t, 4) = time;  // resets time
				if (e(aux, 0) == "GET") {
					// resets map and boxes
					A[e(t, 1)][e(t, 2)] += e(t, 3);  // A[x][y] += nr_box
					boxes_carried[id] -= e(t, 3);
					e(t, 0) = 1;  // sets command type
				} else {  // DROP
					// resets map and boxes
					A[e(t, 1)][e(t, 2)] -= e(t, 3);  // A[x][y] -= nr_box
					boxes_carried[id] += e(t, 3);
					e(t, 0) = 0;  // sets command type
				}
				bots[id].push_front(t);  // inserts command back into queue
			}
		} else {
			if (!bots[e(t, 0)].isEmpty()) {
				// checks if command has not yet been removed
				if (e(t, 4))  // priority = 1
					bots[e(t, 0)].pop_back();  // bots[id]
				else
					bots[e(t, 0)].pop_front();  // bots[id]
			}
		}
	}
	else
		g << "UNDO: No history\n";
}

void LAST_EXECUTED_COMMAND(out_ref g, robot *bots, stack_type *exec) {
	if (!exec->isEmpty()) {
		std::tuple<std::string, tuple_type> aux;
		aux = exec->peek();
		tuple_type t = e(aux, 1);  // gets second element of pair aux
		g << e(t, 0) << ": " << e(aux, 0) << " ";  // command id and type
		g << e(t, 1) << " " << e(t, 2) << " " << e(t, 3) << "\n";
		// x, y, nr_box
	} else {
		g << "No command was executed\n";
	}
}

void HOW_MUCH_TIME(out_ref g, stack_type *exec) {
	if (!exec->isEmpty()) {
		std::tuple<std::string, tuple_type> aux;
		aux = exec->peek();
		g << e(e(aux, 1), 4) << "\n";  // time
		// last element of second element (tuple) of aux
	} else {
		g << "No command was executed\n";
	}
}

void HOW_MANY_BOXES(out_ref g, int *boxes_carried, int id) {
	g << boxes_carried[id] << "\n";  // returns number of boxes
}

int main() {
	int n, lin, col, **A,  // input data
	id,  // id of a robot
	*boxes_carried,  // array of numbers of boxes carried by each robot
	time = 0;  // array of time passed
	std::tuple<int, int, int, int, int> t;  // group of 5 integer elements
	std::string cmd;  // command name
	robot *bots;  // array of deues
	stack_type exec,  // stack of executed comands
	done;  // stack of cmds that can be undone

	std::ifstream f;  // input file
	f.open("robots.in");
	std::ofstream g;  // ouput file
	g.open("robots.out");

	A = read(&n, &lin, &col, f);  // function allocates memory
	bots = new robot[n];
	boxes_carried = new int[n];
	for (int i = 0; i < n; ++i)
		boxes_carried[i] = 0;  // initialisation

	f >> cmd;  // scans first command separately
	while(!f.eof()) {
		time++;  // increases time
		if (cmd == "UNDO"){
			UNDO(g, A, boxes_carried, bots, &done, &exec, time);
		}
		if (cmd == "EXECUTE") {
			f >> id;
			EXECUTE(g, A, bots, boxes_carried, id, &done, &exec, time);
			}
		if (cmd == "ADD_GET_BOX") {
			//     id          x          y  	   nr_box   priority
			f >> e(t, 0) >> e(t, 1) >> e(t, 2) >> e(t, 3) >> e(t, 4);
			ADD_GET_BOX(bots, t, time);
			done.push(std::make_tuple("ADD", t));
		}
		if (cmd == "ADD_DROP_BOX") {
			f >> e(t, 0) >> e(t, 1) >> e(t, 2) >> e(t, 3) >> e(t, 4);
			ADD_DROP_BOX(bots, t, time);
			done.push(std::make_tuple("DROP", t));
		}
		if (cmd == "PRINT_COMMANDS") {
			g << cmd + ": ";
			f >> id;
			PRINT_COMMANDS(g, id, bots);
		}
		if (cmd == "LAST_EXECUTED_COMMAND") {
			g << cmd + ": ";
			LAST_EXECUTED_COMMAND(g, bots, &exec);
		}
		if (cmd == "HOW_MUCH_TIME") {
			g << cmd + ": ";
			HOW_MUCH_TIME(g, &exec);
		}
		if (cmd == "HOW_MANY_BOXES") {
			g << cmd + ": ";
			f >> id;
			HOW_MANY_BOXES(g, boxes_carried, id);
		}
		f >> cmd;  // scans next command
	}  // endwhile
	f.close();
	g.close();
	// deallocating
	while(!exec.isEmpty())
		exec.pop();
	while(!done.isEmpty())
		done.pop();
	for(int i = 0; i < n; i++)
		while(!bots[i].isEmpty())
			bots[i].pop_front();
	delete[] bots;
	delete[] boxes_carried;
	for(int i = 0; i < lin; i++)
		delete[] A[i];
	delete[] A;
	return 0;
}
