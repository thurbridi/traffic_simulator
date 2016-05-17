#include "../include/EventHandler.h"


int EventHandler::processNextEvent() {
    Event e = event_list_.popFront();
    switch (e.type()) {
    // SPAWN_VEHICLE
    case 0:
        spawnVehicle();

        schedule(Event{e.time() + 10, kSpawnVehicle, e.elementA()});
        schedule(Event{e.time() + 5, kArrival, e.elementA()});
        std::cerr << "vehicle spawned\n";
        break;

    // CHANGE_LANE
    case 1:
        changeLane();
        schedule(Event{e.time() + 5, kChangeLane, e.elementA()});
        break;

    // REMOVE_VEHICLE
    case 2:
        arrival();
        break;

    // CHANGE_SEMAPHORE
    case 3:
        changeSemaphore();
        schedule(Event{e.time() + 20, kChangeSemaphore, e.elementA()});
        break;
    }

    return e.time();
}


void EventHandler::schedule(const Event& e) {
    event_list_.insert(e);
}

int EventHandler::n_of_events() {
    return event_list_.size();
}

void EventHandler::arrival() {

    std::cerr << "vehicle arrived\n";
}

void EventHandler::changeLane(Semaphore* sem) {
    // enquanto
    std::cerr << "attempting to change lanes\n";
}

void EventHandler::changeSemaphore(Semaphore* sem) {
    // troca o sinal
    // reagenda troca de sinal
    std::cout << "semaphore lights changed\n";
}

void EventHandler::spawnVehicle(SourceLane* lane) {
    Vechicle v{lane->generateDirection()};
    lane->insertVehicle(v);
    std::uniform_int_distribuition<int> dist{lane->base_frequency() - lane->variation(),
                                             lane->base_frequency() + lane->variation()};


}
