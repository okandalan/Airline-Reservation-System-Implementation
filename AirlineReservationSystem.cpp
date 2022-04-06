#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger new_passenger(firstname, lastname);
    if (passengers.search(new_passenger))
        return;

    passengers.insert(new_passenger);

}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    BSTNode<Passenger> * ps_node = passengers.search(Passenger(firstname, lastname));
    if (ps_node) 
        return &(ps_node->data);
    else
        return NULL;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    Flight new_flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    if (flights.search(new_flight))
        return;

    flights.insert(new_flight);
}


/* helper function to compare strings */
int AirlineReservationSystem::compare(const std::string &str1, const std::string &str2) const{
    int i = 0;
    for (; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] < str2[i])
            return -1;
        if (str1[i] > str2[i])
            return 1;
    }

    if (str1[i] == '\0' && str2[i] != '\0')
        return -1;

    if (str1[i] != '\0' && str2[i] == '\0')
        return 1;

    return 0;
}

/*helper function*/
void AirlineReservationSystem::searchFlight_helper(BSTNode<Flight> *r ,std::vector<Flight *> &finded_flights ,const std::string &departureCity, const std::string &arrivalCity) {
    if (r == NULL)
        return;

    /* use !compare() to check equality since compare retun 0 when strings are equal*/
    if (!compare(r->data.getDepartureCity(), departureCity) && !compare(r->data.getArrivalCity(), arrivalCity)) {
        finded_flights.push_back(&(r->data));
    }

    searchFlight_helper(r->left, finded_flights, departureCity, arrivalCity);
    searchFlight_helper(r->right, finded_flights, departureCity, arrivalCity);
}




std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight *> finded_flights;
    searchFlight_helper(flights.getRoot(), finded_flights, departureCity, arrivalCity);

    return finded_flights;
}

/* helper function to find flight with corresponding flightCode*/
Flight * AirlineReservationSystem::find_flight(BSTNode<Flight> *r, const std::string  &flight_code) {
    if (r == NULL)
        return NULL;
    
    int comp = compare(r->data.getFlightCode(), flight_code);

    /* flightCodes are equal */
    if (comp == 0)
        return &(r->data);

    /* flight_code is bigger so move on the right hand side */
    if (comp == -1)
        return find_flight(r->right, flight_code);

    /* flight_code is smaller so move on the left hand side */
    if (comp == 1)
        return find_flight(r->left, flight_code);
}

/* helper function to check if there is available seat */
bool AirlineReservationSystem::available_seat(Flight  *flight, TicketType ticket_type) {
    return true;
    
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger *ps = searchPassenger(firstname, lastname);
    if (!ps){
    std::cout << "***************\n";

        return;
    }
    Flight * fl = find_flight(flights.getRoot(), flightCode);
    if (!fl){
    std::cout << "-------------\n";

        return;
    }
    Ticket new_ticket(ps, fl, ticketType);
    fl->addTicket(new_ticket);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger *ps = searchPassenger(firstname, lastname);
    if (!ps)
        return;  

    Flight * fl = find_flight(flights.getRoot(), flightCode);
    if (!fl)
        return;
    Ticket new_ticket(ps, fl, ticketType);
    freeTicketRequests.enqueue(new_ticket);                  
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    Flight * fl = find_flight(flights.getRoot(), flightCode);
    if (!fl)
        return;

    int size = freeTicketRequests.size();
    for (int i = 0; i < size; i++) {
        Ticket t = freeTicketRequests.dequeue();

        if (fl->getFlightCode() == t.getFlight()->getFlightCode() && fl->addTicket(t)) 
            continue;
        else
            freeTicketRequests.enqueue(t);
    }

    fl->setCompleted(true);    
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
