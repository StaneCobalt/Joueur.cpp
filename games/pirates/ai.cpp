// AI
// This is where you build your AI

#include "ai.hpp"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
#include "fuzzy.hpp"
#include <cmath>
// <<-- /Creer-Merge: includes -->>


namespace cpp_client
{

namespace pirates
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "The Black Perl";
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    //<<-- /Creer-Merge: ended -->>
}


/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
    // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
  



  std::cout << "numUnits: " << this->player->units.size() << std::endl;
  	//Actions based upon unit sizes.
  if (this->player->units.size() == 0)
    {
        // Spawn a crew if we have no units
        this->player->port->spawn("crew");
    }
    else if (this->player->units[0]->ship_health == 0)
    {
        // Spawn a ship so our crew can sail
        this->player->port->spawn("ship");
    }
    else if(this->player->port->tile->unit == NULL && this->player->gold >= 800){
      this->player->port->spawn("crew");
    }
    else if( (this->player->port->tile->unit != NULL && this->player->port->tile->unit->ship_health == 0) && this->player->gold >=600){
	this->player->port->spawn("ship");
      }
 

    // Heal our unit if the ship is almost dead
    // Node: Crew also have their own health. Maybe try adding a check to see if the crew need healing?

      else{
	//multiship logic now:
	for(Unit u : this->player->units){//for each unit we control
	  if(u->ship_health > 0){//then u is a ship controlled by me
	    if(u->ship_health < 10){
	      this->retreat(u);
	    }
	    else
	      {
		this->merchant_logic(u);
	      }
	  }
	}
      }
 



    // <<-- /Creer-Merge: runTurn -->>
    return true;
}

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <param name="unit">the Unit that will move</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> AI::find_path(const Tile& start, const Tile& goal, const Unit& unit)
{
    // no need to make a path to here...
    if(start == goal)
    {
        return {};
    }

    // the tiles that will have their neighbors searched for 'goal'
    std::queue<Tile> fringe;

    // How we got to each tile that went into the fringe.
    std::unordered_map<Tile,Tile> came_from;

    // Enqueue start as the first tile to have its neighbors searched.
    fringe.push(start);

    // keep exploring neighbors of neighbors... until there are no more.
    while(fringe.size() > 0)
    {
        // the tile we are currently exploring.
        Tile inspect = fringe.front();
        fringe.pop();

        // Note, we are using the `auto` keyword here
        //   The compiler can discern that this is a `std::vector<Tile>` based on the return type of `getNeighbors()`
        auto neighbors = inspect->get_neighbors();

        // cycle through the tile's neighbors.
        for(unsigned i = 0; i < neighbors.size(); i++)
        {
            Tile neighbor = neighbors[i];

            // If we found the goal we've found the path!
            if(neighbor == goal)
            {
                // Follow the path backward starting at the goal and return it.
                std::deque<Tile> path;
                path.push_front(goal);

                // Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                for(Tile step = inspect; step != start; step = came_from[step])
                {
                    path.push_front(step);
                }

                // we want to return a vector as that's what we use for all containers in C++
                // (and they don't have push_front like we need)
                // So construct the vector-ized path here
                std::vector<Tile> vector_path;
                for(auto& tile : path)
                {
                    vector_path.push_back(tile);
                }
                return vector_path;
            }

            // if the tile exists, has not been explored or added to the fringe yet, and it is pathable
            if(neighbor && came_from.count(neighbor) == 0 && neighbor->is_pathable(unit))
            {
                // add it to the tiles to be explored and add where it came from.
                fringe.push(neighbor);
                came_from[neighbor] = inspect;
            }

        } // for each neighbor

    } // while fringe not empty

    // if you're here, that means that there was not a path to get to where you want to go.
    //   in that case, we'll just return an empty path.
    return {};
}

//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call


  //distance function:
  //returns the distance between two units passed as arguments
  	double AI::distance(Unit unit1, Unit unit2){
		//values that will determine distance;
		int x1 = unit1->tile->x;
		int x2 = unit2->tile->x;
		int y1 = unit1->tile->y;
		int y2 = unit2->tile->y;
		
		//this is to make less writing
		int distancex = x1 - x2;
		int distancey = y1 - y2;
		
		//euclidean distance formula
		return sqrt(distancex*distancex + distancey*distancey);

	}

  ////////////////////////////ENEMY INFO FUNCTIONS////////////////////
  //vector functions that return info on enemy ships, see ai.hpp for more info

  bool AI::high_threat(Unit unit){
		//returns our current threat level, a value from 0.0 - 1.0
		//thresholds are scaled up for larger range when unit has low hp
		float unitHealth = (float)(unit->ship_health/20);
		int healthScale = (1 - unitHealth)*10; //automagic flooring
		float low = 3.0f + (float)healthScale; //lower threshold
		float up = 10.0f + (float)healthScale; //upper threshold
		std::vector<double> enemyDistances = dist_to_enemies(unit);
		float f, isNear, isFar;
		int enemyCount = 0;
		for(double ed : enemyDistances){
			f = (float)ed;
			isFar = Fuzzy::Grade(f,low,up);
			isNear = Fuzzy::NOT(isFar);
			if(isNear >= isFar){
				/* if enemy is considered near
				   in relation to our health
				   then add them to the count
				*/
				enemyCount++;
			}
		}
		//thresholds are tighter when hp is lower for allies, since it needs more immediate protection
		low = 6.0f - (float)healthScale;
		up = 13.0f - (float)healthScale;
		std::vector<double> allyDistances = dist_to_allies(unit);
		int allyCount = 0;
		for(double ad : allyDistances){
			f = (float)ad;
			isFar = Fuzzy::Grade(f,low,up);
			isNear = Fuzzy::NOT(isFar);
			if(isNear >= isFar){
				/* if ally is close enough to help */
				allyCount++;
			}
		}
		return enemyCount > allyCount;
	}
  
  template <typename T>
  void AI::display_vector(std::vector<T> vec){
    typename std::vector<T>::iterator itr;
    for(itr = vec->begin(); itr!= vec.end(); itr++){
      std::cout << *itr << std::endl;
    }
  }
  
  std::vector<double> AI::dist_to_allies(Unit the_unit){
    std::vector<double> temp; //return vector
    for(Unit u : this->player->units){
      if(u->ship_health > 0){ //if the unit is a ship
	temp.push_back(distance(u, the_unit));
      }
    }
    return temp;
  }
  
  std::vector<double> AI::dist_to_enemies(Unit the_unit){
    std::vector<double> temp; //return vector
    for(Unit u : this->player->opponent->units){
      if(u->ship_health > 0){ //if the unit is a ship
	temp.push_back(distance(u, the_unit));
      }
    }
    return temp;
  }

  //returns the hp of the enemy fleet
  std::vector<int> AI::enemy_fleet_health(){
    std::vector<int> temp; //return vector
    for(Unit u : this->player->opponent->units) {
      if(u->ship_health > 0){ //if the unit is a ship
	temp.push_back(u->ship_health);
      }
    }
    return temp;
  }

  std::vector<int> AI::enemy_fleet_crew_count(){
    std::vector<int> temp; //return vector
    for(Unit u : this->player->opponent->units){
      if(u->ship_health > 0){ //if the unit is a ship
	temp.push_back(u->crew);
      }
    }
    return temp;
  }

  std::vector<Unit> AI::find_abandoned_ships(){
    std::vector<Unit> temp; //return vector
    for(Unit u : this->game->units)//for every unit in the game..
      //if it is a healthy ship with no crew then...
      if(u->ship_health > 0 && u->crew == 0)
	temp.push_back(u);
    return temp;
  }
  /////////////////////////////////////////////////////////////////
  
  
	void AI::retreat(Unit this_unit){
	  this->retreat_rest(this_unit);
	}
	void AI::retreat_rest(Unit this_unit){
	  //Running away, and healing.
	  Unit unit = this_unit;

	  // Find a path to our port so we can heal
	  std::vector<Tile> path = this->find_path(unit->tile, this->player->port->tile, unit);
	  if (path.size() > 0)
		{
		  // Move along the path if there is one
		  unit->move(path[0]);
		}
	  else
		{
		  // Try to deposit any gold we have while we're here
		  unit->deposit();

		  // Try to rest
		  unit->rest();
		}
	}

	void AI::merchant_logic(Unit unit){

    std::vector<Port> m_ports;						//All the merchant ports on the map.

    // Look for merchant ports.
		for(Port p: this->game->ports){
    	if(p->owner == NULL)
        m_ports.push_back(p);
    }

    //Decide which port to lazy river at.
    auto murder_location = m_ports[0]->tile;
    //Find a path to it.
    std::vector<Tile> path = this->find_path(unit->tile, murder_location, unit);

    //Pick the closest approaching enemy (usually a merchant).
    float closest_dist = 100;
    Unit closest_enemy;
    for(Unit u: this->game->units){
      if(u->owner != unit->owner && closest_dist < this->distance(unit, u)){
        closest_enemy = u;
      }
    }

    //If you can't fire on the enemy, move closer to the port.
    if (distance(unit,closest_enemy) > this->game->ship_range){
      unit->move(path[0]);
    }
    else{
      // Try to attack the nearest enemy ship. 
      unit->attack(closest_enemy->tile, (std::string)"ship");
    }

	}

//<<-- /Creer-Merge: methods -->>

} // pirates

} // cpp_client
