# 🔄 Two-Way UART Communication – PIC16F877A (Master–Slave)

## 📌 Project Overview

This project demonstrates **bi-directional UART communication** between two PIC16F877A microcontrollers:

- 🔵 Master (Transmitter)
- 🟢 Slave (Receiver with LCD)

The Master sends characters **A–D** using push buttons.  
The Slave receives the character, displays it on LCD, and sends back a response **a–d**.

The Master then controls LEDs based on the received response.

---

## 🧠 System Architecture

```
[Master PIC]  <--UART-->  [Slave PIC]
     |                          |
  Switches                    LCD Display
     |                          |
     ---> Sends A–D            ---> Sends back a–d
     <--- Receives a–d         ---> Displays Rx & Tx
     |
   Controls LEDs
```

---

## 🔘 Master (Transmitter) Functionality

### Input:
Push buttons connected to RB4–RB7

| Switch | Transmitted Character |
|--------|-----------------------|
| RB4    | 'A' |
| RB5    | 'B' |
| RB6    | 'C' |
| RB7    | 'D' |

### Output:
Based on received response:

| Received | PORTD Output | LED Action |
|----------|-------------|------------|
| 'a' | 0x40 | RD6 ON |
| 'b' | 0x02 | RD1 ON |
| 'c' | 0x00 | Both OFF |
| 'd' | 0x42 | Both ON |

---

## 📟 Slave (Receiver) Functionality

### Receives:
Characters 'A' – 'D'

### Displays on LCD:
```
Rx DATA: A
Tx DATA: a
```

### Sends Back:
| Received | Sent Back |
|----------|------------|
| 'A' | 'a' |
| 'B' | 'b' |
| 'C' | 'c' |
| 'D' | 'd' |

---

## ⚙️ UART Configuration

Both microcontrollers use:

- Asynchronous mode
- Baud Rate Generator (SPBRG = 0x09)
- TXSTA = 0x20
- RCSTA = 0x90
- Fosc = 6 MHz

Baud rate is configured for standard serial communication.

---

## 🔌 Hardware Connections

### UART Wiring

| Master | Slave |
|--------|--------|
| RC6 (TX) | RC7 (RX) |
| RC7 (RX) | RC6 (TX) |
| GND | GND |

⚠️ Cross connection required:
- TX → RX
- RX → TX

---

### Master Side:
- Switches → RB4–RB7
- LEDs → PORTD

### Slave Side:
- 16x2 LCD → PORTB & PORTD
- UART → RC6 & RC7

---

## 📂 Project Structure

```
UART-TwoWay-Communication-PIC/
│
├── Master/
│   └── uart_master.c
│
├── Slave/
│   └── uart_slave.c
│
└── README.md
```

---

## 🔄 Communication Flow Example

1️⃣ Master switch RB4 pressed  
2️⃣ Master sends 'A'  
3️⃣ Slave receives 'A'  
4️⃣ Slave displays "A" on LCD  
5️⃣ Slave sends back 'a'  
6️⃣ Master receives 'a'  
7️⃣ Master turns ON RD6 LED  

---

## 🧠 Embedded Concepts Covered

- UART Communication (Full Duplex)
- Master–Slave Architecture
- Switch Interfacing
- LED Control Logic
- LCD Interfacing
- Serial Data Transmission
- Register-Level Programming
- Polling-Based Communication

---

## ▶️ How to Run

1. Program Master code into first PIC.
2. Program Slave code into second PIC.
3. Connect UART pins cross-wise.
4. Connect common ground.
5. Power both boards.
6. Press switches on Master.
7. Observe LCD on Slave and LEDs on Master.

---

## 📈 Learning Outcomes

After completing this project, you will understand:

- How UART works in PIC microcontrollers
- Two-way serial communication
- How to build Master–Slave systems
- Handling TX and RX registers
- Embedded system communication debugging

---

## 🚀 Future Improvements

- Add interrupt-based UART
- Add error handling (Overrun error)
- Add checksum validation
- Display communication status
- Implement PC-to-PIC communication

---

## 👨‍💻 Author

**Digambar Samala**  
Embedded Systems Developer  

---

## 📜 License

Open-source project for educational purposes.
