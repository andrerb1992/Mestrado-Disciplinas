/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 
 *
 * Created on 23 de Abril de 2018, 08:33
 */

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define MAXWORDS 200

struct elemq {
    int node;
    int dist;

    elemq(int node, int dist) {
        this->node = node;
        this->dist = dist;
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    int casos_teste;
    cin >> casos_teste;
    int dist = 0;
    int marcador = 0;

    for (int num_caso = 0; num_caso < casos_teste; num_caso++) {
        string dic;
        map<string, int> str;
        int num_words = 0;
        while (cin >> dic, dic != "*")
            str[dic] = num_words++;
        getline(cin, dic);

        array<vector<int>, MAXWORDS> graph;

        for (auto it1 = str.begin(); it1 != str.end(); it1++) {
            for (auto it2 = str.begin(); it2 != str.end(); it2++) {
                const string w1 = it1->first;
                const string w2 = it2->first;
                int diff_chars = 0;

                if (w1.size() == w2.size()) {
                    diff_chars = 0;
                    for (int k = 0; k < w1.size(); k++) {
                        if (w1[k] != w2[k]) {
                            diff_chars++;
                        }
                    }
                    if (diff_chars == 1) {
                        graph[it1->second].push_back(it2->second);
                    }
                }

            }
        }

        while (true) {
            string linha;
            getline(cin, linha);
            if (linha == "")
                break;
            istringstream slinha(linha);
            string from_word, to_word;
            slinha >> from_word >> to_word;

            // BFS
            int from_n = str[from_word];
            int to_n = str[to_word];

            queue<elemq> q;
            q.push(elemq(from_n, 0));
            set<int>visited;
            int distancia;
            while (q.size() > 0) {
                elemq e = q.front();
                q.pop();
                distancia = e.dist;
                if (e.node == to_n)
                    break;
                visited.insert(e.node);
                int total = graph[e.node].size();
                for (int t = 0; t < total; t++) {
                    if (!visited.count(graph[e.node][t])) {
                        //visited.insert(graph[e.node][t]);
                        q.push(elemq(graph[e.node][t], e.dist+1));
                    }

                }
                
            }
            cout<<from_word<<" "<< to_word<<" "<< distancia<<endl;

        }
        if(num_caso!=casos_teste-1) cout<<endl;

    }
    return 0;
}