#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    
    // Store the nodes found in the RoutePlanner's start_node and end_node attributes.
	
  RouteModel::Node &strt = m_Model.FindClosestNode(start_x, start_y);
  RouteModel::Node &end = m_Model.FindClosestNode(end_x, end_y);
  
  
  	start_node = &strt;
  	end_node = &end;
}

//Implementation of Hvalue is distance to end node

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*end_node);
}


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

RouteModel::Node *RoutePlanner::NextNode() {

std::sort(open_list.begin(), open_list.end(), Compare);
  RouteModel::Node *minNode = open_list.back();
  open_list.pop_back();
  return minNode;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
	
  	int i = 0;
  int k =0;
  int j = 0;
  

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
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of that to get meters.
 return path_found;

 }

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
	
  
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
