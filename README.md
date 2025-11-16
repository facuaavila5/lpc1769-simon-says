# Musical Simon Says Game for LPC1769

A "Simon Says" game implemented on the NXP LPC1769 microcontroller. This project generates musical note sequences that the user must replicate, with input handled via a UART terminal.


## Project Description

This is an embedded systems project that brings the classic "Simon Says" memory game to life using an LPC1769 ARM Cortex-M3 processor.

Instead of colored lights, the game generates a sequence of musical notes (from A to G). The notes are generated in real-time using the **DAC** (Digital-to-Analog Converter) and **DMA** (Direct Memory Access) to play a 100-sample sine wave at different frequencies.

The game's logic (generating sequences, checking user input) is handled in C. The user interacts with the game by typing the note sequence into a **UART** terminal (like Tera Term or PuTTY).

## 🛠️ Key Features

* **MCU:** NXP LPC1769 (ARM Cortex-M3)
* **Audio Generation:** Real-time musical note synthesis (Do, Re, Mi, Fa, Sol, La, Si) using the DAC.
* **High-Performance Audio:** Uses **GPDMA** to stream a 100-sample sine wave buffer to the DAC, ensuring zero CPU load during playback.
* **Game Logic:** Implements a full "Simon Says" game loop, generating progressively longer random sequences.
* **User Interface:** Uses **UART** for all user input, allowing the player to type the sequence they heard.
* **Timers:** Utilizes two timers for note duration and sequence timing.

## 🎮 How to Play

1.  Connect to the board using a UART terminal.
2.  Press the button connected to P2.10 (EINT0 pin)
3.  The game will play the first note of the sequence.
4.  Type the corresponding number for the note (e.g., 0 for Do, 1 for Re...) and press Enter.
5.  If correct, you have to push the button again. The game will play the first note *again*, followed by a new random note.
6.  Repeat the new, longer sequence.
7.  The game continues until you make a mistake!

## 📺 Demo Video

**[Click here to watch the project demo on YouTube!](https://www.youtube.com/shorts/m86qcenKUOQ)**

## 👥 Authors

* **Ezequiel Marredo**
* **Candela Benavides**
* **Facundo Avila**

* ## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
