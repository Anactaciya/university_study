#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include <string>
#include <optional>
#include <vector>
#include <memory>
#include <stdexcept>

class CheckPoint {
public:
    enum class Type {
        MANDATORY,
        OPTIONAL
    };

private:
    std::string name_;
    double latitude_;
    double longitude_; 
    Type type_;
    std::optional<double> penalty_;

public:
    CheckPoint(const std::string& name, double latitude, double longitude)
        : name_(name), latitude_(latitude), longitude_(longitude), 
          type_(Type::MANDATORY), penalty_(std::nullopt) {
        validateCoordinates();
    }

    CheckPoint(const std::string& name, double latitude, double longitude, double penalty)
        : name_(name), latitude_(latitude), longitude_(longitude),
          type_(Type::OPTIONAL), penalty_(penalty) {
        validateCoordinates();
    }

    const std::string& getName() const { return name_; }
    double getLatitude() const { return latitude_; }
    double getLongitude() const { return longitude_; }
    Type getType() const { return type_; }
    std::optional<double> getPenalty() const { return penalty_; }
    
    bool isOptional() const { return type_ == Type::OPTIONAL; }
    bool isMandatory() const { return type_ == Type::MANDATORY; }

private:
    void validateCoordinates() {
        if (latitude_ < -90.0 || latitude_ > 90.0) {
            throw std::out_of_range("Latitude must be in range [-90, 90]");
        }
        if (longitude_ < -180.0 || longitude_ > 180.0) {
            throw std::out_of_range("Longitude must be in range [-180, 180]");
        }
    }
};

class Track {
private:
    std::vector<std::shared_ptr<CheckPoint>> checkpoints_;
    std::string track_name_;

public:
    Track(const std::string& name) : track_name_(name) {}
    
    void addCheckPoint(std::shared_ptr<CheckPoint> p) {
        checkpoints_.push_back(p);
    }
    
    const std::vector<std::shared_ptr<CheckPoint>>& getCheckPoints() const {
        return checkpoints_;
    }
    
    size_t size() const { return checkpoints_.size(); }
};

#endif // CHECKPOINT_H_