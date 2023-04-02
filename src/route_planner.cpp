#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
	
  RouteModel::Node &strt = m_Model.FindClosestNode(start_x, start_y);
  RouteModel::Node &end = m_Model.FindClosestNode(end_x, end_y);
  
  
  	start_node = &strt;
  	end_node = &end;
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*end_node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  
  current_node->FindNeighbors();
  
  for (RouteModel::Node *nodeVal: current_node->neighbors) {
    
    nodeVal->parent = current_node;
    nodeVal->h_value = CalculateHValue(nodeVal);
    nodeVal->g_value = current_node->g_value + current_node->distance(*nodeVal);
    nodeVal->visited = true;
    
    open_list.push_back(nodeVal); 
   
    }
 
}


bool Compare(RouteModel::Node *node1, RouteModel::Node *node2) {
  return ((node1->h_value + node1->g_value) > (node2->h_value + node2->g_value));
  }

// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {

std::sort(open_list.begin(), open_list.end(), Compare);
  RouteModel::Node *minNode = open_list.back();
  open_list.pop_back();
  return minNode;
}

// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
	
  	int i = 0;
  int k =0;
  int j = 0;
  
//     // TODO: Implement your solution here.
  while (current_node != start_node) {
   distance= distance + current_node->distance(*(current_node->parent));
    path_found.push_back(*current_node);
    current_node = current_node->parent;
    
    i++;
  }
  //start_node needs to be added to path found
  path_found.push_back(*current_node);
  
  for ( k = path_found.size()-1; k>path_found.size()/2; k--) {
   std::swap(path_found[k], path_found[j]);
    j++;
  }
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of thap to get meters.
 return path_found;

 }


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
	
    // TODO: Implement your solution here.
  
  current_node = start_node;
  current_node->visited = true;
  open_list.push_back(start_node);
  
  
  while(!open_list.empty()) {
    
  //sorts open list and returns the next node
  current_node=NextNode();
    
    if (current_node == end_node) {
      m_Model.path = ConstructFinalPath(current_node);
    return;
    }
  //adds unvisited neighbors of node to open list
  AddNeighbors(current_node);
  
  }
  
 
}
