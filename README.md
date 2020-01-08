# AIM-Lab-Automation

**Current Challenges**

1. Find the exact coordinates of GO(Graphene Oxide), Quartz, Kapton.
2. Calibrate the Laser power and monitor if patterning is done properly or not.
3. Run experiments on many points of a sample to monitor time-out issues from ESP 300 (motion controller) and solve them if it shows up.


# Stage 1
1. Populate Data on a csv file with random data. The csv file contains 4 Features: Laser Power, Laser Exposure Time, Pressure      and Gas. Each of the 4 features have some ranges except the discrete feature Gas. </br>
   The file is located in AIM-Lab-Automation/initial experiment.ipynb. </br>
   
2. Initially 2 background pictures should be taken: background 1D at 1500 wavenumber and another background at 2700 wavenumber.
   The code is located in AIM-Lab-Automation/Backgrounds.ipynb. </br>
   
3. When these are done, we have to run the experiment to fillup initial G/D ratios of those random datasets. The code is     located in AIM-Lab-Automation/main program.ipynb.


# Stage 2
1. Now comes second stage of the experiment. Now, the csv file created from initial experiment.ipynb is populated with each configurations having G/D ratios. Now they are fed to the R code. R code predicts a new parameter configuration, which is saved in the same csv file. The code reads the csv file again, conducts experiment, finds G/D ration, then again R code reads the file and thus the close loop experiment takes place. </br>
The code is located in AIM-Lab-Automation/main program.ipynb. </br>

2. The R code is located in AIM-Lab-Automation/R Python interface.ipynb (though it's already in the main program.ipynb).
