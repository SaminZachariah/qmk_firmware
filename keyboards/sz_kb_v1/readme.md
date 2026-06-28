# sz-kb-v1

Custom wired split ergonomic keyboard. Sofle v2-inspired layout with 58 keys + 2 rotary encoders, per-key RGB, and optional OLED.

* Keyboard Maintainer: [saminzachariah](https://github.com/saminzachariah)
* Hardware Supported: Adafruit KB2040 (RP2040)
* Hardware Availability: Custom PCB

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb sz_kb_v1 -km default

Flashing example for this keyboard:

    qmk flash -kb sz_kb_v1 -km default

Enter the bootloader: hold the BOOT button on the KB2040 while plugging in USB.

# Quickstart Guide

Sections
- File Overview
- Setting up environment
- Building your Firmware
- Flashing Firmware

## File Overview

All relevant files live in `<qmk-repo>/keyboards/sz_kb_v1/`:

| File | What it does |
|------|-------------|
| `keyboard.json` | Data-driven hardware config — pin assignments, split communication, RGB LEDs, encoders |
| `config.h` | hardware config options not supported in .json — UART pins, handedness, debug flags |
| `keymaps/<name>/keymap.c` | **Keybindings and layers — edit this file to customize your layout** |
| `keymaps/<name>/rules.mk` | Hardware feature toggles |

## Setting up your environment

Setup instructions are for MacOS. For windows, or more information, see [QMK Setup Docs](https://docs.qmk.fm/newbs_getting_started)

### 1. Install Homebrew

[Homebrew](https://brew.sh/) is a package manager for macOS. If you already have it, skip this step.

```shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Follow the instructions it prints at the end (it may ask you to add Homebrew to your PATH).

### 2. Install QMK Command Line

```shell
curl -fsSL https://install.qmk.fm | sh
```

### 3. Create Your Fork

1. Go to https://github.com/SaminZachariah/qmk_firmware and click the 'Fork' button in the top right (you will need be to signed into your personal github account)

2. Once your fork is created, click the green 'Code' button, ensure 'https' is selected, and copy the link.

3. In a terminal, clone the repository into your desired location
```shell
cd ~/Documents/ # repo will be in Documents/qmk_firmware
git clone --recurse-submodules <your-github-repo-link>
```

### 4. Setup QMK

1. Point QMK CLI to your clone
```shell
qmk config user.qmk_home=<path-to-qmk-repo> # e.g. ~/Documents/qmk_firmware
```

2. Verify environment setup was successful
```shell
qmk doctor
```

3. Test compiling works, using the default keymap
```shell
qmk compile -kb sz_kb_v1 -km default
```

## Building Firmware

For more information see [QMK docs](https://docs.qmk.fm/newbs_building_firmware)

> [!TIP]
> You can configure a default keyboard and keymap for the CLI to avoid always having to add the  
> `-kb <keyboard> -km  <keymap>` flags. Run the following:  
> `qmk config user.keyboard=sz_kb_v1`  
> `qmk config user.keymap=<your-keymap-name>` (conventionally people use their github username for the keymap name)

### 1. Create Your Keymap

For your personalized keymap, run the following to create a copy of the `default` keymap.
```shell
qmk new-keymap # or `qmk new-keymap -kb sz_kb_v1 -km <your-keymap-name>`
```

The command should output something like: "Created a new keymap called <your-keymap-name> in ./keyboards/sz_kb_v1/keymaps/<your-keymap-name>"

### 2. Customizing Your Keymap

Open your *new* `keymap.c` file in a text editor and customize the layout to your liking. It's recommended to make small changes and test them frequently while you're getting started. See the [Notes section](#notes--tips) at the end for some tips on customizing layouts.

### 3. Compiling

When your changes to the keymap are complete, you're ready to build the firmware. Run
```shell
qmk compile # or qmk compile -kb sz_kb_v1 -km <your-keymap-name>
```

There will be a lot of output in the terminal showing information on what is being compiled. If everything went well, the end of the output should look something like
```
Generating: .build/obj_sz_kb_v1_default/src/default_keyboard.h     [OK]
Compiling: quantum/keymap_introspection.c                          [OK]
Linking: .build/sz_kb_v1_default.elf                               [OK]
Creating UF2 file for deployment: .build/sz_kb_v1_default.uf2      [OK]
Copying sz_kb_v1_default.uf2 to qmk_firmware folder                [OK]
```

If compiling results in errors, you likely have an error in your `keymap.c` file.

## Flashing

For more information see [QMK docs](https://docs.qmk.fm/newbs_flashing)

**Read all the following sub-sections in their entirity before attempting to flash your firmware.**

### The Bootloader

In order to flash your firmware, you must first put the keyboard into DFU (bootloader) mode. While it it is in this mode, you will not be able to type or otherwise use the keyboard.

There are 3 ways to enter the bootloader mode on this keyboard.

|Method |Notes |Requirements | Caveats |
|-------|------|-------------|---------|
|`QK_BOOT` | best every-day method | Having a `QK_BOOT` key somewhere in your keymap | If your new firmware moves the `QK_BOOT` key/layer, you'll need to use the old-location when flashing both halves.|
|Bootmagic| useful if you accidentally removed `QK_BOOT` from your keymap|bootmagic enabled in `keyboard.json` features & split sections | **Always resets EEPROM**, so left/right handedness settings are wiped.|
|Physical boot button| use if neither above option works | access to MCU buttons | n/a - this is a foolproof method, but requires taking the case apart. Unlike bootmagic, this does not wipe the EEPROM|

Usage:
- `QK_BOOT`: press the `QK_BOOT` key (the default map has this on the SYS layer right-hand top-right)
- Bootmagic: unplug the keyboard from the computer, then while holding the bootmagic key, plug the keyboard into the computer. (the default map has these on the top-left key for both halves)
- Physical boot button: unplug the keyboard from the computer, then while holding the boot-button on the MCU, plug the keyboard into the computer.

> [!CAUTION]
> It is **very important** that you DO NOT unplug the keyboard or interrupt the flashing process while the firmware is being written.

### Split Handedness and Flashing

The process of flashing is relatively simple, but there are a couple things to be aware of due to this being a split keyboard.

1. Whichever side is plugged into the computer automatically becomes the 'master'. The 'master' handles all the firmware logic (layer state, sending keystrokes to the computer, RGB effects, etc.), while the 'slave' just transmits which physical switches are pressed during the scan.
Therefore, a firmware update to the plugged-in-side will immediately start working with the new keymap across both halves. **However** the other side is still running the older firmware, so if the computer is then plugged into that half it will become the 'master', and the whole keyboard will use the old layout. Because of this it is *strongly recommended* to always flash both halves to prevent version skew.

2. Because either half can be plugged into the computer and act as the host, each half needs a way to know whether it is the left or the right. This information is stored in the non-volatile EEPROM so it is retained even when the halves are unplugged/unpowered. The handedness can be set during flashing by adding an extra flag. Once the handedness has been written to EEPROM, subsequent flashes do not need to specify handedness *unless the EEPROM has been cleared* (e.g. due to using the bootmagic method).

The basic flash command, assuming the left/right EEPROM has already been set:
```shell
qmk flash # or qmk flash -kb sz_kb_v1 -km <your-keymap-name>
```

To specify handedness while flashing, (if EEPROM was wiped)
```shell
qmk flash -bl uf2-split-left # left half
qmk flash -bl uf2-split-right # right half
# or the full command: qmk flash -kb sz_kb_v1 -km <your-keymap> -bl uf2-split-[left|right]
```

### Flashing Steps

QMK has a nice feature where you can run the `qmk flash` command *before* putting your keyboard into the bootloader mode. The command will wait until it detects a device in bootloader mode, and then run the flashing process.

You can of course put the keyboard into bootloader mode first, and then run the flash command. Just make sure you have a 2nd keyboard available (or the laptop keyboard), since you'll need it to hit 'enter' to run the flash command.

If using the `QK_BOOT` method:
1. Keep both halves of the keyboard connected, and one half plugged into the computer
2. Run the `qmk flash` command
3. The terminal should print some info, then pause with a line like "Waiting for drive to deploy..."
4. Press the `QK_BOOT` key on your keyboard
5. The terminal should print output indicating the flashing has begun
6. Wait for the flashing to complete, with something like "Wrote 93696 bytes to /Volumes/RPI-RP2/NEW.UF2"
7. Test the keyboard by typing something, then flash the other half by swapping which side is connected to the computer and repeating the above steps. (remember, if you moved the `QK_BOOT` key, it will still be on the old position on the unflashed half)

If using Bootmagic or the Physical boot button, the order is reversed and you will need a 2nd keyboard available.
1. Unplug the keyboard from the computer (it is fine to leave the halves connected)
2. While holding the Bootmagic key, or the physical boot button, plug one half into the computer
3. You should see a new drive 'RPI-RP2' connected in the file explorer. If you do not, then you're not in the bootloader and should unplug and try again.
4. Run the `qmk flash` or `qmk flash -bl uf2-split-[left|right]` command
5. Wait for the flashing to complete, with something like "Wrote 93696 bytes to /Volumes/RPI-RP2/NEW.UF2"
6. Test the keyboard by typing something, then flash the other half by repeating the above steps.

## Notes & Tips

### Permissive Hold

Some keys in this layout are *mod-tap* keys: they send one keycode when tapped and activate a layer (or modifier) when held. For example, the inner-left thumb key sends Tab on tap and acts as Shift when held.

By default, QMK decides tap vs. hold based solely on timing: if you release the key before the tapping term expires, it's a tap. **Permissive hold** changes this: if you press and release *another key* while holding a mod-tap key, QMK immediately treats it as a hold, regardless of timing. This makes layer access feel more natural during fast typing.

Permissive hold is enabled per-key via `get_permissive_hold()` in `keymap.c`, and activated by `#define PERMISSIVE_HOLD_PER_KEY` in the keymap's `config.h`. To disable it for a specific key, remove its `case` from the switch statement. To disable it entirely, either delete the `#define` from `config.h`, or make the function always return `false`:

```c
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return false;
}
```

### Tri-layer

This layout has 4 layers: BASE, CODE, NAV, and SYS. BASE is always active. CODE activates when the right inner thumb key is held. NAV activates when the left homerow pinky is held. **SYS activates when both CODE and NAV are held simultaneously** — this is the tri-layer behaviour.

The logic lives in `layer_state_set_user()` in `keymap.c`:

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _CODE, _NAV, _SYS);
}
```

`update_tri_layer_state` checks the layer state on every change: if both `_CODE` and `_NAV` are active, it adds `_SYS`; when either is released, it removes `_SYS`. To change which layer combination triggers SYS, change the two layer arguments. To remove the tri-layer behaviour entirely, delete this function.