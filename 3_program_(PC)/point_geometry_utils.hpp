#ifndef POINTCLOUD_PREPROCESSOR__POINT_GEOMETRY_UTILS_HPP_
#define POINTCLOUD_PREPROCESSOR__POINT_GEOMETRY_UTILS_HPP_

#include "PointCloud.h"
#include <cmath>

namespace pointcloud_preprocessor {

class IDistanceCalculator {
public:
    virtual ~IDistanceCalculator() = default;
    virtual double GetDistance(const PointCloud& pc, size_t index) const = 0;
};

class IAzimuthCalculator {
public:
    virtual ~IAzimuthCalculator() = default;
    virtual double GetAzimuth(const PointCloud& pc, size_t index) const = 0;
};

class PointCloudGeometryCalculator : public IDistanceCalculator, IAzimuthCalculator {
public:
    double GetDistance(const PointCloud& pc, size_t index) const override {
        if (pc.type() == PointType::XYZIR) {
            double x = pc.points()[index * pc.pointSize() + 0];
            double y = pc.points()[index * pc.pointSize() + 1];
            double z = pc.points()[index * pc.pointSize() + 2];
            return std::hypot(x, y, z);
        }
        return pc.points()[index * pc.pointSize() + 5];
    }
    
    double GetAzimuth(const PointCloud& pc, size_t index) const override {
        if (pc.type() == PointType::XYZIR) {
            double x = pc.points()[index * pc.pointSize() + 0];
            double y = pc.points()[index * pc.pointSize() + 1];
            return std::atan2(y, x);
        }
        return pc.points()[index * pc.pointSize() + 6];
    }
};

}

#endif