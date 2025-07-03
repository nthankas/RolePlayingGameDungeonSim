# RolePlayingGameDungeonSim

Text-Based RPG Dungeon Crawler (C, Terminal-Based)

Author: Nikhil Thankasala

Overview:  
This is a terminal-based role-playing game (RPG) built entirely in C. The game simulates dungeon exploration, allowing a player to navigate interconnected rooms, collect items, and unlock new areas based on their inventory. All game state and room data are stored in external binary-formatted room files, and the game responds in real time to keyboard input. The entire game runs through the terminal using `getchar()` input and provides clean directional prompts, inventory tracking, and branching room logic.

Design and Structure:  
The game engine is organized into a modular system using two custom libraries: one for handling player inventory and item tracking, and another for controlling room transitions, file I/O, and dynamic room descriptions. Each room is stored as a structured binary file containing multiple versions of the room—each with its own description, exit layout, and item drop logic—dependent on the player's current inventory. At runtime, the game selects and renders the most appropriate version of the room the player is eligible to access.

The player interacts with the game using single-character commands (`n`, `s`, `e`, `w`, and `q` to quit). After each move, the terminal is updated with the new room’s title, description, and available directions. Room transitions and descriptions are entirely driven by file parsing and inventory conditions, and no heap memory or global state is used. A clean and efficient `makefile` handles build and cleanup automation for object files and the executable.

Development Process:  
The core logic was developed incrementally, beginning with a file parsing engine to interpret the custom binary room format. From there, I implemented room navigation and exit handling, followed by the inventory system to collect and check items across transitions. The final stage involved wiring together the main event loop and building a display function to update the terminal output with meaningful prompts and descriptions. I also implemented proper input sanitization and fallbacks for malformed input or unreachable rooms.

Outcome and Notes:  
The final result is a compact, replayable RPG engine built entirely from scratch with no external dependencies. It runs in any POSIX terminal, uses pure standard I/O functions, and demonstrates practical applications of file I/O, event-driven design, and stateful logic in C. The entire project was designed for low-level performance, and all memory is statically managed. Future improvements could include combat logic, persistent save states, or randomly generated dungeon layouts. This project took around 10–12 hours to complete and serves as a fun demonstration of how far simple C code can be pushed to simulate interactive gameplay.
