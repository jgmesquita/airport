#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;

public:
    /**
     * @brief Constructor for the Airport Class.
     * @param code Code of the Airport.
     * @param name Name of the Airport.
     * @param city City of the Airport.
     * @param country Country of the Airport.
     * @param latitude Latitude of the Airport.
     * @param longitude Longitude of the Airport.
     */
    Airport(string code, string name, string city, string country, string latitude, string longitude) {
        this->code = code;
        this->name = name;
        this->city = city;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    /**
     * @brief Default constructor.
     */
    Airport() {}
    /**
     * @brief Get the code of the airport.
     * @return Code of the airport.
     */
    string getCode() {
        return this->code;
    }
    /**
     * @brief Get the name of the airport.
     * @return Name of the airport.
     */
    string getName() {
        return this->name;

    }
    /**
     * @brief Get the city of the airport.
     * @return City of the airport.
     */
    string getCity() {
        return this->city;
    }
    /**
     * @brief Get the country of the airport.
     * @return Country of the airport
     */
    string getCountry() {
        return this->country;
    }
    /**
     * @brief Get the latitude of the airport.
     * @return Latitude of the airport.
     */
    string getLatitude() {
        return this->latitude;
    }
    /**
     * @brief Get the longitude of the airport.
     * @return Longitude of the airport.
     */
    string getLongitude() {
        return this->longitude;
    }
    /**
     * @brief Overloading of the operator ==.
     * @param a2 Second object.
     * @return Boolean value if both objects are the same.
     */
    bool operator == (const Airport &a2) const {
        return this->code == a2.code;
    }
    /**
     * @brief Overloading of the operator <.
     * @param a2 Second object.
     * @return Boolean value.
     */
    bool operator < (const Airport &a2) const {
        return this->code < a2.code;
    }
};
/**
 * @brief Struct to use unordered set container.
 */
struct HashAirport {
    bool operator() (Airport a1, Airport a2) const {
        return a1.getCode() == a2.getCode();
    }
    int operator() (Airport a) const {
        string s1 = a.getCode();
        int v = 0;
        for (unsigned int i = 0; i < s1.size(); i++) {
            v = 37*v + s1[i];
        }
        return v;
    }
};