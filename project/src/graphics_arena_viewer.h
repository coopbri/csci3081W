/**
 * @file graphics_arena_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_GRAPHICS_ARENA_VIEWER_H_
#define SRC_GRAPHICS_ARENA_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MinGfx-1.0/mingfx.h>
#include <string>
#include <vector>
#include "src/arena.h"
#include "src/braitenberg_vehicle.h"
#include "src/controller.h"
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Controller;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the MinGfx library to open up a window that
 *  includes a few buttons for controlling the simulation and can be used to
 *  draw circles and other computer graphics.
 *
 *  After constructing a new GraphicsArenaViewer, call Run to start and run the
 *  application. Run will not return until the application window is closed.
 *  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open UpdateSimulation will be called repeatedly,
 *  once per frame. Fill this in to update your simulation or perform any other
 *  processing that should happen over time as the simulation progresses.
 *
 *  Fill in the `On*()` methods as desired to respond to user input events.
 *
 *  Fill in the `Draw*()` methods to draw graphics on the screen using
 *  either the `nanovg` library or raw `OpenGL`.
 */
class GraphicsArenaViewer : public mingfx::GraphicsApp, public ArenaViewer {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of the Arena and the entities therein.
   */
  explicit GraphicsArenaViewer(int width, int height,
                               Controller *controller);

  /**
   * @brief Destructor.
   *
   * `delete` the contained Arena.
   */
  ~GraphicsArenaViewer() override { delete arena_; }

  /** Used to setup the 2D GUI. */
  void InitNanoGUI() override;

  /**
   * @brief Informs the Arena of the new time, so that it can update.
   *
   * @param dt The new timestep.
   */
  void UpdateSimulation(double dt) override;

  /**
  * @brief Update the entity panels with new information
  *
  * The information is provided by a subject, i.e. a robot. statistical
  * information is updated in the GUI to be viewed.
  *
  * @param wv A vector containing a state of a robot's contributing wheel
  * velocity factors.
  */
  void OnUpdate(std::vector<WheelVelocity> wv);

  /**
   * @brief Handle the user pressing the pause button on the GUI.
   *
   * This will freeze the graphics--no update, until the pause button is
   * pressed again.
   */
  void OnPlayingBtnPressed();

  /**
   * @brief Handle the user pressing the reset button on the GUI.
   *
   * This will completely remake the game. It does so by calling
   * the reset method located in controller, which will destroy
   * everything and make everything anew
   */
  void OnResetButtonPressed();


  /**
   * @brief A method to receive a new arena pointer from controller.
   *
   * When the reset button is pressed, a new arena must be received from the
   * controller.
   */
  void SetArena(Arena *arena) override;

  /**
   * @brief Called each time the mouse moves on the screen within the GUI
   * window.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   * @param[in] delta How far the mouse has moved.
   */
  void OnMouseMove(__unused const mingfx::Point2& pos,
                   __unused const mingfx::Vector2& delta) override {};

  /**
   * @brief Called each time the left mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseDown(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the left mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseUp(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseDown(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseUp(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time a character key is pressed.
   *
   * @param[in] c Character representing a key that was pressed.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnKeyDown(__unused const char *c, __unused int modifiers) override {};

  /**
   * @brief Called each time a character key is released.
   *
   * @param[in] c Character representing a key that was released.
   * @param[in] modifiers Any modifier keys that were held with the key.
   */
  void OnKeyUp(
    __unused const char *c, __unused int modifiers) override { };

  /**
   * @brief Called each time a special (non-alphabetic) key is pressed.
   *
   * @param[in] key The key that was pressed.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyDown(__unused int key, __unused int scancode,
                        __unused int modifiers) override {}

  /**
   * @brief Called each time a special (non-alphabetic) key is released.
   *
   * @param[in] key The key that was released.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyUp(__unused int key, __unused int scancode,
                      __unused int modifiers) override {};

  /**
   * @brief Draw the Arena with all of its entities using `nanogui`.
   *
   * This is the primary driver for drawing all entities in the Arena. It is
   * called at each iteration of `nanogui::mainloop()`.
   *
   * @param[in] ctx Context for nanogui.
   */
  void DrawUsingNanoVG(NVGcontext *ctx) override;

  /**
   * @brief Draw using `OpenGL`. This method is unimplemented, as currently
   * we are doing all drawing with `nanovg` in this application, so it is empty.
   */
  void DrawUsingOpenGL() override {}

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  GraphicsArenaViewer &operator=(const GraphicsArenaViewer &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  GraphicsArenaViewer(const GraphicsArenaViewer &other) = delete;

 private:
  void DrawArena(NVGcontext *ctx);

  /**
   * @brief Draw an Light in the Arena using `nanogui`.
   *
   * This function requires an active `nanovg` drawing context (`ctx`), so it
   * should probably only be called from with DrawUsingNanoVG.
   *
   * @param[in] ctx The `nanovg` context.
   * @param[in] light The Light handle.
   */
  void DrawEntity(NVGcontext *ctx, const class ArenaEntity *const entity);

  /**
  * @brief Draw a new entity panel in the GUI menu
  */
  void AddEntityPanel(nanogui::Widget * panel);

  /**
  * @brief Execute the process of running the viewer
  */
  bool RunViewer() override;

  //! Controller as part of the model-view-controller framework
  Controller *controller_;

  //! Robot that GAV is currently subscribed to (NULL by default)
  BraitenbergVehicle* current_bv_;

  //! Boxes for displaying robot wheel velocity contributions
  std::vector<nanogui::TextBox*> velocity_container_;

  //! Format the values in the GUI wheel velocity section
  std::string formatValue(float val);

  //! Boolean to identify if the viewer is currently observing a robot
  bool observing_{false};

  //! Arena in which all entities operate
  Arena *arena_;

  //! Determine if the simulation is paused
  bool paused_{true};

  //! Play button
  nanogui::Button *playing_button_{nullptr};

  //! Button for starting the simulation over
  nanogui::Button *reset_button_{nullptr};

  //! Offset for drawing graphics in the viewer
  float xOffset_;

  //! Determine if the GUI has been initialized
  bool nanogui_intialized_;

  //! GUI menu
  nanogui::FormHelper* gui;

  //! Window which the GUI is drawn within
  nanogui::ref<nanogui::Window> window;
};

NAMESPACE_END(csci3081);

#endif  // SRC_GRAPHICS_ARENA_VIEWER_H_
