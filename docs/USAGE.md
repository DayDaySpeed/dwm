# dwm usage guide

This document describes the default `dwm/config.h`, `dwmblocks/config.h`, and `scripts/` in this repository. After changing configuration, recompile and restart dwm (**Alt + Shift + r**).

## Modifier keys

| Name | Macro | Key |
|------|-------|-----|
| **Alt** | `MODKEY` (`Mod1Mask`) | Most dwm shortcuts |
| **Super** | `SUPERKEY` (`Mod4Mask`) | Helper scripts in `scripts/` |
| **Shift** | `ShiftMask` | Combined with Alt or Super |

Gap shortcuts use **Alt + Super** (`MODKEY|Mod4Mask`).

## Build and install

```bash
cd dwm
make
sudo make install
```

Default install path: `/usr/local/bin/dwm`. If you change `PREFIX` in `config.mk`, update `DWM_PATH` in `selfrestart.c` as well.

### dwmblocks

```bash
cd dwmblocks
make
sudo make install
```

Copy `dwmblocks/bin/` to `~/.local/bin` and add it to `$PATH` (see comments at the top of `dwmblocks/config.h`). Start `dwmblocks` in your X session; dwm reads its output via `STATUSBAR "dwmblocks"`.

After editing scripts under `bin/`, you do not need to recompile—copy them and refresh the module, for example:

```bash
kill -44 $(pidof dwmblocks)   # refresh clock (signal 10)
```

### Helper scripts

Install repository `scripts/` to `~/.config/scripts/`:

```bash
./scripts/install.sh
```

Some scripts depend on external tools (`rofi`, `ffmpeg`, `hsetroot`, `thinkpad_acpi`, etc.).

### Default programs

| Item | Default |
|------|---------|
| Terminal | `st` (`/usr/local/bin/st`) |
| Launcher | `rofi` / `dmenu_run` |
| File manager | `dolphin` |
| Browser | `librewolf-bin` |
| Script path | `~/.config/scripts/` (`S_PATH`) |
| Audio | PipeWire `wpctl` |
| Brightness | `xbacklight` |

## Tags

| Shortcut | Action |
|----------|--------|
| **Alt + 1–9** | View tag |
| **Alt + Ctrl + 1–9** | Toggle tag in current view |
| **Alt + Shift + 1–9** | Move window to tag |
| **Alt + Ctrl + Shift + 1–9** | Sticky tag |
| **Alt + 0** | Toggle scratchpad |
| **Alt + Shift + 0** | Show window on all tags |
| **Alt + Tab** | Previous tag |
| **Alt + ,** / **Alt + .** | Focus previous / next monitor |
| **Alt + Shift + ,** / **Alt + Shift + .** | Move window to previous / next monitor |

## Window actions

| Shortcut | Action |
|----------|--------|
| **Alt + h** / **Alt + l** | Decrease / increase master width (±0.05) |
| **Alt + j** / **Alt + k** | Focus next / previous window |
| **Alt + m** / **Alt + Shift + m** | Increase / decrease master count |
| **Alt + p** | Zoom focused window to master |
| **Alt + Ctrl + j** / **Alt + Ctrl + k** | Increase / decrease client height (cfact) |
| **Alt + Shift + h/j/k/l** | Move window within stack |
| **Alt + Shift + o** | Reset client height factor |

Each tag **remembers** its own layout, `nmaster`, and `mfact` (pertag patch).

## Layouts

Default: `nmaster = 1`, `mfact = 0.5`. **Left-click** the layout symbol on the bar to cycle; **right-click** switches to Spiral.

| Shortcut | Layout | Symbol |
|----------|--------|--------|
| **Alt + t** | Tile | `[]=` |
| **Alt + Shift + t** | Monocle | `[M]` |
| **Alt + y** | Spiral | `[@]` |
| **Alt + Shift + y** | Dwindle | `[\]` |
| **Alt + u** | Deck | `D[]` |
| **Alt + Shift + u** | Bstack | `TTT` |
| **Alt + i** | Bstack horizontal | `===` |
| **Alt + Shift + i** | Grid | `HHH` |
| **Alt + o** | Nrowgrid | `###` |
| **Alt + Shift + o** | Horizgrid | `---` |
| **Alt + p** | Gapless grid | `:::` |
| **Alt + Shift + p** | Centered master | `\|M\|` |
| **Alt + Shift + Space** | Toggle floating / tiled |

**Tile**: master stack on the left, stack on the right.  
**Monocle**: one maximized window at a time.  
**Spiral / Dwindle**: Fibonacci tiling, opposite winding.  
**Deck**: master on the left; stack windows overlap in one column.  
**Bstack**: master row on top, stack row below.  
**Grid variants**: see `vanitygaps.c` and each `arrange` function.  
**Centered master**: master in the center, stacks on both sides.  
**Centered floating master** (`>M>`): no keybinding—cycle via the layout symbol.

## Gaps

| Shortcut | Action |
|----------|--------|
| **Alt + Super + 0** | Toggle gaps |
| **Alt + Super + Shift + 0** | Reset defaults |
| **Alt + Super + 1** / **Shift + 1** | Increase / decrease all gaps |
| **Alt + Super + 2–7** (with Shift) | Adjust inner/outer, horizontal/vertical gaps |

Defaults: inner horizontal 20px, inner vertical 10px, outer 20px (`gapp*` in `config.h`).

## System and launchers

| Shortcut | Action |
|----------|--------|
| **Alt + b** | Toggle bar |
| **Alt + f** | Fullscreen |
| **Alt + Shift + c** | Kill client |
| **Alt + Shift + r** | Restart dwm |
| **Alt + Shift + q** | Quit dwm |
| **Alt + Enter** | Terminal (`st`) |
| **Alt + Shift + Enter** | Scratchpad (120×34) |
| **Alt + d** | Rofi |
| **Alt + Shift + d** | dmenu |
| **Alt + Shift + f** | Dolphin |
| **Alt + Shift + w** | LibreWolf |

## Script shortcuts (Super)

Scripts run in `st` under `~/.config/scripts/`:

| Shortcut | Script | Notes |
|----------|--------|-------|
| **Super + d** | `displayselect` | Display selection |
| **Super + f** | `set-fan` | Fan speed (ThinkPad) |
| **Super + i** | `inactivity` | Periodic mouse move |
| **Super + l** | `screenlock` | Lock (floating `st`) |
| **Super + m** | `dmenumount` | Mount drives |
| **Super + r** | `screenrecord` | Screen record |
| **Super + t** | `toggletouchpad` | Touchpad toggle |
| **Super + u** | `dmenuumount` | Unmount |
| **Super + w** | `randomwall-now` | Random wallpaper |
| **Super + Shift + b** | `safe-switch` | Safe mode |
| **Super + Shift + e** | `dmenuunicode` | Emoji picker |
| **Super + Shift + l** | `launcher` | Script launcher |
| **Super + Shift + r** | `reminder` | Reminder |
| **Super + Shift + u** | `disk-usage` | Disk usage |
| **XF86Search** | `downloader` | Downloader |

## Multimedia and screenshots

| Shortcut | Action |
|----------|--------|
| **Print** | Full screenshot (`scrot`) |
| **Alt + Print** | Select region (`scrot -s`) |
| **XF86Audio*** | `wpctl` volume/mic; refresh dwmblocks (signal 6) |
| **XF86MonBrightness*** | `xbacklight ±10`; refresh brightness (signal 3) |
| **XF86Touchpad*** | `synclient` |

## Mouse

| Action | Effect |
|--------|--------|
| Left-click tag | View tag |
| Right-click tag | Toggle tag view |
| **Alt + left-click** tag | Move window to tag |
| **Alt + right-click** tag | Toggle sticky |
| **Alt + drag** client | Move / placemouse |
| **Alt + middle-click** | Toggle floating |
| **Alt + right-drag** | Resize |
| **Alt + Shift + left-drag** | Drag master factor |
| Middle-click title | Zoom |
| Status bar clicks | Per `dwmblocks/bin/*` scripts |

## dwmblocks status bar

Module order (delimiter `|`, from `dwmblocks/config.h`):

```
brightness | memory | cpu | media | fanspeed | internet | battery | clock
```

Refresh: `kill -(34 + signal) $(pidof dwmblocks)`

| Module | Signal | Interval |
|--------|--------|----------|
| brightness | 3 | 5s |
| memory | 4 | 10s |
| cpu | 5 | 5s |
| media | 6 | 3s |
| fanspeed | 7 | 5s |
| internet | 8 | 5s |
| battery | 9 | 10s |
| clock | 10 | 30s |

**memory / cpu**: left-click shows top processes; middle-click opens `htop`.  
**internet**: left-click runs `nmtui`.  
**clock**: left-click shows date notifications; middle-click opens `calcurse`.  
**brightness**: percentage via `xbacklight`.

If the `media` block is empty, ensure `~/.local/bin/media` exists (you may align `bin/volume` with your setup).

## Appearance

Colors are set in `dwm/config.h` and can be overridden via `~/.Xresources`, for example:

```
dwm.normbgcolor: #15181E
dwm.normfgcolor: #7FC1E9
```

Default fonts: `Iosevka` + `JoyPixels`. See the Fonts section in the main [README](../README.md).

## Window rules

`rules[]` sets floating, terminal, swallow, and similar behavior for apps such as `St`, Firefox/LibreWolf popups, Zoom windows, VirtualBox, etc. See `config.h`.

## Customization

| Goal | Steps |
|------|--------|
| Keys, layouts, colors | Edit `dwm/config.h` → `make install` → **Alt + Shift + r** |
| Status modules | Edit `dwmblocks/config.h` → rebuild dwmblocks |
| Status scripts | Edit `dwmblocks/bin/*` → copy to PATH → `kill` with signal |
| Helper scripts | Edit `scripts/*` → `./scripts/install.sh` |

Patch list: [dwm/README](../dwm/README) and the main README.
