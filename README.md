# AIM-Lab-Automation
In the Artificially Intelligent Manufacturing (AIM) center, we are producing Graphene from Graphene Oxide with laser patterning mechanism powered by Artificial Intelligence (AI). To get the best parameter configuration we use Bayesian Optimization(BO) as sequential Model Based Optimization(sMBO). 

I was assigned with the task of making a closed loop autonomous system for the manufacturing. I'm using R to utilize the BO with mlrMBO package. For the automation works, I'm using python. The codes are inside > codes folder. and the main code is in AIM-Lab-Automation/codes/main program.ipynb.



![Alt Text](https://github.com/SourinDeyUW/AIM-Lab-Automation/blob/master/final.gif)


# Work Flow
 
**Stage 1** 
1. Populate Data on a csv file with random data. The csv file contains 4 Features: Laser Power, Laser Exposure Time, Pressure      and Gas. Each of the 4 features have some ranges except the discrete feature Gas. </br>
   The file is located in AIM-Lab-Automation/initial experiment.ipynb. </br>
   
2. Initially 2 background pictures should be taken: background 1D at 1500 wavenumber and another background at 2700 wavenumber.
   The code is located in AIM-Lab-Automation/updated codes/Backgrounds.ipynb. </br>
   
3. When these are done, we have to run the experiment to fillup initial G/D ratios of those random datasets. The code is     located in AIM-Lab-Automation/updated codes/main program.ipynb.


**Stage 2**
1. Now comes second stage of the experiment. Now, the csv file created from initial experiment.ipynb is populated with each configurations having G/D ratios. They are fed to the R code. R code predicts a new parameter configuration, which is saved in the same csv file. The code reads the csv file again, conducts experiment, finds G/D ratio, then again R code reads the file and thus the close loop experiment takes place. </br>
The code is located in AIM-Lab-Automation/updated codes/main program.ipynb. </br>

2. The R code is located in AIM-Lab-Automation/updated codes/R Python interface.ipynb (though it's already in the main program.ipynb).



**Coordinates**

(4,3)-->(10,10). Step=1

**Past Challenge**

1. Find the exact coordinates of GO(Graphene Oxide), Quartz, Kapton.
    
        GO Coordinates : (3,3)--->(9,9), step size .5, .5. It worked well.
        Kapton Coordinates: under research.
        Quartz: under research.
     
2. Calibrate the Laser power and monitor if patterning is done properly or not. (Solved).

        laser_power.power=((power_in_csv_file-2.7979)/0.4639)/1000
        This equation is used to calibrate the laser power, because the machine LightHouse Photonics doesn't exactly delivers the power         which it shows up in it's display. Some power loss occurs during propagation.
        
3. Run experiments on many points of a sample to monitor time-out issues from ESP 300 (motion controller) and solve them if it shows up.
 (Time out issues solved)
 
