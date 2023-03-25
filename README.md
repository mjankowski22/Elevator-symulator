## Elevator symulator

<p>The program is created in win-api and the animation is built on timer. We can divide the program on the main following parts:</p>

![diagram](https://user-images.githubusercontent.com/106553136/175787969-3521825e-cf56-41e9-b2d5-616cd1db5a24.PNG)


<p>The green part was done by Michał Jankowski and the red part by Bartosz Hermanowski.</p>

![image](https://user-images.githubusercontent.com/106553136/175788019-475efdcf-616c-4780-8b0b-5173f99b816a.png)

### The algorithm
<ul>
<li>Each floor has 4 buttons. Clicking one of them adds passenger willing to go to the floor with the number on the button.</li>

<li>When the elevator goes up it takes only the passengers willing to go up and the same in the opposite case.</li>

<li>The elevator has weight-controll system. The max weight is set to 600kg.</li>

<li>The actual weight is presented on top of the window and shows the number of passengers in the elevator multiplied by weight of a single passenger (We assumed that each passenger weights 70kg).</li>

<li>After 5 seconds of inactivity the elevator goes to the floor with number 0.</li>

<li>The maximum number of passengers waiting on the single floor is set to 7.</li>

<li>We assumed that the elevator goes with the constant speed.</li>
</ul>
Passengers have the number of the floor which they are going to written on their heads.

![image](https://user-images.githubusercontent.com/106553136/175788359-f01213df-8563-434d-a75f-c88ac8d64758.png)



