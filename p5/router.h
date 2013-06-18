// Author: Sean Davis
// Author: Huajun Chai
#ifndef ROUTER_H
#define	ROUTER_H

#include "TripsRunner.h"
#include <vector>

using namespace std;

typedef struct Airport
{
  unsigned short duration;
  vector<unsigned> flightNum;///something is wrong here
  unsigned currentAirport;
  unsigned from;
  Airport *next;
};

typedef struct City
{
  unsigned short earlyTime;///
  unsigned flightNum;
  unsigned pre;
  unsigned current;
  friend  bool operator< (const City& lhs,const City& rhs)
  {
    return lhs.earlyTime > rhs.earlyTime;
  }
};

class Router
{
public:
  Router(int numCities, int numFlights, Flight *flights);
  void findRoute(const Trip* trip, Itinerary *itinerary);
  void insertFlight(Airport *temp, Flight *f, int i);
  ///destructor
private:
  Airport* airports[5700];
  Flight *flights_copy;
};

#endif	/* ROUTER_H */

