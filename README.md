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

- Schneider ❓❓❓


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

- The PLC is configured to run on `192.168.0.10`
  
- It hosts a **MODBUS server** which maps all inputs and outputs to REGISTERS. The mapping is available in the CODESYS Project (**where exactly❓**).

---

## 🍓 Raspberry Pi Configuration

### 🔲 Model: 

- Raspberry Pi 4


### 🔐 Access

- **IP**: `192.168.0.100`
  
     📝 Note: this IP must be `192.168.0.100` due to PLC configuration, which whitelists MODBUS communication for this address. **Where exactly is this whitelisting configured❓**)
  
- **Alternative IP**: `10.227.17.233` or `mpscontroller.local`
  
- **Username**: pi
  
- **Password**: raspberry
  
- You can SSH into the Raspberry Pi using the following command:
   ```bash
   ssh pi@mpscontroller.local
   ```


### 🖥️ Programming

- The Raspberry Pi is configured with a **CODESYS project**. The project can be found [here](https://github.com/DIGI2-FEUP/TF4iM/blob/main/controller/factorisDemoController.project).

- **CODESYS Login**: 
  - Username: `admin`
  - Password: `raspberry`
    
- The variable mapping is available in this [Excel file](https://github.com/DIGI2-FEUP/TF4iM/blob/main/festo/Mapeamento_IOs.xlsx).

### 🌐 Communication 

- **Protocol**: OPC UA
  
- **Port**: 4840
  
- Additional info on the OPC UA setup? (**Details to be clarified❓**)

---

## 🦖 Dinasore

### 1. 🚀 Run Dinasore

#### 1.1 Add Function Blocks

- Copy your function blocks (`.fbt` and `.py` files) to the Dinasore resources directory `dinasore-2.0/resources/function_blocks/`

#### 1.2 Navigate to the Dinasore Directory

- Open your terminal or command prompt and change to the Dinasore directory:

 ```bash
 cd /path/to/dinasore-2.0
 ```

#### 1.3 Execute Dinasore

- Start the Dinasore application by running:

 ```bash
 python3 core/main.py
 ```

### 2. ⚙️ Configure 4DIAC-IDE

#### 2.1 Launch Workspace

- Open 4DIAC-IDE and click `Launch` to launch the default workspace

#### 2.2 Create a New System

- Chose `Create New System` option, then enter the `<workspace_name>` and click `Finish`

#### 2.3 Create the System Configuration

- Copy the function blocks (`.fbt` and `.py` files) to the 4DIAC workspace `4diac-ide-1.11/4diac-ide/workspace/<workspace_name>/<fb_folder_name>/`

📝 Note: You may need to restart the 4DIAC-IDE in order to the new function blocks appear in the Pallete.

#### 2.4 Create the System Configuration

- Open the `System Configuration` tab and build the following schematic using the components in the Pallete:

![system_conf](https://github.com/user-attachments/assets/3a492057-6bf1-4bc0-9926-caf9315dd2d5)

#### 2.5 Create the Main Application using the Function Blocks

- Open the `<workspace_name>App` tab and build your main aplication using the components added before to the Pallete, as in the following example:

![4diac_app](https://github.com/user-attachments/assets/ef5c3480-b41e-45a0-a6a5-b69ba3656515)

📝 Note: don't forget to correctly set all the needed function blocks inputs

- After building the application, the function blocks need to be mapped, for this: right-click on the block -> `Map to ...` -> `RaspberryPI` -> `EMB_RES`

📝 Note: The system variables state can be seen in real time by clicking in `Debug` -> `Debug System` -> `<workspace_name>` and then right-clicking a function block -> `🔍 Watch`

#### 2.6 Deploy the System

- Deploy the system by right-clicking the `<workspace_name>` in the left tab and then click `Deploy`
