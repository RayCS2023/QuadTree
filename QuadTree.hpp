//
//  QuadTree.hpp
//  Trees
//
//  Created by Raymond Chen on 2020-03-02.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <iostream>
#include <algorithm>

struct Point{
    double x;
    double y;
    Point();
    Point(double x, double y);
};

class TreeNode{
private:
    friend class QuadTree;
    
    //keys
    //the class default constructor will be called if no parameters
    Point pos;
    std::string name;
    int population;
    int livingCost;
    int salery;
    
    //childs and parent
    TreeNode *nodeNW;
    TreeNode *nodeNE;
    TreeNode *nodeSW;
    TreeNode *nodeSE;
public:
    //accessors
    std::string getName() const;
    int getPopulation() const;
    int getLivingCost() const;
    int getSalery() const;

    TreeNode(const Point &pos, const std::string &name, const int &population, const int &livingCost, const int &salery);
    ~TreeNode();
};


class QuadTree{
private:
    //member variables
    std::size_t count;
    //make public for now
    TreeNode *root;
    
    //member functions
    bool insert(TreeNode* const &obj);
    bool insertNode(TreeNode* const &node,  TreeNode* const &obj);
    
    int getMax(TreeNode *&node, std::string &attr);
    int getMax(Point &pos, std::string &dir, std::string &attr);
    
    unsigned getMin(TreeNode *&node, std::string &attr);
    unsigned getMin(Point &pos, std::string &dir, std::string &attr);
    
    TreeNode* search(TreeNode* const &node, Point const &pos);
    
    TreeNode* dirStringMapper(TreeNode * &node, std::string &dir);
    int attrStringMapper(TreeNode * &node, std::string &attr);
    
    int getTotal(TreeNode *&node, std::string &attr);
    int getTotal(Point &pos, std::string &dir, std::string &attr);
    void print(TreeNode* const &node) const;
    void clear(TreeNode* const &node) const;
    
public:

    bool callInsert(TreeNode* const obj);
    TreeNode* callSearch(Point pos);
    int callGetMax(Point &pos, std::string &dir, std::string &attr);
    unsigned callGetMin(Point &pos, std::string &dir, std::string &attr);
    int callGetTotal(Point &pos, std::string &dir, std::string &attr);
    std::size_t size() const;
    
    void print() const;
    void clear();
    QuadTree();
    ~QuadTree();
};



#endif /* QuadTree_hpp */
