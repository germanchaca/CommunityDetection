#pragma once

#ifndef COMMUNITY_DETECTION_GRAPH_H
#define COMMUNITY_DETECTION_GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <ctime>
#include <queue>
#include <math.h>
#include <string>
#include <bitset>
#include "Helper.h"
#include "string.h"

using namespace std;

#define STEP_LENGTH 2
#define EDGE_ENDPOINT_NUMBER 2
#define BEGIN_POINT 0
#define END_POINT 1
#define PRECISE 0.0000001
#define DEFAULT_WINDOWS_SIZE 10
#define DEFAULT_SUPPORT 0.7

struct EdgeKey {
    int iBegin;
    int iEnd;

    bool operator<(const EdgeKey &right) const {
        if (iBegin == right.iBegin) {
            return iEnd < right.iEnd;
        }

        return iBegin < right.iBegin;
    }
};

struct EdgeValue {
    bitset<32> * bDeltaWindow;
    int iNewestDeltaIndex;
    static int iWindowSize ;

    double dWeight;
    double aDistance[STEP_LENGTH];
    set<int> *pCommonNeighbours;
    set<int> *pExclusiveNeighbours[EDGE_ENDPOINT_NUMBER];

    EdgeValue():  iNewestDeltaIndex(0), bDeltaWindow(nullptr) {}

    void addNewDelta2Window(double &dDelta);
    static void initWindowSize(int iSize);
};


struct VertexValue
{
    set<int>* pNeighbours;
    double aWeightSum[STEP_LENGTH];
};

class Graph {
private:
    map<EdgeKey, EdgeValue*> m_dictEdges;
    map<int, VertexValue*> m_dictVertices;

private:
    void AddVertex(int iBegin, int iEnd);
    void ClearVertices();
    void ClearEdges();

public:

    bool AddEdge(int iBegin, int iEnd, double dWeight, EdgeValue* &pNewEdgeValue);
    void UpdateEdge(int iBegin, int iEnd, double dNewDistance, int iStep);
    double Distance(int iBegin, int iEnd, int iStep);
    double Weight(int iBegin, int iEnd);
    double GetVertexWeightSum(int iVertexId, int iStep);
    void AddVertexWeight(int iVertexId, double dWeight, int iStep);
    void ClearVertexWeight(int iStep);
    map<int, set<int>* >* FindAllConnectedComponents();
    map<EdgeKey, EdgeValue*>* GetAllEdges();
    set<int>* GetVertexNeighbours(int iVertexId);

    ~Graph();

    static void RefineEdgeKey(int& iBegin, int& iEnd);
};

#endif