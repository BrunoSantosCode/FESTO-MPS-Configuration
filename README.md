# FESTO Modular Production System (MPS) Setup Guide 🏭

This guide explains how to set up and configure the FESTO MPS system with PLC, Raspberry Pi (CODESYS), and OPC UA communication.

## System Overview

**FESTO MPS** ➡️ **PLC** ➡️ **Raspberry Pi (CODESYS)** ➡️ **OPC UA** ➡️ **Dinasore (4DIAC-IDE)**

---

## ⚡ Quick Start: Automatic Operation

If everything is functioning correctly, no configuration is required! Simply **connect the factory system to power**, and everything should **run automatically**. 🎉

However, if there is an issue with the **PLC** or **Raspberry Pi**, follow the configuration steps below to troubleshoot and resolve the problem.

---

## ⚙️ PLC Configuration (If Needed)

### Model: Schneider ??? 🤔

### Access 🛠️
The communication is established via a blue interface cable with a **DIN plug**. This cable contains an FTDI chip which requires the **CH340 Driver (USB to Serial)**. For any assistance, contact **Daniel** from I004.

- Communication with the PLC is handled through the **UNITELWAY Driver**.

### Setup and Programming 🖥️
To configure the PLC, you'll need to use **PL7 Pro** (an older Schneider IDE for Telemecanique PLCs).

1. Identify the **Comm Port number (COMXX)** in the device manager.
2. Open **PL7 Pro** and navigate to:
   - `PLC` ➡️ `Define PLC Address` ➡️ `Options` ➡️ `Configuration of the driver` ➡️ `UNITELWAY Driver` ➡️ `Configuration`
   - Change the port to match the **Comm Port number** from the device manager.
3. Once connected, you can modify the settings or upload the project `.stx` file to the PLC. The project file is available [here](https://github.com/DIGI2-FEUP/TF4iM/blob/main/plc/FactorisDemoPLC.stx).

📌 **Important Info**:
- The PLC is configured to run on **192.168.0.10**.
- It hosts a **MODBUS server** which maps all inputs and outputs to REGISTERS. The mapping is available in the CODESYS Project (**where exactly?** 🤔).

### Questions to Clarify: ❓
- Does it work with other PLC models? 🤔
- Is the `.stx` file universal for all PLCs?
- Can the `.stx` file be edited in **PL7 Pro**?

---

## 🍓 Raspberry Pi Configuration (If Needed)

### Model: Raspberry Pi 4

### Access 🔌
- **IP**: 192.168.0.100 (This IP must be **192.168.0.100** due to PLC configuration, which whitelists MODBUS communication for this address. **Where exactly is this whitelisting configured?** 🤔)
- **Alternative IP**: 10.227.17.233
- **Username**: pi
- **Password**: raspberry
- You can SSH into the Raspberry Pi using the following command:

  `ssh pi@mpscontroller.local`

### Programming 🧑‍💻
The Raspberry Pi is configured with a **CODESYS project**. The project can be found [here](https://github.com/DIGI2-FEUP/TF4iM/blob/main/controller/factorisDemoController.project).

- **CODESYS Login**: 
  - Username: `admin`
  - Password: `raspberry`
- Variable mapping is available in this [Excel file](https://github.com/DIGI2-FEUP/TF4iM/blob/main/festo/Mapeamento_IOs.xlsx).

### Communication 🌐
- **Protocol**: OPC UA
- **Port**: 4840
- Additional info on the OPC UA setup? (**Details to be clarified** 🤔)

---

## 📋 Additional Notes

- Please ensure you have the correct drivers installed for the FTDI chip on the PLC interface cable.
- The communication between components follows this flow: **FESTO MPS** ➡️ **PLC** ➡️ **Raspberry Pi (CODESYS)** ➡️ **OPC UA** ➡️ **Dinasore (4DIAC-IDE)**.

---

## Summary 📝

- If everything is working fine, all you need to do is **connect the system to power** and it should run automatically.
- Only use the detailed configuration steps for **PLC** and **Raspberry Pi** if there are issues with communication or operation.

Feel free to reach out for any questions or clarifications! 😊
