# Narrow-Bridge

You are asked to write a program that synchronizes traffic over a narrow light-duty bridge in the region. Traffic
may only cross the bridge in one direction at a time, and if there are ever more than 3 vehicles on the bridge at
one time, it will collapse under their weight. In your program, each vehicle will be represented by one thread,
which executes the procedure oneVehicle when it arrives at the bridge:
oneVehicle(int vehicle_id,int dir, int time_to_cross) {
 arriveBridge(dir);
 crossBridge(vehicle_id,dir,time_to_cross);
 exitBridge(vehicle_id,dir);
}
vehicle_id is an integer which uniquely identifies each vehicle (1, 2, 3... and so on).
dir is either 0 or 1; it gives the direction in which the vehicle will cross the bridge.
time_to_cross is the time it takes a vehicle to cross the bridge – assume that every vehicle takes 5 seconds to
cross the bridge.
Implement a traffic control policy that imposes a limit on the number of vehicles that can cross the bridge in one
direction (3 vehicles), while vehicles travelling in the opposite direction are waiting to get on the bridge. NOTE:
if there are no vehicles waiting to get on the bridge in the opposite direction, your policy should not switch
directions. Your policy should provide fairness if there is traffic in both directions, but should never force a
vehicle to wait to get on the bridge if there is no traffic in the opposite direction.
Use semaphores in implementing arriveBridge, crossBridge and exitBridge procedures. arriveBridge procedure
must not return until it is safe for the car to cross the bridge in the given direction (it must guarantee that there
will be no head-on collisions or bridge collapses. crossBridge procedure should just delay for some time to
cross the bridge and print out a debug message. exitBridge is called to indicate that the caller has finished
crossing the bridge; exitBridge should take steps to let additional cars cross the bridge. In addition, exitBridge
should update a shared variable departure_index, which keeps track of the order in which the cars leave the
bridge, i.e., the first car to leave the bridge has departure_index 1, the second car has 2, and so on. The
exitBridge procedure should also print out the departure_index for each vehicle.
NOTE: You need to run your program, at least, for the three vehicle arrival schedules as follows:
(i) 5 : DELAY(10) : 5 : DELAY(10) : 5 : DELAY(10) : 5 (ii) 10 : DELAY(10) : 10 (iii) 20
The numbers indicate the number of vehicles arriving simultaneously at the bridge, while the numbers in
parentheses indicate the delay before the next arrival(s). Note that vehicles arriving simultaneously do not imply
that they are all traveling in the same direction (randomly assign a direction to each vehicle).
You may use Java or any multithreaded programming library for doing this assignment. In addition to your
program, make sure to submit a report with a snapshot result from the 3 vehicle arrival schedules.
