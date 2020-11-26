# bootcamp_project
<h2>BACKGROUND</h2>
This project was written by Robert Gothäll, Rasmus Källum and Jessica Green as a part of a C++ bootcamp carried out during the autumn 2020. The bootcamp started with 2 weeks of lectures and individual assignments and ended with a 4 week group assignment with the goal to create car driveline simulation. We were initially asked to have two binaries. 
The first binary is Inputhandler taking driver input and outputting it on CAN. 
The second binary, the Emulator should have two threads the first thread running a CANreader taking in the frames from the inputHandler the second thread running the asked for driveline which should output a number of signals on the same CAN bus.
Later on we also added a third binary giving us the possibility to display the output in an instrumentcluster. 

<h2>PLANNING</h2>
We started out our project by defining what we wanted to achieve. To aid us we used different uml charts and text files,  available in the_docs folder. We intentionally planned for a very minimal functionality as a mvp and gradually adding functionality to it. The main outcome of the planning was a MVP according to below.

"We want to build a SW giving a simulated driver the possiblity to
start/stop a vehicle, change it gears and accelelrate/decelerate it.

This will be done using two threads, the first one running a CAN reader
taking the input from driver and placing it in a shared memory.
The second one a component processing the input from driver and 
outputting the vehicle status on CAN in order to emulate engine and
gearbox of a car.

For inputs/outputs see CanFrameMessages.txt"

<h2>THE "FINISHED" PRODUCT</h2>
At the end of the bootcamp we have three binaries, the relation between them and what they're doing can be seen in this picture: 
<img src="https://github.com/SubspaceBob/bootcamp_project/blob/main/Docs/ComponentDiagram.png"> 

The InputHandler is designed to take in keybordpresses and translate them to a canframe that can be sent out. The SW is based on provided SW that aids in the two tasks and to controll these we have written code to use the provide API according to our demands (i.e. connect our chosen key with the proper CAN frame and byte).

The Emulator is our main code. The main function creates two threads, one running a function called runCANIO and the other thread running the function runVehicle.
runCANIO is responsible for reading incoming frames and storing them to a memory which the runVehicle thread can access. It also reads from the memory to get the output from th runVehicle and send it out on CAN.
runVehicle is the actual vehicle emulation. It is split into an engine and a gearbox. Both the engine and the gearbox is using input from the other ECU to calculate its outputs. Once calculated the output is saved in the memory waiting for the runCANIO thread to send it out on CAN

Finally we have a GUI running a provided graphical instrument cluster that we have set up to take in CAN frames connect the data to the proper inputs in order to move gauges, light up telltales etc.

<h2>CMAKE AND BASH</h2>
Our project consists of a large number of .cpp and .h files. We use tiered cmake files to describe the intended dependencies on the diferent files. As a top layer we also have bash scripts that automatically performs a wanted action. Either starting the project or running the test cases.

<h2>TESTING</h2>
We have unit tests for the engine and gearbox that utilize google test to run them and summarize the result in a report. In order to perform the tests, open a terminal at the proper level and write ./run_tests. This will build all necesary SW, run the tests and write xml reports in the folder Code/6_TestReports. It will also create a html representation of the xmls and open it up in a browser tab.

<h2>RUNNING IT</h2>
as mentioned there is a bash file that compiles, builds and starts all the binaries. In order to it simply open a terminal window on the proper level and write ./magic_start. Once they're up and running press alt+tab to make sure that the little window that actually registers keypresses is the one active.

To start the engine push the brake and start button (down arrow + enter). Once the engine is started it will eventually output our idle rpm (roughly 800). 
To change gear press the brake once again and this time chose P, R, N or D (down arrow + Letter P/ Letter R/Letter N/ LeterD)
To accelerate press up arrow. (Only works in D and R)
To decelerate press down arrow. (Only works in D and R)
To light up various telltales press buttons 1-+.
Turn off engine press the start button (enter) while in gear P.
To turn off the Emulator binary press q.
To turn off the inputhandler press esc. (Note turn off the binary first.)

<h2>STILL TO DO</h2>
There are a number of things we would like to improve on our project. For starters we currently have no automatic way of shutting down the GUI.

Create a database using a template to create a number of frames with a unique ID and 8 data bytes. We could then rewrite the CANIO to have general read/writes to CAN as well as for storing to memory. Based on the database we could then do an extraction from the memory in the runVehicle thread and isolate the individual signals for use in the calculations before putting back all of them as a frame message in the outgoing memory. This would give both levels a more readable code.

Feature improvement. We have more features than planned for in the MVP but there are still features that could be added and improved.

More tests. Right now we have only unit tests on the engine and gearbox separately. It would be good to implement system testing on both ECUs to verify their cooperation. We also lack testing for the inputHandler and the GUI.


