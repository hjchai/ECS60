// Author: Sean Davis

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "TripsRunner.h"
#include "router.h"
#include "CPUTimer.h"

typedef struct
{
  int originIndex;
  int destinationIndex;
} CityIndices;


using namespace std;

void readFile(Flight **flights2, Trip **trips2, int *numTrips, int *numFlights, 
  int *numCities, const char *filename, Flight **flights3)
{
  ifstream inf(filename);
  inf >> *numCities >> *numFlights >> *numTrips;
  Flight *flights = new Flight[*numFlights];
  Flight *flights1 = new Flight[*numFlights];
  Trip *trips = new Trip[*numTrips];
  inf.ignore(1000, '\n');
  
  for(int i = 0; i < *numFlights; i++)
  {
    flights[i].flightNum = i;
    inf >> flights[i].departureTime >> flights[i].duration 
      >> flights[i].originIndex >> flights[i].destinationIndex;
    flights1[i] = flights[i];
  }  // for each flight
  
   for(int i = 0; i < *numTrips; i++)
    inf >> trips[i].departureTime >> trips[i].originIndex 
      >> trips[i].destinationIndex;
  
  *flights2 = flights;
  *flights3 = flights1;
  *trips2 = trips;
}  // readFile())


int checkRoutes(Flight *flights, Trip *trips, int numTrips, int numFlights, 
  Itinerary *itineraries, int argc, char **argv)
{
  unsigned currentCityIndex, flightNum, currentCityTime, tripTime, totalTime = 0,
    dayCount;
  ofstream outf;
  
  if(argc > 2)
    outf.open(argv[2]);
  
  for(int i = 0; i < numTrips; i++)
  {
    
    if(argc > 2)
      outf << i << ": (" << trips[i].departureTime << ") ";
    
    currentCityIndex = trips[i].originIndex;
    currentCityTime = trips[i].departureTime;
    tripTime = 0;
    dayCount = 0;
    
    for(int j = 0; j < itineraries[i].numFlights; j++)
    {
      flightNum = itineraries[i].flightNums[j];
      
      if(argc > 2)
        outf << flightNum << '(' << flights[flightNum].departureTime << ","
          << (flights[flightNum].duration + flights[flightNum].departureTime) % 1440
          << ") ";
      
      if(flights[flightNum].originIndex != currentCityIndex)
        cout << "\nTrip #" << i << " connection #" << j << " starts at "
          << flights[flightNum].originIndex << " instead of " 
          << currentCityIndex << endl;
      
      if(flights[flightNum].departureTime < currentCityTime) // next day
        dayCount++;
      
      currentCityIndex = flights[flightNum].destinationIndex;
      currentCityTime = flights[flightNum].departureTime 
        + flights[flightNum].duration;
      
      if(currentCityTime > 1440)
      {
        currentCityTime %= 1440;
        dayCount++;
      }
      
      if(j + 1 < itineraries[i].numFlights)  // not last flight so add necessary wait
        currentCityTime += 30;
    }  // for each connection 
    
   
   
    if(flights[flightNum].destinationIndex != trips[i].destinationIndex)
      cout << "\nTrip #" << i << " ends at " << flights[flightNum].destinationIndex 
        << " instead of " << trips[i].destinationIndex << endl;
    
    tripTime =  ((flights[flightNum].departureTime + flights[flightNum].duration) % 1440) 
      - trips[i].departureTime + dayCount * 1440;
    totalTime += tripTime;

    if(argc > 2)
      outf << "= " << tripTime << endl;
  } // for each trip

  if(argc > 2)
  {
    outf << "Total time: "  << totalTime << endl;
    outf.close();
  } // if printing solution
  
  cout << " Total time: " << totalTime << endl;
  return totalTime;
} // checkRoutes()





int main(int argc, char** argv)
{
  int numTrips, numFlights, numCities;
  Flight *flights, *flights2;
  Trip *trips;
  readFile(&flights, &trips, &numTrips, &numFlights,  &numCities, argv[1],
    &flights2);
  Itinerary *itineraries = new Itinerary[numTrips];
  CPUTimer ct;
  Router *router = new Router(numCities, numFlights, flights2);
  delete [] flights2;

  for(int i = 0 ; i < numTrips; i++)
    router->findRoute((const Trip*) &trips[i], &itineraries[i]);

  cout << "CPU Time: " << ct.cur_CPUTime();
  checkRoutes(flights, trips, numTrips, numFlights, itineraries, argc, argv);
 
  return 0;
} // main()


