# dwm Usage Guide

This document describes the current `dwm/config.h` and `dwmblocks/` setup in this repository.

## Table of Contents

- [Modifier keys](#modifier-keys)
- [Build and install](#build-and-install)
- [Tags](#tags)
- [Window actions](#window-actions)
- [Layouts](#layouts)
- [Gaps](#gaps)
- [Appearance](#appearance)
- [System](#system)
- [Launchers](#launchers)
- [Script shortcuts](#script-shortcuts)
- [Multimedia and screenshots](#multimedia-and-screenshots)
- [Mouse](#mouse)
- [dwmblocks status bar](#dwmblocks-status-bar)
- [Window rules](#window-rules)
- [Customization](#customization)
- [Applied patches](#applied-patches)

[简体中文](zh-CN.md) · [Repository README](../README.md)

## Modifier keys

| Name | Macro | Key |
|------|-------|-----|
| **Super** | `MODKEY` (`Mod4Mask`) | Win/Super; primary modifier for most shortcuts |
| **Alt** | `SUPERKEY` (`Mod1Mask`) | Gaps and helper scripts |
| **Shift** | `ShiftMask` | Used with Super or Alt |

Below, **Super**, **Alt**, and **Shift** refer to the keys above.

## Build and install

```bash
cd dwm
make
sudo make install
```

Default install path: `/usr/local/bin/dwm`. If you change `PREFIX` in `config.mk`, update `DWM_PATH` in `selfrestart.c`.

### dwmblocks status bar

```bash
cd dwmblocks
make
sudo make install          # installs dwmblocks and bin/ scripts
```

Copy scripts to `~/.local/bin` on `$PATH`. **No rebuild needed** after script edits—copy and refresh:

```bash
cp dwmblocks/bin/clock ~/.local/bin/clock   # example
kill -44 $(pidof dwmblocks)                 # refresh clock (signal 10)
```

Run `dwmblocks` at X startup; dwm reads it via `STATUSBAR "dwmblocks"`.

### Dependencies and defaults

| Item | Default | Notes |
|------|---------|-------|
| Terminal | `kitty` | `TERMCMD`; float class `kitty-float` |
| Launcher | `rofi` / `dmenu_run` | Super+d / Super+Shift+d |
| File manager | `thunar` | Super+Shift+f |
| Browser | `edge` | Super+Shift+w |
| Scripts | `~/.config/scripts/` | `S_PATH` under home |
| Status fonts | JetBrainsMono Nerd Font + Noto Sans CJK SC | icons + CJK fallback |
| Audio | `wpctl` / PipeWire | volume via `wpctl-vol` helper |
| Brightness | `brightnessctl` or `xbacklight` | prefers brightnessctl |

## Tags

| Shortcut | Action |
|----------|--------|
| **Super + 1–9** | View tag 1–9 |
| **Super + Ctrl + 1–9** | Toggle tag in current view |
| **Super + Shift + 1–9** | Move window to tag |
| **Super + Ctrl + Shift + 1–9** | Sticky tag |
| **Super + 0** | Toggle scratchpad |
| **Super + Shift + 0** | Show window on all tags |
| **Super + Tab** | Previous tag |
| **Super + ,** / **Super + .** | Focus previous / next monitor |
| **Super + Shift + ,** / **Super + Shift + .** | Move window to previous / next monitor |

## Window actions

| Shortcut | Action |
|----------|--------|
| **Super + h** / **Super + l** | Decrease / increase master width (±0.05) |
| **Super + j** / **Super + k** | Focus next / previous window |
| **Super + m** / **Super + Shift + m** | Increase / decrease master count |
| **Super + p** | Zoom to master |
| **Super + Ctrl + j** / **Super + Ctrl + k** | Increase / decrease client height |
| **Super + Shift + h/j/k/l** | Move window in stack |
| **Super + Shift + o** | Reset client height factor |

## Layouts

Each tag (1–9) **stores its own** layout, `nmaster`, and `mfact`. The screen has a **master** area and a **stack**. Default `nmaster = 1`. Use **Super + m** / **Super + Shift + m** for master count; **Super + h/l** for `mfact` (default 0.5); **Super + Ctrl + j/k** for `cfact`.

| Shortcut | Layout | Symbol |
|----------|--------|--------|
| **Super + t** | Tile (default) | `[]=` |
| **Super + Shift + t** | Monocle | `[M]` |
| **Super + y** | Spiral | `[@]` |
| **Super + Shift + y** | Dwindle | `[\]` |
| **Super + u** | Deck | `D[]` |
| **Super + Shift + u** | Bstack | `TTT` |
| **Super + i** | Bstack horizontal | `===` |
| **Super + Shift + i** | Grid | `HHH` |
| **Super + o** | Nrowgrid | `###` |
| **Super + Shift + o** | Horizgrid | `---` |
| **Super + Ctrl + p** | Gapless | `:::` |
| **Super + Shift + p** | Centered master | `\|M\|` |
| **Super + Shift + Space** | Toggle floating / tiled |

**Left-click** the layout symbol on the bar to cycle; **right-click** for Spiral.

Layout details match the Chinese guide ([docs/zh-CN.md](zh-CN.md#布局)): Tile, Monocle, Spiral/Dwindle, Deck, Bstack variants, Grid, Nrowgrid, Horizgrid, Gapless, Centered master, Centered floating master (`>M>`, via bar), and floating `><>`.

## Gaps

Gap shortcuts use **Super + Alt**:

| Shortcut | Action |
|----------|--------|
| **Super + Alt + 0** | Toggle gaps |
| **Super + Alt + Shift + 0** | Reset defaults |
| **Super + Alt + 1** / **Shift + 1** | Increase / decrease all gaps |
| **Super + Alt + 2–7** (with Shift) | Inner/outer, horizontal/vertical gaps |

Defaults: inner H 20px, inner V 10px, outer 20px each.

## Appearance

Bar colors are in `dwm/config.h`. After edits: `make install`, then **Super + Shift + r**.

| Variable | Default | Role |
|----------|---------|------|
| `normbgcolor` | `#15181E` | Bar background |
| `normfgcolor` | `#7FC1E9` | Normal text |
| `selbgcolor` | `#15181E` | Selected tag background |
| `selfgcolor` | `#FFFFFF` | dmenu selected text |
| `statusgradfrom` / `statusgradto` | `#7FC1E9` / `#E97FC1` | Status text gradient |
| `selfgrainbow` | `1` | Rainbow tags 1–9 and title |
| `baralpha` | `0xd0` | Bar transparency |

Override via `~/.Xresources` (xresources patch). With `selfgrainbow = 1`, tags use rainbow colors and the selected tag has a 2px underline; focused titles use per-word rainbow coloring.

### Display power (DPMS)

Set in `~/.xinitrc` (outside this repo). Use `apply_dpms` so DPMS timeout is not stuck at 30s. Check with `xset q`: Screen Saver and DPMS should match your `IDLE_SEC` (e.g. 600).

### UI scaling (2560×1440 @ 1.35×)

| Mechanism | Setting |
|-----------|---------|
| X11 / dwm | `Xft.dpi: 130` |
| GTK | `gtk-xft-dpi=133120` |
| Qt / fcitx5 | `QT_SCALE_FACTOR=1.35` |
| Electron | `1.35` |
| dwm font | `size=14` |

Do **not** set `GDK_SCALE=1` / `GDK_DPI_SCALE=1` or GTK dialogs misalign. Re-login after changes. Scale: `Xft.dpi = 96 × factor`, `gtk-xft-dpi = Xft.dpi × 1024`.

## System

| Shortcut | Action |
|----------|--------|
| **Super + b** | Toggle bar |
| **Super + f** | Fullscreen |
| **Super + Shift + c** | Kill client |
| **Super + Shift + r** | Restart dwm |
| **Super + Shift + q** | Quit dwm |

## Launchers

| Shortcut | Program |
|----------|---------|
| **Super + Enter** | Terminal (`kitty`) |
| **Super + Shift + Enter** | Scratchpad (120×34) |
| **Super + d** | Rofi |
| **Super + Shift + d** | dmenu |
| **Super + Shift + f** | Thunar |
| **Super + Shift + w** | Edge |

## Script shortcuts

Scripts in `~/.config/scripts/`, bound to **Alt**:

| Shortcut | Script | Action |
|----------|--------|--------|
| **Alt + d** | `displayselect` | Select display |
| **Alt + f** | `set-fan` | Fan speed (ThinkPad) |
| **Alt + i** | `inactivity` | Move mouse periodically |
| **Alt + l** | `screenlock` | Lock (`slock`, float kitty) |
| **Alt + m** | `dmenumount` | Mount |
| **Alt + r** | `screenrecord` | Record (`ffmpeg`) |
| **Alt + t** | `toggletouchpad` | Touchpad toggle |
| **Alt + u** | `dmenuumount` | Unmount |
| **Alt + w** | `randomwall-now` | Wallpaper (`hsetroot`) |
| **Alt + Shift + b** | `safe-switch` | Safe mode |
| **Alt + Shift + e** | `dmenuunicode` | Emoji picker |
| **Alt + Shift + l** | `launcher` | Script launcher |
| **Alt + Shift + r** | `reminder` | Reminder |
| **Alt + Shift + u** | `disk-usage` | Disk usage |
| **XF86Search** | `downloader` | Downloader |

Also: `killkittytag` — close visible `kitty` / `kitty-float` on current tag (via `launcher` or manual). Install: `./scripts/install.sh`.

## Multimedia and screenshots

| Shortcut | Action |
|----------|--------|
| **Print** / **Super + Print** | Region screenshot (`flameshot gui` → `~/Pictures/`) |
| **XF86Audio*** | Mute/volume/mic via `wpctl`; refresh status modules |
| **XF86MonBrightness*** | Brightness ±10% |
| **XF86Touchpad*** | Touchpad (`synclient`) |

## Mouse

| Action | Effect |
|--------|--------|
| Left/right-click tag bar | View / toggle tag |
| Selected tag | Colored underline (`selfgrainbow`) |
| **Super + click** tag | Move / sticky tag |
| **Super + drag** client | Move / placemouse / resize |
| **Super + Shift + left-drag** | Drag master factor |
| Middle-click title | Zoom |
| Status bar | See dwmblocks below |

## dwmblocks status bar

Module order (delimiter ` │ ` with spaces):

```
memory │ cpu │ fanspeed │ internet │ bluetooth │ battery │ volume │ brightness │ mic │ clock
```

Spacing: `dwmblocks/bin/dwmblocks-lib` (`ICON_GAP`, `SEG_GAP`). Icons: `dwmblocks/bin/icons` + **JetBrainsMono Nerd Font** ([cheat sheet](https://www.nerdfonts.com/cheat-sheet)).

Refresh: `kill -(34 + signal) $(pidof dwmblocks)` — brightness 3, memory 4, cpu 5, bluetooth 6, fanspeed 7, internet 8, battery 9, clock 10, volume 11, mic 12.

**Clicks:** memory/cpu — left: top processes, middle: `htop`; internet — `nmtui`; bluetooth — `blueman-manager`; clock — date notify / `calcurse`; volume/mic — `pavucontrol`, mute, scroll ±5% (mic bar 100% = 153% in pavucontrol); brightness — scroll ±10%. **Super + right-click** on a module edits its script.

## Window rules

See `rules[]` in `config.h`. Examples: `kitty` / `kitty-float`, LibreWolf/Firefox popups, Zoom by title, floating `copyq` / `Volume Control`.

## Customization

| Goal | Steps |
|------|--------|
| Keys, layouts, colors | `dwm/config.h` → `make install` → **Super + Shift + r** |
| Rainbow / gradient | `selfgrainbow`, `statusgradfrom`, `statusgradto`, etc. |
| Status modules | `dwmblocks/config.h` → rebuild → restart dwmblocks |
| Status scripts | `dwmblocks/bin/*`, `dwmblocks-lib` → PATH → `kill` signal |
| Helper scripts | `scripts/*` → `./scripts/install.sh` |
| Runtime colors | Xresources (`dwm-xresources` patch) |

## Applied patches

- Translucent bar + systray
- vanitygaps, cfacts, statuscmd, pertag
- Status gradient, rainbow tags, underline (custom)
- scratchpad, swallow, selfrestart, togglefullscreen
- focusfollowmouse, dragmfact, placemouse, inplacerotate
- sortscreens, resizecorners, rulerefresher

Full list: [dwm/README](../dwm/README).
