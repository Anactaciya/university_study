#ifndef TRACK_BUILDER_H_
#define TRACK_BUILDER_H_

#include "checkpoint.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>


class TrackBuilder {
public:
    virtual ~TrackBuilder() = default;
    virtual void buildHeader(const Track& track) = 0;
    virtual void buildCheckPoint(int index, const CheckPoint& cp) = 0;
};


class TextTrackBuilder : public TrackBuilder {
private:
    std::string output_;

public:
    void buildHeader(const Track& track) override {
        output_ += "----------------------------------------------------------------\n";
        output_ += "№ | Name                    | Coordinates        | Penalty\n";
        output_ += "----------------------------------------------------------------\n";
    }
    
    void buildCheckPoint(int index, const CheckPoint& cp) override {
        std::stringstream ss;
        ss << std::setw(2) << (index + 1) << " | ";
        ss << std::setw(22) << std::left << cp.getName() << " | ";
        
        ss << std::fixed << std::setprecision(4);
        ss << std::setw(8) << cp.getLatitude() << ", ";
        ss << std::setw(8) << cp.getLongitude() << " | ";
        
        if (cp.isMandatory()) {
            ss << "незачёт СУ";
        } else {
            double penalty = cp.getPenalty().value();
            ss << std::fixed << std::setprecision(1) << penalty << " ч";
        }
        
        ss << "\n";
        output_ += ss.str();
    }

    std::string getResult() { return output_; }
};

class PenaltyCalculatorBuilder : public TrackBuilder {
private:
    double total_penalty_;

public:
    PenaltyCalculatorBuilder() : total_penalty_(0.0) {}
    
    void buildHeader(const Track&) override {}
    
    void buildCheckPoint(int, const CheckPoint& cp) override {
        if (cp.isOptional()) {
            total_penalty_ += cp.getPenalty().value();
        }
    }
    
    double getTotalPenalty() { return total_penalty_; }
};


// Director
class TrackDirector {
private:
    std::unique_ptr<TrackBuilder> builder_;

public:
    void setBuilder(std::unique_ptr<TrackBuilder> builder) {
        builder_ = std::move(builder);
    }
    
    void construct(const Track& track) {
        builder_->buildHeader(track);
        
        const auto& points = track.getCheckPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            builder_->buildCheckPoint(i, *points[i]);
        }
    }
    
    template<typename T>
    T* getBuilderAs() {
        return dynamic_cast<T*>(builder_.get());
    }
};

#endif // TRACK_BUILDER_H_