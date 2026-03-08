# [Touhou] Bad Apple!! - ASCII Animation Player

# Author

ByAnAlex

Alias: **Mika Von Euphillia**

---

⚠️ **Important Notice**

This program is designed **only for Windows**.

It uses Windows-specific libraries:

* `windows.h`
* `mmsystem.h`
* `PlaySound()` from **winmm**

Because of this, the program **will not compile or run on Linux or macOS without modification.**

---

# Description

This program plays the Touhou **"Bad Apple!!"** animation inside the Windows console using ASCII frames.

Frames are stored as `.txt` files and loaded into memory before playback.
The program synchronizes frame rendering with real time to maintain a stable frame rate while the audio track plays simultaneously.

---

# How It Works

1. The program reads the total number of frames from:

```
res/numberOfFrames.txt
```

2. All ASCII frames are loaded into memory:

```
res/BA1.txt
res/BA2.txt
...
```

3. The audio file is played asynchronously:

```
res/BA.wav
```

4. Frames are rendered at **30 FPS** using time-based frame calculation.

---

# Setup Guide

## Method 1 — Using Dev-C++

### 1. Open the Project

Open the file:

```
main.c
```

using **Dev-C++**.

### 2. Configure the Compiler

Before running the program, you must link the **Windows Multimedia Library**.

Steps:

1. Open the **Tools** menu
2. Click **Compiler Options**
3. Find the field labeled:

```
Add the following commands when calling the compiler
```

4. Add the following flag:

```
-lwinmm
```

5. Click **OK** to save.

This flag links the **Windows Multimedia Library** required for the `PlaySound()` function.

### 3. Run the Program

After configuration:

1. Click **Compile & Run**
2. The program will build and start in the console window.

---

# Method 2 — Using Visual Studio Code

### 1. Install a C Compiler

If you don't have a compiler installed, install **MinGW (GCC)**.

After installation, verify the compiler works by opening a terminal and running:

```
gcc --version
```

If the version information appears, the compiler is correctly installed.

---

### 2. Install VS Code Extensions

Install an extension that supports C development.

Recommended extension:

```
C/C++ (Microsoft)
```

This extension provides:

* Syntax highlighting
* IntelliSense
* Debug support

---

### 3. Open the Project Folder

Open the folder containing:

```
main.c
res/
```

in **VS Code**.

---

### 4. Open the Terminal

Open the integrated terminal in VS Code.

You can use either:

* **PowerShell**
* **Command Prompt (CMD)**

Menu:

```
Terminal → New Terminal
```

---

### 5. Adjust Terminal Size (Recommended)

For proper display of the ASCII animation:

1. Maximize the terminal window.
2. Reduce the font size using:

```
CTRL + -
```

Continue until the terminal size shows approximately:

```
147 x 38
```

This ensures the ASCII frames fit properly inside the console.

---

### 6. Compile the Program

Run the following command:

```bash
gcc main.c -o badapple -lwinmm
```

Explanation:

* `gcc` → C compiler
* `main.c` → source code
* `-o badapple` → output executable name
* `-lwinmm` → links Windows multimedia library

---

### 7. Run the Program

After compilation finishes, run:

```bash
./badapple.exe
```

Press **ENTER** when prompted and the animation will begin.

---

# Directory Structure

```
res/
 ├─ BA1.txt
 ├─ BA2.txt
 ├─ ...
 ├─ numberOfFrames.txt
 └─ BA.wav

main.c
```

---

# Notes

* The console must support **ANSI escape codes**.
* All frames are loaded into memory before playback.
* Large animations may require significant RAM usage.

---

