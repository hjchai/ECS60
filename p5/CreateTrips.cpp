// Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

const int NUM_CITIES = 5700;
using namespace std;

typedef struct 
{
  unsigned departureTime;
  unsigned short duration;
  unsigned originIndex;
  unsigned destinationIndex;
}Flight;


typedef struct
{
  unsigned short departureTime;
  unsigned originIndex;
  unsigned destinationIndex;
} Trip;

unsigned short** readDistances()
{
  ifstream inf("airportDistances.csv");
  char *line = new char[1000000];
  unsigned short **distances = new unsigned short*[NUM_CITIES];
  inf.getline(line, 1000000);
  strtok(line, ",");
  
 
  for(int i = 0; i < NUM_CITIES; i++)
  {
    distances[i] = new unsigned short[NUM_CITIES];
    inf.getline(line, 1000000);
    strtok(line, ",");  // label
    
    for(int j = 0; j < NUM_CITIES; j++)
      distances[i][j] = atoi(strtok(NULL, ","));
  } // for i
  
  delete [] line;
  return distances;
} //readDistances()


void selectCities(short cities[], int num_cities)
{
  int city, j;
  
  for(int i = 0; i < num_cities; i++)
  {
    do
    {
      city = rand() % NUM_CITIES;

      for(j = 0; j < i; j++)
        if(cities[j] == city)
          break;
    } while (j != i);

    cities[i] = city;
  }  // for i
}  // selectCities())


Flight* createFlights(unsigned short **distances, short cities[], 
    int num_cities, int num_flights)
{
  Flight *flights = new Flight[num_flights];

  int flight_num = 0;
  
  for(int i = 0; i < num_cities; i++)  // assure that every city is connected
  {
    flights[flight_num].originIndex = cities[i];
    flights[flight_num].destinationIndex = cities[(i + 1) % num_cities];
    flights[flight_num].duration = distances[cities[i]][cities[(i + 1) % num_cities]] / 8;
    flights[flight_num++].departureTime = rand() % 1440;
  }  // for i
  
  while(flight_num < num_flights)
  {
    int city1, city2, city1Index, city2Index;
    city1Index = rand() % num_cities;
    city1 = cities[city1Index];
    
    do
    {
      city2Index = rand() % num_cities;
    }  while(city1Index == city2Index);
   
    city2 = cities[city2Index];
    flights[flight_num].originIndex = city1;
    flights[flight_num].destinationIndex = city2;
    flights[flight_num].duration = distances[city1][city2] / 8;
    flights[flight_num++].departureTime = rand() % 1440;
  }  // while more flights needed
  
  return flights;
} // createFlights())


Trip* createTrips(short *cities, int num_cities, int num_trips)
{
  Trip *trips = new Trip[num_trips];
  
  for(int i = 0; i < num_trips; i++)
  {
    int city1, city2, city1Index, city2Index;
    
    city1Index = rand() % num_cities;
    city1 = cities[city1Index];
    
    do
    {
      city2Index = rand() % num_cities;
    }  while(city1Index == city2Index);
    
    city2 = cities[city2Index];
   
    trips[i].originIndex = city1;
    trips[i].destinationIndex = city2;
    trips[i].departureTime = rand() % 1440;
  }  // for trips
    
  return trips;
}  // createTrips())


void writeFile(int num_cities, int num_flights, int num_trips, int seed,
  Flight *flights, Trip *trips)
{
  char filename[80];
  sprintf(filename, "trips-%d-%d-%d-%d.txt", num_cities, num_flights, num_trips,
    seed);
  ofstream outf(filename);
  outf << num_cities << ' ' << num_flights << ' ' << num_trips << endl;
  
  for(int i = 0; i < num_flights; i++)
  {
    outf << flights[i].departureTime << ' ' << flights[i].duration << ' '
      << flights[i].originIndex << ' ' << flights[i].destinationIndex <<  endl;
  }  // for each flight
  
   for(int i = 0; i < num_trips; i++)
  {
    outf << trips[i].departureTime  << ' ' << trips[i].originIndex 
      << ' ' << trips[i].destinationIndex <<  endl;
  }  // for each trip
  
  outf.close();
}  // writeFlight

int main(int argc, char** argv)
{
  int num_cities = 10, num_flights = 100, num_trips = 10, seed = 2;
  short cities[NUM_CITIES];
  cout << "Number of cities ( 3 < cities < " << NUM_CITIES << " ): ";
  cin >> num_cities;
  cout << "Number of flights ( > cities): ";
  cin >> num_flights;
  cout << "Number of trips: ";
  cin >> num_trips;
  cout << "Seed: ";
  cin >> seed;   
  srand(seed);
  unsigned short **distances = readDistances();
  selectCities(cities, num_cities);
  Flight *flights = createFlights(distances, cities, num_cities, num_flights);
  Trip *trips = createTrips(cities, num_cities, num_trips);
  writeFile(num_cities, num_flights, num_trips, seed, flights, trips);
  
  return 0;
} // main()


