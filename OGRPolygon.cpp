//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRPolygon.h"

void OGRPolygon::ImportFromWkt(const char *filepath) {
    std::ifstream fin;
    fin.open(filepath); // 读取文件
    std::string s, tempstring;
    std::getline(fin, s);
    std::regex words_regex("-?\\d+(\\.\\d+)?"); // 用于匹配一个小数

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') { // 开启一个新tempstring
            tempstring = "";
        } else if (s[i] == ')') {
            if (tempstring.length() != 0) {
                // 此处开始读取坐标序列
                std::vector<OGRPoint> list;
                auto words_begin =
                        std::sregex_iterator(tempstring.begin(), tempstring.end(), words_regex);
                auto words_end = std::sregex_iterator();

                for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                    double x = std::atof((*i).str().c_str());
                    ++i;
                    double y = std::atof((*i).str().c_str());

                    list.push_back(OGRPoint(x, y));
                }
                if (list.size()) {
                    OGRLinearRing newring = OGRLinearRing(list); // 新建一个ring
                    this->list.emplace_back(newring); // 将ring加入list
                }
            }
            tempstring = "";
        } else {
            tempstring += s[i];
        }
    }
}

std::string OGRPolygon::print(){
    std::string s;

    s += "(";

    s += list[0].print();

    for(int i = 1; i < list.size(); i++){
        s += ", " + list[i].print();
    }

    s += ")";

    return s;
}

void OGRPolygon::ExportToWkt(const char *filepath) {
    std::ofstream fout(filepath);
    fout << "Polygon ";
    fout << print();
    fout.close();
}

double OGRPolygon::GetArea() {
    double area = list[0].GetArea();
    for (int i = 1; i < list.size(); i++) {
        area -= list[i].GetArea();
    }
    return area;
}

double OGRPolygon::GetPerimeter() {
    double perimeter = 0;
    if (list.empty()) return perimeter;
    for (auto &i : list) {
        perimeter += i.GetLength();
    }
    return perimeter;
}

bool OGRPolygon::Contains(OGRPoint &object) {
    if (!list[0].Contains(object))
        return false;
    for (int i = 1; i < list.size(); i++) {
        if (list[i].Contains(object) || list[i].On(object)) // 如果在环内或环上 说明不在多边形内
            return false;
    }
    return true;
}

bool OGRPolygon::Contains(OGRLineString &object) {
    const std::vector<OGRPoint> &stringlist = object.GetList();
    for (auto i : stringlist){
        if (Contains(i))
            continue;
        else
            return false;
    }
    return true;
}

bool OGRPolygon::Contains(OGRPolygon &object) {
    const std::vector<OGRLinearRing> &polygonlist = object.GetList();
    for (auto i : polygonlist){
        if (Contains(i))
            continue;
        else
            return false;
    }
    return true;
}

bool OGRPolygon::Intersects(OGRPolygon &object) {
    std::vector<OGRLinearRing> olist;

    for (int i = 0; i < list.size(); i++){
        for (int j = 0; j < olist.size(); j++){
            if (list[i].Intersects(olist[j]))
                return true;
        }
    }

    return false;
}

bool OGRPolygon::Intersects(OGRLineString &object) {

    for (int i = 0; i < list.size(); i++){
        if (list[i].Intersects(object)) // 如果相交就返回相交
            return true;
    }

    return false;
}