#ifndef GAMES_PIRATES_AI_HPP
#define GAMES_PIRATES_AI_HPP


#include "impl/pirates.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "port.hpp"
#include "tile.hpp"
#include "unit.hpp"

#include "../../joueur/src/base_ai.hpp"
#include "../../joueur/src/attr_wrapper.hpp"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional #includes here
// <<-- /Creer-Merge: includes -->>

namespace cpp_client
{

namespace pirates
{

/// <summary>
/// This is the header file for building your Pirates AI
/// </summary>
class AI : public Base_ai
{
public:
    /// <summary>
    /// This is a reference to the Game object itself, it contains all the information about the current game
    /// </summary>
    Game game;

    /// <summary>
    /// This is a pointer to your AI's player. This AI class is not a player, but it should command this Player.
    /// </summary>
    Player player;

    //<<-- Creer-Merge: class variables -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can add additional class variables here.
    //<<-- /Creer-Merge: class variables -->>

    /// <summary>
    /// This returns your AI's name to the game server.
    /// Replace the string name.
    /// </summary>
    /// <returns>The name of your AI.</returns>
    virtual std::string get_name() const override;

    /// <summary>
    /// This is automatically called when the game first starts, once the game objects are created
    /// </summary>
    virtual void start() override;

    /// <summary>
    /// This is automatically called when the game ends.
    /// </summary>
    /// <param name="won">true if you won, false otherwise</param>
    /// <param name="reason">An explanation for why you either won or lost</param>
    virtual void ended(bool won, const std::string& reason) override;

    /// <summary>
    /// This is automatically called the game (or anything in it) updates
    /// </summary>
    virtual void game_updated() override;

    /// <summary>
    /// This is called every time it is this AI.player's turn.
    /// </summary>
    /// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
    bool run_turn();

    // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can add additional methods here.



  //distance func
  //returns a double which is the coordinate distance between the argument units
  double distance(Unit unit1, Unit unit2);

  /////////////////////ENEMY INFO FUNCTIONS//////////////////////////////////
  //these functions return a vector containing information on the enemy fleet
  //based upon the way the info is fetched, the respective indexes of the vectors
  //should refer to the same enemy unit, provided that the functinos are called in
  //the SAME TURN

  bool high_threat(Unit unit);
  
  template <typename T>
  void display_vector(std::vector<T> vec);
  
  //returns a vector which contains the distances of all ally units
  std::vector<double> dist_to_allies(Unit the_unit);
  
  //returns a vector which contains the distances of all enemy units
  std::vector<double> dist_to_enemies(Unit the_unit);

  //returns a vector which contains the ship hp of all enemy ships
  std::vector<int> enemy_fleet_health();

  //finds every ship in the enemy fleet and returns a vector
  //containing the number of crew in them.
  //keep in mind an abandoned ship is not in the enemy fleet
  std::vector<int> enemy_fleet_crew_count();

  //function returns a vector containing all abandoned ships
  std::vector<Unit> find_abandoned_ships();
  	//<summary>
  	// General retreat logic, dictates how long to retreat based upon fuzzy logic, calls retreat_rest() if dying.
    void retreat(Unit this_unit);

    //<summary>
  	// This function, when called, signals a ship's frantic retreat for the port, it's attempt is to be healed.
    void retreat_rest(Unit this_unit);

    //<summary>
  	// Here is where we define any form of attack towards a merchant.
  	// TODO: Not likely a permanent function.
    void merchant_logic(Unit this_unit);





    // <<-- /Creer-Merge: methods -->>

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <param name="unit">the Unit that will move</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> find_path(const Tile& start, const Tile& goal, const Unit& unit);



    // ####################
    // Don't edit these!
    // ####################
    /// \cond FALSE
    virtual std::string invoke_by_name(const std::string& name,
                                       const std::unordered_map<std::string, Any>& args) override;
    virtual void set_game(Base_game* ptr) override;
    virtual void set_player(std::shared_ptr<Base_object> obj) override;
    virtual void print_win_loss_info() override;
    /// \endcond
    // ####################
    // Don't edit these!
    // ####################

};

} // PIRATES

} // cpp_client

#endif // GAMES_PIRATES_AI_HPP
