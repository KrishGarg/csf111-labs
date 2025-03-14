# Practice Question

## Learning objectives

* Dealing with structs: user-defined datatypes
* Working with strings and `string.h` functions

## Starting point

Use the shortcut Ctrl + Shift + V to open the README.md file in Preview mode. 

The starter code contains *skeletons* of the `best_sector` and `best_setup` functions, as well as the `view_setups`, `main` and `get_input` functions. It will not compile at this point as there are some important bits of code to be added. Complete the tasks below in order.

**Do NOT modify the** `main` **function in any way.**

## Background
Lewis Hamilton is a race car driver who competes in Formula One. This year, he is starting with a new team, Ferrari, and they need your help to win this Sunday's season opening race, the 2025 Australian Grand Prix. 

During pre-season testing two weeks ago, they tried various aerodynamic configurations (setups) of their new car, and based on the data obtained, simulated laps of the Australian racetrack. The race takes place at Albert Park Circuit in Melbourne, and the track is made of three parts called *sectors* (see the image `albertpark.jpg` in this directory). 

You are given the *sector times* for each setup: the time the car took to drive through each sector. Complete the function bodies in the `.c` file to help Ferrari choose the best setup for Sunday's race.  


# Tasks

## Task 0

First, rename the `.c` file to your `BITSID.c`. For example, if your ID is 2024AXPS5678G, rename the file to `2024AXPS5678G.c`. 


To rename the file:

- Right-click on it in the explorer column on the left.
- Click the rename option.
- Type in the new name and hit enter.

### Compilation instructions

To compile your C program, you can run:
```sh
gcc BITSID.c -o structs.out
```

and this command to run the compiled program:

```sh
./structs.out
```

## Task 1

Include the appropriate header files at the top of the program.

## Task 2
Define a user-defined datatype (structure) called `setup`. The fields in `setup` are:

* `setup_no`: An integer that uniquely labels each setup.
* `sector1_time`: A string containing the sector 1 time for this setup of the car.
* `sector2_time`: A string containing the sector 2 time for this setup of the car.
* `sector3_time`: A string containing the sector 3 time for this setup of the car.
* `lap_time`: A string containing the lap time for this setup of the car in the format `m:ss.SSS`.

The format of all sector times is `ss.SSS` (S for milliseconds) and the format of all lap times is `m:ss.SSS`. 
For example, a sector 1 time of 1 minute, 35.324 seconds corresponds to `"95.324"` for `sector1_time`. A sector time cannot be larger than 99.999 seconds.
A lap time of 1 minute, 53.423 seconds corresponds to `"1:53:423"`. A lap time cannot be larger than `"9:59.999"`. 

## Task 3
There is an error in the `get_input` function. Currently, the lap time from the simulation for all setups is set to `0:00.000`.

Modify the code below `TODO` to correctly calculate the lap time for each setup using the sector times.

After this step, you can uncomment `view_setups(s, setup_count);` in `main` to check if your code compiles and executes correctly till this step. 

Don't forget to comment out `view_setups(s, setup_count);` in `main()` again after you are done checking so that the autograder can match outputs correctly.

## Task 4

Find out which setup performed the best in a particular sector and print the corresponding time. The best time in a sector is the fastest (least) time achieved in that sector.

* Implement the function `best_sector` to match its description (`@brief`).
* You can use functions provided in `string.h`.
* Run your code, select the appropriate function and test it with the examples provided in the description.

## Task 5

Find out which setup is the best for Sunday's race. The best setup is the one that achieved the fastest (least) time over one lap. 

* Implement the function `best_setup` to match its description (`@brief`).
* You can use functions provided in `string.h`.
* Run your code, select the appropriate function and test with the example provided in the description.

## Verify your code
We have provided some test cases with the code.
You can test your program against these by running the following command in the terminal:

```python
python3 autograder.py BITSID.c practice-tests.json
```
It is recommended to test your program manually with a few inputs of your own before running the autograder on it.

## Prepare Submission
This problem is just for practice and so you do not need to submit it anywhere. However, if you would like to practice running the `prepare_submission` script, follow the instructions below.

1. First, make sure the .c file is renamed properly and works as expected.
2. Run the following command in the terminal to make the program to prepare your submission an executable:

   ```sh
   chmod u+x prepare_submission
   ```

3. Execute that program to produce the submission file `BITSID.tar.gz`:

   ```sh
   ./prepare_submission
   ```
