//
//  main.cpp
//  Trees
//
//  Created by Raymond Chen on 2020-03-02.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include <iostream>
#include "QuadTree.cpp"


using std::string;
using std::cin;
using std::endl;
using std::cout;
using std::stoi;
using std::stod;
using std::size_t;

int main(int argc, const char * argv[]) {
    
    QuadTree quadTree;
    string line;
    
    while (!cin.eof()) {
//        string command = "";
        getline(cin, line);
        if(line == "")
            break;
        
//        for(int i = 0; i <line.length(); i++){
//            if(line[i] == ' '){
//                break;
//            }
//            else{
//                command+=line[i];
//            }
//        }
        size_t space_index = line.find(" ");
        string command = line.substr(0,space_index);
        
        if(command == "i"){
            //locate semi colons
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");
            size_t semi_colon_2 = info.find(";", semi_colon_1 + 1);
            size_t semi_colon_3 = info.find(";", semi_colon_2 + 1);
            size_t semi_colon_4 = info.find(";", semi_colon_3 + 1);
            size_t semi_colon_5 = info.find(";", semi_colon_4 + 1);
            
            //get data
            string cityName = info.substr(0, semi_colon_1);
            double xpos = stod(info.substr(semi_colon_1+1,semi_colon_2-(semi_colon_1+1)));
            double ypos = stod(info.substr(semi_colon_2+1,semi_colon_3-(semi_colon_2+1)));
            int population = stoi(info.substr(semi_colon_3+1, semi_colon_4-(semi_colon_3+1)));
            int cost = stoi(info.substr(semi_colon_4+1, semi_colon_5-(semi_colon_4+1)));
            int salery = stoi(info.substr(semi_colon_5+1));
            
            //create objects
            Point pos(xpos,ypos);
            
            if(quadTree.callInsert(new TreeNode(pos, cityName, population, cost, salery))){
                cout << "success" << endl;
            }
            else{
               cout << "failure" << endl;
            }
        }
        else if(command == "s"){
            //locate semi colons
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");
            
            double xpos = stod(info.substr(0,semi_colon_1));
            double ypos = stod(info.substr(semi_colon_1+1));
            
            TreeNode* found = quadTree.callSearch(Point(xpos,ypos));
            
            if(found){
                cout << "found " << found->getName() << endl;
            }
            else{
                cout << "not found" << endl;
            }
            
        }
        else if(command == "q_max" || command == "q_min" || command == "q_total"){
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");
            size_t semi_colon_2 = info.find(";", semi_colon_1 + 1);
            size_t semi_colon_3 = info.find(";", semi_colon_2 + 1);
            
            double xpos = stod(info.substr(0,semi_colon_1));
            double ypos = stod(info.substr(semi_colon_1+1, semi_colon_2-(semi_colon_1+1)));
            Point pos(xpos,ypos);
            
            string direction = info.substr(semi_colon_2+1, semi_colon_3-(semi_colon_2+1));
            string attr = info.substr(semi_colon_3+1);
            
            if(command == "q_max"){
                int max = quadTree.callGetMax(pos, direction, attr);
                
                if(max == -1){
                    cout << "failure" << endl;
                }
                else {
                    cout << "max " << max << endl;
                }
            }
            else if(command == "q_min"){
                unsigned int min = quadTree.callGetMin(pos, direction, attr);
                
                if(min == 4294967295){
                    cout << "failure" << endl;
                }
                else {
                    cout << "min " << min << endl;
                }
            }
            else if(command == "q_total"){
                int total = quadTree.callGetTotal(pos, direction, attr);
                
                if(total == -1){
                    cout << "failure" << endl;
                }
                else {
                    cout << "total " << total << endl;
                }
            }
        }
        else if(command == "size"){
            cout << "tree size "<< quadTree.size() <<endl;
        }
        else if(command == "print"){
            quadTree.print();
        }
        else if(command == "clear"){
            quadTree.clear();
            cout << "success" << endl;
        }
    }
    return 0;
}
