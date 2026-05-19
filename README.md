# Graphing Calculator

A desktop graphing calculator built with **C++17** and **SFML 2.6**. Enter mathematical expressions, plot them in Cartesian or polar coordinates, define reusable functions, view derivatives, and optionally stream live sensor data from an Arduino.

![calcdemo-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/4840fd2d-8c3f-42ac-ab59-2e4624c9fc14)

---

## Table of Contents

- [Requirements](#requirements)
- [Building](#building)
- [Running](#running)
- [Interface Overview](#interface-overview)
- [Features](#features)
- [Expression Syntax](#expression-syntax)
- [Graph Modes](#graph-modes)
- [Keyboard & Mouse Controls](#keyboard--mouse-controls)
- [User-Defined Functions](#user-defined-functions)
- [History & Persistence](#history--persistence)
- [Arduino Live Data](#arduino-live-data)
- [Error Handling](#error-handling)
- [Project Structure](#project-structure)

---

## Requirements

| Dependency | Notes |
|------------|-------|
| **CMake** 3.5+ | Build system |
| **C++17 compiler** | MSVC, GCC, or Clang |
| **Git** | SFML is fetched automatically via CMake `FetchContent` |
| **Python 3** (optional) | Only needed for Arduino serial import (`pyserial`) |

**Font files** (must be in the program’s working directory):

- `arial.ttf` — graph axis labels
- `Roboto-Thin.ttf` — UI panels

**Data files** (created automatically or shipped with the project):

- `historyData.txt` — saved equation history and user functions
- `ArduinoData.txt` — Arduino sensor stream (required at startup)
- `stop.txt` — coordination file for the Python serial script (created by the app)

---

## Building

```bash
# From the project root
cmake -B build
cmake --build build
```

On **Windows** with Visual Studio, open the generated solution or use:

```powershell
cmake -B build
cmake --build build --config Debug
```

The executable is written to:

- **Windows (Debug):** `build/bin/Debug/main.exe`
- **Other platforms:** `build/bin/main`

---

## Running

1. Copy `arial.ttf`, `Roboto-Thin.ttf`, `historyData.txt`, and `ArduinoData.txt` into the **working directory** (the folder containing the executable, e.g. `build/bin/Debug/`).
2. Run the executable from that directory, or configure your IDE’s working directory accordingly.

```bash
# Example (Linux/macOS)
cd build/bin
./main
```

```powershell
# Example (Windows)
cd build\bin\Debug
.\main.exe
```

If a required font or data file is missing, the program prints an error and exits.

---

## Interface Overview

The window is **1400×800** pixels:

| Region | Location | Purpose |
|--------|----------|---------|
| **Graph area** | Left ~80% | Coordinate plane, grid, axes, plotted curves |
| **Sidebar** | Top-right | Mouse position, last key/action, mode toggle |
| **Settings bar** | Bottom-right | Save, clear history, graph mode |
| **History / Functions panel** | Right center | Past equations or stored `f0`–`f9` definitions |
| **Input bar** | Bottom-left (toggle) | Type and submit equations |

A small **red dot** follows the mouse when the cursor is over the window.

---

## Features

### Graphing

- Plot **y = f(x)** in Cartesian mode
- Plot **r = f(θ)** in polar mode (θ is the variable `x` in the expression)
- Plot the **numerical derivative** (slope) of the active equation
- **Adaptive polar sampling** with screen-boundary detection for smoother curves
- **Grid and axis labels** that scale with zoom
- Up to **400 sample points** per curve across the visible domain

### Navigation

- **Pan** with arrow keys or click-and-drag on the graph
- **Zoom** with Page Up / Page Down, mouse wheel, or Shift/Ctrl-modified wheel
- **Square scale** (equal x/y units) — `Tab`
- **Square domain** (match x range to y range) — `\`

### Expressions

- Infix math with standard operator precedence
- Trigonometric, logarithmic, min/max, and exponent functions
- **10 user-defined functions** (`f0` … `f9`)
- **Polar angle bounds** via `{lower, upper}` syntax
- Case-insensitive input

### UI & Data

- **Equation history** — recall past entries with a click
- **Function library** — view, select, or delete stored definitions
- **Save / clear** history to `historyData.txt`
- **Live Arduino plotting** — stream numeric samples from a serial device

---

## Expression Syntax

### Variables and numbers

| Token | Meaning |
|-------|---------|
| `x` | Independent variable (x in Cartesian, θ in polar) |
| `3.14`, `2`, `0.5` | Numeric literals |

### Operators

| Operator | Meaning | Precedence |
|----------|---------|------------|
| `+` `-` | Addition, subtraction | Low |
| `*` `/` | Multiplication, division | Medium |
| `^` | Exponentiation | High |

Unary minus is supported (e.g. `-x`, `-3`).

### Built-in functions

| Function | Description | Example |
|----------|-------------|---------|
| `sin(x)` `cos(x)` `tan(x)` | Standard trig (radians) | `sin(x)` |
| `sec(x)` `csc(x)` `cot(x)` | Reciprocal trig | `sec(x)` |
| `log(a, x)` | Logarithm base `a` | `log(10, x)` |
| `ln(x)` | Natural log | `ln(x)` |
| `max(a, b)` `min(a, b)` | Maximum / minimum | `max(sin(x), cos(x))` |
| `f0(x)` … `f9(x)` | User-defined function call | `2*x + f0(x)` |

Expressions are parsed with a **shunting-yard** algorithm and evaluated via **RPN**.

### Examples

```
sin(x)
x^2 + 3*x - 7
log(2, x)
max(sin(x), cos(x))
2*x + f0(x)
```

### Polar angle domain

In **polar mode**, append `{lower, upper}` to set the θ range (in radians). Default is approximately **−4π to 4π**.

```
cos(x){0, 6.28}
```

Only one domain block is allowed per expression.

---

## Graph Modes

Cycle modes by clicking **CARTESIAN** in the settings bar (bottom-right).

| Mode | Label | What is plotted |
|------|-------|-----------------|
| **0** | `CARTESIAN` | y = f(x) |
| **1** | `POLAR` | r = f(θ), converted to (x, y) |
| **2** | `DERIVATIVE` | Approximate slope dy/dx |
| **3** | `ARDUINO` | Live (time, value) pairs from `ArduinoData.txt` |

---

## Keyboard & Mouse Controls

### Graph navigation

| Input | Action |
|-------|--------|
| **← → ↑ ↓** | Pan left / right / up / down |
| **Page Up** | Zoom in (centered on screen) |
| **Page Down** | Zoom out |
| **Mouse wheel** | Zoom toward cursor |
| **Shift + wheel** | Zoom **x** only |
| **Ctrl + wheel** | Zoom **y** only |
| **Left-click + drag** | Pan the view |
| **Tab** | Square scale (equal unit length on both axes) |
| **\\** (backslash) | Square domain (x range = y range) |

### Equation input

| Input | Action |
|-------|--------|
| **Enter** | Show input bar (if hidden) or submit equation |
| **← →** | Move text cursor (while input bar is focused) |
| **Backspace** | Delete character before cursor |
| **Escape** | Quit the application |

### Mouse (panels)

| Action | Result |
|--------|--------|
| Click **HISTORY / FUNCTIONS** (sidebar) | Toggle between history list and function list |
| Click a **history entry** | Load that equation into the input bar |
| Click a **function entry** | Load that function’s body for editing/plotting |
| Click the **red delete button** (functions panel) | Clear that function slot |
| Click **SAVE ALL** | Write history and functions to `historyData.txt` |
| Click **CLEAR HISTORY** | Erase equation history (functions are kept) |
| Click **CARTESIAN** (etc.) | Cycle graph mode |

---

## User-Defined Functions

Ten slots are available: **f0** through **f9**.

### Define a function

1. Show the input bar (**Enter** if hidden).
2. Type a definition in the form `fN:expression` (N = 0–9):

   ```
   f0:x^2 + 1
   f1:sin(x) + f0(x)
   ```

3. Press **Enter**. If valid, the definition is stored and added to history.

### Use a function

Reference it in any equation:

```
f0(x)
2*x + f0(x)
```

### Rules

- Names must be a single digit: `f0` … `f9`
- Circular references are detected and rejected
- Undefined functions cannot be called
- Delete a function from the **Functions** panel (click the red area on the right of a row)

---

## History & Persistence

### In-session history

Every successfully plotted equation is appended to the **History** panel. Click an entry to reload it.

### Save to disk

Click **SAVE ALL** to write:

- Equation history → `historyData.txt`
- User function definitions → same file

File format:

```
Base:FileState:Data:
<equation 1>
<equation 2>
...
Base:FileState:Functions:
<function 0 body>
<function 1 body>
...
```

### Clear history

Click **CLEAR HISTORY** to remove saved equations while keeping function definitions.

History and functions are **loaded automatically** on startup from `historyData.txt`.

---

## Arduino Live Data

The app can plot streaming numeric data from an Arduino (or any serial source) via a file bridge.

### Setup

1. Install Python dependency:

   ```bash
   pip install pyserial
   ```

2. Edit `py_serial_import.py`:

   - Set `arduino_port` to your COM port (e.g. `"COM4"` on Windows, `"/dev/ttyUSB0"` on Linux).
   - Adjust `baud_rate` if needed (default `9600`).

3. Ensure `ArduinoData.txt` exists with this first line:

   ```
   Base:FileState:Arduino:
   ```

4. Uncomment the launch line in `main.cpp` if you want the app to start the Python script automatically:

   ```cpp
   system("start /B python py_serial_import.py");
   ```

   Otherwise, start the script manually before or while the calculator runs:

   ```bash
   python py_serial_import.py
   ```

### Behavior

- The Python script reads one numeric value per line from serial and appends it to `ArduinoData.txt`.
- The calculator polls the file each frame and plots points as **(time, value)** in **ARDUINO** mode.
- On exit, the app writes `terminate` to `stop.txt`, which stops the Python loop.

---

## Error Handling

Invalid input is caught during parsing or evaluation. Messages appear in the input bar, for example:

| Error | Typical cause |
|-------|----------------|
| Unknown Input | Unrecognized token or typo |
| Missing left paren | Unbalanced `(` `)` |
| Invalid function name | `f10(x)` or bad index |
| Circular definition | `f0` calls `f1` calls `f0` |
| Division by zero | `/` with zero divisor |
| Trig domain error | e.g. `tan(π/2)`, `csc(0)` |
| Log domain error | Non-positive argument |
| Domain redefinition | Multiple `{…}` blocks |
| Upper bound < lower bound | Bad polar range |

---

## Project Structure

```
Graphing_Calculator/
├── main.cpp                 # Entry point, Arduino/history file setup
├── CMakeLists.txt           # Build config (SFML via FetchContent)
├── py_serial_import.py      # Optional Arduino serial bridge
├── historyData.txt          # Saved history & functions
├── includes/
│   └── animate/
│       ├── animate.cpp/h    # Main window, events, UI logic
│       ├── constants.cpp/h  # Screen size, graph/UI constants
│       ├── exception.cpp/h  # Error types and validation
│       ├── Calculator/      # Graph, plot, text UI, coordinate transform
│       ├── Parser/          # Shunting-yard and RPN evaluator
│       └── Tokens/          # Lexer tokens (operators, trig, functions, …)
└── _tests/                  # Google Test unit tests (optional build)
```

---

## License

See repository license information if provided.
