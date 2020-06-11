//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRGeometry.h"

bool OGRGeometry::IsEmpty() {
    return false;
}

void OGRGeometry::GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) {
    return;
}

bool OGRGeometry::Equals(const OGRGeometry & object) {
    std::cout << "Error!" << std::endl;
    return false;
}

void OGRGeometry::ImportFromWkt(const char *filepath) {

}

void OGRGeometry::ExportToWkt(const char *filepath) {

}

void OGRGeometry::Clone(OGRGeometry & sample) {
    std::cerr << "Wrong !";
    return ;
}

OGRGeometry &OGRGeometry::Clone() {
    std::cerr << "Wrong !";
    assert(true);
    return *this;
}
