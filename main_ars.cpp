#include <iostream>

#include "AirlineReservationSystem.h"

int main() {
    AirlineReservationSystem ars;
    /*
    Passenger p1("jack", "sophia");
    Passenger p2("kate", "sophia");
    */
    Passenger *p;
    /*
    Flight f1("DS7020", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 200, 10);
    Flight f2("DS7010", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 200, 10);
    */

    ars.print();

    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    
    ars.addFlight("DS7020", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 200, 10);
    
    ars.addFlight("DS7010", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "Istanbul", 200, 10);
    
    ars.issueTicket("archie", "rosie", "DS7010", economy);
    ars.issueTicket("harry", "isabella", "DS7010", economy);
    
    ars.issueTicket("jack", "sophia", "DS7020", economy);
    
    ars.print();

    p = ars.searchPassenger("jack", "sophia");
    if (p)
        std::cout << p->getFirstname() << " " << p->getLastname() << '\n';
    else
        std::cout << "YOK öyle birisi" << '\n';
    
    return 0;
}
