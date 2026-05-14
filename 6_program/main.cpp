#include "checkpoint.h"
#include "track_builder.h"
#include <iostream>
#include <memory>

int main() {
    Track track("Гоночная трасса <...>");
    
    track.addCheckPoint(std::make_shared<CheckPoint>("Start", 48.8566, 2.3522));
    track.addCheckPoint(std::make_shared<CheckPoint>("CP1 - Valley", 49.1234, 3.5678, 0.5));
    track.addCheckPoint(std::make_shared<CheckPoint>("CP2 - Mountain", 50.2345, 4.6789));
    track.addCheckPoint(std::make_shared<CheckPoint>("CP3 - River", 51.3456, 5.7890, 1.0));
    track.addCheckPoint(std::make_shared<CheckPoint>("CP4 - Forest", 50.4567, 6.8901));
    track.addCheckPoint(std::make_shared<CheckPoint>("Finish", 49.5678, 7.9012, 0.0));
    
    TrackDirector director;
    
    auto textBuilder = std::make_unique<TextTrackBuilder>();
    director.setBuilder(std::move(textBuilder));
    director.construct(track);
    
    TextTrackBuilder* textResult = director.getBuilderAs<TextTrackBuilder>();
    if (textResult) {
        std::cout << textResult->getResult();
    }

    // 2. Подсчёт штрафа
    auto penaltyBuilder = std::make_unique<PenaltyCalculatorBuilder>();
    director.setBuilder(std::move(penaltyBuilder));
    director.construct(track);
    
    PenaltyCalculatorBuilder* penaltyResult = director.getBuilderAs<PenaltyCalculatorBuilder>();
    if (penaltyResult) {
        std::cout << "Total penalty: " << penaltyResult->getTotalPenalty() << " hours\n";
    }

    return 0;
}