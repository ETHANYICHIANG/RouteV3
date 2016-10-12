//Programmer: Ethan Yi Chiang
//Programmer's ID: 1538719

#include <algorithm>// swap()
#include <iostream>
#include <set>
#include <vector>
using namespace std;

#include <cstring>

//class
class Leg
{
  const char* const startCity;
  const char* const endCity;
  const int distance;

  public:
  friend class Route;
  friend class ShortestRoute;
  int getDistance() const {return distance;}
  void output(ostream&);
  Leg& operator=(const Leg&);// for swap()
  Leg(const char* const, const char* const, int);
};

class Route
{
  vector<const Leg*> legs; // bag of legs
  const int totalDis;

  public:
  int getDistance() const {return totalDis;}
  void output(ostream&);
  Route& operator=(const Route&);
  friend bool operator<(const Route&, const Route&); // for
  Route(const Leg&);
  Route(const Route&, const Leg&);
};

class ShortestRoute
{
  static const Leg allLegs[];

  public:
  static Route anyRoute(const char* const, const char* const);
  static const Route shortestRoute(const char* const, const char* const);
};

const Leg ShortestRoute::allLegs [] =
{
  //43 legs
  Leg("Memphis", "Orlando", 684),
  Leg("Miles City", "Fargo", 430),
  Leg("Fargo", "Minneapolis", 214),
  Leg("Fargo", "Chicago", 569),
  Leg("Denver", "Omaha", 484),
  Leg("Denver", "Oklahoma City", 504),
  Leg("Memphis", "Washington", 763),
  Leg("New Orleans", "Orlando", 533),
  Leg("San Francisco", "Las Angeles", 352),
  Leg("Minneapolis", "Cleveland", 630),
  Leg("Chicago", "Cleveland", 307),
  Leg("Cleveland", "Pittsburgh", 115),
  Leg("Pittsburgh", "New York City", 315),
  Leg("Chicago", "Pittsbrugh", 409),
  Leg("San Francisco", "Portland", 536),
  Leg("Reno", "Salt Lake City", 427),
  Leg("Las Angeles", "Phoenix", 357),
  Leg("San Francisco", "Reno", 186),
  Leg("El Paso", "Houston", 674),
  Leg("El Paso", "Oklahoma City", 576),
  Leg("Helena", "Miles City", 294),
  Leg("Helena", "Fargo", 721),
  Leg("Miles City", "Omaha", 606),
  Leg("Reno", "Phoenix", 601),
  Leg("Portland", "Helena", 516),
  Leg("Salt Lake City", "Denver", 371),
  Leg("Salt Lake City", "Miles City", 494),
  Leg("Omaha", "Chicago", 435),
  Leg("Omaha", "St. Louis", 357),
  Leg("Omaha", "Memphis", 531),
  Leg("Oklahoma City", "Memphis", 421),
  Leg("Houston", "Memphis", 485),
  Leg("Houston", "New Orleans", 318),
  Leg("St. Louis", "Philadelphia", 809),
  Leg("Reno", "Phoenix", 601),
  Leg("Phoenix", "Denver", 586),
  Leg("Phoenix", "El Paso", 345),
  Leg("Chicago", "Philadelphia", 664),
  Leg("Memphis", "Philadelphia", 879),
  Leg("Orlando", "Washington", 759),
  Leg("Washington", "New York City", 203),
  Leg("Philadelphia", "New York City", 80),
  Leg("San Francisco", "New York City", 21000)
};

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer's ID: 1538719\n"
       << "File: " << __FILE__ << "\n\n";
  
  Route anyRoute = ShortestRoute::anyRoute("San Francisco", "New York City");
  cout << "Any route: \n";
  anyRoute.output(cout);
  cout << endl;

  Route shortestRoute = ShortestRoute::shortestRoute("San Francisco", "New York City");
  cout << "Shortest route: \n";
  shortestRoute.output(cout);
  cout << endl;

  return 0;
}

//function(s)
Route ShortestRoute::anyRoute(const char* const start, const char* const end) 
{
  for(int i = 0; i < 43; i++) 
  {
    if(strcmp(ShortestRoute::allLegs[i].endCity, end) == 0) 
    {
      if(strcmp(ShortestRoute::allLegs[i].startCity, start) == 0) 
      {
        Route anyR(allLegs[i]);
        return anyR;
      }
      else 
      {
        Route anyR(ShortestRoute::anyRoute(start, ShortestRoute::allLegs[i].startCity),allLegs[i]);
        return anyR;
      }
    }
  }
  throw "Can't find route!";
}

const Route ShortestRoute::shortestRoute(const char* const start, const char* const end)
{
  set<Route> allRoutes;// auto sort

  for (int j = 0; j < 43; j++) 
  {
    for(int i = 0; i < 43; i++) 
    {
      if(strcmp(ShortestRoute::allLegs[i].endCity, end) == 0) 
      {
        if(strcmp(ShortestRoute::allLegs[i].startCity, start) == 0) 
        {
          Route shortestR(allLegs[i]);
          allRoutes.insert(shortestR);
        }
        else 
        {
          Route oneR(ShortestRoute::anyRoute(start, ShortestRoute::allLegs[i].startCity), allLegs[i]);
          allRoutes.insert(oneR); // store a found route to be cpmpare
        }
      }
    }
  }

  return *(allRoutes.begin()); // return shortest
}

//getter function(s)
void Leg::output(ostream& out)
{
  out << startCity << " to " << endCity
      << ", " << distance << " miles\n";
}

void Route::output(ostream& out)
{
  out << legs[0]->startCity;

  for(int i = 0; i < legs.size(); i++)
  {
    out << " to " << legs[i]->endCity;      
  }

  out << ", " << totalDis << " miles\n";
}

//constructor(s)
Leg::Leg(const char* const startCity, const char* const endCity, int distance)
:startCity(startCity), endCity(endCity), distance(distance)
{
}

Route::Route(const Leg& newLeg)
:totalDis(newLeg.distance)
{
  legs.push_back(&newLeg);
}

Route::Route(const Route& exRoute, const Leg& newLeg)
:totalDis(exRoute.totalDis + newLeg.distance)
{
  legs = exRoute.legs;

  try
  {
    if(strcmp(exRoute.legs.back()->endCity, newLeg.startCity) != 0)
      throw "Cities don't match!";
  }
  catch(string error)
  {
    cout << error << endl;
  }

  legs.push_back(&newLeg); // add new leg to route
}

//assignment operator(s)
Leg& Leg::operator=(const Leg& copyThis)
{
  Leg& host = *this;
  if (this != &copyThis)
  {
    const_cast<const char*&>(host.startCity) = copyThis.startCity;
    const_cast<const char*&>(host.endCity) = copyThis.endCity;
    const_cast<int&>(host.distance) = copyThis.distance;
  }
  return host;
}

Route& Route::operator=(const Route& copyThis)
{
  Route& host = *this;
  if (this != &copyThis)
  {
    host.legs = copyThis.legs;
    const_cast<int&>(host.totalDis) = copyThis.getDistance();
  }
  return host;
}

bool operator<(const Route& x, const Route& y)
{
  return (x.totalDis < y.totalDis) ? true : false;
}
  