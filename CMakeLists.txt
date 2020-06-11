cmake_minimum_required(VERSION 3.16)
project(OGR_Geometry)

set(CMAKE_CXX_STANDARD 14)

add_executable(OGR_Geometry main.cpp OGRGeometry.cpp OGRGeometry.h OGRGeometryCollection.cpp OGRGeometryCollection.h OGRSimpleCurve.cpp OGRSimpleCurve.h OGRLineString.cpp OGRLineString.h OGRLinearRing.cpp OGRLinearRing.h OGRMultiCurve.cpp OGRMultiCurve.h OGRMultiLineString.cpp OGRMultiLineString.h OGRMultiPoint.cpp OGRMultiPoint.h OGRMultiSurface.cpp OGRMultiSurface.h OGRMultiPolygon.cpp OGRMultiPolygon.h OGRPoint.cpp OGRPoint.h OGRSurface.cpp OGRSurface.h OGRCurvePolygon.cpp OGRCurvePolygon.h OGRPolygon.cpp OGRPolygon.h util_variable.h util_variable.cpp OGRCurve.cpp OGRCurve.h Destructor.cpp Destructor.h)