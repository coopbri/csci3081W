# Braitenberg Vehicles Simulator: Iteration 2

### UPDATES

- April 11, 2019 at 8:40 am. Several clarifications across the document. All are prefaced with the word _CLARIFICATION_ in all caps. 

- April 7, 2019 at 3:45 pm. Factory Requirement pushed back to Iteration 3

- April 6, 2019 at 5:30 pm. Added assessment weights at bottom of document

- March 27, 2019 at 2:15 pm. 1) You may use behavior base class as kNone behavior, 2) you may use a single variable as the Observer "list", and 3) add an option in the GUI to set the Braitenberg Vehicle Sensor behavior.

- March 26, 2019 at 9:15 am. Instructions for Preliminary submissions via Canvas

<hr>

This is YOUR project, and it is your decision in how you want to implement the various requirements (provided it meets the requirements). You may change the interface (and probably have to change the interface) of classes. You can add features that are not specified as long as they don't interfere with what is required.

_Your software is a reflection of your understanding of the requirements as specified in this document. If you do not understand any portion of the requirements or you think that the requirements are underspecified, it is your responsibility to get clarification from the instructor or a TA. Please read this document carefully and review it often WELL IN ADVANCE of turning in your iteration for assessment._

|*Due Date* | **Item(s) Due** |
|-----|-----|
| MON,  April 1, 11:55pm | Unit Tests for Strategy Pattern and completed implementation of the Strategy Pattern (the only time they will be assessed). DRAFT BraitenbergVehicle Sensors with behavior implemented. On _devel_ branch. **Additional submission on Canvas -- see instructions below this table.**|
| MON, April 8, 11:55pm | Observer Pattern fully implemented. DRAFT Predator class that consumes BVs implemented. On _devel_ branch. **Additional submission on Canvas -- see instructions below this table.** |
| MON,  April 15, 11:55pm | FINAL Submission of Iteration 2. On _master_ branch. |

> To simplify our grading process, we will compile and run the code from the _devel_ branch, and we will inspect the code and diagrams submitted on Canvas.

**Canvas Submission for Preliminary 1 (due April 1)**: In a **SINGLE** .pdf document (do not zip!), please include 
- doxy generated UML diagrams for the Strategy Pattern classes
- code snippet of the BraitenbergVehicle method that calls the Strategy/Behavior method
- code snippet of the BraitenbergVehicle method that uses the BraitenbergVehicle "sensor" (this might be the same method as above)
- all code for the unit tests for the Strategy Pattern

**Canvas Submission for Preliminary 2 (due April 8)**: In a **SINGLE** .pdf document (do not zip!), please include
- doxy generated UML diagrams for those classes implementing the Observer Pattern
- code snippet from the viewer that manage the viewing of the wheel velocities (be sure to use good naming conventions and add comments within your code where appropriate so that it is easy for others to understand)
- code snippet of the implementation of the Notify method of the "Subject" of the Observer Pattern
- doxy generated UML diagram of the Predator class

### Project Overview

In this iteration, you will continue to develop your Braitenberg Vehicle simulation to provide more functionality, to apply design patterns, and to expand documentation. Feature enhancements include the additions of a Predator class that can consume Braitenberg Vehicles, Braitenberg Vehicle sensors with a corresponding behavior so that robots react to robots, output of wheel velocity information to better understand behavior, <del>factories for entity creation that do not use JSON</del>, robots that can starve, and a weighted function for determining wheel velocity. As you develop and refactor your code, you will employ the Factory Pattern to initialize entities, the Strategy Pattern to implement the 4 behaviors (and write unit tests), and the Observer pattern to view wheel velocities. For documentation, you will include a landing page for the Doxygen generated html pages and add Doxygen documentation to the classes and elements added to your code.

<hr>

## Iteration 2 Requirements - Table of Contents

<ol type="I">
<li> <a href="#reqs">Iteration Requirements</a>
  <ol type="A">
    <li><a href="#reqs_design">Design Requirements</a>
  <li><a href="#reqs_doc">Documentation Requirements</a>
    <ol type="i">
    <li> <a href="#design_doc">Design Document</a>
    <li> <a href="#doxy">Doxygen</a>
    <li> <a href="#style">Style Compliance</a>
    <li> <a href="#self_doc">Self-Documenting Code</a>
    </ol>
  <li><a href="#reqs_dev">Code Development Requirements</a><ol>
  <li> <a href="#issue">Issue Report</a>
  <li> <a href="#git_usage">Git Usage</a></ol>
  <li><a href="#reqs_imp">Implementation Requirements</a>
    <ol type="i">
    <li><a href="#reqs1">Priority Level 1: Strategy Pattern, Unit Tests, and BV sensors</a>
    <li><a href="#reqs2">Priority Level 2: Observer Pattern, Predator class, and BV consumption</a>
    <li><a href="#reqs3">Priority Level 3: Starving BVs, Weighted wheel velocity equation, <del>non-JSON factory</del>.</a>
       </ol>
  </ol>
<li> <a href="#deliver">Deliverables and Submission</a>
 <li> <a href="#resources">Resources</a>
</ol>

<hr>

### <a name="reqs_design">Design Requirements</a>

#### Strategy Design Pattern

Employ the Strategy Pattern to implement the Braitenberg Vehicle (BV) behaviors of Explore, Aggression, Coward, and Love. This pattern makes use of an abstract base class of a behavior from which other behaviors are derived OR, as a student suggested, the base class may be used as the kNone default behavior. The BV entities contain (i.e. are composed of) a behavior for each of its sensors. In this iteration, the BV entities will have food, light, and BV sensors.

The Predator class is essentially a BV with a few exceptions. It always ignores Food entities, Cowers from the Light, and is Aggressive towards BVs. CLARIFICATION as discussed in class: It can be a subclass of BV or of ArenaMobileEntity, or it can be a specialized BV -- your choice.

#### Observer Design Pattern

Employ the Observer pattern to view the left and right wheel velocities calculated from the behaviors associated with the lights, food, and BVs for a user specified BV. In the provided implementation of the code for iteration 1, these values correspond to the light\_wheel\_velocity and the food\_wheel\_velocity in BraitenbergVehicle::Update(). These 6 values should be visible in the menu pane of the Graphics Arena Viewer. There should be a menu option to select which BV to observe.

Refer to _Head First Design Patterns_ to see the typical UML diagram for the Observer Pattern. You will note that as an Observer, the class contains an Update function that the Subject calls to convey its _state_ information. As a Subject, the class contains a Register/Subscribe function and a Remove/Unsubscribe function that an Observer calls to get added or removed from the observer list. A Subject also has a NotifyObservers function that, at the appropriate time(s), updates all its Observers on its list.

There are many ways to implement the required functionality of displaying the wheel velocities attributed to each sensor. However, for this assignment, you must implement it with this pattern in that there is an observer "list" to which subjects subscribe and unsubscribe (since there can only be 1 observer in this version, you may use a single variable that is set to the observer or to nothing). It is up to you in how you implement the pattern. In other words, your assignment is to think about the design and figure out what is the best solution to implement that design. CLARIFICATION as posted on announcements: the BV should be _pushing_ wheel velocity information. 

#### Factory Design Pattern

> **This requirement has been pushed to Iteration 3**

<del>Continue your use of the Factory pattern to instantiate and initialize Arena Entities. When complete, you should have 2 versions of factories -- one that uses a JSON for configuration and one that uses a text file. We will provide the format and some parsing functionality for this configuration file.</del>

<hr>

## <a name="reqs_doc">Documentation Requirements</a>

- Design Document
- Doxygen generated web pages including a landing page
- Self-Documenting code that is Google Style Compliant

Code documentation comes in many forms for many audiences. For this project, **your audience is other programmers** who need to understand class structure and relationships, interfaces, function parameters, function behavior, code organization, class organization, and code logic. Self-documenting code (i.e. using good organization and naming conventions) is an efficient means of communicating, since you have to write the code anyway. _Good_ comments - not too many, not too few - help guide others through the logic and class interfaces. For the larger picture of code and class structure, use UML diagrams and Doxygen-generated (automatic) web pages.

> A note about UML: In the third iteration, we will require the UML diagram again that represents the final implementation. This will include the Arena, BraitenbergVehicle, Predator, Food, Light, all factories, the strategy pattern, and the observer pattern (however you decide to implement that). We will not be assessing the UML this iteration, but you might want to keep it up-to-date as you develop code.

### <a name="design_doc">Design Document

Put the design document through another draft to refine your Factory Pattern design description. Extend the document by describing two alternative implementations of the viewing of the wheel velocities. One alternative is that the viewer uses getters instead of the Observer Pattern. The other is your implementation of the Observer Pattern. CLARIFICATION as announced in Larson's class: we discussed 3 alternative implementation of the Observer pattern in class. You may compare and contrast any of these with your version rather than comparing with using getters.

In your comparisons, provide an overall description highlighting key points of the implementation and using UML and/or code snippets to clarify your ideas. Also provide at least one advantage and one disadvantage of each implementation.

Name the design document *iteration2_design.pdf*.

**CLARIFICATION of SUBMISSION as published in announcements: Please submit via Canvas.**


### <a name="style">Google Style Guide Compliance</a>

Please comply to the Google C++ Style. Running cpplint on your code should generate 0 errors, except we do allow the use of rand(). Check that your methods are CamelCase (except for getters and setters) and your class variables end in an underscore.

See the information at the URL: https://google.github.io/styleguide/cppguide.html  for more details.

### <a name="doxy">Doxygen</a>

Continue to refine your in-code Doxygen documentation including a brief description for all classes and a full documentation of Arena, Braitenberg Vehicles, and your factories with JSON including both methods and member variables. _You do not have to fully document your new factory classes that do not use JSON._

In addition to the code documentation, please create a draft of the _landing page_ (i.e. mainpage.h) in this iteration. This file is placed in the **src** directory for Doxygen to find. You can try it out by placing this text in _mainpage.h_ :

```
  /*! \mainpage My Personal Index Page
   *
   * \section intro_sec Introduction
   *
   * This is the introduction.
   *
   */
```

Run doxygen and open up the index.html file and you will see how this is presented. In this iteration, communicate to other programmers the general structure of this software including the key Model-Viewer-Controller aspects. You do not need to describe the Braitenberg vehicles and behaviors, but include a link that describes it. Provide general guidance in how to understand the code structure and how to modify it. Think back to the first time that you saw this code -- what is the critical information that you needed to understand the code?

The minimum requirement for text is 3 paragraphs. If you were to print it out with 1.5 line spacing, it should take at least 1 page.

<hr>

## <a name="reqs_dev">Code Development Requirements</a>

- Git Branches
- Git Issue Tracking
- Git Commits and Messages

### <a name="git_usage">Git Branches and Issues</a>

Again for this iteration, create Git issues to document bugs, feature enhancements, refactoring, documentation, clean-up, etc. As you address significant issues, create a branch off of _devel_. CLARIFICATION: several issues can be handled within a single branch.

As in the previous iteration, code should be developed in a branch off of the _devel_ branch. There are a lot more coding requirements for this iteration, so we should see at least double the branches that were created in the last iteration. Please do not delete these branches after they are merged so that we can grade that aspect of development.

Commit messages for less significant modification can be composed at the command line, but should be consistent in style and be informative with regard to what changes were made where. You can make minor edits on the _devel_ branch, but the version you keep in your development branch should always compile without errors and execute.

Do not merge the _devel_ branch with _master_ until the final implementation is ready for submission.

<hr>

## <a name="reqs_imp">Implementation Requirements</a>

The iterative method identifies and prioritizes feature enhancements and code refactoring over short intervals called sprints. Below is a prioritized list of feature enhancements, fixes, and refactoring of the code. **Complete all functionality in one priority level before moving on to the next.** In this way, if we run out of time, the low priority items will be dropped from the requirements.

### <a name="reqs1">Priority Level 1 : Braitenberg Sensors, Behaviors, and the Strategy Pattern with Unit Tests </a>
### Due: MON,  April 1st at 11:55pm

- Unit tests for the strategy pattern implementation.
- Braitenberg Vehicle behaviors implemented using the Strategy Pattern.
- Braitenberg Vehicle sensors with behaviors implemented in the BV class.

Implement unit tests for the Strategy Pattern. The general requirements for this are described in the next paragraph. As for the unit tests, place these in separate files in the _test_ directory. Test all behaviors under a few different scenarios (i.e. different sensor readings). Design the strategy pattern in a way that testing is easy and doesn't require a complex SetUp for testing.

Implement the Braitenberg behaviors of Love, Explore, Coward, and Aggression using the Strategy Pattern (as described here and above in the Design Requirements section). Refer to _Head First Design Patterns_ (Chapter 1) to see how this pattern is used to create different flying and quacking behaviors for ducks. Similarly, the BVs move their wheels with different behavior depending on its type with respect to its sensors. There should be an abstract class from which all behaviors derive. BVs should _contain_ behaviors. Implement this pattern in such a way to make **testing easy**, as you will have to write the unit tests for this.

Add a new sensor to all Braitenberg Vehicles -- the _Braitenberg Vehicle Sensor_. This behaves exactly like the Food and Light sensor, except it senses other BVs. Any of the 4 behaviors can be associated with this sensor. Add the option in the GUI to set the behavior of the Braitenberg Vehicle Sensor.

CLARIFICATION as announced: There should be an option in the GUI to select the robot behavior AND you should add "robot_behavior" to your JSON configuration so that you can test your code. 

<hr>

### <a name="reqs2">Priority Level 2 : Predators and Observing Wheel Velocities
### Due: MON, April 8th at 11:55pm

- Real-time display of wheel velocities implemented with the Observer Pattern.
- A Predator class implemented with Aggressive behavior towards BVs, Cowaring behavior towards Lights, and no behavior towards Food or other Predator's.
- Add the functionality for BVs to be consumed by the a predator.

Use the Observer Pattern (as described above in the Design Requirements section) to implement the display of wheel velocities for a user-specified Braitenberg Vehicle. This is a real-time display of the contributing elements of the various sensors -- in other words, the light_wheel_velocity and food_wheel_velocity AND bv_wheel_velocity calculated in the BV::Update() function. The user should have a menu to select a BV to display -- only those BVs that are currently in existence should be displayed (CLARIFICATION: which is how the code functioned when it was distributed, so you shouldn't have to change anything).

Create a Predator class that is another type of ArenaEntity. It is very similar to a BV, except that it has fixed behaviors with respect to the various stimuli. It is Aggressive toward BVs, Cowering towards Lights, but no behavior towards Food or other Predators. It can pass through Food, Light, and BVs (because it consumes them), but should go into avoidance upon collision with a wall or another predator.

Add to the simulation the ability for Predators to consume BVs. This means that if the Predator collides with a BV, that BV dies. Leave a "ghost" of the BV in the Arena -- make it very light in color. It should no longer move and everything can pass through it. CLARIFICATION: The BV should no longer influence any other entity.

CLARIFICATION as announced on Canvas: Add "Predator" to your JSON -- otherwise, how would you test it?

<hr>

##### <a name="reqs3">Priority Level 3 : Starving BVs, Weighted Behaviors, and <del>non-JSON Factory</del>
### Due: April 15th at 11:55pm

- Add the functionality for BVs to starve if they do not consume after 600 iterations.
- Calculate the wheel velocity of a BV based on a dynamically weighted combination of all wheel velocity behaviors. Vary the weight depending on the current situation and sensor readings. For example, if both light and food sensors are active, rather than the equation (light\_wheel\_velocity + food\_wheel\_velocity)/2, if the robot is starving then use the food\_wheel\_velocity exclusively.
- <del>Another factory that instead of JSON for configuration, uses a text file.</del>

Add to the simulation the feature that BVs will starve after not eating for 600 iterations. Once the BV eats something, its "timer" is reset for another 600 iterations. If the BV dies of starvation, as with it being consumed by a Predator, it should become a ghost.

> CLARIFICATION: You can choose what to do with the food once it has been consumed. Note that if you delete it, eventually all the robots will starve. Alternatives include depleting each food item as it is consumed, deleting it, deleting it but regenerating food elsewhere, "ghosting" it, etc. REALLY -- it's your choice and we won't assess your choice. What we do suggest is that right after the robot eats, it ignores the food so it can be free to explore other areas of the Arena -- this would be a good application of the dynamic wheel velocities.

The second feature enhancement in this grouping is your opportunity to experiment with the wheel velocity equation. Instead of always using the average of all wheel velocities generated by the stimuli, use a formula that changes dynamically depending on the current circumstance. It should depend on something that the BV can sense (e.g. it is close to death because it hasn't eaten in a long time). There is no right answer for the equation to calculate wheel velocities -- the idea is that you create an implementation that can be experimented with so that you (or some user) can derive an equation to achieve some goal (e.g. keep the BV alive for as long as possible).

CLARIFICATION: You may both weight wheel velocities and dynamically change the behavior (e.g. be aggressive towards food when it is starving and use user-specified behavior when not). Presumably, you will create an equation that results in _rational_ behavior, like seeking food when it is starving, but this is not a requirement.

ANOTHER CLARIFICATION: If you are unsatisfied with how your BV is behaving, you may modify the sensor reading equation or the default speed or the maximum speed or make other tweaks, provided the wheel velocity equation changes dynamically with respect to the current situation and the user-specified behaviors are used to "control" the robot in certain situations.

<hr>

## <a name="deliver">Deliverables and Submission Process</a>

For the final iteration submission, everything will be submitted via Github in the master branch of the project directory in your class repo **AND the design document will be submitted via Canvas**. We will pull your repository at the specified due dates and grade according to the contents at that time. You should be developing in your_ devel_ branch, but at the time of final submission, merge _devel_ with _master_.

For the preliminary submissions, submit via Github on the _devel_ branch AND follow the directions at the top regarding a Canvas submission. We will look at both.

**Late assignments will not be accepted**, but you will receive partial credit for partial completion of the requirements.

Your software will be assessed through automatic testing and by the TA. The process for testing will be to start by typing  `make clean` then `make`. We **highly encourage** you to make a new clone of your repo on a **cselabs machine** and also `make clean` and `make` to confirm all is working well before submitting your iteration 2 code.

<hr>

## <a name="assessment">Assessment Weighting</a>

Preliminary 1 (18.5%)
- 5% Strategy Pattern for implementing behaviors for wheel velocity calculations. Final Submission.
- 10% Unit tests for strategy pattern. Final Submission.
- 2.5% Draft of BraitenbergVehicle sensor implementation
- 1% Style Compliance

Preliminary 2 (15%)
- 10% Observer Pattern for implementing the display of wheel velocities. Final Submission.
- 4% Draft of Predator implementation. 
- 1% Style Compliance

Final Iteration 2 Submission (67.5%)
- 13% Design Document (more heavily weighted on Observer Pattern description)
- 10% Doxygen landing page
- 5% Doxy documentation of classes
- 5% Google Style Compliance
- 2.5% BraitenbergVehicle sensor implementation including GUI option to choose behavior
- 11% Predator implementation with "ghosting" BVs
- 5% Starving BVs
- 5% Dynamic Wheel Velocity calculation including GUI display of values
- 10% Git usage including issues, branching, and commit messages

## <a name="resources">Resources</a>

Graphics Libraries :
- https://github.com/wjakob/nanogui
- https://nanogui.readthedocs.io/en/latest/
- https://github.com/memononen/NanoVG
- https://www.opengl.org/

Local System and Compilation:
- Repo: https://github.umn.edu/umn-csci-3081-S19/csci3081-shared-upstream
- Linking library: `/project/bin/obj/
- Compilation: https://gcc.gnu.org/
- Linux quick reference: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/linux.html
- Makefile Resources: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/cpp.html

Testing:
- https://github.com/google/googletest
- Unit Testing: https://martinfowler.com/bliki/UnitTest.html

Style:
- https://google.github.io/styleguide/cppguide.html
- https://github.com/google/styleguide/tree/gh-pages/cpplint
- https://www.python.org/downloads/

Documentation:
- http://www.stack.nl/~dimitri/doxygen/
- https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

IDEs:
- Xemacs: https://www.xemacs.org/
- vi: http://www.lagmonster.org/docs/vi.html
- Atom: https://atom.io/
- Sublime: https://www.sublimetext.com/
- Eclipse: https://eclipse.org/

<hr>
