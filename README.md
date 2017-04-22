# README
This demo is an example of integration of the margot framework in an existing program, provided that the original function to be tuned expose some knobs. In this demo the function expose the num_trial knob.



## Installation Instruction

The first step is cloning the margot_core project from the repo:
~~~
:::bash
$ git clone https://gitlab.com/margot_project/core.git
~~~

Then proceed with the installation (follow instruction in the repository).
To test that everything is ok, run the margot_test executable in the core/build/framework folder.

Proceed with the setup of the Demo: 
1)copy the /margot_heel/margot_heel_if/ folder in the root of the Demo project.
~~~
:::bash
	$ cp -r core/margot_heel/margot_heel_if/ .
~~~

2)delete the default config files from the margot_heel_if folder.
~~~
:::bash
	$ rm margot_heel_if/config/*
~~~

3)copy the config folder from the root of the Demo to the margot_heel_if/
~~~
:::bash
	$ cp config/* margot_heel_if/config/
~~~

The point in doing this procedure is that the margot_heel_if is a collection of functionalities that are needed to create the interface and the library starting from configuration files that are customized from the single application. 
		
4)create a build folder inside margot_heel_if/, and run cmake and make
~~~
:::bash
	$ cd margot_heel_if/
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make
~~~

At this point a library should have been created that will be used from the application containing the interface described in terms of monitors, goals, knobs and objectives.

5)go back to the Demo root folder and create the build folder, run cmake and make
~~~
:::bash
	$ cd ../..
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make
~~~



