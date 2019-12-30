//
//  main.cpp
//  Graph
//
//  Created by Haider Ali on 12/27/19.
//  Copyright © 2019 Haider Ali. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class Node{
public:
    int vertex;
    int distance;
    Node* next;
    
    Node(){
        next = nullptr;
    }
};

class LinkList{
public:
    Node* first;
     Node* last;
    
    LinkList(){
        first = nullptr;
    }
    void insert(int v, int d){
        Node *temp = new Node();
        temp->distance = d;
        temp->vertex = v;
        if (first == nullptr) {
            first = temp;
            last = temp;
        }
        else{
            last->next = temp;
            last = temp;
        }
    }
};

class Graph{
    
    string provinces[6] = {"Gilgit Baltistan", "Punjab", "Sindh", "KPK", "Balochistan", "Kashmir"};
    Node* adjacencyList[6] = {};
    
public:
    Graph(){
        LinkList* l[6] = {};
        
        for (int i=0; i<6; i++) {
            l[i] = new LinkList();
            switch (i) {
                    case 0:
                // Gilgit Neighbour Provinces
                    l[0]->insert(3, 285);
                    l[0]->insert(5, 268);
                    break;
                    
                    case 1:
                    //Punjab Neighbour Provinces
                    l[1]->insert(2, 885);
                    l[1]->insert(3, 597);
                    l[1]->insert(4, 1200);
                    l[1]->insert(5, 314);
                    break;
                    
                    case 2:
                    //Sindh Neighbour Provinces
                    l[2]->insert(1, 885);
                    l[2]->insert(4,780);
                    break;
                    
                    case 3:
                    //KPK Neighbour Provinces
                    l[3]->insert(4, 1328);
                    l[3]->insert(1, 597);
                    l[3]->insert(5, 411);
                    l[3]->insert(0, 285);
                    break;
                    
                    case 4:
                    //Balochistan Neighbour Provinces
                    l[4]->insert(1, 1200);
                    l[4]->insert(2, 780);
                    l[4]->insert(3, 1328);
                    break;
                    
                    case 5:
                    //Kashmir Neighbour Provinces
                    l[5]->insert(1, 314);
                    l[5]->insert(0, 268);
                    l[5]->insert(3, 411);
                    break;
                default:
                    break;
            }
            adjacencyList[i] = l[i]->first;
        }
    
    }
    
    void dijkstra(int v){
           stack<int> s;
           bool* visited = new bool[6];
           distNode* distance = new distNode[6];
           distance[v].distance = 0;
           
           for(int i=0; i<6; i++){
               visited[i] = false;
           }
           
           
           for (int i=0; i<5; i++) {
               int minVertex = findMinVertex(distance, visited);
               visited[minVertex] = true;
               Node* t = adjacencyList[minVertex];
               
               while (t != nullptr) {
                   
                   if (!visited[t->vertex]) {
                       int dist = distance[minVertex].distance + cost(minVertex, t->vertex);
                       if (dist < distance[t->vertex].distance) {
                           distance[t->vertex].distance = dist;
                           distance[t->vertex].pv = minVertex;
                       }
                   }
                   t = t->next;
               }
           }
           
           for (int i=0; i<6; i++) {
               if (v != i) {
                   cout<<provinces[v]<<" To ";
                   int pv = distance[i].pv;
                   while (pv != v) {
                       s.push(pv);
                       pv = distance[pv].pv;
                   }
                   while (!s.empty()) {
                       cout<<provinces[s.top()]<<" To ";
                       s.pop();
                   }
                   cout<<provinces[i]<<" "<<distance[i].distance<<endl;
               }
           }
       }
    
    int cost(int v1, int v2){
        Node* t = adjacencyList[v1];
        while (t!=nullptr) {
            if (t->vertex == v2) {
                return t->distance;
            }
            t = t->next;
        }
        return -1;
    }
    
    class distNode{
       public:
           int pv;
           int distance;
           
           distNode(){
               pv = -1;
               distance = INT_MAX;
           }
       };
       
       
       int findMinVertex(distNode* distance, bool* visited){
           
           int minIndex = -1;
           for (int i=0; i<6; i++) {
               if (!visited[i] && (minIndex == -1 || distance[i].distance < distance[minIndex].distance)) {
                   minIndex = i;
               }
           }
           return minIndex;
       }
    
//    void distance() {
//        for (int i=0; i<6; i++) {
//            Node* t = adjacencyList[i];
//            while (t!=nullptr) {
//                cout<<provinces[i]<<" To "<<provinces[t->vertex]<<" "<<t->distance<<" KM"<<endl;
//                t = t->next;
//            }
//        }
//    }
//    void BFS_Traversal(int v){
//        bool *visited = new bool[6];
//        queue<int> q;
//        q.push(v);
//
//        for (int i=0; i<6; i++) {
//            visited[i] = false;
//        }
//
//        while (!q.empty()) {
//            v = q.front();
//            cout<< provinces[v] <<" ";
//            visited[v] = true;
//            q.pop();
//
//            Node* t = adjacencyList[v];
//            while (t != nullptr) {
//                if (!visited[t->vertex]) {
//                    visited[t->vertex] = true;
//                    q.push(t->vertex);
//                }
//                t = t->next;
//            }
//        }
//    }
//
//    bool detect_cycle(int v){
////        bool *visited = new bool[6];
//        int *flag = new int[6];
//        queue<int> q;
//        q.push(v);
//
//        for (int i=0; i<6; i++) {
////            visited[i] = false;
//            flag[i] = -1;
//        }
//
//        while (!q.empty()) {
//            v = q.front();
//            cout<< provinces[v] <<" ";
////            visited[v] = true;
//            flag[v] = 1;
//            q.pop();
//
//            Node* t = adjacencyList[v];
//            while (t != nullptr) {
//                if (flag[v] == -1) {
//                    flag[t->vertex] = 0;
//                    q.push(t->vertex);
//
//                }
//                if (flag[v] == 0) {
//                    return true;
//                }
//                t = t->next;
//            }
//        }
//        return false;
//    }
//
//    void DFS_Traversal(int v){
//        bool *visited = new bool[6];
//        stack<int> s;
//        s.push(v);
//
//        for (int i=0; i<6; i++) {
//            visited[i] = false;
//        }
//        visited[v] = true;
//
//
//        while (!s.empty()) {
//            v = s.top();
//
//            bool unvisited_found = false;
//
//            Node* t = adjacencyList[v];
//            while (t != nullptr && !unvisited_found) {
//
//                if (!visited[t->vertex]) {
//                    s.push(t->vertex);
//                    visited[t->vertex] = true;
//                    unvisited_found = true; // To break loop
//                }
//                t = t->next;
//            }
//            if (!unvisited_found) {
//                cout<<provinces[s.top()]<<" ";
//                s.pop();
//            }
//        }
//    }
//
   
   
};

int main(int argc, const char * argv[]) {
    Graph *g = new Graph();
    g->dijkstra(0);
}
