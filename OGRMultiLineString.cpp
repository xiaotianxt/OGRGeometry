//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRMultiLineString.h"

double OGRMultiLineString::GetLength() {
    double lenth = 0.0;
    if (list.empty()) return lenth;
    for (auto i : list)
        lenth += i->GetLength();
    return lenth;
}