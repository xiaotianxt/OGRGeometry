//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRMultiPoint.h"

void OGRMultiPoint::GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) {
    GetMBR();
    XMin = this->XMin;
    XMax = this->XMax;
    YMin = this->YMin;
    YMax = this->YMax;
    return;
}

std::pair<OGRPoint, OGRPoint> OGRMultiPoint::GetMBR() {
    if (this->IsEmpty())
        return std::pair<OGRPoint, OGRPoint> (OGRPoint(), OGRPoint());
    OGRPoint* realpoint = dynamic_cast<OGRPoint *>(list[0]);
    XMin = realpoint->getX();
    XMax = realpoint->getX();
    YMin = realpoint->getY();
    YMax = realpoint->getY();

    for (int i = 0; i < list.size(); i++){
        OGRPoint* point = dynamic_cast<OGRPoint *>(list[i]);
        if (point->getX() < XMin)
            XMin = point->getX();
        if (point->getX() > XMax)
            XMax = point->getX();
        if (point->getY() < YMin)
            YMin = point->getY();
        if (point->getY() > YMax)
            YMax = point->getY();
    }

    return std::pair<OGRPoint, OGRPoint> (OGRPoint(XMin, YMin), OGRPoint(XMax, YMax));
}


void OGRMultiPoint::ImportFromWkt(const char *filepath) {
    std::ifstream fin;
    try{
    fin.open(filepath); // 读取文件
    std::string s;
    std::getline(fin, s);

    std::regex words_regex("-?\\d+(\\.\\d+)?");
    auto words_begin =
            std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        double x = std::atof((*i).str().c_str());
        ++i;
        double y = std::atof((*i).str().c_str());

        list.push_back(new OGRPoint(x, y));
    }}
    catch (const char * e) {
        std::cerr << e << std::endl;
    }
}
void OGRMultiPoint::ExportToWkt(const char *filepath) {
    std::ofstream fout;
    fout.open(filepath);
    fout << "MultiPoint (";
    for (int i = 0; i < list.size(); i++){
        if (i != 0)
            fout << ", ";
        fout << dynamic_cast<OGRPoint *>(list[i])->print();
    }
    fout << ")";
    fout.close();
}
