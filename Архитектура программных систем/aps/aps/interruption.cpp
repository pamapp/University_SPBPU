//
//  interruption.cpp
//  Created by Alina Potapova on 22.04.2022.
//

#include "interruption.h"
#include "rtos_api.h"

#include <iostream>
#include <csignal>

void InterruptionHandler::processInterruption(Interruption interruption) {
    std::cout << "Interruption: " << interruption.message << '\n';
    raise(SIGINT);
}


