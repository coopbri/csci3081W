/**
 * @file controller.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <vector>

#include "src/arena.h"
#include "src/common.h"
#include "src/arena_viewer.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Controller that mediates Arena and GraphicsArenaViewer communication.
 *
 * The Controller instantiates the Arena and the GraphicsArenaViewer. The
 * viewer contains the main loop that keeps it live, but at each update, the
 * viewer sends a message to the controller to update its time.
 *
 * Other types of communication between Arena and Viewer include:
 * - keypresses intercepted by the Viewer.
 * - Play/Pause/New Game user input via the Viewer.
 * - Game status from arena to the viewer.
 **/
class Controller {
 public:
  /**
   * @brief Controller's constructor that will create Arena and Viewer.
   */
  Controller(int argc, char **argv);

  /**
   * @brief Controller's copy constructor.
   */
  Controller(const Controller &c2);

  /**
   * @brief Controller's destructor.
   */
  virtual ~Controller();

  /**
   * @brief Create the arena viewer.
   */
  virtual ArenaViewer* CreateViewer(int width, int height);

  /**
   * @brief Run launches the graphics and starts the game.
   */
  void Run();

  /**
   * @brief AdvanceTime is communication from the Viewer to advance the
   * simulation.
   */
  void AdvanceTime(double dt);

 /**
  * @brief Completely destroy and remake the arena
  */
  void Reset();

 /**
  * @brief Under certain circumstances, the compiler requires that the copy
  * constructor is not defined. This `deletes` the default copy constructor.
  */
  Controller &operator=(const Controller &other) = delete;

 /**
  * @brief Convert a CSV configuration file to a JSON file.
  */
  std::string ConvertCsv(char* csv);

 private:
 /**
  * @brief For CSV files: add quotes around a string
  */
  std::string add_quotes(std::string word);

 /**
  * @brief For CSV files: determine if quotes should be put around a parsed
  * word
  */
  bool in_number_set(std::string word);

  //! x dimension of arena
  double x_dim_;

  //! y dimension of arena
  double y_dim_;

  //! Previous time differential
  double last_dt{0};

  //! Pointer to the arena
  Arena* arena_{nullptr};

  //! Pointer to the viewer
  ArenaViewer* viewer_{nullptr};

  //! Container of viewers
  std::vector<ArenaViewer*> viewers_;

  //! JSON configuration
  json_value* config_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_CONTROLLER_H_
