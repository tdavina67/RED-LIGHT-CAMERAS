# Red Light Cameras — Chicago Violation Analysis 🚦

A C++ data analysis tool that processes real red light camera 
violation data from the City of Chicago, aggregating statistics 
and surfacing insights across neighborhoods, intersections, 
and time periods.

## Overview
Chicago's red light camera network generates thousands of violation 
records across the city. This program reads that structured dataset, 
processes it efficiently in C++, and produces meaningful analysis — 
from which neighborhoods have the highest violations to monthly 
trend charts — all from the command line.

## Features
- Parses and processes large CSV-formatted violation datasets
- Aggregates total violations and unique camera counts city-wide
- Reports neighborhood-level violation counts and camera distributions
- Generates ASCII bar charts of monthly violation trends
- Search by intersection name or neighborhood
- Clean menu-driven console interface

## Sample Output
```
Monthly Violations (Bar Chart):
Jan |████████████| 1,204
Feb |█████████| 934
Mar |███████████████| 1,502
...

Top Neighborhoods by Violations:
1. Austin          - 3,241 violations
2. Humboldt Park   - 2,876 violations
3. West Englewood  - 2,104 violations
```

## Concepts Demonstrated
- File I/O and CSV parsing in C++
- Data aggregation with maps and vectors
- Sorting and ranking algorithms
- String search and filtering
- Console data visualization (ASCII charts)
- Menu-driven program architecture

## Data Format
Each record contains:
```
intersection, address, camera_number, date, violations, neighborhood
```

## How to Run
```bash
git clone https://github.com/davina-titus/RED-LIGHT-CAMERAS.git
cd RED-LIGHT-CAMERAS
g++ -o redlightcameras main.cpp
./redlightcameras
```
Then follow the on-screen prompts to load the data file and explore.

## Language
- **C++**

---
*Data sourced from the City of Chicago Open Data Portal*  

