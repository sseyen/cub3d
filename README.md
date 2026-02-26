# cub3d 👩🏻‍🎤
*This project has been created as part of the 42 curriculum by jlager and alisseye*


## Description
Brief overview of what this project does and its main goal.

The project implements [main concept/functionality] and focuses on [key learning objective such as memory management, algorithms, system calls, etc.].

### Project Structure - Connection Flow Diagram:

```
[.cub File]
    ↓
[Parsing Module] → [Validation]
    ↓
[Game Init] → Load textures, create window
    ↓
┌───[Game Loop]────────────────────────────┐
│                                          │
│  [Input Handler] → [Player Update]       │
│         ↓                                │
│  [Collision Detection] ← [Map Data]      │
│         ↓                                │
│  [Raycasting Engine] ← [Player State]    │
│         ↓              ← [Map Data]      │
│  [Rendering] ← [Textures]                │
│         ↓      ← [Colors]                │
│  [Display via miniLibX]                  │
│         ↓                                │
│  [Loop back or Exit]                     │
└──────────────────────────────────────────┘
```

```
Init             █████ 5%
Parsing          ████████████████████ 20%
Input            █████ 5%
Raycasting       ███████████████████████████████████ 35%
Rendering        ███████████████ 15%
Game Loop/Polish ██████████ 10%
Player/Camera    █████ 5%
Collision        █████ 5%
```

## Instructions

### Installation and Compilation
This project is using the [MLX42](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-macos) library. To compile, make sure you have `cmake` installed or install it:

**on Linux (Ubuntu/Debian):**
```bash
sudo apt-get install cmake
```

**on macOS:**
```bash
bashbrew install cmake
```

**... than you can simply clone and make this proyect:**
```bash
git clone git@github.com:sseyen/cub3d.git cub3D
cd cub3D
make
```

**Available commands:**

`make` - Compile the project

`make clean` - Remove object files

`make fclean` - Remove objects and executable

`make re` - Recompile everything if there were any changes to the code (especially header file *.h or Makefile)

### Execution
```bash
./[executable-name] [arguments]
```

**...for example:**
```bash
./[executable-name] example_argument
```

### Textures
The included textures (saved in /textures) are 64x64px.


## Resources

- [Lode's Computer Graphics Tutorial | Raycasting](https://lodev.org/cgtutor/) - Main source for understanding ray casting
- [aaaa.sh | The DDA Algorithm, explained interactively](https://aaaa.sh/creatures/dda-algorithm-interactive/) - Very simple trigonometry algorithm explanation
- [YouTube | javidx9](https://www.youtube.com/watch?v=NbSee-XM7WA) - Super Fast Ray Casting in Tiled Worlds using DDA
- [xxx]() - Placeholder for additional references
- Textures were created with AI

### AI Usage
- Debugging: ["understanding error messages"]
- Concept clarification: [examples such as "understanding pointers", "learning about file descriptors", "understanding project partners' code"]
- Testing: [examples such as "generating edge case tests"]

**Note:** All code implementation and logic were written independently; AI was used as a learning and debugging assistant.

# Additional sections may be required depending on the project 
(e.g., usage examples, feature list, technical choices, etc.).

...Any required additions will be explicitly listed below.