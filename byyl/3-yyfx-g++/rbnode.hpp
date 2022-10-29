#include <cstdarg>
#include <iostream>
#include <vector>
#include <map>
#include <list>

struct variProperties {
    std::string specify;
};

struct arrProperties {
    int dim;
    int lower = 0, upper;
};

struct funcProperties {
    std::string returnType;
    // std::vector<std::string> paramList;
};

class RBNode {
    private:
        std::string type; // 指示符号类型：字面常量、变量、数组、结构体、函数
        int num; // 字面常量，目前仅考虑整数
        variProperties vrp; // 变量
        arrProperties arp; // 数组
        // 结构体struct xxx后面紧跟新的作用域，直接沿用判断变量的思路
        funcProperties fcp; // 函数声明 ;

    public:
        RBNode(std::string type, int cnt, ...) { // va_list中cnt可能存在问题
            // int cnt;
            va_list args;
            if(type == "Variable") {
                cnt = 1;
                this->type = type;
                va_start(args, cnt);
                std::string arg = va_arg(args, const char*);
                this->vrp.specify= arg;
            }
            else if(type == "Constant") {
                cnt = 1;
                this->type = type;
                va_start(args, cnt);
                int arg = va_arg(args, int);
                this->num = arg;
            }
            else if(type == "Array") {
                cnt = 2;
                this->type = type;
                va_start(args, cnt);
                int arg1 = va_arg(args, int);
                this->arp.dim = arg1;
                int arg2 = va_arg(args, int);
                this->arp.upper = arg2;
            }
            else if(type == "Struct") {
                this->type = type;
            }
            else if(type == "Function") {
                cnt = 1;
                this->type = type;
                va_start(args, cnt);
                std::string arg = va_arg(args, const char *);
                this->fcp.returnType = arg;
            }
            va_end(args);
        }
        ~RBNode(){};
        void setType(std::string t) {
            type = t;
        }
        void setNum(int n) {
            num = n;
        }
        void setArray(int d, int up) {
            arp.dim = d;
            arp.upper = up;
        }
        void setFunc(std::string rt) {
            fcp.returnType = rt;
        }
};