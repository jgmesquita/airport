#include <iostream>
#include "Methods.cpp"

using namespace std;

void run() {
    vector<Airline> airlines;
    vector<Airport> airports;
    vector<Flight> flights_vector;
    Graph<Airport> flights;
    set<string> cities;
    set<string> countries;
    string input;
    menu();

    while(cin >> input) {
        if (input == "1") {
            airlines = loadAirlines();
            airports = loadAirportsVector(cities, countries);
            flights = loadAirportsGraph();
            flights_vector = loadFlightsVector();
            loadFlights(flights, airports, airlines);
            cout << "The data was loaded!" << endl;
        }
        else if (input == "2") {
            numberAirport(flights);
            numberFlights(flights);
            numberAirlines(airlines);
            numberCountries(countries);
            numberCities(cities);
        }
        else if (input == "3") {
            string airport_code;
            cout << "Introduce the code from the airport!" << endl;
            cin >> airport_code;
            numberFlightsFromAirport(airports, airlines, flights, airport_code);
        }
        else if (input == "4") {
            cout << "Choose one of the following options:" << endl;
            cout << "[0] - Select city!" << endl;
            cout << "[1] - Select airline!" << endl;
            string input2;
            cin >> input2;
            if (input2 == "0") {
                string city;
                cout << "Introduce the name of the city:" << endl;
                cin >> city;
                numberFlightsCity(city, flights);
            }
            else if (input2 == "1") {
                string airline_code;
                cout << "Introduce the airline code:" << endl;
                cin >> airline_code;
                numberFlightsAirline(airline_code, airlines, flights);
            }
        }
        else if (input == "5") {
            string input2;
            cout << "Choose one of the following options:" << endl;
            cout << "[0] - From an airport!" << endl;
            cout << "[1] - From a city!" << endl;
            cin >> input2;
            if (input2 == "0") {
                string airport_code;
                cout << "Introduce the code of the airport:" << endl;
                cin >> airport_code;
                numberCountriesFromAirport(airport_code, airports, flights);

            }
            else if (input2 == "1") {
                string city;
                cout << "Introduce the name of the city:" << endl;
                cin >> city;
                numberCountriesFromCity(city, flights);
            }
        }
        else if (input == "6") {
            string airport_code;
            cout << "Introduce the airport code:" << endl;
            cin >> airport_code;
            string input2;
            cout << "Choose one of the following options:" << endl;
            cout << "[0] - Airports available!" << endl;
            cout << "[1] - Cities available!" << endl;
            cout << "[2] - Countries available!" << endl;
            cin >> input2;
            if (input2 == "0") {
                numberAirportsFromAirport(airport_code, airports, flights);
            }
            else if (input2 == "1") {
                numberCitiesFromAirport(airport_code, airports, flights);
            }
            else if (input2 == "2") {
                numberCountriesFromAirport(airport_code, airports, flights);
            }
        }
        else if (input == "7") {
            int k;
            cout << "Introduce the number of stops:" << endl;
            cin >> k;

            string airport_code;
            cout << "Introduce the code of the airport:" << endl;
            cin >> airport_code;

            string input2;
            cout << "Choose one of the following options:" << endl;
            cout << "[0] - Number of reachable airports!" << endl;
            cout << "[1] - Number of reachable cities!" << endl;
            cout << "[2] - Number of reachable countries!" << endl;
            cin >> input2;
            Graph<Airport>* reference = &flights;
            if (input2 == "0") {
                numberAirportsFromXstops(airport_code, k, airports, reference);
            }
            else if (input2 == "1") {
                numberCitiesFromXstops(airport_code, k, airports, reference);
            }
            else if (input2 == "2") {
                numberCountriesFromXstops(airport_code, k, airports, reference);
            }
        }
        else if (input == "8") {
            Graph<Airport>* reference = &flights;
            FloydWarshallDiameter(reference);
        }
        else if (input == "9") {
            int k;
            cout << "Introduce the size of the list:" << endl;
            cin >> k;
            maximumTraffic(flights, k);
        }
        else if (input == "10") {
            int count = 0;
            Graph<Airport>* reference = &flights;
            auto it = articulationPoints(reference);
            cout << "The following airports are essential for the network's circulation capability:" << endl;
            for (Airport a : it) {
                count++;
                cout << "-> [" << a.getCode() << "] - " << a.getName() << endl;
            }
            cout << "There are " << count << " essential airports!" << endl;
        }
        else if (input == "11") {
            string input2;
            cout << "Choose the initial criteria:" << endl;
            cout << "[0] - By airport code!" << endl;
            cout << "[1] - By city name!" << endl;
            cout << "[2] - By geographical coordinates" << endl;
            cin >> input2;
            string input3;
            cout << "Choose the final criteria:" << endl;
            cout << "[0] - By airport code!" << endl;
            cout << "[1] - By city name!" << endl;
            cout << "[2] - By geographical coordinates" << endl;
            cin >> input3;
            if (input2 == "0" && input3 == "0") {
                Graph<Airport>* reference = &flights;
                string airport_source;
                cout << "Introduce the code of the source airport:" << endl;
                cin >> airport_source;
                string airport_target;
                cout << "Introduce the code of the target airport:" << endl;
                cin >> airport_target;
                bestAirportAirport(reference, airports, airport_source, airport_target, flights_vector);
            }
            else if (input2 == "0" && input3 == "1") {
                Graph<Airport>* reference = &flights;
                string airport_source;
                cout << "Introduce the code of the source airport:" << endl;
                cin >> airport_source;
                string city_target;
                cout << "Introduce the target city:" << endl;
                cin >> city_target;
                bestAirportCity(reference, city_target, airport_source, airports);
            }
            else if (input2 == "0" && input3 == "2") {
                Graph<Airport>* reference = &flights;
                string airport_source;
                cout << "Introduce the code of the source airport:" << endl;
                cin >> airport_source;
                double latitude;
                cout << "Introduce the target latitude:" << endl;
                cin >> latitude;
                double longitude;
                cout << "Introduce the target longitude:" << endl;
                cin >> longitude;
                double radius;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius;
                bestAirportCoordinate(reference, airports, airport_source, latitude, longitude, radius);
            }
            if (input2 == "1" && input3 == "0") {
                Graph<Airport>* reference = &flights;
                string city_source;
                cout << "Introduce the source city:" << endl;
                cin >> city_source;
                string airport_target;
                cout << "Introduce the code of the target airport:" << endl;
                cin >> airport_target;
                bestCityAirport(reference, city_source, airport_target, airports);

            }
            else if (input2 == "1" && input3 == "1") {
                Graph<Airport>* reference = &flights;
                string city_source;
                cout << "Introduce the source city:" << endl;
                cin >> city_source;
                string city_target;
                cout << "Introduce the target city:" << endl;
                cin >> city_target;
                bestCityCity(reference, city_source, city_target, airports);

            }
            else if (input2 == "1" && input3 == "2") {
                Graph<Airport>* reference = &flights;
                string city_source;
                cout << "Introduce the source city:" << endl;
                cin >> city_source;
                double latitude;
                cout << "Introduce the target latitude:" << endl;
                cin >> latitude;
                double longitude;
                cout << "Introduce the target longitude:" << endl;
                cin >> longitude;
                double radius;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius;
                bestCityCoordinate(reference, airports, city_source, latitude, longitude, radius);
            }
            if (input2 == "2" && input3 == "0") {
                Graph<Airport>* reference = &flights;
                double latitude;
                cout << "Introduce the source latitude:" << endl;
                cin >> latitude;
                double longitude;
                cout << "Introduce the source longitude:" << endl;
                cin >> longitude;
                double radius;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius;
                string airport_target;
                cout << "Introduce the target airport code:" << endl;
                cin >> airport_target;
                bestCoordinateAirport(reference, airports, airport_target, latitude, longitude, radius);
            }
            else if (input2 == "2" && input3 == "1") {
                Graph<Airport>* reference = &flights;
                double latitude;
                cout << "Introduce the source latitude:" << endl;
                cin >> latitude;
                double longitude;
                cout << "Introduce the source longitude:" << endl;
                cin >> longitude;
                double radius;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius;
                string city_target;
                cout << "Introduce the target city:" << endl;
                cin >> city_target;
                bestCoordinateCity(reference, airports, city_target, latitude, longitude, radius);
            }
            else if (input2 == "2" && input3 == "2") {
                Graph<Airport>* reference = &flights;
                double latitude_source;
                cout << "Introduce the source latitude:" << endl;
                cin >> latitude_source;
                double longitude_source;
                cout << "Introduce the source longitude:" << endl;
                cin >> longitude_source;
                double radius_source;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius_source;
                double latitude_target;
                cout << "Introduce the target latitude:" << endl;
                cin >> latitude_target;
                double longitude_target;
                cout << "Introduce the target longitude:" << endl;
                cin >> longitude_target;
                double radius_target;
                cout << "Introduce the maximum radius:" << endl;
                cin >> radius_target;
                bestCoordinateCoordinate(reference, airports, latitude_source, longitude_source, radius_source, latitude_target, longitude_target, radius_target);
            }
        }
        else if (input == "12") {
            continue;
        }
        menu();
    }
}

int main() {
    cout << "The program is running!" << endl;
    run();
    return 0;
}
