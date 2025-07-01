# sampuix.inc - Version 1.0

A lightweight, modern-style UI helper for SA-MP servers written in Pawn.
This include provides a structured way to create and manage dialogs (UI forms) with response callbacks, simulating an extended UI system for SA-MP.

---

## 📦 Overview

**sampuix** (User Interface eXtension for SA-MP) allows server developers to easily create and manage interactive dialogs with assigned callbacks, without the hassle of manual dialog ID management or repetitive code.

It simplifies dialog creation into one clean function:

```pawn
UIX_CreateForm(playerid, title[], message[], buttons[], callback[]);
```

---

## ⚙️ Installation

1. Download `sampuix.inc`
2. Place it in your `pawno/include/` directory
3. Include it in your script:

```pawn
#include <sampuix>
```

4. Compile your script

---

## 🚀 Basic Usage

### Step 1: Create a dialog

```pawn
UIX_CreateForm(playerid, "Title", "Your message", UIX_BUTTONS("Yes", "No", "Cancel"), "OnMyFormResponse");
```

### Step 2: Handle the callback

```pawn
forward OnMyFormResponse(playerid, response);
public OnMyFormResponse(playerid, response)
{
    if(response == 0) SendClientMessage(playerid, -1, "You chose Yes.");
    else if(response == 1) SendClientMessage(playerid, -1, "You chose No.");
    else SendClientMessage(playerid, -1, "You cancelled.");
}
```

---

## 🧠 How It Works

* `sampuix.inc` manages dialog IDs internally, starting from 6000.
* Each dialog is stored in a `UIX_Forms` array with:

  * `playerid`
  * assigned `dialogid`
  * the name of the callback function (as a string)
* When a dialog is shown, it's tracked.
* When the player responds, `OnDialogResponse` internally routes it to the corresponding callback function using `CallLocalFunction()`.
* The original form is released from memory once responded.

---

## 🔄 Internal Logic

* Supports up to `MAX_UIX_FORMS` (256 by default)
* Internal dialog ID counter is reset when it reaches 65000
* Form entries are reused when `dialogid` slot becomes `0`
* `UIX_BUTTONS(a, b, c)` is a macro to build 3-button dialog strings (null-separated)

---

## 📚 API Reference

### `UIX_CreateForm(playerid, title[], message[], buttons[], callback[])`

Creates and shows a dialog to the specified player.

* `playerid`: ID of the player
* `title[]`: Dialog title
* `message[]`: Body of the dialog
* `buttons[]`: Buttons, created using `UIX_BUTTONS()` macro
* `callback[]`: Name of the function to call when the player responds

Returns the dialog ID used, or -1 if form storage is full.

### `UIX_BUTTONS(text1, text2, text3)`

Macro to format 3 buttons separated by null characters (`\0`), required for `DIALOG_STYLE_MSGBOX`.

---

## ❗ Notes & Limitations

* Only supports `DIALOG_STYLE_MSGBOX` (for now)
* Requires a unique callback name per form instance
* Dialogs are not stacked: only one form per player is handled at once

---

## 📄 License

MIT License. Use freely. Credit is appreciated.

---

## 👥 Credits

* Developed by: **PrizDC**
* Designed to look and feel like a modern UI toolkit

---

## 💡 Future Plans

* Add support for input boxes, lists, and text inputs
* Add timeout expiration and auto-close
* Create optional textdraw HUD mode
* Callback result structures with more arguments
* Plugin version (faster performance)

---

Happy scripting!

— sampuix team