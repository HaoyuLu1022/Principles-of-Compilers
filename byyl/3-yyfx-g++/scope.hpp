#include "rbnode.hpp"

class Scope {
    private:
        std::vector<std::map<std::string, RBNode> > scope;
    public:
        void enter() {
            scope.push_back({}); // 进入作用域
        }
        void exit() {
            scope.pop_back(); // 退出作用域
        }
        bool inGlobal() {
            return (scope.size() == 1); // 判断是否是全局作用域
        }
        bool push(std::string name, RBNode node) {
            auto result = scope[scope.size()-1].insert({name, node});
            return result.second;
        }
        bool findDef(std::string name) {
            for(auto it = scope.rbegin(); it != scope.rend(); it++) {
                auto iter = it->find(name);
                if(iter != it->end()) {
                    return true;
                }
            }
            return false;
        }
        // int find(std::string name) {
        //     for(auto it = scope.rbegin(); it != scope.rend(); it++) {
        //         auto iter = it->find(name);
        //         if(iter != it->end()) {
        //             return (unsigned int)iter->second;
        //         }
        //     }
        //     return -1; // 没找到
        // }
};

