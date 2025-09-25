#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;


Graph :: Graph ()
{
	return;
}

//copying. what I had bbefore 
//Previous one was for debugging 
void Graph::addMovie(string movieTitle, vector<string> actors) {
    Movie m;
    m.title = movieTitle;
    movies.insert(m);
    vector<shared_ptr<Actor>> a_vector;

    for (const string& a : actors) {
        shared_ptr<Actor> new_actor = make_shared<Actor>();
        new_actor->name = a;

        auto it = std::find_if(this->actors.begin(), this->actors.end(), 
            [&a](const Actor* actor) { return actor->name == a; });
        
        if (it != this->actors.end()) {
            new_actor = shared_ptr<Actor>(*it); // Use existing Actor*
        } else {
            this->actors.insert(new_actor.get());  // Insert new actor's raw pointer
        }

        a_vector.push_back(new_actor);
    }

    for (auto& a : a_vector) {
        m.m_actors.push_back(*a);
    }

    for (auto& a : a_vector) {
        for (auto& b : a_vector) {
            if (a->name != b->name) {
                a->neighbors[b->name] = m;
                b->neighbors[a->name] = m;
            }
        }
    }
}


void Graph :: printGraph()
{
	for (const auto& a : actors)
	{
		cout << a->name << "-->";
		for (auto& n : a->neighbors)
		{
			cout << n.first << " ";
		}
		cout << endl;
	}
}



//Pasting BFS function, that. I had before 
void Graph::BFS(string startStr, string endStr, ofstream& output) {
    if (startStr == endStr) {
        output << startStr << endl;
        return;
    }

    unordered_map<shared_ptr<Actor>, bool> visited;
    unordered_map<shared_ptr<Actor>, shared_ptr<Actor>> pred;

    auto s = this->actors.find(new Actor{startStr});
    auto e = this->actors.find(new Actor{endStr});
    
    if (s == this->actors.end() || e == this->actors.end()) {
        output << "Not present" << endl;
        return;
    }

    shared_ptr<Actor> startActor = shared_ptr<Actor>(*s);
    shared_ptr<Actor> endActor = shared_ptr<Actor>(*e);

    queue<shared_ptr<Actor>> q;
    q.push(startActor);
    visited[startActor] = true;

    bool pathFound = false;

    while (!q.empty()) {
        shared_ptr<Actor> current = q.front();
        q.pop();

        for (auto& n : current->neighbors) {
            auto neighborIt = this->actors.find(new Actor{n.first});
            if (neighborIt != this->actors.end()) {
                shared_ptr<Actor> neighborActor = shared_ptr<Actor>(*neighborIt);
                if (!visited[neighborActor]) {
                    visited[neighborActor] = true;
                    pred[neighborActor] = current;
                    q.push(neighborActor);
                    if (neighborActor->name == endStr) {
                        pathFound = true;
                        break;
                    }
                }
            }
        }
        if (pathFound) break;
    }

    if (!pathFound) {
        output << "Not present" << endl;
        return;
    }

    vector<shared_ptr<Actor>> path;
    shared_ptr<Actor> crawl = endActor;
    path.push_back(crawl);
    while (pred.find(crawl) != pred.end()) {
        crawl = pred[crawl];
        path.push_back(crawl);
    }

    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++) {
        if (i != 0) {
            output << "-(" << path[i-1]->neighbors[path[i]->name].title << ")-";
        }
        output << path[i]->name;
    }
    output << endl;
}
