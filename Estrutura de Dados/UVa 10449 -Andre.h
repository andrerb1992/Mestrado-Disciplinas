/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 14 de Maio de 2018, 08:25
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <math.h>
#include<stdio.h>
#include <valarray>



#define INF 9999999

using namespace std;

/*
 * 
 */

int distancia[INF];

typedef struct {
    int verticeA;
    int verticeB;
    int peso;
    int flag;
} node;

int main(int argc, char** argv) {

    int numero_vertices;

    int pergunta;
    int qtd_perguntas, qtd_ligacao;
    int qtd_perguntas1=1;
    cin>>numero_vertices;
    cout << "numero_vertices: " << numero_vertices << endl;
    node no[numero_vertices];

    for (int i = 1; i <= numero_vertices; i++) {
        cin >> no[i].flag;
        cout << "flag: " << no[i].flag << endl;
    }
    cin>>qtd_ligacao;
    cout << "quantidade de ligação: " << qtd_ligacao << endl;

    for (int i = 1; i <= qtd_ligacao; i++) {
        cin >> no[i].verticeA >> no[i].verticeB;
        no[i].peso = (no[no[i].verticeB].flag - no[no[i].verticeA].flag)*(no[no[i].verticeB].flag - no[no[i].verticeA].flag)*(no[no[i].verticeB].flag - no[no[i].verticeA].flag);
        cout << "A: " << no[i].verticeA << "B: " << no[i].verticeB << "flag: " << no[i].peso << endl;
    }
    //bellman ford
    for (int i = 1; i <= numero_vertices; i++) {
        distancia[i] = INF;
    }
    distancia[1] = 0;

    for (int i = 1; i <= numero_vertices - 1; i++) {
        for (int j = 1; j <= qtd_ligacao; j++) {
            if (distancia[no[j].verticeA] + no[j].peso < distancia[no[j].verticeB])
                distancia[no[j].verticeB] = distancia[no[j].verticeA] + no[j].peso; //min
        }
    }
    //cout << "RRWRWRW  " << distancia[3] << endl;

    vector<int>ss,ff;
    for (int j = 1; j <= numero_vertices; ++j)
        if (distancia[no[j].verticeA] + no[j].peso < distancia[no[j].verticeB]){
            ss.push_back(no[j].verticeA);
            ff.push_back(no[j].verticeB);
        }

    for (int i=1;i<=ss.size();++i){
        distancia[ss[i] ]=-INF;
        distancia[ff[i] ]=-INF;
    }
    
   for (int i = 1; i <= numero_vertices - 1; i++) {
        for (int j = 1; j <= qtd_ligacao; j++) {
            if (distancia[no[j].verticeA] + no[j].peso < distancia[no[j].verticeB])
                distancia[no[j].verticeB] = distancia[no[j].verticeA] + no[j].peso;
        }
    }

    cin>>qtd_perguntas;
    cout << "Set #" << qtd_perguntas1 << endl;
    for (int j = 1; j <= qtd_perguntas; j++) {
        cin>>pergunta;
        //cout<<pergunta<<endl;
        if (distancia[pergunta] < 3 || distancia[pergunta] > INF)
            cout << "?" << endl;
        else
            cout << distancia[pergunta] << endl;
    }

    return 0;
}

