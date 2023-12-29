#include <fstream>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_set>
#include "Airport.cpp"
#include "Airline.cpp"
#include "Flight.cpp"
#include "Graph.h"

using namespace std;

double haversineAirport(Airport a1, Airport a2) {
    double dLat = (stod(a2.getLatitude()) - stod(a1.getLatitude())) * M_PI / 180.0;
    double dLon = (stod(a2.getLongitude()) - stod(a1.getLongitude())) * M_PI / 180.0;

    double lat_a1 = stod(a1.getLatitude()) * M_PI / 180.0;
    double lat_a2 = stod(a2.getLatitude()) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat_a1) * cos(lat_a2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

Graph<Airport> loadAirportsGraph() {
    Graph<Airport> flights;
    ifstream inputFile("airports.csv");
    string line;
    bool isFirstLine = true;
    while (getline(inputFile, line)) {
        vector<string> temp;
        istringstream stream(line);
        string in;
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        while (getline(stream, in, ',')) {
            temp.push_back(in);
        }
        string code = temp[0];
        string name = temp[1];
        string city = temp[2];
        string country = temp[3];
        string latitude = temp[4];
        string longitude = temp[5];
        Airport a = Airport(code, name, city, country, latitude, longitude);
        flights.addVertex(a);
    }
    return flights;
}

vector<Airport> loadAirportsVector(set<string>& cities, set<string>& countries) {
    vector<Airport> airports;
    ifstream inputFile("airports.csv");
    string line;
    bool isFirstLine = true;
    while (getline(inputFile, line)) {
        vector<string> temp;
        istringstream stream(line);
        string in;
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        while (getline(stream, in, ',')) {
            temp.push_back(in);
        }
        string code = temp[0];
        string name = temp[1];
        string city = temp[2];
        string country = temp[3];
        string latitude = temp[4];
        string longitude = temp[5];
        Airport a = Airport(code, name, city, country, latitude, longitude);
        airports.push_back(a);
        countries.insert(country);
        cities.insert(city);
    }
    return airports;
}

vector<Airline> loadAirlines() {
    vector<Airline> airlines;
    ifstream inputFile("airlines.csv");
    string line;
    bool isFirstLine = true;
    while (getline(inputFile, line)) {
        vector<string> temp;
        istringstream stream(line);
        string in;
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        while (getline(stream, in, ',')) {
            temp.push_back(in);
        }
        string code = temp[0];
        string name = temp[1];
        string callsign = temp[2];
        string country = temp[3];
        Airline a = Airline(code, name, callsign, country);
        airlines.push_back(a);
    }
    return airlines;
}

vector<Flight> loadFlightsVector() {
    ifstream inputFile("flights.csv");
    vector<Flight> flights_vector;
    string line;
    bool isFirstLine = true;
    while (getline(inputFile, line)) {
        vector<string> temp;
        istringstream stream(line);
        string in;
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        while (getline(stream, in, ',')) {
            temp.push_back(in);
        }
        string source = temp[0];
        string target = temp[1];
        string airline_code = temp[2];
        Flight f = Flight(source, target, airline_code);
        flights_vector.push_back(f);
    }
    return flights_vector;
}

void loadFlights(Graph<Airport>& flights, vector<Airport>& airports, vector<Airline> airlines) {
    ifstream inputFile("flights.csv");
    string line;
    bool isFirstLine = true;
    while (getline(inputFile, line)) {
        vector<string> temp;
        istringstream stream(line);
        string in;
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        while (getline(stream, in, ',')) {
            temp.push_back(in);
        }
        string source = temp[0];
        string target = temp[1];
        string airline_code = temp[2];

        Airport x;
        Airport y;
        Airline z;

        for (Airport& a : airports) {
            if (a.getCode() == source) {
                x = a;
            }
        }
        for (Airport& b : airports) {
            if (b.getCode() == target) {
                y = b;
            }
        }
        unsigned n = 0;
        for (Airline& c : airlines) {
            if (c.getCode() == airline_code) {
                break;
            }
            n++;
        }
        flights.addEdge(x, y, haversineAirport(x, y), n);
    }
}

void numberAirport(Graph<Airport>& flights) {
    cout << "The number of airports is: " << flights.getVertexSet().size() << endl;
}
void numberFlights(Graph<Airport>& flights) {
    unsigned count = 0;
    auto v = flights.getVertexSet();
    for (auto vertex : v) {
        count += vertex->getAdj().size();
    }
    cout << "The number of flights is: " << count << endl;
}

void numberAirlines(vector<Airline>& airlines) {
    cout << "The number of airlines is: " << airlines.size() << endl;
}

void numberCountries(set<string>& countries) {
    cout << "The number of countries is: " << countries.size() << endl;
}

void numberCities(set<string>& cities) {
    cout << "The number of cities is: " << cities.size() << endl;
}

void numberFlightsFromAirport(vector<Airport>& airports, vector<Airline>& airlines, Graph<Airport>& flights, string airport_code) {
    set<unsigned> airlines_set;
    Airport airport;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Airport not found!" << endl;
        return;
    }

    unsigned global = 0;
    cout << "The airport " << airport.getName() << " [" << airport_code << "] has the following flights: \n" << endl;
    auto v = flights.findVertex(airport);
    for (auto e : v->getAdj()) {
        auto v2 = e.getDest();
        airlines_set.insert(e.getAirline());
        global++;
        cout << "-> " << v2->getInfo().getName() << " [" << v2->getInfo().getCode() << "] by " << airlines[e.getAirline()].getName() << " with a distance of " << e.getWeight() << " km!" << endl;
    }
    cout << "\nThe total of flights is " << global << " and the total of airlines is " << airlines_set.size() << "!" << endl;
}

void numberFlightsCity(string& city, Graph<Airport>& flights) {
    unsigned global = 0;
    auto vertexSet = flights.getVertexSet();
    for (auto v : vertexSet) {
        if (v->getInfo().getCity() == city) {
            global += v->getAdj().size();
        }
    }
    cout << "The following city has " << global << " flights" << endl;
}

void numberFlightsAirline(string& airline_code, vector<Airline>& airlines, Graph<Airport>& flights) {
    unsigned global = 0;
    unsigned count = 0;
    auto it = airlines.begin();
    for (; it != airlines.end(); it++) {
        if (it->getCode() == airline_code) {
            break;
        }
        count++;
    }

    if (it == airlines.end()) {
        cout << "Airline not found!" << endl;
        return;
    }

    auto vertexSet = flights.getVertexSet();
    for (auto v : vertexSet) {
        for (auto w : v->getAdj()) {
            if (w.getAirline() == count) {
                global++;
            }
        }
    }
    cout << "The following airline has " << global << " flights!" << endl;
}

void numberAirportsFromAirport(string& airport_code, vector<Airport>& airports, Graph<Airport>& flights) {
    set<Airport> counter;
    Airport airport;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Airport not found!" << endl;
        return;
    }
    auto v = flights.findVertex(airport);
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        counter.insert(w->getInfo());
    }
    cout << "The following airports can be reached from [" << airport_code << "]:" << endl;
    for (auto it : counter) {
        cout << "["<< it.getCode() << "]" << " " << it.getName() << " !" << endl;
    }
    cout << "The following airport has " << counter.size() << " airports has a destination!" << endl;
}

void numberCitiesFromAirport(string& airport_code, vector<Airport>& airports, Graph<Airport>& flights) {
    set<string> cities;
    Airport airport;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Airport not found!" << endl;
        return;
    }
    auto vertexSet = flights.getVertexSet();
    for (auto v : vertexSet) {
        if (v->getInfo() == airport) {
            for (auto w: v->getAdj()) {
                string city = w.getDest()->getInfo().getCity();
                cities.insert(city);
            }
        }
    }
    cout << "The following cities can be reached from [" << airport_code << "]:" << endl;
    for (auto it : cities) {
        cout << it << "!" << endl;
    }
    cout << "The following airport has " << cities.size() << " cities has a destination!" << endl;
}

void numberCountriesFromAirport(string& airport_code, vector<Airport>& airports, Graph<Airport>& flights) {
    set<string> countries;
    Airport airport;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Airport not found!" << endl;
        return;
    }
    auto vertexSet = flights.getVertexSet();
    for (auto v : vertexSet) {
        if (v->getInfo() == airport) {
            for (auto w: v->getAdj()) {
                string country = w.getDest()->getInfo().getCountry();
                countries.insert(country);
            }
        }
    }
    cout << "The following countries can be reached from [" << airport_code << "]:" << endl;
    for (auto it : countries) {
        cout << it << "!" << endl;
    }
    cout << "The following airport has " << countries.size() << " countries has a destination!" << endl;
}

void numberCountriesFromCity(string& city, Graph<Airport>& flights) {
    set<string> countries;
    auto vertexSet = flights.getVertexSet();
    for (auto v : vertexSet) {
        if (v->getInfo().getCity() == city) {
            for (auto w : v->getAdj()) {
                countries.insert(w.getDest()->getInfo().getCountry());
            }
        }
    }
    cout << "The following city has " << countries.size() << " countries has a destination!" << endl;
}

void numberAirportsFromXstops(string& airport_code, int k, vector<Airport>& airports, Graph<Airport>* flights) {
    set<pair<Airport,int>> reachable;
    queue<Vertex<Airport>*> temp;
    int level = 0;
    auto vertexSet = flights->getVertexSet();
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    Airport x;
    for (Airport& a : airports) {
        if (a.getCode() == airport_code) {
            x = a;
        }
    }
    auto v = flights->findVertex(x);
    temp.push(v);
    v->setVisited(true);
    while(!temp.empty() && level <= k) {
        int size = temp.size();
        for (int i = 0; i < size; i++) {
            auto u = temp.front();
            reachable.insert({u->getInfo(), level});
            temp.pop();
            for (auto &e: u->getAdj()) {
                auto w = e.getDest();
                if (!w->isVisited()) {
                    temp.push(w);
                    w->setVisited(true);
                }
            }
        }
        level++;
    }
    for (int i = 1; i <= k; i++) {
        set<Airport> airports_set;
        cout << "\nThe following airports can be reached by " << i << " stops:\n" << endl;
        for (auto it : reachable) {
            if (it.second == i) {
                if (airports_set.find(it.first) == airports_set.end()) {
                    cout << "[" << it.first.getCode() << "]" << " " << it.first.getName() << "!" << endl;
                    airports_set.insert(it.first);
                }
            }
        }
    }
}

void numberCitiesFromXstops(string& airport_code, int k, vector<Airport>& airports, Graph<Airport>* flights) {
    set<pair<Airport,int>> reachable;
    queue<Vertex<Airport>*> temp;
    int level = 0;
    auto vertexSet = flights->getVertexSet();
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    Airport x;
    for (Airport& a : airports) {
        if (a.getCode() == airport_code) {
            x = a;
        }
    }
    auto v = flights->findVertex(x);
    temp.push(v);
    v->setVisited(true);
    while(!temp.empty() && level <= k) {
        int size = temp.size();
        for (int i = 0; i < size; i++) {
            auto u = temp.front();
            reachable.insert({u->getInfo(), level});
            temp.pop();
            for (auto &e: u->getAdj()) {
                auto w = e.getDest();
                if (!w->isVisited()) {
                    temp.push(w);
                    w->setVisited(true);
                }
            }
        }
        level++;
    }
    for (int i = 1; i <= k; i++) {
        set<string> cities;
        cout << "\nThe following cities can be reached by " << i << " stops:\n" << endl;
        for (auto it : reachable) {
            if (it.second == i) {
                if (cities.find(it.first.getCity()) == cities.end()) {
                    cout << it.first.getCity() << "!" << endl;
                    cities.insert(it.first.getCity());
                }
            }
        }
    }
}

void numberCountriesFromXstops(string& airport_code, int k, vector<Airport>& airports, Graph<Airport>* flights) {
    set<pair<Airport,int>> reachable;
    queue<Vertex<Airport>*> temp;
    int level = 0;
    auto vertexSet = flights->getVertexSet();
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    Airport x;
    for (Airport& a : airports) {
        if (a.getCode() == airport_code) {
            x = a;
        }
    }
    auto v = flights->findVertex(x);
    temp.push(v);
    v->setVisited(true);
    while(!temp.empty() && level <= k) {
        int size = temp.size();
        for (int i = 0; i < size; i++) {
            auto u = temp.front();
            reachable.insert({u->getInfo(), level});
            temp.pop();
            for (auto &e: u->getAdj()) {
                auto w = e.getDest();
                if (!w->isVisited()) {
                    temp.push(w);
                    w->setVisited(true);
                }
            }
        }
        level++;
    }
    for (int i = 1; i <= k; i++) {
        set<string> countries;
        cout << "\nThe following countries can be reached by " << i << " stops:\n" << endl;
        for (auto it : reachable) {
            if (it.second == i) {
                if (countries.find(it.first.getCountry()) == countries.end()) {
                    cout << it.first.getCountry() << "!" << endl;
                    countries.insert(it.first.getCountry());
                }
            }
        }
    }
}



bool compare(pair<Airport, unsigned> p1, pair<Airport, unsigned> p2) {
    return p1.second > p2.second;
}

map<Airport,unsigned> maximumPartida(Graph<Airport>& flights, int k) {
    map<Airport,unsigned> traffic;
    for (auto w : flights.getVertexSet()) {
        traffic.insert({w->getInfo(),w->getAdj().size()});
    }
    vector<pair<Airport, unsigned>> temp;
    for (auto it : traffic) {
        temp.push_back(it);
    }
    sort(temp.begin(), temp.end(), compare);
    cout << "The following list contains the airports with the most departure traffic: " << endl;
    for (int i = 0; i < k; i++) {
        cout << "-> " << temp[i].first.getName() << " [" << temp[i].first.getCode() << "] with the traffic of " << temp[i].second << " flights!" << endl;
    }
    cout << endl;
    return traffic;
}

map<Airport,unsigned> maximumChegada(Graph<Airport>& flights, int k) {
    map<Airport,unsigned> traffic;
    for (auto w : flights.getVertexSet()) {
        unsigned count = 0;
        for (auto v : flights.getVertexSet()) {
            for (auto& e : v->getAdj()) {
                if (w->getInfo() == e.getDest()->getInfo()) {
                    count++;
                }
            }
        }
        traffic.insert({w->getInfo(), count});
    }
    vector<pair<Airport, unsigned>> temp;
    for (auto it : traffic) {
        temp.push_back(it);
    }
    sort(temp.begin(), temp.end(), compare);
    cout << "The following list contains the airports with the most coming traffic: " << endl;
    for (int i = 0; i < k; i++) {
        cout << "-> " << temp[i].first.getName() << " [" << temp[i].first.getCode() << "] with the traffic of " << temp[i].second << " flights!" << endl;
    }
    cout << endl;
    return traffic;
}


void maximumTraffic(Graph<Airport>& flights, int k) {
    map<Airport, unsigned> traffic1 = maximumChegada(flights, k);
    map<Airport, unsigned> traffic2 = maximumPartida(flights, k);
    map<Airport, unsigned> traffic;
    for (auto it : traffic1) {
        traffic.insert(it);
    }
    for (auto it : traffic2) {
        traffic[it.first] += it.second;
    }
    vector<pair<Airport, unsigned>> temp;
    for (auto it : traffic) {
        temp.push_back(it);
    }
    sort(temp.begin(), temp.end(), compare);
    cout << "The following list contains the airports with the most traffic in general: " << endl;
    for (int i = 0; i < k; i++) {
        cout << "-> " << temp[i].first.getName() << " [" << temp[i].first.getCode() << "] with the traffic of " << temp[i].second << " flights!" << endl;
    }
}

void dfs_art(Graph<Airport> *g, Vertex<Airport> *v, stack<Airport> &s, unordered_set<Airport, HashAirport, HashAirport> &l, int &i){
    v->setVisited(true);
    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    s.push(v->getInfo());
    i++;

    int count = 0;

    for (auto& e: v->getAdj()) {
        auto w = e.getDest();
        if(!w->isVisited()) {
            count++;
            dfs_art(g,w,s,l,i);
            v->setLow(min(v->getLow(), w->getLow()));
            if (w->getLow() >= v->getNum() && v->getNum() != 1) {
                l.insert(v->getInfo());
            }
        }
        else if (w->isProcessing()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
        if (count > 1 && v->getNum() == 1) {
            l.insert(v->getInfo());
        }
    }
    v->setProcessing(false);
    s.pop();
}

unordered_set<Airport, HashAirport, HashAirport> articulationPoints(Graph<Airport> *g) {
    unordered_set<Airport, HashAirport, HashAirport> res;
    stack<Airport> s;
    int index = 1;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    for (auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            dfs_art(g, v,s, res, index);
        }
    }
    return res;
}

void interfacePath(vector<Airport> airports, vector<Flight> flights_vector) {
    for (unsigned i = 0; i < airports.size() - 1; i++) {
        set<string> airlines;
        for (auto it : flights_vector) {
            if (it.getSource() == airports[i].getCode() && it.getTarget() == airports[i+1].getCode()) {
                airlines.insert(it.getAirline());
            }
        }
        cout << "From " << airports[i].getCode() << " to " << airports[i+1].getCode() << " by the following airlines:" << endl;
        for (auto it : airlines) {
            cout << "-> " << it << endl;
        }
    }
}

void bestAirportAirport(Graph<Airport>* flights, vector<Airport>& airports, string airport_code1, string airport_code2, vector<Flight> flights_vector) {
    Airport airport1;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code1) {
            airport1 = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Source airport not found!" << endl;
        return;
    }
    Airport airport2;
    auto it2 = airports.begin();
    for (; it2 != airports.end(); it2++) {
        if (it2->getCode() == airport_code2) {
            airport2 = *it2;
            break;
        }
    }
    if (it2 == airports.end()) {
        cout << "Target airport not found!" << endl;
        return;
    }
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestAirportCity(Graph<Airport>* flights, string city, string airport_code, vector<Airport> airports, vector<Flight> flights_vector) {
    Airport airport1;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport1 = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Source airport not found!" << endl;
        return;
    }
    vector<Airport> temp;
    for (Airport a : airports) {
        if (a.getCity() == city) {
            temp.push_back(a);
        }
    }
    if (temp.empty()) {
        cout << "Target city not found!" << endl;
        return;
    }
    cout << "For the following city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp.size(); i++) {
        cout << "[" << i << "] - Name: " << temp[i].getName() << " Code: " << temp[i].getCode() << endl;
    }
    unsigned number;
    cout << "Choose its index:" << endl;
    cin >> number;
    Airport airport2 = temp[number];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

double haversineAirportCoordinate(Airport a1, double latitude, double longitude) {
    double dLat = (latitude - stod(a1.getLatitude())) * M_PI / 180.0;
    double dLon = (longitude - stod(a1.getLongitude())) * M_PI / 180.0;

    double lat_a1 = stod(a1.getLatitude()) * M_PI / 180.0;
    double lat_a2 = latitude * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat_a1) * cos(lat_a2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void bestAirportCoordinate(Graph<Airport>* flights, vector<Airport> airports, string airport_code, double latitude, double longitude, double radius, vector<Flight> flights_vector) {
    Airport airport1;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport1 = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Source airport not found!" << endl;
        return;
    }
    vector<Airport> temp;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude, longitude) <= radius) {
            temp.push_back(a);
        }
    }
    if (temp.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following target coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp.size(); i++) {
        cout << "[" << i << "] - Name: " << temp[i].getName() << " Code: " << temp[i].getCode() << endl;
    }
    unsigned number;
    cout << "Choose its index:" << endl;
    cin >> number;
    Airport airport2 = temp[number];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCityAirport(Graph<Airport>* flights, string city, string airport_code, vector<Airport> airports, vector<Flight> flights_vector) {
    Airport airport2;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport2 = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Source airport not found!" << endl;
        return;
    }
    vector<Airport> temp;
    for (Airport a : airports) {
        if (a.getCity() == city) {
            temp.push_back(a);
        }
    }
    if (temp.empty()) {
        cout << "Target city not found!" << endl;
        return;
    }
    cout << "For the following target city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp.size(); i++) {
        cout << "[" << i << "] - Name: " << temp[i].getName() << " Code: " << temp[i].getCode() << endl;
    }
    unsigned number;
    cout << "Choose its index:" << endl;
    cin >> number;
    Airport airport1 = temp[number];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCityCity(Graph<Airport>* flights, string city1, string city2, vector<Airport> airports, vector<Flight> flights_vector) {
    vector<Airport> temp1;
    for (Airport a : airports) {
        if (a.getCity() == city1) {
            temp1.push_back(a);
        }
    }
    if (temp1.empty()) {
        cout << "Source city not found!" << endl;
        return;
    }
    cout << "For the following source city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp1.size(); i++) {
        cout << "[" << i << "] - Name: " << temp1[i].getName() << " Code: " << temp1[i].getCode() << endl;
    }
    unsigned number1;
    cout << "Choose its index:" << endl;
    cin >> number1;
    Airport airport1 = temp1[number1];

    vector<Airport> temp2;
    for (Airport a : airports) {
        if (a.getCity() == city2) {
            temp2.push_back(a);
        }
    }
    if (temp2.empty()) {
        cout << "Target city not found!" << endl;
        return;
    }
    cout << "For the following target city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp2.size(); i++) {
        cout << "[" << i << "] - Name: " << temp2[i].getName() << " Code: " << temp2[i].getCode() << endl;
    }
    unsigned number2;
    cout << "Choose its index:" << endl;
    cin >> number2;
    Airport airport2 = temp2[number2];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCityCoordinate(Graph<Airport>* flights, vector<Airport> airports, string city, double latitude, double longitude, double radius, vector<Flight> flights_vector) {
    vector<Airport> temp1;
    for (Airport a : airports) {
        if (a.getCity() == city) {
            temp1.push_back(a);
        }
    }
    if (temp1.empty()) {
        cout << "Source city not found!" << endl;
        return;
    }
    cout << "For the following source city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp1.size(); i++) {
        cout << "[" << i << "] - Name: " << temp1[i].getName() << " Code: " << temp1[i].getCode() << endl;
    }
    unsigned number1;
    cout << "Choose its index:" << endl;
    cin >> number1;
    Airport airport1 = temp1[number1];

    vector<Airport> temp2;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude, longitude) <= radius) {
            temp2.push_back(a);
        }
    }
    if (temp2.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following target coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp2.size(); i++) {
        cout << "[" << i << "] - Name: " << temp2[i].getName() << " Code: " << temp2[i].getCode() << endl;
    }
    unsigned number2;
    cout << "Choose its index:" << endl;
    cin >> number2;
    Airport airport2 = temp2[number2];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCoordinateAirport(Graph<Airport>* flights, vector<Airport> airports, string airport_code, double latitude, double longitude, double radius, vector<Flight> flights_vector) {
    vector<Airport> temp;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude, longitude) <= radius) {
            temp.push_back(a);
        }
    }
    if (temp.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp.size(); i++) {
        cout << "[" << i << "] - Name: " << temp[i].getName() << " Code: " << temp[i].getCode() << endl;
    }
    unsigned number;
    cout << "Choose its index:" << endl;
    cin >> number;
    Airport airport1 = temp[number];

    Airport airport2;
    auto it = airports.begin();
    for (; it != airports.end(); it++) {
        if (it->getCode() == airport_code) {
            airport1 = *it;
            break;
        }
    }
    if (it == airports.end()) {
        cout << "Source airport not found!" << endl;
        return;
    }
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCoordinateCity(Graph<Airport>* flights, vector<Airport> airports, string city, double latitude, double longitude, double radius, vector<Flight> flights_vector) {
    vector<Airport> temp1;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude, longitude) <= radius) {
            temp1.push_back(a);
        }
    }
    if (temp1.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp1.size(); i++) {
        cout << "[" << i << "] - Name: " << temp1[i].getName() << " Code: " << temp1[i].getCode() << endl;
    }
    unsigned number1;
    cout << "Choose its index:" << endl;
    cin >> number1;
    Airport airport1 = temp1[number1];

    vector<Airport> temp2;
    for (Airport a : airports) {
        if (a.getCity() == city) {
            temp2.push_back(a);
        }
    }
    if (temp2.empty()) {
        cout << "Target city not found!" << endl;
        return;
    }
    cout << "For the following city, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp2.size(); i++) {
        cout << "[" << i << "] - Name: " << temp2[i].getName() << " Code: " << temp2[i].getCode() << endl;
    }
    unsigned number2;
    cout << "Choose its index:" << endl;
    cin >> number2;
    Airport airport2 = temp2[number2];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

void bestCoordinateCoordinate(Graph<Airport>* flights, vector<Airport> airports, double latitude_source, double longitude_source, double radius_source, double latitude_target, double longitude_target, double radius_target, vector<Flight> flights_vector) {
    vector<Airport> temp1;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude_source, longitude_source) <= radius_source) {
            temp1.push_back(a);
        }
    }
    if (temp1.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp1.size(); i++) {
        cout << "[" << i << "] - Name: " << temp1[i].getName() << " Code: " << temp1[i].getCode() << endl;
    }
    unsigned number1;
    cout << "Choose its index:" << endl;
    cin >> number1;
    Airport airport1 = temp1[number1];

    vector<Airport> temp2;
    for (Airport a : airports) {
        if (haversineAirportCoordinate(a, latitude_target, longitude_target) <= radius_target) {
            temp2.push_back(a);
        }
    }
    if (temp2.empty()) {
        cout << "No airports found with the information provided!" << endl;
        return;
    }
    cout << "For the following coordinates, there are the following airports:" << endl;
    for (unsigned i = 0; i < temp2.size(); i++) {
        cout << "[" << i << "] - Name: " << temp2[i].getName() << " Code: " << temp2[i].getCode() << endl;
    }
    unsigned number2;
    cout << "Choose its index:" << endl;
    cin >> number2;
    Airport airport2 = temp2[number2];
    auto v = flights->dijkstra(airport1, airport2);
    interfacePath(v, flights_vector);
}

bool findEdge(Vertex<Airport>* source, Vertex<Airport>* target) {
    for (auto& e : source->getAdj()) {
        auto w = e.getDest();
        if (w->getInfo() == target->getInfo()) {
            return true;
        }
    }
    return false;
}

void FloydWarshallDiameter(Graph<Airport>* g) {
    int n = g->getNumVertex();
    auto vset = g->getVertexSet();
    vector<vector<int>> matrix (n, vector<int>(n));

    //Creation of the matrix NxN
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                if (findEdge(vset[i], vset[j])) {
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = numeric_limits<int>::max();
                }
            }
        }
    }
    // Floyd-Warshall's Algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] != numeric_limits<int>::max() &&
                    matrix[k][j] != numeric_limits<int>::max() &&
                    matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }

    // Find the maximum distance (diameter) in the matrix
    int diameter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != numeric_limits<int>::max() && matrix[i][j] > diameter) {
                diameter = matrix[i][j];
            }
        }
    }

    // Print or use the diameter as needed
    cout << "Diameter of the graph: " << diameter << endl;
}

Graph<Airport> createCustomGraph(vector<Airport> airports, vector<Flight> flights_vector) {
    Graph<Airport> g;
    string airport_code;
    cout << "Introduce the code of the airports you wish to travel:" << endl;
    while(cin >> airport_code) {
        auto it = airports.begin();
        for (; it != airports.end(); it++) {
            if (it->getCode() == airport_code) {
                g.addVertex(*it);
                break;
            }
        }
        if (it == airports.end()) {
            cout << "Invalid airport! Try another one!" << endl;
            continue;
        }
        string input;
        cout << "Add more airports? [Yes/No]" << endl;
        cin >> input;
        if (input == "Yes") {
            cout << "Airport Code: " << endl;
            continue;
        }
        else if (input == "No") {
            break;
        }
        else {
            cout << "Invalid input! Try again!" << endl;
            continue;
        }
    }
    cout << "Introduce the code of the airline you wish to travel:" << endl;
    string airline_code;
    while(cin >> airline_code) {
        unsigned count = 0;
        auto it = flights_vector.begin();
        for (; it != flights_vector.end(); it++) {
            if (it->getAirline() == airline_code) {
                string a1 = it->getSource();
                string a2 = it->getTarget();
                Airport x;
                Airport y;
                for (Airport a : airports) {
                    if (a.getCode() == a1) {
                        x = a;
                    }
                    else if (a.getCode() == a2) {
                        y = a;
                    }
                }
                break;
                g.addEdge(x,y, haversineAirport(x,y), count);
            }
            count++;
        }
        if (it == flights_vector.end()) {
            cout << "Invalid airport! Try another one!" << endl;
            continue;
        }
        string input;
        cout << "Add more airlines? [Yes/No]" << endl;
        cin >> input;
        if (input == "Yes") {
            cout << "Airline Code: " << endl;
            continue;
        }
        else if (input == "No") {
            break;
        }
        else {
            cout << "Invalid input! Try again!" << endl;
            continue;
        }
    }
    return g;
}

void menu() {
    cout << "###################################################################################################" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "[1]  - Load data from files!" << endl; //Full Working
    cout << "[2]  - See the global number of airports and available flights! " << endl; //Full Working
    cout << "[3]  - See the number of flights out of an airport and from how many airlines!" << endl; //Full Working
    cout << "[4]  - See the number of flights of a given airline/city!" << endl; //Only city working!
    cout << "[5]  - See the number of different countries of a given airport/city" << endl; //Full Working
    cout << "[6]  - See the number of destinations available for a given airport!" << endl; //Full Working
    cout << "[7]  - See the number of reachable destinations from a given airport in a maximum number of X stops!" << endl; //Full Working
    cout << "[8]  - See the maximum trip and corresponding pair source-destination airports!" << endl; //TODO
    cout << "[9]  - See the airport with the greatest air traffic capacity!" << endl; //Full Working
    cout << "[10] - See the essential airports to the network's circulation capability!" << endl; //Full Working
    cout << "[11] - Present the best flight option!" << endl; //Full Working
    cout << "[12] - Search for the best flight option with filters!" << endl; //TODO
    cout << "[0]  - Exit the program!" << endl; //Full Working
    cout << "###################################################################################################" << endl;
}