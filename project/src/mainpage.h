/**
 * @file mainpage.h
 *
 * @copyright 2019 Brian Cooper
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage CSCI3081 Project Documentation

    \tableofcontents

    \section title Braitenberg Vehicle Simulator

    <hr>

    \subsection intro Introduction and Program Structure

    <p>This software involves the interactions of "Braitenberg vehicles," which
    are robots based on a thought experiment by Valentino Braitenberg. Specific
    interactions include interactions among other Braitenberg vehicles (also
    called "robots" in this program), interactions with other kinds of entities
    (food, lights, and predators), and interactions with the environment space
    (named the "arena"). More about Braitenberg vehicles can be read at the
    Wikipedia article <a href="https://en.wikipedia.org/wiki/
    Braitenberg_vehicle">here</a>. To view how Braitenberg vehicles are
    implemented in this program, the class can be observed here:
    BraitenbergVehicle. The source code is structured into segments. Arena is a
    class that represents the simulation space in which entities operate
    within; it aggregates entities. GraphicsArenaViewer is a class that renders
    graphics tied to the logic employed by the source code. Entities are
    generated and managed by an inheritance tree, which begins with the
    ArenaEntity class and trickles down. More on how the source code works will
    be explained further on.</p>

    <p>The program employs a "model-view-controller" scheme, which allows one
    to witness and observe the aforementioned interactions. A model-view-
    controller pattern (commonly called "MVC") divides an interface into three
    parts. The model, serving as the core component, handles all of the logic
    in the robot simulation. This is represented by the source code, which is
    abstracted away from the user. The view, serving as a viewport interface
    for perceptively experiencing the simulation, is represented by the
    graphical rendering of the arena and its contained entities (see
    GraphicsArenaViewer). The controller, which serves as a construct for
    inputting model state changes, is provided by a graphical user interface
    menu. This menu allows the user to select an entity in scope, and change
    its properties (depending on what kind of entity it is). The menu also
    includes a play/pause button, which causes the application to run and stop,
    and a reset button, which resets the simulation.</p>

    <p>Entities are generated by "factories" (based on the
    <a href="https://en.wikipedia.org/wiki/Factory_method_pattern">Factory
    pattern</a>). To add another entity, you can add a factory with similar
    logic to the current ones. All factories thus far inherit from the Factory
    class, which is a virtual interface. To modify the entity properties, the
    code can be modified under their corresponding class name (e.g. Predator
    for predator entities). To modify the GUI, check out the code in
    GraphicsArenaViewer. If you would like to modify the code in another way
    beyond what is specified here, please explore the generated UML on this
    documentation site.</p>

    <hr>

    \subsection started Getting Started

    \subsection dependency Dependencies

    <p>This program relies on the following libraries:
    <ul>
    <li> MinGfx
    <li> nanogui
    <li> picojson
    </ul>
    More can be read about them at the links in the references section
    below.</p>

    \subsection executing Compiling and Executing

    <p>The program can be compiled with GNU make from the project directory:</p>
    \code{.sh}
    cd <path>/project/
    make
    \endcode

    <p>After the program compiles, it can be run as follows:</p>
    \code{.sh}
    ./build/bin/arenaviewer xdim ydim scenes/example.json
    \endcode

    <p>or</p>

    \code{.sh}
    ./build/bin/arenaviewer xdim ydim scenes/example.csv
    \endcode

    <p>depending on which configuration file type (JSON or CSV) you would like
    to use. The \code{.sh}xdim\endcode and \code{.sh}ydim\endcode parameters
    specify the size of the arena window. 600 for each value is a good
    benchmark.</p>

    \subsection configs Custom Configuration Files

    <p>If you would like to make your own entity configuration files, you
    have the choice of making a JSON or a CSV file. Each file declares the
    following parameters:

    <ul>
    <li> type: Entity type (food, light, braitenberg, predator)
    <li> x: x position of entity in arena
    <li> y: y position of entity in arena
    <li> r: radius of entity
    <li> theta: angle direction of entity's view
    </ul>

    <p>Each of the four possible entities require the above five parameters.
    Braitenberg vehicles and predators take on the above parameters, as well as
    the following:</p>

    <ul>
    <li> light_behavior: behavior towards light entities
    <li> food_behavior: behavior towards food entities
    <li> robot_behavior: behavior towards Braitenberg vehicle entities
    </ul>

    <p>The possible behaviors are None, Aggressive, Love, Coward, and Explore,
    as per the Braitenberg vehicle specifications.</p>

    An example of each file type can be seen below:</p>

    <table border="0">
    <tr><td>\image html json.png "JSON" width=900
    </table>

    <table border="0">
    <tr><td>\image html csv.png "CSV" width=400
    </table>

    <p>To make a custom configuration file, simply follow the syntax as above.
    Please note that CSV files require the "header" row at the top that
    describes the parameter names, and JSON files require the entities array
    to be wrapped in a scope declared by two curly braces (as in standard
    JSON syntax).</p>

    <hr>

    \subsection refs References

    <ul>
    <li> Project source code:
    https://github.umn.edu/umn-csci-3081-S19/repo-coope824/tree/devel/project
    <li> GNU make:
    https://www.gnu.org/software/make/manual/html_node/Introduction.html
    <li> MinGfx: https://github.com/ivlab/MinGfx
    <li> nanogui: https://github.com/wjakob/nanogui
    <li> picojson: https://github.com/kazuho/picojson
    </ul>

   */

#endif  // SRC_MAINPAGE_H_