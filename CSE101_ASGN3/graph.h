#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <functional>
#include <iostream> // Include this for std::cerr and std::endl

using namespace std;

class Movie;
class Actor;

class Movie {
public:
    string title;
    vector<Actor> m_actors;
    bool operator< (const Movie & other) const {
        return (title < other.title);
    }
};

template<>
struct std::hash<Movie> {
    std::size_t operator()(Movie const& m) const noexcept {
        return std::hash<std::string>{}(m.title);
    }
};

class Actor {
public:
    string name;
    unordered_map<string, Movie> neighbors;
    bool operator< (const Actor & other) const {
        return (name < other.name);
    }
};

template<>
struct std::hash<Actor> {
    std::size_t operator()(Actor const& a) const noexcept {
        return std::hash<std::string>{}(a.name);
    }
};

struct actorptrcmp {
    bool operator()(const Actor* lhs, const Actor* rhs) const {
        if (!lhs || !rhs) {
            std::cerr << "Null pointer detected: lhs=" << lhs << ", rhs=" << rhs << std::endl;
            return lhs < rhs;  // Handle the null pointer case gracefully
        }
        return lhs->name < rhs->name;
    }
};

class Graph {
private:
    set<Movie> movies;
    set<Actor*, actorptrcmp> actors;
public:
    Graph();
    void addMovie(string, vector<string>);
    void printGraph();
    void BFS(string, string, ofstream&);
};

#endif // GRAPH_H
