//  Author: Sean Davis
//  Author: Huajun Chai
#include "TripsRunner.h"
#include "router.h"
#include <cstddef>
#include <iostream>
#include <queue>
#include <limits>
using namespace std;

void Router::insertFlight(Airport *temp, Flight *f, int i)
{
  temp->flightNum.push_back(f[i].flightNum);
  int size = temp->flightNum.size();
///  if(i==7)
///  cout << size << endl;
  unsigned tempfnum = 0;
  for(; size >= 2; size--)
  {
    if(flights_copy[temp->flightNum[size - 1]].departureTime
    < flights_copy[temp->flightNum[size - 2]].departureTime)
    {
      tempfnum = temp->flightNum[size - 2];
      temp->flightNum[size - 2] = temp->flightNum[size - 1];
      temp->flightNum[size - 1] = tempfnum;
    }
  }
}

Router::Router(int numCities, int numFlights, Flight *flights)
{
  flights_copy = new Flight[numFlights];
  int i = 0, j = 0;
  Airport *temp;
  for(; i < numFlights; i++)
  {
    flights_copy[i] = flights[i];
    if(airports[flights[i].originIndex - 1] == NULL)
    {
      temp = new Airport();
      temp->duration = flights[i].duration;
      insertFlight(temp, flights, i);
      temp->currentAirport = flights[i].destinationIndex;
      temp->from = flights[i].originIndex;
      temp->next = NULL;
      airports[flights[i].originIndex - 1] = temp;
    }
    else
    {
      ///cout << flights[i].originIndex << endl;
      ///cout << airports[flights[i].originIndex]->currentAirport << endl;
      temp = airports[flights[i].originIndex - 1];
///     cout << flights[i].destinationIndex << " vs " << temp->currentAirport << endl;
      while(temp != NULL && flights[i].destinationIndex != temp->currentAirport)
      {
        temp = temp->next;
      }
      if(temp == NULL)///No this adjacency node
      {
        temp = new Airport();
        temp->duration = flights[i].duration;
        ///temp->flightNum.push_back(flights[i].flightNum);
        insertFlight(temp, flights, i);
        temp->currentAirport = flights[i].destinationIndex;
        temp->from = flights[i].originIndex;
        temp->next = airports[flights[i].originIndex - 1];
        airports[flights[i].originIndex - 1] = temp;
      }
      else///this node is already in the adj list
      {
 ///       cout << temp->flightNum.size() << endl;
        ///temp->flightNum.push_back(flights[i].flightNum);
        insertFlight(temp, flights, i);
      }
    }
  }
} // Router()

void Router::findRoute(const Trip* trip, Itinerary *itinerary)
{
   itinerary->numFlights = 0;  /// to be set by student
   City cities[5700];
   for(int i = 0; i < 5700; i++)
   {
     cities[i].earlyTime = numeric_limits<unsigned short>::max();
     cities[i].current = i + 1;
   }

   unsigned origin = trip->originIndex;
   unsigned destination = trip->destinationIndex;
   unsigned short time = trip->departureTime;
   unsigned short destTime;

   Airport *temp;

   priority_queue<City> pq;
   cities[origin - 1] = {time, 0, NULL, origin};
   pq.push(cities[origin - 1]);

   while(!pq.empty())
   {
	   destTime = cities[destination - 1].earlyTime;
     unsigned short tm = pq.top().earlyTime, tm1;
     unsigned v = pq.top().current;///the airport we look at
     pq.pop();
     ///cout << pq.size() << endl;
     temp = airports[v - 1];
     while(temp != NULL)
     {
       tm1 = tm;
       int num = temp->flightNum.size();///有几家飞机从A到B

       /*Airport *ne = airports[v - 1];
       if(origin == 5231 && v == 5675)
       {
       cout << "origin: " << origin << endl;
       cout << "v: " << v << endl;
       while(ne != NULL)
       {
         cout << ne->currentAirport << endl;
         ne = ne->next;
       }
       }*/
         ///cout << "current earlyT: " << cities[v - 1].earlyTime << endl;
       for(int i = 0; i < num; i++)
       {
           /* if(origin == 5231 && destination == 1543 && time == 1199 && temp->currentAirport == 1543 && v == 4363 )
           {
             cout << "origin: " << origin << endl;
             cout << "current city: " << temp->currentAirport << endl;
             cout << "flight " << i << " : " << flights_copy[temp->flightNum[i]].departureTime << endl;
             cout << temp->from << " , " << origin << endl;
           }
           if(origin == 5231 && destination == 1543 && time == 1199 && temp->currentAirport == 1543 && v == 5675 )
           {
             cout << "origin: " << origin << endl;
             cout << "current city: " << temp->currentAirport << endl;
             cout << "flight " << i << " : " << flights_copy[temp->flightNum[i]].departureTime << endl;
             cout << temp->from << " , " << origin << endl;
           }*/
         if(temp->from != origin)
         {
           if((tm1) % 1440 + 30 > flights_copy[temp->flightNum[i]].departureTime)
           {
             if(i < num - 1)
               continue;
             else///这个机场当天最后一家飞机都没有赶上
             {
               int flag = 0;
               /*if(tm1 % 1440 + 30 > 1440 + flights_copy[temp->flightNum[0]].departureTime)
                 tm1 = tm1 + 30 - (tm1 + 30) % 1440 + 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
               else if(tm1 % 1440 + 30 >= 1440 && tm1 % 1440 + 30 <= 1440 + flights_copy[temp->flightNum[0]].departureTime)
                 tm1 = tm1 + 30 - (tm1 + 30) % 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
               else
                 tm1 = tm1 - tm1 % 1440 + 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
               */
               if(tm1 % 1440 + 30 <= 1440 + flights_copy[temp->flightNum[0]].departureTime)///出发时间比第二天第一家飞机要早
               {
                 if(tm1 % 1440 + 30 < 1440)///出发+30min在第一天之内
                   tm1 = tm1 + 30 - (tm1 + 30) % 1440 + 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
                 else///出发+30min在第二天，但是在第二天第一家飞机之前
                   tm1 = tm1 + 30 - (tm1 + 30) % 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
               }
               else///出发+30min在第二天，但是呢比第1家飞机要皖一些
               {
                 if(num == 1)
                   tm1 = tm1 + 30 - (tm1 + 30) % 1440 + 1440  + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
                 else
                 {
                   int j = 1;
                   while(j < num && tm1 % 1440 + 30 > 1440 + flights_copy[temp->flightNum[j]].departureTime)
                   {
                     j++;
                   }
                   if(j == num)
                     tm1 = tm1 + 30 - (tm1 + 30) % 1440 + 1440  + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
                   else
                   {
                     tm1 = tm1 + 30 - (tm1 + 30) % 1440  + flights_copy[temp->flightNum[j]].departureTime + flights_copy[temp->flightNum[j]].duration;
                     flag = j;
                   }
                 }

               }
               if(tm1 < cities[temp->currentAirport - 1].earlyTime)
               {
                 cities[temp->currentAirport - 1].earlyTime = tm1;
                 if(flag == 0)
                   cities[temp->currentAirport - 1].flightNum = temp->flightNum[0];
                 else
                   cities[temp->currentAirport - 1].flightNum = temp->flightNum[flag];
                 cities[temp->currentAirport - 1].pre = v;
				 if(tm1 < destTime)
                 pq.push(cities[temp->currentAirport - 1]);
               }
             }
           }
           else
           {
             ///if(tm1 % 1440 + 30 > 1440)
               ///tm1 = tm1 - tm1 % 1440 + 1440 + flights_copy[temp->flightNum[i]].departureTime + flights_copy[temp->flightNum[i]].duration;
             ///else
               tm1 = tm1 - tm1 % 1440 + flights_copy[temp->flightNum[i]].departureTime + flights_copy[temp->flightNum[i]].duration;

             if(tm1 < cities[temp->currentAirport - 1].earlyTime)
             {
               cities[temp->currentAirport - 1].earlyTime = tm1;
               cities[temp->currentAirport - 1].flightNum = temp->flightNum[i];
               cities[temp->currentAirport - 1].pre = v;
			   if(tm1 < destTime)
               pq.push(cities[temp->currentAirport - 1]);
             }
             break;
           }
         }
         else
         {
           if(tm1 % 1440 > flights_copy[temp->flightNum[i]].departureTime)
           {
             if(i < num - 1)
               continue;
             else///这个机场当天最后一家飞机都没有赶上
             {
               tm1 = tm1 - tm1 % 1440 + 1440 + flights_copy[temp->flightNum[0]].departureTime + flights_copy[temp->flightNum[0]].duration;
               if(tm1 < cities[temp->currentAirport - 1].earlyTime)
               {
                 cities[temp->currentAirport - 1].earlyTime = tm1;
                 cities[temp->currentAirport - 1].flightNum = temp->flightNum[0];
                 cities[temp->currentAirport - 1].pre = v;
				 if(tm1 < destTime)
                 pq.push(cities[temp->currentAirport - 1]);
               }
             }
           }
           else
           {
             tm1 = tm1 - tm1 % 1440 + flights_copy[temp->flightNum[i]].departureTime + flights_copy[temp->flightNum[i]].duration;
             if(tm1 < cities[temp->currentAirport - 1].earlyTime)
             {
               cities[temp->currentAirport - 1].earlyTime = tm1;
               cities[temp->currentAirport - 1].flightNum = temp->flightNum[i];
               cities[temp->currentAirport - 1].pre = v;
			   if(tm1 < destTime)
               pq.push(cities[temp->currentAirport - 1]);
             }
             break;
           }
         }
       }
       temp = temp->next;
     }
   }
   City tempCity = cities[destination - 1];
   short count = 0;
   int container[20];
   ///if(origin == 2325)
   ///{
     ///cout << origin << "->" << destination << endl;
   ///}
   ///cout << tempCity.current << endl;
   //cout << tempCity.pre << endl;

   while(tempCity.pre != NULL)
   {
     ///if(tempCity.pre==511)
     ///cout << "here" << endl;
     ///cout << tempCity.pre << endl;
     container[count] = tempCity.flightNum;
     tempCity = cities[tempCity.pre - 1];
     count++;
   }
   itinerary->numFlights = count;
   for(int j = count - 1, i = 0; j >= 0; j--, i++)
   {
     itinerary->flightNums[i] = container[j];
   }
///   cout << "nums: " << itinerary->numFlights << endl;
}  // findRoute

