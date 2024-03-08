# How to upload firmware to MCU

If you found this thread and want just to flash and run simple projects to your STM32VLDISCOVERY without debug, use can configure CubeIDE to use ST-LINK_CLI.EXE for flash and run:

1. Install st-link utilites

2. in stm32cubeide open Project→ Properties→ C/C++ Build→ Settings→ tab "Tool Settings" → MCU Post build outputs check "Convert to Intel Hex file"

3. in Run → Debug Configurations double-click on first line "C/C++ Application" to create new configuration. Under the tab "Main" set "C/C++ Application" to C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe, under the tab "Arguments" set "Program arguments" to -c SWD -P ${project_loc}\${config_name:${project_name}}\${project_name}.hex -Rst, under the tab "Common" check "Display in favorites menu" – "Run"

4. in Window → Preferences → General → Keys set Command "Run" Binding to Ctrl+F11

Now you can write simple code and quickly flash it to your STM32VLDISCOVERY by pressing Ctrl+B and then Ctrl+F11. Although debugger is not working, you can still find some bugs and solve problems by manually sending debug information over UART using TTL to USB converter.

https://community.st.com/t5/stm32cubeide-mcus/does-the-ide-support-debugging-of-the-stm32vldiscovery-board-how/td-p/341521