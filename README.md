# Ring-WearTech
A research project on wearable technology

Requirements to implement this project:

    Hardware: 
    1. EFR32BG13 - starter kit, BMA280, Android Phone.
    
    Software 
    1. Simplicity Studio 4, Android Studio
    
    Steps: 
    1. Import the Firmware from this project to the Simplicity Studio 4
    2. Connect EFR32BG13 through USB and start Debugging/Execute
    3. Use two different instances of the Android Studio and import BLE and DTW apps, and execute them 
       (With new version you dont have to generate any signed apks)
    4. Open the DTW app and the BLE app. 
    5. The BLE advertisements will be visible in the BLE app, select it.
    6. Double tap on the sensor (BMA280) - the acknowledgment of the double tap is displayed on the BLE app.
    7. The user can start the gestures/commands/notes and it will be automatically transferred to the DTW app. 
    8. The DTW app provides visual graphs of realtime-data received, 
       to train with a particular command/notes/gesture - switch the button to the traning mode and hold-down the touch. and relese the touch once you are done with the gesture. 
    9. To recognise the gesture/command/notes, switch the button to the recognition mode and hold-down the touch to record the gesture and release once done. 
    10. If it is a match, it will be displayed on the app.
   
If eager to build the entire project ground up, 

    1. The schematics and the Layout desins are given in the "Altium-Schematics_Layout" folder.
    2. The components to order are given in the Excel sheet in same folder. 
    3. Run a free DFM check, and Submit the Gerber files to PCBWay 
    
    
The workinng prototype is uploaded on youtube,

   1. Ring-WearTech: https://www.youtube.com/watch?v=jb6WAhV-7PE
   2. BLE MESH: https://www.youtube.com/watch?v=EVaqNhNOGpU
   
   
