#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class TreeType{
    string name;
    string color;
    string texture;

    public:
        TreeType(string name, string color, string texture) : name(name), color(color), texture(texture) {}

        void draw(int x, int y){
            cout<<"Drawing" <<name<<"tree at (" << x << "," << y << ")" << endl;
        }
};

class Tree{
    int x;
    int y;

    TreeType* treeType;

    public:
        Tree(int x, int y, TreeType* treeType) : x(x), y(y), treeType(treeType) {}

        void draw(){
            treeType->draw(x, y);
        }
};

class TreeFactory{
    static unordered_map<string, TreeType*> treeTypeMap;

    public:
        static TreeType* getTreeType(string name, string color, string texture){
            string key = name + " - " + color + " - " + texture;
            if(treeTypeMap.find(key) == treeTypeMap.end()){
                treeTypeMap[key] = new TreeType(name, color, texture);
            }
            return treeTypeMap[key];
        }
};

unordered_map<string, TreeType*> TreeFactory::treeTypeMap;

class Forest{
    vector<Tree*> trees;

    public:
        void plantTree(int x, int y, string name, string color, string texture){
            TreeType* treeType = TreeFactory::getTreeType(name, color, texture);
            Tree* tree = new Tree(x, y, treeType);
            trees.push_back(tree);
        }

        void draw(){
            for(auto& tree : trees){
                tree->draw();
            }
        }

        ~Forest(){
            for(auto& tree : trees){
                delete tree;
            }
        }
};

int main(){
    Forest forest;
    forest.plantTree(10, 20, "Oak", "Green", "Rough");
    forest.plantTree(15, 25, "Pine", "Dark Green", "Smooth");
    forest.plantTree(10, 20, "Oak", "Green", "Rough");
    forest.plantTree(30, 40, "Birch", "Light Green", "Peeling");
    forest.plantTree(15, 25, "Pine", "Dark Green", "Smooth");

    forest.draw();
    return 0;
}

