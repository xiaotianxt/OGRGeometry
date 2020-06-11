//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRPoint.h"


void OGRPoint::ImportFromWkt(const char *filepath) {
    std::ifstream fin;
    fin.open(filepath); // 读取文件
    std::string templine;
    std::getline(fin, templine);
    std::smatch result;
    std::regex pattern("Point \\((-?\\d+(\\.\\d+)?) (-?\\d+(\\.\\d+)?)\\)");

    if (std::regex_match(templine, result, pattern)){
        x = std::atof(result[1].str().c_str());
        y = std::atof(result[3].str().c_str());
    }
}

void OGRPoint::ExportToWkt(const char *filepath) {
    std::ofstream fout;
    fout.open(filepath);
    fout << "Point (" + std::to_string(x) + " " + std::to_string(y) + ")\n\r";
    fout.close();
}

bool OGRPoint::IsEmpty() {
    return x == (std::numeric_limits<double>::max)() && y == (std::numeric_limits<double>::max)();
}

void OGRPoint::GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) {
    XMin = x;
    YMin = y;
    XMax = x;
    YMax = y;
}

OGRPoint & OGRPoint::Clone() {
    return *(new OGRPoint(x, y));
}


bool OGRPoint::Equals(const OGRGeometry& object){
    const auto* point = dynamic_cast<const OGRPoint*>(&object);
    return COMPARE(point->getX(), x) == 0 && COMPARE(point->getY(), y) == 0;
}

double OGRPoint::getX() const {
    return x;
}

double OGRPoint::getY() const {
    return y;
}

std::string OGRPoint::print() const {
    return "(" + std::to_string(x) + " " + std::to_string(y) + ")";
}

OGRPoint OGRPoint::operator-(const OGRPoint &objectb) const {
    return OGRPoint(x - objectb.getX(), y - objectb.getY());
}

double OGRPoint::operator^(const OGRPoint &objectb) const {
    return x*objectb.getY() - y*objectb.getX();
}

double OGRPoint::operator*(const OGRPoint &objectb) const {
    return x*objectb.getX() + y*objectb.getY();
}

void OGRPoint::Clone(OGRPoint &Sample) {
    x = Sample.x;
    y = Sample.y;
}

std::pair<OGRPoint, OGRPoint> OGRPoint::GetMBR() {
    return std::pair<OGRPoint, OGRPoint>(OGRPoint(x, y), OGRPoint(x, y));
}

bool OGRPoint::operator==(const OGRPoint &objectb) const {
    return COMPARE(x, objectb.x)==0 && COMPARE(y, objectb.y) == 0;
}
