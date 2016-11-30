# Blockbusted
This is the Blockbusted Video Project for CS433


There's a problem with adding .pro and .pro.user files
Therefore if you want to start from scratch you have to create a new project in Qt and move the files over.
Download the .zip, unzip it and move the files into your new project's location, replacing the prefabed 
main.cpp, mainwindow.cpp, mainwindow.h, and mainwindow.ui

Append "sql" to the provided (7th) line on your .pro:
"QT       += core gui"

Therefore it'll look like this:
"QT       += core gui sql "

Also the only other change necessary is in the dbmanager.cpp file
line 2 needs to be you specific absolute path to the blockbusted_db.db file


Sprint 1:

    Major Class Design
    Learn QT and incorporate a main window
    Add Button shells for Add and Remove Employee, Customer as well as Edit Inventory
    Make shells for Check in and Check out inventory
    Create a quit button
    
    
    
Sprint 2:

   Resizing windows for many resolutions
   Add emp_verification for restricted privelage functions
   Add employee/customer screen definitions
   Edit inventory screen definition
 
 
Sprint 3: 

    Alter Resizing so buttons can't change size, and add scaling for quit button
    Merge all button definitions into one master branch
    Worked on and resolved one universal database accessor class 
    
    
Sprint 4: 
    
    Refactored code to prevent stale unused code from taking up too much space
    Refined Add buttons and Edit Inventory
    
Sprint 5:

    Added View/Edit Employee, View Edit Customer, Remove Employee, Remove Customer
    Changed log in to activate and deactivate buttons based on authority level
    Added Inventory Count to keep track of how many of what the store has
    Resized all remaining windows
