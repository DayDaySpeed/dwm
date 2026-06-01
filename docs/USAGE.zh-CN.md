# dwm 使用说明

本文档描述本仓库默认 `dwm/config.h`、`dwmblocks/config.h` 与 `scripts/` 的用法。修改配置后请重新编译并重启 dwm（**Alt + Shift + r**）。

## 修饰键

| 名称 | 配置宏 | 按键 |
|------|--------|------|
| **Alt** | `MODKEY`（`Mod1Mask`） | 大部分 dwm 快捷键 |
| **Super** | `SUPERKEY`（`Mod4Mask`） | `scripts/` 辅助脚本 |
| **Shift** | `ShiftMask` | 与 Alt 或 Super 组合 |

窗口间距快捷键为 **Alt + Super** 组合（`MODKEY|Mod4Mask`）。

## 编译与安装

```bash
cd dwm
make
sudo make install
```

默认安装到 `/usr/local/bin/dwm`。若修改 `config.mk` 中的 `PREFIX`，请同步修改 `selfrestart.c` 中的 `DWM_PATH`。

### dwmblocks

```bash
cd dwmblocks
make
sudo make install
```

将 `dwmblocks/bin/` 复制到 `~/.local/bin` 并加入 `$PATH`（见 `dwmblocks/config.h` 顶部注释）。在 X 会话中启动 `dwmblocks`；dwm 通过 `STATUSBAR "dwmblocks"` 读取输出。

修改 `bin/` 下脚本后无需重新编译，复制并刷新对应模块即可，例如：

```bash
kill -44 $(pidof dwmblocks)   # 刷新 clock（信号 10）
```

### 辅助脚本

仓库内 `scripts/` 需安装到 `~/.config/scripts/`：

```bash
./scripts/install.sh
```

部分脚本依赖外部工具（`rofi`、`ffmpeg`、`hsetroot`、`thinkpad_acpi` 等），请按需安装。

### 默认程序

| 项目 | 默认值 |
|------|--------|
| 终端 | `st`（`/usr/local/bin/st`） |
| 启动器 | `rofi` / `dmenu_run` |
| 文件管理器 | `dolphin` |
| 浏览器 | `librewolf-bin` |
| 脚本路径 | `~/.config/scripts/`（`S_PATH`） |
| 音量/麦克风 | PipeWire `wpctl` |
| 亮度 | `xbacklight` |

## 标签（Tags）

| 快捷键 | 功能 |
|--------|------|
| **Alt + 1～9** | 切换到标签 |
| **Alt + Ctrl + 1～9** | 在当前视图中切换显示该标签 |
| **Alt + Shift + 1～9** | 将窗口移到该标签 |
| **Alt + Ctrl + Shift + 1～9** | 粘性标签（在其他标签也显示） |
| **Alt + 0** | 切换 Scratchpad |
| **Alt + Shift + 0** | 窗口显示在所有标签 |
| **Alt + Tab** | 上一个标签 |
| **Alt + ,** / **Alt + .** | 聚焦上/下一个显示器 |
| **Alt + Shift + ,** / **Alt + Shift + .** | 将窗口移到上/下一个显示器 |

## 窗口操作

| 快捷键 | 功能 |
|--------|------|
| **Alt + h** / **Alt + l** | 减小 / 增大 master 区宽度（±0.05） |
| **Alt + j** / **Alt + k** | 聚焦下一个 / 上一个窗口 |
| **Alt + m** / **Alt + Shift + m** | 增加 / 减少 master 区窗口数 |
| **Alt + p** | 当前窗口升至 master（Zoom） |
| **Alt + Ctrl + j** / **Alt + Ctrl + k** | 增大 / 减小当前窗口高度（cfact） |
| **Alt + Shift + h/j/k/l** | 在堆栈中移动窗口 |
| **Alt + Shift + o** | 重置窗口高度比例 |

每个 tag **独立保存**布局、`nmaster` 与 `mfact`（pertag 补丁）。

## 布局

默认 `nmaster = 1`，`mfact = 0.5`。点击状态栏左侧布局符号 **左键** 循环切换；**右键** 切换到 Spiral。

| 快捷键 | 布局 | 符号 |
|--------|------|------|
| **Alt + t** | Tile | `[]=` |
| **Alt + Shift + t** | Monocle | `[M]` |
| **Alt + y** | Spiral | `[@]` |
| **Alt + Shift + y** | Dwindle | `[\]` |
| **Alt + u** | Deck | `D[]` |
| **Alt + Shift + u** | Bstack | `TTT` |
| **Alt + i** | Bstack 水平 | `===` |
| **Alt + Shift + i** | Grid | `HHH` |
| **Alt + o** | Nrowgrid | `###` |
| **Alt + Shift + o** | Horizgrid | `---` |
| **Alt + p** | Gapless grid | `:::` |
| **Alt + Shift + p** | Centered master | `\|M\|` |
| **Alt + Shift + Space** | 切换浮动 / 平铺 |

**Tile**：左侧 master 垂直堆叠，右侧 stack 垂直堆叠。  
**Monocle**：一次只显示一个最大化窗口。  
**Spiral / Dwindle**：斐波那契分割，方向相反。  
**Deck**：master 在左，stack 窗口叠在同一位置。  
**Bstack**：上方 master 水平排列，下方 stack 水平排列。  
**Grid / Gapless / Nrowgrid / Horizgrid**：各类网格布局，详见 `vanitygaps.c` 与各 `arrange` 函数。  
**Centered master**：主窗居中，stack 分左右。  
**Centered floating master**（`>M>`）：无快捷键，通过点击布局符号切换。

## 窗口间距（Gaps）

| 快捷键 | 功能 |
|--------|------|
| **Alt + Super + 0** | 开关间距 |
| **Alt + Super + Shift + 0** | 恢复默认 |
| **Alt + Super + 1** / **Shift + 1** | 增大 / 减小全部间距 |
| **Alt + Super + 2～7**（配合 Shift） | 调节内/外、水平/垂直间距 |

默认：水平内 20px、垂直内 10px、水平外 20px、垂直外 20px（见 `config.h` 中 `gapp*`）。

## 系统与启动

| 快捷键 | 功能 |
|--------|------|
| **Alt + b** | 显示/隐藏状态栏 |
| **Alt + f** | 全屏 |
| **Alt + Shift + c** | 关闭窗口 |
| **Alt + Shift + r** | 重启 dwm |
| **Alt + Shift + q** | 退出 dwm |
| **Alt + Enter** | 终端（`st`） |
| **Alt + Shift + Enter** | Scratchpad 终端（120×34） |
| **Alt + d** | Rofi |
| **Alt + Shift + d** | dmenu |
| **Alt + Shift + f** | Dolphin |
| **Alt + Shift + w** | LibreWolf |

## 脚本快捷键（Super）

脚本由 **Super** 触发，在 `st` 中运行 `~/.config/scripts/` 下对应程序：

| 快捷键 | 脚本 | 说明 |
|--------|------|------|
| **Super + d** | `displayselect` | 选择显示器 |
| **Super + f** | `set-fan` | 风扇转速（ThinkPad） |
| **Super + i** | `inactivity` | 周期性移动鼠标 |
| **Super + l** | `screenlock` | 锁屏（浮动 `st`） |
| **Super + m** | `dmenumount` | 挂载 |
| **Super + r** | `screenrecord` | 录屏 |
| **Super + t** | `toggletouchpad` | 触摸板开关 |
| **Super + u** | `dmenuumount` | 卸载 |
| **Super + w** | `randomwall-now` | 随机壁纸 |
| **Super + Shift + b** | `safe-switch` | 安全模式 |
| **Super + Shift + e** | `dmenuunicode` | Emoji 选择 |
| **Super + Shift + l** | `launcher` | 脚本启动器 |
| **Super + Shift + r** | `reminder` | 提醒 |
| **Super + Shift + u** | `disk-usage` | 磁盘用量 |
| **XF86Search** | `downloader` | 下载器 |

## 多媒体与截图

| 快捷键 | 功能 |
|--------|------|
| **Print** | 全屏截图（`scrot`） |
| **Alt + Print** | 区域截图（`scrot -s`） |
| **XF86AudioMute** 等 | `wpctl` 调节音量/麦克风，并刷新 dwmblocks（信号 6） |
| **XF86MonBrightnessUp/Down** | `xbacklight ±10`，刷新亮度模块（信号 3） |
| **XF86TouchpadOn/Off/Toggle** | `synclient` |

## 鼠标

| 操作 | 功能 |
|------|------|
| 标签栏左键 | 切换标签 |
| 标签栏右键 | 切换标签显示 |
| **Alt + 左键** 点标签 | 窗口移到该标签 |
| **Alt + 右键** 点标签 | 粘性标签 |
| **Alt + 左键** 拖窗口 | 移动 / placemouse |
| **Alt + 中键** | 切换浮动 |
| **Alt + 右键** 拖窗口 | 调整大小 |
| **Alt + Shift + 左键** 拖 | 调整 master 比例 |
| 标题栏中键 | Zoom |
| 状态栏左/中/右键 | 见 dwmblocks 各脚本 |

## dwmblocks 状态栏

模块顺序（分隔符 `|`，见 `dwmblocks/config.h`）：

```
brightness | memory | cpu | media | fanspeed | internet | battery | clock
```

刷新信号：`kill -(34 + signal) $(pidof dwmblocks)`

| 模块 | 信号 | 间隔 |
|------|------|------|
| brightness | 3 | 5s |
| memory | 4 | 10s |
| cpu | 5 | 5s |
| media | 6 | 3s |
| fanspeed | 7 | 5s |
| internet | 8 | 5s |
| battery | 9 | 10s |
| clock | 10 | 30s |

**memory / cpu**：左键通知占用排行，中键 `htop`。  
**internet**：左键 `nmtui`。  
**clock**：左键日期通知，中键 `calcurse`。  
**brightness**：由 `xbacklight` 显示百分比。

若 `media` 模块无输出，请确认 `~/.local/bin/media` 存在（可与 `bin/volume` 对照配置）。

## 外观

颜色在 `dwm/config.h` 中设置，也可通过 `~/.Xresources` 覆盖（xresources 补丁），例如：

```
dwm.normbgcolor: #15181E
dwm.normfgcolor: #7FC1E9
```

字体默认：`Iosevka` + `JoyPixels`（emoji）。字体配置见主 [README](../README.md) 的 Fonts 章节。

## 窗口规则

`rules[]` 中为常见程序预设浮动/终端/swallow 等，例如 `St`、`Firefox`/`LibreWolf` 弹窗、`zoom` 各窗口标题、VirtualBox 等。详见 `config.h`。

## 自定义

| 目标 | 操作 |
|------|------|
| 快捷键、布局、颜色 | 编辑 `dwm/config.h` → `make install` → **Alt + Shift + r** |
| 状态栏模块 | 编辑 `dwmblocks/config.h` → 重新编译 dwmblocks |
| 状态栏脚本 | 编辑 `dwmblocks/bin/*` → 复制到 PATH → `kill` 对应信号 |
| 辅助脚本 | 编辑 `scripts/*` → `./scripts/install.sh` |

补丁列表见 [dwm/README](../dwm/README) 与主 README。
