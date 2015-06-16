echo off
cls
echo Demonstrating Requirement 3,8
echo ----------------------------- 
echo Searching with Sub Folders
"Debug/Executive.exe" "TEST FOLDER" "*.*" "/s" 
cls
echo Demonstrating Requirement 3,8
echo ----------------------------- 
echo Searching at location (Not Sub Folders)
"Debug/Executive.exe" "TEST FOLDER" "*.*"

cls
echo Demonstrating Requirement 5,8
echo ----------------------------- 
echo Searching Duplicate Files
"Debug/Executive.exe" "TEST FOLDER" "*.*" "/s" "/d"
cls
echo Demonstrating Requirement 6,8
echo ----------------------------- 
echo Searching files with search Text -- Searching for word Raagu
"Debug/Executive.exe" "TEST FOLDER" "*.*" "/s" "/d" "/f<Raagu>"

cls
echo Demonstrating Requirement 7,8
echo ----------------------------- 
echo Brief Summary 
"Debug/Executive.exe" "TEST FOLDER"