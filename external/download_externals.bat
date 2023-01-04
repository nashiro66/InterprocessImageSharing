@echo off

set GLFW_VERSION=3.3.8
set GLEW_VERSION=2.2.0
set SPOUT2_VERSION=2.007.009
set GLM_VERSION=0.9.9.8
set CURRENT_DIRECTORY=%~dp0

echo.

:: download glfw
if not exist glfw (
    powershell "wget https://github.com/glfw/glfw/releases/download/%GLFW_VERSION%/glfw-%GLFW_VERSION%.zip -OutFile %CURRENT_DIRECTORY%/glfw.zip"
    powershell "$progressPreference = 'silentlyContinue'; expand-archive -force glfw.zip ."
    ren glfw-%GLFW_VERSION% glfw
    del glfw.zip
    echo download glfw successful.
)

:: download glew
if not exist glew (
    powershell "wget https://github.com/nigels-com/glew/releases/download/glew-%GLEW_VERSION%/glew-%GLEW_VERSION%.zip -OutFile %CURRENT_DIRECTORY%/glew.zip"
    powershell "$progressPreference = 'silentlyContinue'; expand-archive -force glew.zip ."
    ren glew-%GLEW_VERSION% glew
    del glew.zip
    echo download glew successful.
)

:: download spout2
if not exist spout2 (
    powershell "wget https://github.com/leadedge/Spout2/archive/refs/tags/%SPOUT2_VERSION%.zip -OutFile %CURRENT_DIRECTORY%/spout2.zip"
    powershell "$progressPreference = 'silentlyContinue'; expand-archive -force spout2.zip ."
    ren Spout2-%SPOUT2_VERSION% spout2
    del spout2.zip
    echo download spout2 successful.
)

:: download glm
if not exist glm (
    powershell "wget https://github.com/g-truc/glm/releases/download/%GLM_VERSION%/glm-%GLM_VERSION%.zip -OutFile %CURRENT_DIRECTORY%/glm.zip"
    powershell "$progressPreference = 'silentlyContinue'; expand-archive -force glm.zip ."
    ren glm-%GLM_VERSION%.zip glm
    del glm.zip
    echo download glm successful.
)

echo.
pause