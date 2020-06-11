//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRMultiPolygon.h"

void OGRMultiPolygon::ImportFromWkt(const char *filepath) {
    std::ifstream fin;
    fin.open(filepath); // 读取文件
    std::string s, tempstring;
    std::getline(fin, s);
    std::regex words_regex("-?\\d+(\\.\\d+)?"); // 用于匹配一个小数
    int i = 0;
    for (i = 0; i < s.length(); i++){
        if (s[i] == '(')
            break;
    } // 去除第一个括号
    for ( i++; i < s.length(); i++){
        // 一次匹配一个多边形

        std::string ringstring;
        if (s[i] == '('){ // 发现一个多边形
            std::vector<OGRLinearRing> ringlist;

            while (true) {
                i++; // 去掉多边形开头的括号
                if (s[i] == '(') // 发现一个环
                {
                    while (s[i] != ')') ringstring += s[i++]; // 将环内元素匹配出来
                    std::cout << ringstring << std::endl;
                    std::vector<OGRPoint> list; // 所有环内坐标放进去

                    auto words_begin =
                            std::sregex_iterator(ringstring.begin(), ringstring.end(), words_regex);
                    auto words_end = std::sregex_iterator();

                    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                        double x = std::atof((*i).str().c_str());
                        ++i;
                        double y = std::atof((*i).str().c_str());

                        list.push_back(OGRPoint(x, y));
                        std::cout << "hello " << std::endl;

                    }
                    if (!list.empty()) {
                        OGRLinearRing newring = OGRLinearRing(list); // 新建一个ring
                        std::cout << newring.print() << std::endl;
                        ringlist.push_back(newring);
                    }
                    i++; // 跳出环继续遍历
                    ringstring = "";
                }

                if (s[i] == ')') { // 多边形结束
                    OGRPolygon polygon = OGRPolygon(ringlist);
                    list.push_back(polygon);
                    break;
                }
            }


        }
    }
}

void OGRMultiPolygon::ExportToWkt(const char *filepath) {
    std::ofstream fout;
    fout.open(filepath);
    fout << "MultiPolygon (";
    fout << list[0].print();
    for (int i = 1; i < list.size(); i++)
    {
        fout << ", " << list[i].print();
    }
    fout << ")";

    fout.close();
}
double OGRMultiPolygon::GetArea() {
    double area = list[0].GetArea();
    for (int i = 1; i < list.size(); i++){
        area += list[i].GetArea();
    }
    return area;
}

double OGRMultiPolygon::GetPerimeter() {
    double perimeter = 0;
    for (auto i : list){
        perimeter += i.GetPerimeter();
    }
    return perimeter;
}

bool OGRMultiPolygon::Contains(OGRPoint &object) {
    for (auto i : list){
        if (i.Contains(object))
            return true;
    }
    return false;
}

bool OGRMultiPolygon::Contains(OGRLineString &object) {
    for (auto i : list){
        if (i.Contains(object))
            return true;
    }
    return false;
}

bool OGRMultiPolygon::Contains(OGRPolygon &object) {
    for (auto i : list){
        if (i.Contains(object))
            return true;
    }
    return false;
}
