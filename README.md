# Tiva C "TM4C123GH6PM"
Microprocessors Project for 3rd Year CSE Ain Shams University Students 


<div align="center">
<img src="https://github.com/Salmasherif33/GPS-Tracking-System/blob/main/images/tiva.jpg" width="300" height="380" >   
<img src="https://github.com/Salmasherif33/GPS-Tracking-System/blob/main/images/conf.png" width="500" height="380" >  
<br>
<br>
  
![GitHub language count](https://img.shields.io/github/languages/count/Salmasherif33/GPS-Tracking-System?color=%2300&logo=GitHub)
![GitHub contributors](https://img.shields.io/github/contributors/Salmasherif33/GPS-Tracking-System?color=%2300&logo=GitHub)
![GitHub top language](https://img.shields.io/github/languages/top/Salmasherif33/GPS-Tracking-System?color=%2300)    
  
  
</div>  
  

# GPS-Tracking-System

this system reads coordinates from  NMEA GPS module NEO 6. It calculates the distance from a starting point until the distance reaches 100 m, then it turns on the LED of the TIVA C Board and displays the calculated distance on the LCD.

## First MileStone
- We Should implement a function that turns on the LED when the distance exceeded 100 meters
- We Should implement the function that will display the output distance in the LCD and test it by writing on them a dummy data
- We Should implement a function to calculate the total distance taken , configure UART to communicate with GPS
- We Should write the function that parse the coordinates sent from the GPS in the form of ASCII
- We should implement the software part that draws the trajectory  


<div align="center">
<img src="https://github.com/Salmasherif33/GPS-Tracking-System/blob/main/images/first_mile_stone.jpeg" width="650" height="400" >  
</div>

- Note: Arduino is used as a 5v Supplier 
- The image show the testing of the LCD Display when the distance exceeded 100 and the Red LED is On when the distance exceeded 100


## For SoftWare Setup  

TO RUN THIS PROJECT YOU NEED TO :
##### First: You Need To Install visual studio community From here >>[link](https://visualstudio.microsoft.com/vs/community/) and you need to install .NET desktop development packages
##### Second: Create New Project and choose Windows form APP(.NET FramWork )
##### Third: INSTALL PACKAGES FROM HERE:
[GMap.NET.Windows 2.0.2](https://www.nuget.org/packages/GMap.NET.Windows/2.0.2?_src=template)
##### Fourth:Copy this files in SW folder To you Directory project.
##### Fifth: Restart your Project.

- Note:This program must be connected to the Internet.
- Note:You have to add the file Directory that containing your data to line 22 and 23 in file Form1.cs .
