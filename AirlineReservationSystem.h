#ifndef AIRLINERESERVATIONSYSTEM_H
#define AIRLINERESERVATIONSYSTEM_H

#include "BST.h"
#include "Queue.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"

class AirlineReservationSystem {
public: // DO NOT CHANGE THIS PART.
    AirlineReservationSystem() {}

    void addPassenger(const std::string &firstname, const std::string &lastname);

    Passenger *searchPassenger(const std::string &firstname, const std::string &lastname);

    void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity);

    void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void executeTheFlight(const std::string &flightCode);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void searchFlight_helper(BSTNode<Flight> *r ,std::vector<Flight *> &finded_flights ,const std::string &departureCity, const std::string &arrivalCity);
    int compare(const std::string &str1, const std::string &str2) const;
    bool available_seat(Flight * flight,TicketType ticket_type);
    Flight * find_flight(BSTNode<Flight> *r, const std::string  &flight_code);

private: // DO NOT CHANGE THIS PART.
    BST<Passenger> passengers;
    BST<Flight> flights;

    Queue<Ticket> freeTicketRequests;
};

#endif //AIRLINERESERVATIONSYSTEM_H
