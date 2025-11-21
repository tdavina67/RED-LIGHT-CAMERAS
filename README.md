Overview
This project analyzes red light camera violation data using C++. It reads structured data from a file, aggregates statistics, and outputs findings on violations, 
neighborhoods, cameras, and monthly trends.​

Features
Reads red light camera violation records from a data file

Aggregates statistics for total violations and unique cameras

Reports neighborhood-level violation counts and camera distributions

Generates monthly charts (bar graph in text format) of violations

Provides search capability by intersection or neighborhood

Getting Started
Prerequisites
C++ compiler (e.g., g++, clang++)

Standard C++ libraries

Data file formatted with intersections, addresses, dates, camera numbers, violations, and neighborhoods

Installation
Clone the repository:

git clone https://github.com/tdavina67/RED-LIGHT-CAMERAS.git
Compile the program:

g++ -o red_light_cameras main.cpp
Usage
Run the program in your terminal/console:

./red_light_cameras
Follow on-screen prompts to enter the data file name and select menu options.

Example Data File
Each line contains:

intersection,address,camNum,date,violations,neighborhood
Project Structure
main.cpp: Source code for processing, analyzing, and displaying red light camera data

Data file: Expects a CSV-formatted text file

License
This project is released under the MIT License.

Author
Davina Titus
University of Illinois at Chicago
CS 141 - Program Design II
April 2025
