//
//  QuadTree.cpp
//  Trees
//
//  Created by Raymond Chen on 2020-03-02.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include "QuadTree.hpp"
using std::min;
using std::max;

//-------constructors-------//
Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

//default constructor used at run time when a instance of TreeNode is created
Point::Point() {}

TreeNode::TreeNode(const Point &pos, const std::string &name, const int &population, const int &livingCost, const int &salery) {
    this->pos = pos;
    this->name = name;
    this->population = population;
    this->livingCost = livingCost;
    this->salery = salery;
    nodeNE = nullptr;
    nodeNW = nullptr;
    nodeSE = nullptr;
    nodeSW = nullptr;
}

QuadTree::QuadTree() {
    root = nullptr;
    count = 0;
}
//end of constructors



//-------destructors-------//
QuadTree::~QuadTree() {
    clear();
}

TreeNode::~TreeNode() {
    nodeNE = nullptr;
    nodeNW = nullptr;
    nodeSE = nullptr;
    nodeSW = nullptr;
}
//end of destructors



//-------TreeNode accessors with in main driver-------//
std::string TreeNode::getName() const {
    return this->name;
}

int TreeNode::getPopulation() const {
    return this->population;
}

int TreeNode::getLivingCost() const {
    return this->livingCost;
}

int TreeNode::getSalery() const {
    return this->salery;
}

//end of Tree Node accessors



//-------insert functions-------//
//public insert function to call private insert functions
bool QuadTree::callInsert(TreeNode* const obj) {
     return insert(obj);
}
//helper insert function to see if we need to call the "recusive" insert function
bool QuadTree::insert(TreeNode* const &obj) {
    //check to see if the insert object is valid
    if(obj != nullptr){
        //if root is not defined
        if(root == nullptr){
            root = obj;
            count++;
        }
        //if we need to recusively traverse the tree to insert
        else{
            if(insertNode(root, obj)){
                count++;
            }
            else{
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

//"recusive" insert function
bool QuadTree::insertNode(TreeNode* const &node, TreeNode* const &obj) {
        //If insert_node's x >= current_nodes's x and insert_node's y > current_nodes's y
        if(obj->pos.x >= node->pos.x && obj->pos.y > node->pos.y){
            //traverse until we reach a leaf node
            if(node->nodeNE != nullptr){
                return insertNode(node->nodeNE, obj);
            }
            else{
                node->nodeNE = obj;
                return true;
            }
            
        }
        //If insert_node's x < current_nodes's x and insert_node's y >= current_nodes's y
        else if(obj->pos.x < node->pos.x && obj->pos.y >= node->pos.y){
            //traverse until we reach a leaf node
            if(node->nodeNW != nullptr){
                return insertNode(node->nodeNW, obj);
            }
            else{
                node->nodeNW = obj;
                return true;
            }
    
        }
        //If insert_node's x <= current_nodes's x and insert_node's y < current_nodes's y
        else if(obj->pos.x <= node->pos.x && obj->pos.y < node->pos.y){
            //traverse until we reach a leaf node
            if(node->nodeSW != nullptr){
                return insertNode(node->nodeSW, obj);
            }
            else{
                node->nodeSW = obj;
                return true;
            }
            
        }
        //If insert_node's x > current_nodes's x and insert_node's y <= current_nodes's y
        else if(obj->pos.x > node->pos.x && obj->pos.y <= node->pos.y){
            //traverse until we reach a leaf node
            if(node->nodeSE != nullptr){
                return insertNode(node->nodeSE, obj);
            }
            else{
                node->nodeSE = obj;
                return true;
            }
            
        }
        //insertion failed
        else{
            return false;
        }
}
//end of insert functions




//-------search functions-------//
//public search function to call private search functions
TreeNode* QuadTree::callSearch(Point pos) {
    return search(root,pos);
}
//"recusive" search function
TreeNode* QuadTree::search(TreeNode *const &node, Point const &pos) {
    //return once we reach the bottom level of the tree
    if(node == nullptr){
        return nullptr;
    }
    //return the node if their positions match
    if(pos.x == node->pos.x && pos.y == node->pos.y){
        return node;
    }
    else{
        //searching based on the condition explained in insert
        if(pos.x >= node->pos.x && pos.y > node->pos.y){

            return search(node->nodeNE, pos);
            
        }
        else if(pos.x < node->pos.x && pos.y >= node->pos.y){
            
            return search(node->nodeNW, pos);
    
        }
        else if(pos.x <= node->pos.x && pos.y < node->pos.y){
            
            return search(node->nodeSW, pos);
            
        }
        else if(pos.x > node->pos.x && pos.y <= node->pos.y){
            
            return search(node->nodeSE, pos);
            
        }
        else{
            return nullptr;
        }
    }
}
//end of search functions


//-------Max functions-------//
//public max function to call private max functions
int QuadTree::callGetMax(Point &pos, std::string &dir, std::string &attr) {
    return getMax(pos, dir, attr);
}
//helper max function to see if we need to call the "recusive" max function
int QuadTree::getMax(Point &pos, std::string &dir, std::string &attr) {
    TreeNode * start = search(root, pos);
    //check to see if the starting node is a valid node
    if(start !=nullptr){
        //we need to start at the next node of the starting node
        TreeNode * start_next = dirStringMapper(start, dir);
        //check to see if the next node of the starting node is valid
        if(start_next != nullptr){
            int  max = getMax(start_next,attr);
            return  max;
        }
        //-1 to represent failure in this function
        else{
          return -1;
        }
    }
    else{
        return -1;
    }
}
//"recusive" max function
int QuadTree::getMax(TreeNode *&node, std::string &attr) {
    //value of nullptr represent -1, resulting max will never be -1
    if(node == nullptr){
        return -1;
    }
    //calcuate the value at the current node
    int curr_val = attrStringMapper(node, attr);
    
    //recursively calculate the value at the each direction and finding the max of among them
        int  max_NW = getMax(node->nodeNW,attr);
        int  max_NE = getMax(node->nodeNE,attr);
        int  max_SW = getMax(node->nodeSW,attr);
        int  max_SE = getMax(node->nodeSE,attr);
    
        return max(max(curr_val,max_NW),max(max(max_NE,max_SW),max_SE));
    
    
//    return max(max(curr_val, getMax(node->nodeNE,attr)), max(max(getMax(node->nodeNW,attr),getMax(node->nodeSW,attr)) ,getMax(node->nodeSE,attr)));
}
//end of max functions


//-------Min functions-------//
//public min function to call private min functions
unsigned int QuadTree::callGetMin(Point &pos, std::string &dir, std::string &attr) {
    return getMin(pos, dir, attr);
}
//helper min function to see if we need to call the "recusive" min function
unsigned int QuadTree::getMin(Point &pos, std::string &dir, std::string &attr) {
    TreeNode * start = search(root, pos);
    //check to see if the starting node is a valid node
    if(start !=nullptr){
        //we need to start at the next node of the starting node
        TreeNode * start_next = dirStringMapper(start, dir);
        //check to see if the next node of the starting node is valid
        if(start_next != nullptr){
            unsigned int  min = getMin(start_next,attr);
            return  min;
        }
        //-1 to represent failure in this function
        else{
          return -1;
        }
    }
    else{
        return -1;
    };
}
//"recusive" min function
unsigned int QuadTree::getMin(TreeNode *&node, std::string &attr) {
    //value of nullptr represent 4294967295, resulting min will never be this number because we have assumed the max value that a node can have is the max value of a INT type.
    if(node == nullptr){
        return 4294967295;
    }
    //calcuate the value at the current node
    unsigned int curr_val = attrStringMapper(node, attr);
    //recursively calculate the value at the each direction and finding the min of among them
    return min(min(curr_val, getMin(node->nodeNE,attr)), min(min(getMin(node->nodeNW,attr),getMin(node->nodeSW,attr)) ,getMin(node->nodeSE,attr)));
}
//end of min functions



//-------Total functions-------//
//public total function to call private total functions
int QuadTree::callGetTotal(Point &pos, std::string &dir, std::string &attr) {
    return getTotal(pos, dir, attr);
}
//helper total function to see if we need to call the "recusive" total function
int QuadTree::getTotal(Point &pos, std::string &dir, std::string &attr) {
    TreeNode * start = search(root, pos);
    //check to see if the starting node is a valid node
    if(start !=nullptr){
        //we need to start at the next node of the starting node
        TreeNode * start_next = dirStringMapper(start, dir);
        //check to see if the next node of the starting node is valid
        if(start_next != nullptr){
            int  total = getTotal(start_next,attr);
            
            return total;
        }
        //-1 to represent failure in this function
        else{
          return -1;
        }
    }
    else{
        return -1;
    }
}

//"recusive" total function
int QuadTree::getTotal(TreeNode *&node, std::string &attr) {
    //value of nullptr represent 0
    if(node == nullptr){
        return 0;
    }
    //calcuate the value at the current node
    int curr_val = attrStringMapper(node, attr);
    
    //recursively sum all the values calculated at each direction
    return curr_val + getTotal(node->nodeNE,attr) + getTotal(node->nodeNW,attr) +getTotal(node->nodeSW,attr) +getTotal(node->nodeSE,attr);
}
//end of total functions



//size function
std::size_t QuadTree::size() const {
    return count;
}

//-------print functions-------//
//"recusive" print function
void QuadTree::print(TreeNode *const &node) const {
    if(node!=nullptr){
        print(node->nodeNE);
        print(node->nodeNW);
        std::cout << node->name << " ";
        print(node->nodeSW);
        print(node->nodeSE);
    }
}

//public print function to call private print functions
void QuadTree::print() const {
    if(root != nullptr){
        print(root);
        std::cout << std::endl;
    }
}

//end of print functions 

//-------clear functions-------//
//public clear function to call private clear functions
void QuadTree::clear() {
    clear(root);
    count = 0;
    root = nullptr;
}
//"recusive" clear function
void QuadTree::clear(TreeNode *const &node) const {
    if(node!=nullptr){
        clear(node->nodeNE);
        clear(node->nodeNW);
        clear(node->nodeSW);
        clear(node->nodeSE);
        delete node;
    }
}
//end of clear functions



//Direction String Mapper - tells functions what direction to traverse given a string
TreeNode *QuadTree::dirStringMapper(TreeNode *&node, std::string &dir) {
    if(dir == "NE"){
        return  node->nodeNE;
    }
    else if(dir == "NW"){
        return  node->nodeNW;
    }
    else if(dir == "SE"){
        return  node->nodeSE;
    }
    else if(dir == "SW"){
        return  node->nodeSW;
    }
    else{
        return nullptr;
    }
}

//Attribute String Mapper - tells functions what attribute to get given a string
int QuadTree::attrStringMapper(TreeNode *&node, std::string &attr) {
    if(attr == "p"){
        return  node->population;
    }
    else if(attr == "r"){
        return  node->livingCost;
    }
    else if(attr == "s"){
        return  node->salery;
    }
    else{
        return -1;
    }
}
