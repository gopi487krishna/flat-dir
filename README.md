# flat-dir

Flats the contents of directory into the root folder


# Steps to build

- Clone the repository
- Create a new directory using `mkdir build` inside the root folder of the project
- `cd` into the build directory
- Run `cmake -G Ninja ..` 
- Run `ninja` to generate the executable


# Using flat-dir

- Create a parent directory which will contain all the directories that you want to process.
- Copy the directories that you want to process into the above directory.
- Place the executable inside this directory that contains other directories to be processed.
- Set the OUTPUT_ROOT environment variable to the path where you want the flattened directory to be stored
- Run the executable to flatten the directories.
