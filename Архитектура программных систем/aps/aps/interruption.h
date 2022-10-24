//
//  interruption.hpp
//  Created by Alina Potapova on 22.04.2022.
//

#include <string>

struct Interruption {
    std::string message;
};

class InterruptionHandler {
public:
    InterruptionHandler() = default;
    static void processInterruption(Interruption interruption);
};



