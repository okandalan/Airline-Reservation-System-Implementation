#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    /* TODO */
    int i = 0;
    for (; lastname[i] != '\0' || rhs.lastname[i] != '\0'; i++){
        if (lastname[i] > rhs.lastname[i]) {
            return false;
        }
        else if (lastname[i] < rhs.lastname[i]) {
            return true;
        }
    }

    if (rhs.lastname[i] == '\0' && lastname[i] != '\0')
        return false;
    
    for (i = 0; firstname[i] != '\0' || rhs.firstname[i] != '\0'; i++){
        if (firstname[i] > rhs.firstname[i]) {
            return false;
        }
        else if (firstname[i] < rhs.firstname[i]) {
            return true;
        }        
    }

    if (rhs.firstname[i] == '\0' && firstname[i] != '\0')
        return false;

    return true;    

}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
