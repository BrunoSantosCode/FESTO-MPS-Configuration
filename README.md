# 🏭 FESTO Modular Production System (MPS) - Setup Guide 

This guide explains how to set up and configure the FESTO MPS system.

## 📌 System Overview

🏭 **FESTO MPS**  

&emsp;⬇️ Cable Connection  

📟 **PLC**  

&emsp;⬇️ Modbus Protocol  

🍓 **Raspberry Pi (CODESYS)**  

&emsp;⬇️ OPC UA Protocol  

🖥️ **Dinasore (4DIAC-IDE)**

---

## ⚡ Quick Start: Automatic Operation

- If everything is functioning correctly, no configuration is required! Simply **connect the factory system to power**, and everything should **run automatically**.

- However, if there is an issue with the **PLC** or **Raspberry Pi**, check the configuration steps below.

---

## ⚙️ PLC Configuration

### 🔲 Model: 

- Schneider


### 🔐 Access

- The communication is established via a blue interface cable with a **DIN plug**. This cable contains an FTDI chip which requires the **CH340 Driver (USB to Serial)**. For any assistance, contact **Daniel** from I004.

- Communication with the PLC is handled through the **UNITELWAY Driver**.


### 🖥️ Setup and Programming 

- To configure the PLC, you'll need to use **PL7 Pro** (an older Schneider IDE for Telemecanique PLCs).

1. Identify the **Comm Port number (COMXX)** in the device manager.
     
2. Open **PL7 Pro** and navigate to:
   
   - `PLC` -> `Define PLC Address` -> `Options` -> `Configuration of the driver` -> `UNITELWAY Driver` -> `Configuration`
     
   - Change the port to match the **Comm Port number** from the device manager.
     
4. Once connected, you can modify the settings or upload the project `.stx` file to the PLC. The project file is available [here](https://github.com/DIGI2-FEUP/TF4iM/blob/main/plc/FactorisDemoPLC.stx).


### 🌐 Communication 

- The physical IN/OUTPUTS from FESTO MPS to PLC mapping is available in this [Excel](https://github.com/DIGI2-FEUP/TF4iM/blob/main/festo/Mapeamento_IOs.xlsx).

- The PLC is configured to run on `192.168.0.10`
  
- It hosts a **MODBUS TCP/IP server** (port 502) which maps all inputs and outputs to IB/QB.

- This mapping is available in the CODESYS Project at: `Device` -> `Ethernet` -> `Modbus_TCP_Master` -> `Modbus_TCP_Slave` -> `ModbusTCPSlave I/O Mapping`

📝 Note: If the PCL needs to be changed, both the **PL7 Pro** program and the **`.stx`** project must be substituted, as they are specific to the currently installed PLC.

---

## 🍓 Raspberry Pi Configuration

### 🔲 Model: 

- Raspberry Pi 4


### 🔐 Access

- **IP**: `192.168.0.100`
  
     📝 Note: this IP must be `192.168.0.100` due to PLC configuration, which whitelists MODBUS communication for this address.
  
- **Alternative IP**: `10.227.17.233` or `mpscontroller.local`
  
- **Username**: pi
  
- **Password**: raspberry
  
- You can SSH into the Raspberry Pi using the following command:
   ```bash
   ssh pi@mpscontroller.local
   ```


### 🖥️ Programming

- The Raspberry Pi must be running CODESYS RUNTIME and should be configured as in the following image:

![image](https://github.com/user-attachments/assets/773e8ba3-7eee-4c5b-8bbe-8f901966131d)

- The Raspberry Pi is configured with a **CODESYS project**. The project can be found [here](https://github.com/DIGI2-FEUP/TF4iM/blob/main/controller/factorisDemoController.project).

- **CODESYS Login**:
     - Device name: `mpscontroller.local`
     - Username: `admin`
     - Password: `raspberry`

📝 Note: CODESYS version: 3.5 SP19 (not mandatory)

    
### 🌐 Communication 

- **Protocol**: OPC UA
  
- **Port**: 4840

- **CODESYS Mapping**: `Device` -> `PLC Logic` -> `Application` -> `Symbol Configuration`
  
- **Useful tool**: Prosys OPC UA Browser

     - Login: `opc.tcp://mpscontroller.local:4840`
 
     - Variables: `Objects` -> `DeviceSet` -> `CODESYS Control for Raspberry PI 64 SL` -> `Resources` -> `Application` -> `GlobalVars` -> `GVL`
 
     - The `NodeId` variable attribute value corresponds to the name to use in 4DICA-IDE 

- **Variables**: add a new OPC UA variable in CODESYS:
  
     - Declare variable: `Device` -> `PLC Logic` -> `Application` -> `GVL`
     
     - Map variable to OPC UA: `Device` -> `PLC Logic` -> `Application` -> `Symbol Configuration`

---

## 🦖 Dinasore

### 🚀 Run Dinasore

#### Add Function Blocks

- Copy your function blocks (`.fbt` and `.py` files) to the Dinasore resources directory `dinasore-2.0/resources/function_blocks/`

#### Navigate to the Dinasore Directory

- Open your terminal or command prompt and change to the Dinasore directory:

 ```bash
 cd /path/to/dinasore-2.0
 ```

#### Execute Dinasore

- Start the Dinasore application by running:

 ```bash
 python3 core/main.py
 ```

### ⚙️ Configure 4DIAC-IDE 1.11.0

#### Launch Workspace

- Open 4DIAC-IDE and click `Launch` to launch the default workspace

#### Create a New System

- Chose `Create New System` option, then enter the `<workspace_name>` and click `Finish`

#### Create the System Configuration

- Copy the function blocks (`.fbt` and `.py` files) to the 4DIAC workspace `4diac-ide-1.11/4diac-ide/workspace/<workspace_name>/<fb_folder_name>/`

📝 Note: You may need to restart the 4DIAC-IDE in order to the new function blocks appear in the Pallete.

#### Create the System Configuration

- Open the `System Configuration` tab and build the following schematic using the components in the Pallete:

![system_conf](https://github.com/user-attachments/assets/3a492057-6bf1-4bc0-9926-caf9315dd2d5)

#### Create the Main Application using the Function Blocks

- Open the `<workspace_name>App` tab and build your main aplication using the components added before to the Pallete, as in the following example:

![4diac_app](https://github.com/user-attachments/assets/ef5c3480-b41e-45a0-a6a5-b69ba3656515)

📝 Note: don't forget to correctly set all the needed function blocks inputs

- After building the application, the function blocks need to be mapped, for this: right-click on the block -> `Map to ...` -> `RaspberryPI` -> `EMB_RES`

📝 Note: The system variables state can be seen in real time by clicking in `Debug` -> `Debug System` -> `<workspace_name>` and then right-clicking a function block -> `🔍 Watch`

#### Deploy the System

- Deploy the system by right-clicking the `<workspace_name>` in the left tab and then click `Deploy`
