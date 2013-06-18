// Author: Sean Davis

#ifndef TRIPSRUNNER_H
#define	TRIPSRUNNER_H

typedef struct 
{
  unsigned flightNum;
  unsigned originIndex;
  unsigned destinationIndex;
  unsigned short departureTime;
  unsigned short duration;
}Flight;

typedef struct
{
  unsigned  originIndex;
  unsigned destinationIndex;
  unsigned short departureTime;
} Trip;

typedef struct
{
  int flightNums[20];
  short numFlights;
} Itinerary;


#endif	

