# cub3d 👩🏻‍🎤
*This project has been created as part of the 42 curriculum by jlager and alisseye*


## Discription
Brief overview of what this project does and its main goal.

The project implements [main concept/functionality]. It focuses on [key learning objective like memory management, algorithms, system calls, etc.].

### Project structure - Connection Flow Diagram:

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

## Instructions

### Instalation and Compilation
```bash
git clone [repository-url] [project-name]
cd [project-name]
make
```

**Available commands:**
- `make` - Compile the project
- `make clean` - Remove object files
- `make fclean` - Remove objects and executable
- `make re` - Recompile everything if there were any changes to the code (especially header file *.h)

### Execution
```bash
./[executable-name] [arguments]
```

**...for example:**
```bash
./[executable-name] example_argument
```


## Resources

- [cub3d | 42 Docs](https://harm-smits.github.io/42docs/projects/cub3d) - Main source to understanding RayCasting
- [Resource title](URL) - Brief description...

### AI Usage
- Debugging: ["understanding error messages"]
- Concept clarification: [Examples like "understanding pointers", "learning about file descriptors", "understanding project partners code"]
- Testing: [Examples like "generating edge case tests"]

**Note:** All code implementation and logic was written independently. AI was used as a learning and debugging assistant.

# Additional sections may be required depending on the project 
(e.g., usage examples, feature list, technical choices, etc.).

...Any required additions will be explicitly listed below.