#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include <string>
#include <stdexcept>
#include <vector>

// The lidar's pointcloud contains coordinates of point (X, Y and Z) and Intencity of ret beam for point (I) and beam ring (R)
// Also it can contains Distance (D), Azimuth (A) and Timestamp (T)


enum class PointType : std::size_t {
    XYZIR = 5,
    XYZIRDAT = 8
};

inline std::string pointTypeToString(PointType type) {
    switch (type) {
        case PointType::XYZIR:   return "XYZIR";
        case PointType::XYZIRDAT: return "XYZIRDAT";
        default: return "Unknown";
    }
}

inline std::size_t getPointSize(PointType type) {
    return static_cast<std::size_t>(type);
}


class PointCloud {
private: // исправляем нарушение инкапсуляции
	PointType type_;
    std::size_t size_;
    std::size_t point_size_;
    std::vector<double> points_;
public:
	PointCloud() : type_(PointType::XYZIR), size_(0), point_size_(5) {}

	explicit PointCloud(PointType type, std::size_t points_count = 0) 
        : type_(type), size_(points_count), point_size_(getPointSize(type)) {
        if (points_count > 0) {
            points_.resize(points_count * point_size_);
        }
    }

	void Init(PointType pc_type, size_t points_count) {
		type_ = pc_type;
		size_ = points_count;
		point_size_ = getPointSize(pc_type);
        points_.resize(size_ * point_size_);
	}

	void AddPoint(std::vector<double> point, size_t ind) {
		if (point.size() != point_size_) {
            throw std::runtime_error("Point has unsuported size = " + 
                                   std::to_string(point.size()) + 
                                   " for type " + pointTypeToString(type_));
        }
		if (ind >= size_) {
            throw std::runtime_error("Index out of bounds");
        }
		
		for (size_t i = 0; i < point.size(); ++i) {
			points_[point_size_ * ind + i] = point[i];
		}
	}

	// std::string pointcloud_type_{""}; Перенесено в private
	// size_t size_ = 0;
	// size_t point_size_ = 0;
	// std::vector<double> points_;

	// поэтому нужно добавить геттеры
	std::size_t size() const { return size_; }
	std::size_t pointSize() const { return point_size_; }
	const std::vector<double>& points() const { return points_; }
	std::vector<double>& points() { return points_; }

	PointType type() const { return type_; }
	std::string getTypeString() const { return pointTypeToString(type_); }
};

// For tests
inline void FillPointCloud(PointCloud* pc, size_t points_count, PointType point_type, const std::vector<double>& data) {
	if (!pc) {
        throw std::invalid_argument("FillPointCloud: pc cannot be null");
    }

	pc->Init(point_type, points_count);
	std::size_t point_size = getPointSize(point_type);

	size_t ind = 0;
	for (size_t i = 0; i < data.size(); i += point_size) {
		pc->AddPoint(
			std::vector<double>{
				data.begin() + point_size * ind,
				data.begin() + point_size * (ind + 1)
			},
			ind
		);
		ind++;
	}
}

#endif //POINTCLOUD_H_