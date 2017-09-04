/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

void GraphTools::graphLabeler(Graph &graph)
{
    std::queue<Vertex> q_var;
    Vertex start = graph.getStartingVertex(); //gets the starting vertex of the graph
//----------------------------------------------------------------------------//  
    q_var.push(start);
    //std::cout << graph.getVertexName(start) << std::endl;

    while(!q_var.empty())
    {
        Vertex temp_vrtx = q_var.front();
        q_var.pop();

        //std::cout << graph.getVertexName(temp_vrtx) << std::endl;

        vector<Vertex> vect_var = graph.getAdjacent(temp_vrtx);
        graph.setVertexLabel(temp_vrtx, "UNEXPLORED");
        for(size_t i = 0; i < vect_var.size(); i++)
        {

            //std::cout << graph.getVertexName(vect_var[i]) << std::endl;
            string vrtx_label = graph.getVertexLabel(vect_var[i]); //vertex label getLabel(w)
            string edge_label = graph.getEdgeLabel(temp_vrtx, vect_var[i]);

            //std::cout << "1." << vrtx_label << std::endl;
            //std::cout << "2." << edge_label << std::endl;
            if(vrtx_label != "UNEXPLORED")
            {
                graph.setEdgeLabel(temp_vrtx, vect_var[i], "UNEXPLORED"); //setLabel(v,w, DISCOVERY)
                graph.setVertexLabel(vect_var[i], "UNEXPLORED");//setLabel(w, VISITED)
                q_var.push(vect_var[i]);// enqueue
                //std::cout << "Pushing happened " << i << std::endl;
            }
            else
            {
                if(edge_label != "UNEXPLORED")
                {
                    graph.setEdgeLabel(temp_vrtx, vect_var[i], "UNEXPLORED");
                }
            }
        }
    }
}
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    GraphTools::graphLabeler(graph);
//----------------------------------------------------------------------------//    
    Vertex ret_vrtxA;
    Vertex ret_vrtxB;
    int ret_val;
    std::queue<Vertex> q_var;
    Vertex start;
//----------------------------------------------------------------------------//
    
    ret_val = 10000;
    start = graph.getStartingVertex(); //gets the starting vertex of the graph
    q_var.push(start);
//----------------------------------------------------------------------------//  
    while(!q_var.empty())
    {
        Vertex temp_vrtx = q_var.front();
        q_var.pop();
        graph.setVertexLabel(temp_vrtx, "VISITED");
        vector<Vertex> vect_var = graph.getAdjacent(temp_vrtx);
        for(size_t i = 0; i < vect_var.size(); i++)
        {
            string vrtx_label = graph.getVertexLabel(vect_var[i]); //vertex label getLabel(w)
            string edge_label = graph.getEdgeLabel(temp_vrtx, vect_var[i]);
            if(vrtx_label == "UNEXPLORED")
            {
                graph.setEdgeLabel(temp_vrtx, vect_var[i], "DISCOVERY"); //setLabel(v,w, DISCOVERY)
                graph.setVertexLabel(vect_var[i], "VISITED");//setLabel(w, VISITED)
                q_var.push(vect_var[i]);// enqueue
                if(ret_val > graph.getEdgeWeight(temp_vrtx, vect_var[i]))
                {
                    ret_val = graph.getEdgeWeight(temp_vrtx, vect_var[i]);
                    std::cout << ret_val << std::endl;
                    ret_vrtxA = temp_vrtx;
                    ret_vrtxB = vect_var[i];
                }
            }
            else
            {
                if(edge_label == "UNEXPLORED")
                {
                    graph.setEdgeLabel(temp_vrtx, vect_var[i], "CROSS");
                    if(ret_val > graph.getEdgeWeight(temp_vrtx, vect_var[i]))
                    {
                        ret_val = graph.getEdgeWeight(temp_vrtx, vect_var[i]);
                        ret_vrtxA = temp_vrtx;
                        ret_vrtxB = vect_var[i];
                    }
                }
            }
        }
    }
    graph.setEdgeLabel(ret_vrtxA, ret_vrtxB, "MIN");
    return ret_val;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    GraphTools::graphLabeler(graph);
//----------------------------------------------------------------------------//
    Vertex temp_vrtx;
    Vertex curr_vrtx;

    vector<Vertex> vect_start;
    vector<Vertex> vrtx_curr;
    vector<Vertex> vrtx_temp;
    vector<Vertex> vrtx_ret;

    std::queue<Vertex> que_vrtx;

    std::unordered_map<Vertex, vector<Vertex>> map_vrtx;

    bool check = true;
//----------------------------------------------------------------------------//
    vect_start.push_back(start); // push back the start value to a vector
    map_vrtx[start] = vect_start; // key = START, value to vector of vertices

    que_vrtx.push(start); //push the start vertex into queue
//----------------------------------------------------------------------------//
    while(!que_vrtx.empty() && check)//while keeps going untill you are out of vertex or hit END
    {
        curr_vrtx = que_vrtx.front(); //get the first value of queue
        que_vrtx.pop(); //pop that value we just found 

        graph.setVertexLabel(curr_vrtx, "VISITED"); //mark that value visited

        vrtx_curr = graph.getAdjacent(curr_vrtx); //get the vector of adjacent vextices

        for(size_t i = 0; i < vrtx_curr.size(); i++) //traverse through the vertices
        {
            temp_vrtx = vrtx_curr[i];

            if(graph.getVertexLabel(temp_vrtx) == "UNEXPLORED") //if unexplored
            {
                graph.setVertexLabel(temp_vrtx, "VISITED");//set to visited
                graph.setEdgeLabel(curr_vrtx, temp_vrtx, "DISCOVERY");//set to discovery
                que_vrtx.push(temp_vrtx);//push the visited vertex
//----------------------------------------------------------------------------//
                vrtx_temp = map_vrtx[curr_vrtx];
                vrtx_temp.push_back(temp_vrtx);
                map_vrtx[temp_vrtx] = vrtx_temp;
//----------------------------------------------------------------------------//
            }
            else if(graph.getEdgeLabel(curr_vrtx, temp_vrtx) != "UNEXPLORED") //if visited
            {
                graph.setEdgeLabel(curr_vrtx, temp_vrtx, "CROSS"); //cross 
            }
        }
    }

    int count = 0;
    vrtx_ret = map_vrtx[end];
    for(size_t i = 0; i < vrtx_ret.size() - 1; i++)
    {
        graph.setEdgeLabel(vrtx_ret[i], vrtx_ret[i+1], "MINPATH");
        count++;
    }
    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    GraphTools::graphLabeler(graph);
//----------------------------------------------------------------------------//
    vector<Edge> edge_vect;
    DisjointSets vertices;
    vector<Vertex> vrtx_vect;

    Vertex u;
    Vertex v;
//----------------------------------------------------------------------------//
    edge_vect = graph.getEdges(); //get a list of edges
    sort(edge_vect.begin(), edge_vect.end()); //sort the vector

    vrtx_vect = graph.getVertices(); //get all  the vertices in the graph

    vertices.addelements(vrtx_vect.size()); //create a disjoint set and put in vertices

    for(size_t i = 0; i < edge_vect.size(); i++)
    {
        u = edge_vect[i].source; // get the starting vertex;
        v = edge_vect[i].dest; //get the end point

        if(vertices.find(u) != vertices.find(v)) //meaning they are fron different sets
        {
            vertices.setunion(u, v); //union the vertices
            graph.setEdgeLabel(u, v, "MST"); //label it
        }
    }
}

