<div align="center">

```
_______    ______   __       __   ______   _______    ______   _______    ______
/       \  /      \ /  \     /  | /      \ /       \  /      \ /       \  /      \
$$$$$$$  |/$$$$$$  |$$  \   /$$ |/$$$$$$  |$$$$$$$  |/$$$$$$  |$$$$$$$  |/$$$$$$  |
$$ |__$$ |$$ |  $$ |$$$  \ /$$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |__$$ |$$ |  $$ |
$$    $$/ $$ |  $$ |$$$$  /$$$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$    $$< $$ |  $$ |
$$$$$$$/  $$ |  $$ |$$ $$ $$/$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |
$$ |      $$ \__$$ |$$ |$$$/ $$ |$$ \__$$ |$$ |__$$ |$$ \__$$ |$$ |  $$ |$$ \__$$ |
$$ |      $$    $$/ $$ | $/  $$ |$$    $$/ $$    $$/ $$    $$/ $$ |  $$ |$$    $$/
$$/        $$$$$$/  $$/      $$/  $$$$$$/  $$$$$$$/   $$$$$$/  $$/   $$/  $$$$$$/
```

**A lightweight Pomodoro timer widget for Linux — stay focused without leaving your desktop.**

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?logo=cplusplus&logoColor=white)
![GTK](https://img.shields.io/badge/GTK-3-4A86CF?logo=gtk&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%3E%3D3.10-064F8C?logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey?logo=linux&logoColor=white)
![Display](https://img.shields.io/badge/display-Wayland%20%7C%20X11-lightgrey)

[Features](#features) · [Build](#getting-started) · [Usage](#usage) · [Roadmap](#roadmap) · [Troubleshooting](#troubleshooting) · [Contributing](#contributing)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How the timer works](#how-the-timer-works)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Debian / Ubuntu](#debian--ubuntu)
  - [Fedora](#fedora)
  - [Arch Linux](#arch-linux)
  - [Build and run](#build-and-run)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Troubleshooting](#troubleshooting)
- [Known Limitations](#known-limitations)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

---

## Overview

**Pomodoro Widget** is a small desktop timer for Linux and Unix-like desktop environments. It keeps a compact tomato icon near the upper-left corner of the screen and reveals the timer controls when you click it. Start a focus session, pause when needed, and take a break when the timer switches phases — all without opening a separate productivity application.

The project is written in **C++17** and uses **GTK 3** for its interface. On compatible Wayland sessions, [`gtk-layer-shell`](https://github.com/wmww/gtk-layer-shell) places the widget in the overlay layer. If layer-shell is not supported, the application falls back to a regular always-on-top GTK window.

The default focus duration is **25 minutes**. By default, the break duration is calculated automatically as **20% of the focus duration**, which gives a five-minute break for a 25-minute session. Both durations can be customized in the widget.

> The project is intentionally small: a timer, a compact interface, and sounds for phase changes — without a large framework or a complicated setup.

> **Project status:** this repository is source-only. There are no prebuilt binaries, complete distribution packages, or installers, and none are planned. The only currently planned development item is a separate **Qt 6 branch**. Further maintenance may happen, but ongoing support is not guaranteed.

## Features

- **Compact desktop widget** — a tomato icon stays near the top-left corner of the screen.
- **Expandable controls** — click the icon to show or hide the timer and settings.
- **Start, pause, and reset** — control the current session from the widget.
- **Configurable focus duration** — set hours, minutes, and seconds.
- **Configurable break duration** — choose a fixed break or use automatic calculation.
- **Automatic break calculation** — a break is calculated as 20% of the focus duration, with a minimum of one second.
- **Automatic phase switching** — the timer alternates between work and break phases when a countdown ends.
- **Phase sounds** — bundled sound files are played at phase transitions through `paplay`.
- **Wayland layer-shell integration** — anchors the widget to the upper-left corner on compatible compositors.
- **CMake build** — build the application directly from source.

## How the timer works

The timer alternates between two phases:

| Phase | Default duration | What happens |
|---|---:|---|
| Focus / work | 25 minutes | The timer counts down while you work. |
| Break | 5 minutes | A break begins when the focus countdown ends. |

The break duration can be set in two ways:

- **Automatic:** set the break hours, minutes, and seconds to `0`. The widget calculates the break as 20% of the configured focus duration.
- **Custom:** enter a non-zero break duration to use that exact length.

For example, a 50-minute focus session produces a 10-minute automatic break. A 25-minute session produces a five-minute break.

When a phase reaches zero, the timer switches to the other phase and begins that phase's countdown. A sound is played for the transition. The timer itself updates once per second.

## Tech Stack

| Component | Technology |
|---|---|
| Language | C++17 |
| GUI | GTK 3 |
| Desktop layer integration | `gtk-layer-shell` |
| Build system | CMake (3.10 or newer) |
| Build dependency discovery | `pkg-config` / CMake `PkgConfig` |
| Sound playback | `paplay` |

## Getting Started

### Prerequisites

To build the project, you need:

- A C++17-capable compiler, such as GCC or Clang
- CMake 3.10 or newer
- `pkg-config`
- GTK 3 development files
- `gtk-layer-shell` development files
- `paplay` for sound notifications (usually provided by `pulseaudio-utils` on Debian / Ubuntu)

The widget can use the layer-shell overlay on compatible Wayland compositors. The code also contains a fallback for environments where layer-shell is not supported, such as typical X11 sessions.

### Debian / Ubuntu

Install the required packages:

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libgtk-3-dev libgtk-layer-shell-dev pulseaudio-utils
```

### Fedora

Install the compiler, build tools, GTK 3, layer-shell development files, and PulseAudio command-line utilities:

```bash
sudo dnf install gcc-c++ cmake pkgconf-pkg-config gtk3-devel gtk-layer-shell-devel pulseaudio-utils
```

Package availability can differ by Fedora release and enabled repositories. If a package is not found, check the package name for your release.

### Arch Linux

Install the dependencies with `pacman`:

```bash
sudo pacman -S --needed base-devel cmake pkgconf gtk3 gtk-layer-shell pulseaudio
```

### Build and run

Clone the repository and enter its directory:

```bash
git clone https://github.com/chees89/pomodoro-widget-linux.git
cd pomodoro-widget-linux
```

Configure and compile the project:

```bash
cmake -S . -B build
cmake --build build -j"$(nproc)"
```

Launch the application from the build directory:

```bash
cd build
./Pomodoro-Widget
```

**Tip:** run the executable from `build/` so the relative `sounds/` paths resolve to the sound files copied there by CMake. If you launch the binary from another working directory, audio playback may not find those files.

### Build in one go

After the dependencies are installed, you can use this short command sequence:

```bash
git clone https://github.com/chees89/pomodoro-widget-linux.git
cd pomodoro-widget-linux
cmake -S . -B build
cmake --build build -j"$(nproc)"
(cd build && ./Pomodoro-Widget)
```

## Usage

1. **Launch** `Pomodoro-Widget` from the build directory.
2. **Expand the widget** by clicking the tomato icon. Click it again to collapse the controls.
3. **Start a session** with **Start**.
4. **Pause** the countdown with **Pause**. Use **Reset** to return to the configured focus duration and stop the timer.
5. **Set the focus duration** with the work hours, minutes, and seconds controls.
6. **Choose a break duration.** Leave all break fields at `0` for automatic calculation, or enter a custom non-zero duration.
7. **Apply the settings** with **Accept**. Applying the configuration pauses the timer and starts a new work phase with the selected durations.

The timer display uses the `HH:MM:SS` format. The calculated-break label previews the automatic break duration based on the selected focus time.

## Project Structure

```text
pomodoro-widget-linux/
├── include/
│   ├── Notifier.h          # Sound notification interface
│   ├── PomodoroTimer.h     # Timer state and phase logic
│   └── WidgetWindow.h     # GTK widget and UI callbacks
├── sounds/
│   ├── BreakSound.mp3     # Break-start sound
│   └── WorkSound.mp3      # Work-start sound
├── src/
│   ├── main.cpp           # Application entry point
│   ├── Notifier.cpp       # Sound playback via paplay
│   ├── PomodoroTimer.cpp  # Countdown and phase switching
│   └── WidgetWindow.cpp   # GTK interface and layer-shell setup
├── CMakeLists.txt         # Build configuration
└── README.md
```

## Troubleshooting

### CMake cannot find `gtk+-3.0`

The GTK 3 development package is missing. Install `libgtk-3-dev` on Debian / Ubuntu, `gtk3-devel` on Fedora, or `gtk3` on Arch Linux, then configure the project again.

### CMake cannot find `gtk-layer-shell-0`

Install the **GTK 3** version of the gtk-layer-shell development package. On Debian / Ubuntu, the package is `libgtk-layer-shell-dev`; on Fedora, it is `gtk-layer-shell-devel`; on Arch Linux, it is `gtk-layer-shell`.

Make sure you have not installed only the GTK 4 layer-shell library: this project links against GTK 3 and the `gtk-layer-shell-0` pkg-config module.

### The widget does not appear as an overlay

Layer-shell placement depends on the active Wayland compositor and session. The application checks whether layer-shell is supported and falls back to an always-on-top GTK window if it is not. Window behavior may therefore differ between desktop environments and between Wayland and X11.

### Sounds do not play

The timer calls `paplay` to play `sounds/BreakSound.mp3` and `sounds/WorkSound.mp3`. Check that:

- `paplay` is installed and available in `PATH`;
- the audio server is running and accessible to your session;
- the sound files exist in the `sounds/` directory;
- you launch the application from the `build/` directory, where CMake copies the `sounds/` folder.

On Debian / Ubuntu, install `paplay` with:

```bash
sudo apt install pulseaudio-utils
```

### The executable is missing after building

Confirm that CMake completed successfully, then run:

```bash
cmake --build build
ls -l build/Pomodoro-Widget
```

Run the program from the build directory:

```bash
cd build && ./Pomodoro-Widget
```

## Known Limitations

- **Source-only distribution.** There are no prebuilt binaries, complete distribution packages, or installers, and none are planned. Build the application locally from source using the instructions above.
- **Sound playback depends on `paplay`.** Playback will not work if the command is missing, the audio server is unavailable, or the sound files cannot be found.
- **Overlay behavior depends on the desktop session.** Layer-shell placement is available only where the Wayland compositor supports it; the fallback window behavior can vary across environments.
- **Settings are runtime configuration.** The current implementation does not persist custom timer durations between application launches.
- **There is no `LICENSE` file in the repository at present.** See the [License](#license) section before redistributing the project.

## Roadmap

The planned scope is intentionally limited:

- [ ] Create a separate **Qt 6 branch**.

The current implementation uses **GTK 3**. The Qt 6 branch is planned work and is **not available yet**; until it exists, follow the build instructions above to compile the GTK 3 version.

No complete distribution package, installer, or prebuilt binary is planned. The project is intended to remain buildable from source.

Further maintenance or support may happen in the future, but there is currently **no commitment to ongoing support or a release schedule**. Bug reports and contributions are welcome, though responses and updates are best-effort.

## Contributing

Suggestions, bug reports, and improvements are welcome. As ongoing maintenance is not guaranteed, issues and pull requests are reviewed on a best-effort basis.

1. Open an [issue](https://github.com/chees89/pomodoro-widget-linux/issues) to describe a bug or feature idea.
2. For a code change, create a fork and a feature branch.
3. Keep changes focused and test the application on the relevant desktop session when possible.
4. Submit a pull request with a short explanation of the change and how you tested it.

For build-related issues, include your Linux distribution, desktop environment, whether the session uses Wayland or X11, and the relevant CMake output.

## License

A `LICENSE` file is not currently present in this repository, so the project's redistribution and usage terms are **not explicitly specified**. If you intend to publish or distribute the project as open source, consider adding a license file that matches your intentions before accepting contributions or redistributing copies.

## Author

Created by **[chees89](https://github.com/chees89)**.

- **Repository:** [chees89/pomodoro-widget-linux](https://github.com/chees89/pomodoro-widget-linux)
- **Related project:** [WellTool](https://github.com/chees89/WellTool)

If the widget is useful to you, consider giving the repository a ⭐ on GitHub. Feedback and contributions are appreciated!
