# dwm 使用说明

本文档基于本仓库 `dwm/config.h` 与 `dwmblocks/` 的当前配置编写。

## 修饰键说明

| 名称 | 配置宏 | 对应按键 |
|------|--------|----------|
| **Super** | `MODKEY`（`Mod4Mask`） | Win / Super 键，大部分快捷键的主修饰键 |
| **Alt** | `SUPERKEY`（`Mod1Mask`） | 用于窗口间距调节与脚本快捷键 |
| **Shift** | `ShiftMask` | 配合 Super 或 Alt 使用 |

下文用 **Super**、**Alt**、**Shift** 表示上述修饰键。

## 编译与安装

```bash
cd dwm
make
sudo make install
```

安装路径默认为 `/usr/local/bin/dwm`。修改 `config.mk` 中的 `PREFIX` 后，需同步修改 `selfrestart.c` 里的 `DWM_PATH`。

### dwmblocks 状态栏

```bash
cd dwmblocks
make
sudo make install          # 安装 dwmblocks 与 bin/ 脚本到 /usr/local/bin
```

脚本也可复制到 `~/.local/bin` 并确保在 `$PATH` 中。**修改脚本后无需重新编译 dwmblocks**，复制后刷新即可：

```bash
cp dwmblocks/bin/clock ~/.local/bin/clock   # 示例
kill -44 $(pidof dwmblocks)                 # 刷新 clock 模块（signal 10）
```

在 X 会话启动脚本中运行 `dwmblocks`（dwm 通过 `STATUSBAR "dwmblocks"` 读取其输出）。

### 依赖与配置项

| 项目 | 默认值 | 说明 |
|------|--------|------|
| 终端 | `kitty` | `TERMCMD`，浮动终端类名 `kitty-float` |
| 启动器 | `rofi` / `dmenu_run` | Super+d / Super+Shift+d |
| 文件管理器 | `dolphin` | Super+Shift+f |
| 浏览器 | `librewolf-bin` | Super+Shift+w |
| 脚本目录 | `~/.config/scripts/` | `S_PATH`，相对家目录 |
| 状态栏字体 | JetBrainsMono Nerd Font + Noto Sans CJK SC | 前者显示 Nerd 图标，后者 fallback 中文 |
| 音频 | `wpctl` / PipeWire | 音量键通过 `wpctl-vol` 辅助脚本 |
| 亮度 | `brightnessctl` 或 `xbacklight` | 优先 brightnessctl |

## 标签（Tags）

| 快捷键 | 功能 |
|--------|------|
| **Super + 1～9** | 切换到标签 1～9 |
| **Super + Ctrl + 1～9** | 在当前视图中切换显示该标签 |
| **Super + Shift + 1～9** | 将当前窗口移动到标签 1～9 |
| **Super + Ctrl + Shift + 1～9** | 窗口粘性标签（在其他标签也显示） |
| **Super + 0** | 切换 Scratchpad（临时终端垫） |
| **Super + Shift + 0** | 当前窗口显示在所有标签 |
| **Super + Tab** | 切换到上一个标签 |
| **Super + ,** | 聚焦上一个显示器 |
| **Super + .** | 聚焦下一个显示器 |
| **Super + Shift + ,** | 将窗口移到上一个显示器 |
| **Super + Shift + .** | 将窗口移到下一个显示器 |

## 窗口操作

| 快捷键 | 功能 |
|--------|------|
| **Super + h** | 减小主区域宽度（master factor −0.05） |
| **Super + l** | 增大主区域宽度（master factor +0.05） |
| **Super + j** | 聚焦下一个窗口（顺时针） |
| **Super + k** | 聚焦上一个窗口（逆时针） |
| **Super + m** | 增加 master 区窗口数 |
| **Super + Shift + m** | 减少 master 区窗口数 |
| **Super + p** | 当前窗口升至 master（Zoom） |
| **Super + Ctrl + j** | 增大当前窗口高度 |
| **Super + Ctrl + k** | 减小当前窗口高度 |
| **Super + Shift + h** | 在堆栈中左移窗口 |
| **Super + Shift + j** | 在堆栈中下移窗口 |
| **Super + Shift + k** | 在堆栈中上移窗口 |
| **Super + Shift + l** | 在堆栈中右移窗口 |
| **Super + Shift + o** | 重置窗口高度比例 |

## 布局

每个 tag（1～9）**独立保存**布局、master 区窗口数（`nmaster`）和 master 宽度比例（`mfact`）。在某个 tag 上改布局后，切到其他 tag 再回来，会恢复该 tag 之前的设置。

屏幕分为 **master 区**（主窗口）和 **stack 区**（其余窗口）。默认 `nmaster = 1`（master 区 1 个窗口），可用 **Super + m** / **Super + Shift + m** 增减。master 区宽度由 **Super + h / l** 调节（`mfact`，默认 0.5）。单个窗口在 stack 中的高度比例用 **Super + Ctrl + j / k** 调节（`cfact`）。

| 快捷键 | 布局 | 符号 |
|--------|------|------|
| **Super + t** | Tile（默认） | `[]=` |
| **Super + Shift + t** | Monocle | `[M]` |
| **Super + y** | Spiral | `[@]` |
| **Super + Shift + y** | Dwindle | `[\]` |
| **Super + u** | Deck | `D[]` |
| **Super + Shift + u** | Bstack | `TTT` |
| **Super + i** | Bstack 水平 | `===` |
| **Super + Shift + i** | Grid | `HHH` |
| **Super + o** | Nrowgrid | `###` |
| **Super + Shift + o** | Horizgrid | `---` |
| **Super + Ctrl + p** | Gapless | `:::` |
| **Super + Shift + p** | Centered master | `\|M\|` |
| **Super + Shift + Space** | 切换浮动/平铺 |

点击状态栏左侧布局符号（**左键**）可循环切换布局；**右键**切换到 Spiral 布局。

---

### Tile `[]=` — 经典平铺（默认）（**Super + t**）

dwm 原生布局。屏幕左侧为 **master 区**，窗口垂直堆叠；右侧为 **stack 区**，窗口同样垂直堆叠。两区宽度比由 `mfact` 控制（默认各占约一半）。

```
┌─────────┬─────────┐
│ master  │ stack 1 │
│         ├─────────┤
│         │ stack 2 │
└─────────┴─────────┘
```

适合：一主多辅的日常场景（编辑器 + 终端 + 浏览器等）。

---

### Monocle `[M]` — 单窗口全屏（**Super + Shift + t**）

所有平铺窗口依次最大化占满整个工作区，互相重叠，只显示当前聚焦的那个。状态栏符号会显示 `[N]`（N 为可见窗口数）。

适合：专注单个任务，或临时需要最大化视野。

---

### Spiral `[@]` / Dwindle `[\]` — 斐波那契螺旋（**Super + y** / **Super + Shift + y**）

两者均基于斐波那契（Fibonacci）分割：每增加一个窗口，从当前区域切出一半，形成递归嵌套的矩形。Spiral 与 Dwindle 的区别在于分割方向相反（一个顺时针、一个逆时针）。

```
Spiral 示意:          Dwindle 示意:
┌───┬───────┐         ┌───────┬───┐
│ 1 │   2   │         │   2   │ 1 │
├───┤       │         │       ├───┤
│ 4 │   3   │         │   3   │ 4 │
└───┴───────┘         └───────┴───┘
```

适合：窗口较多、希望均匀分配空间且不想严格区分 master/stack 时。

---

### Deck `D[]` — 牌堆（**Super + u**）

与 Tile 类似，左侧 master 区垂直堆叠；右侧 stack 区的窗口 **全部叠在同一位置**（只露出最上方/聚焦的那个），符号会显示 `D N`（N 为 stack 中隐藏的窗口数）。

```
┌─────────┬─────────┐
│ master  │         │
│         │ stack   │  ← 多个窗口叠在一起
│         │ (deck)  │
└─────────┴─────────┘
```

适合：master 区放主窗口，stack 区像 Alt+Tab 一样快速切换但保持平铺管理。

---

### Bstack `TTT` — 底栏堆叠（**Super + Shift + u**）

与 Tile 的左右分区相反：**上方** master 区窗口 **水平** 排列，**下方** stack 区窗口也 **水平** 排列。上下高度比由 `mfact` 控制。

```
┌───────────────────┐
│ M │ M │ M  master │
├───────────────────┤
│ S │ S │ S  stack  │
└───────────────────┘
```

适合：宽屏显示器、需要同时横向对比多个窗口（如并排文档）。

---

### Bstack 水平 `===` — 上主下辅（**Super + i**）

上方 master 区水平排列；下方 stack 区 **垂直** 堆叠（与 Bstack 的下方水平排列不同）。

```
┌───────────────────┐
│ M │ M │ M  master │
├─────────┬─────────┤
│ stack 1 │ stack 2 │
└─────────┴─────────┘
```

适合：上方放工具栏/标签页类窗口，下方垂直浏览列表内容。

---

### Grid `HHH` — 网格（**Super + Shift + i**）

所有窗口均匀排成近似方阵的网格（行 × 列），每个窗口占一个等大的格子，不区分 master/stack。

```
┌─────┬─────┐
│  1  │  2  │
├─────┼─────┤
│  3  │  4  │
└─────┴─────┘
```

适合：同时监控多个等权重的窗口（监控面板、多终端、多聊天窗口等）。

---

### Nrowgrid `###` — 多行网格（**Super + o**）

按行排列：第一行窗口数最多，后续各行窗口数递减，形成「上宽下窄」的阶梯网格。行数与 `nmaster + 1` 相关；仅 2 个窗口时强制垂直对半分（`FORCE_VSPLIT`）。按 **Super + m** / **Super + Shift + m** 调整 `nmaster` 会改变行数分配。

```
┌───┬───┬───┐
│ 1 │ 2 │ 3 │
├───┼───┤   │
│ 4 │ 5 │   │
└───┴───┘
```

适合：窗口数量不固定、希望第一行容纳更多内容的场景。

---

### Horizgrid `---` — 水平双行（**Super + Shift + o**）

窗口数 ≤ 2 时全部排在上方一行；超过 2 个则 **上方一行、下方一行** 各水平排列，上下各占一半高度。

```
┌───┬───┬───┐  上行
├───┴───┴───┤
│ S │ S │ S │  下行
└───────────┘
```

适合：宽屏上「上面一排工具、下面一排内容」的工作流。

---

### Gapless `:::` — 无缝网格（**Super + Ctrl + p**）

与 Grid 类似，将所有窗口排成网格，但 **尽量消除窗口之间的间距**（在 vanitygaps 补丁下仍保留可配置的 gap，布局算法本身更紧凑）。5 个窗口时固定为 2 列而非通用计算的 1:2:2。

适合：在小屏幕或需要最大化利用屏幕面积时显示多个窗口。

---

### Centered master `|M|` — 居中主窗（**Super + Shift + p**）

master 区窗口 **垂直堆叠在屏幕中央**；stack 区的窗口分别堆叠在 **左侧** 和 **右侧**（奇偶交替分配）。中央区域宽度由 `mfact` 控制。

```
┌───┬─────────┬───┐
│ S │ master  │ S │
│   │         │   │
│ S │         │ S │
└───┴─────────┴───┘
```

适合：强调中央主窗口、两侧放参考材料的布局（如中间写代码、两边看文档）。

---

### Centered floating master `>M>` — 居中浮动主窗（无快捷键，点击布局符号切换）

master 区窗口 **水平排列在屏幕中央**，尺寸约为屏幕的 90% 或按 `mfact` 缩放；stack 区窗口 **水平排列在底部**（或顶部），占满宽度。

适合：中央突出 1～2 个主窗口，底部像任务栏一样排列其余窗口。

---

### 浮动 `><>` — 自由浮动（**Super + Shift + Space** 切换当前窗口）

无独立布局快捷键，需点击布局符号切换到 `><>`。浮动窗口不参与布局算法，可自由拖动和调整大小。

适合：对话框、计算器、临时弹出窗口等不需要平铺管理的场景。

## 窗口间距（Gaps）

间距快捷键使用 **Super + Alt** 组合：

| 快捷键 | 功能 |
|--------|------|
| **Super + Alt + 0** | 开关间距 |
| **Super + Alt + Shift + 0** | 恢复默认间距 |
| **Super + Alt + 1** | 增大全部间距 |
| **Super + Alt + Shift + 1** | 减小全部间距 |
| **Super + Alt + 2** | 增大内间距 |
| **Super + Alt + Shift + 2** | 减小内间距 |
| **Super + Alt + 3** | 增大外间距 |
| **Super + Alt + Shift + 3** | 减小外间距 |
| **Super + Alt + 4** | 增大水平内间距 |
| **Super + Alt + Shift + 4** | 减小水平内间距 |
| **Super + Alt + 5** | 增大垂直内间距 |
| **Super + Alt + Shift + 5** | 减小垂直内间距 |
| **Super + Alt + 6** | 增大水平外间距 |
| **Super + Alt + Shift + 6** | 减小水平外间距 |
| **Super + Alt + 7** | 增大垂直外间距 |
| **Super + Alt + Shift + 7** | 减小垂直外间距 |

默认间距：水平内 20px、垂直内 10px、水平外 20px、垂直外 20px。

## 外观与配色

任务栏颜色在 `dwm/config.h` 中配置（非 dwmblocks）。修改后需 `make && sudo make install`，再 **Super + Shift + r** 重启 dwm。

| 变量 | 默认值 | 作用 |
|------|--------|------|
| `normbgcolor` | `#15181E` | 任务栏背景 |
| `normfgcolor` | `#7FC1E9` | 普通文字（未选中标签等） |
| `selbgcolor` | `#15181E` | 选中标签背景 |
| `selfgcolor` | `#FFFFFF` | dmenu 选中文字 |
| `statusgradfrom` / `statusgradto` | `#7FC1E9` / `#E97FC1` | 右侧状态栏文字渐变色（左→右） |
| `selfgrainbow` | `1` | 开启后：标签 1～9 与窗口标题使用彩虹色 |
| `baralpha` | `0xd0` | 任务栏背景透明度 |

也可通过 `~/.Xresources` 覆盖（需已启用 xresources patch）：

```
dwm.normbgcolor:     #15181E
dwm.statusgradfrom:  #7FC1E9
dwm.statusgradto:    #E97FC1
```

### 标签栏指示

- 标签 **1～9** 在 `selfgrainbow = 1` 时按序号显示彩虹色（红→紫）
- **当前选中的 tag** 底部显示同色下划线（2px）；未选中的 tag 无下划线
- 窗口标题在聚焦时按 **单词/符号** 分段彩虹着色（整词同色）

### 熄屏

在 `~/.xinitrc` 中设置（非 dwm 仓库内）：

```bash
IDLE_SEC=600
xset s "$IDLE_SEC"
xset +dpms
xset dpms "$IDLE_SEC" "$IDLE_SEC" "$IDLE_SEC"
```

建议放在 X 会话启动末尾，避免被其他程序覆盖 DPMS 默认值。

## 系统操作

| 快捷键 | 功能 |
|--------|------|
| **Super + b** | 显示/隐藏状态栏 |
| **Super + f** | 切换全屏 |
| **Super + Shift + c** | 关闭当前窗口 |
| **Super + Shift + r** | 原地重启 dwm（不退出 X 会话） |
| **Super + Shift + q** | 退出 dwm |

## 启动程序

| 快捷键 | 程序 |
|--------|------|
| **Super + Enter** | 终端（`kitty`） |
| **Super + Shift + Enter** | Scratchpad 终端（120×34） |
| **Super + d** | Rofi 应用启动器 |
| **Super + Shift + d** | dmenu 应用启动器 |
| **Super + Shift + f** | 文件管理器（`dolphin`） |
| **Super + Shift + w** | 浏览器（`librewolf-bin`） |

## 脚本快捷键

脚本位于 `~/.config/scripts/`，由 **Alt**（非 Super）触发：

| 快捷键 | 脚本 | 功能 |
|--------|------|------|
| **Alt + d** | `displayselect` | 检测并选择显示器 |
| **Alt + f** | `set-fan` | 设置风扇转速（ThinkPad，需配置 thinkpad_acpi） |
| **Alt + i** | `inactivity` | 周期性移动鼠标 |
| **Alt + l** | `screenlock` | 锁屏（需 `slock`，浮动 kitty 窗口） |
| **Alt + m** | `dmenumount` | 挂载驱动器 |
| **Alt + r** | `screenrecord` | 录屏（需 `ffmpeg`） |
| **Alt + t** | `toggletouchpad` | 开关触摸板（需 synaptics 配置） |
| **Alt + u** | `dmenuumount` | 卸载驱动器 |
| **Alt + w** | `randomwall-now` | 随机壁纸（需 `hsetroot`，壁纸目录 `~/wallpapers`） |
| **Alt + Shift + b** | `safe-switch` | 安全模式 |
| **Alt + Shift + e** | `dmenuunicode` | Emoji / Unicode 选择器 |
| **Alt + Shift + l** | `launcher` | 脚本启动器 |
| **Alt + Shift + r** | `reminder` | 设置提醒 |
| **Alt + Shift + u** | `disk-usage` | 查看磁盘用量 |
| **XF86Search** | `downloader` | 下载器（键盘 Search 键） |

未绑定快捷键、可手动运行或通过 **Alt + Shift + l**（`launcher`）启动：

| 脚本 | 功能 |
|------|------|
| `killkittytag` | 关闭当前 tag 上所有可见的 `kitty` / `kitty-float` 窗口 |

安装脚本：`./scripts/install.sh`（复制到 `~/.config/scripts/`）。

## 多媒体与截图

| 快捷键 | 功能 |
|--------|------|
| **Print** | 区域截图（`flameshot gui`，框选并标注，保存至 `~/Pictures/`） |
| **Super + Print** | 区域截图（`flameshot gui`） |
| **XF86AudioMute** | 静音/取消静音，并刷新状态栏音量 |
| **XF86AudioLowerVolume** | 音量 −5% |
| **XF86AudioRaiseVolume** | 音量 +5% |
| **XF86AudioMicMute** | 麦克风静音切换 |
| **XF86MonBrightnessUp** | 亮度 +10% |
| **XF86MonBrightnessDown** | 亮度 −10% |
| **XF86TouchpadOn / Off / Toggle** | 触摸板开关（`synclient`） |

## 鼠标操作

| 操作 | 功能 |
|------|------|
| 点击标签栏 **左键** | 切换到该标签 |
| 点击标签栏 **右键** | 切换该标签的显示 |
| 当前选中 tag | 底部彩色下划线（`selfgrainbow` 开启时与 tag 文字同色） |
| **Super + 左键** 点击标签 | 将窗口移到该标签 |
| **Super + 右键** 点击标签 | 窗口粘性标签 |
| **Super + 左键** 拖动窗口 | 移动窗口（浮动时）或 placemouse 交换位置 |
| **Super + 中键** 点击窗口 | 切换浮动 |
| **Super + 右键** 拖动窗口 | 调整大小（从最近角落） |
| **Super + Shift + 左键** 拖动 | 拖动调整 master 区域比例 |
| **Super + 中键** 点击标题栏 | Zoom（窗口升至 master） |
| 点击状态栏模块 | 见下方 dwmblocks 章节 |

## dwmblocks 状态栏

状态栏模块顺序（分隔符 ` │ `，两侧有空格）：

```
memory │ cpu │ fanspeed │ internet │ bluetooth │ battery │ clock │ volume │ brightness │ mic
```

模块内间距由 `dwmblocks/bin/dwmblocks-lib` 控制：

| 变量 | 默认 | 说明 |
|------|------|------|
| `ICON_GAP` | 一个空格 | 图标与数值之间 |
| `SEG_GAP` | 两个空格 | 同一模块内多段信息之间（如 WiFi / 有线 / VPN） |

修改 `delim` 或上述变量后，复制 `bin/` 到 PATH 并重启 dwmblocks；改 `dwmblocks/config.h` 中的 `delim` 需重新编译 dwmblocks。

### 模块刷新信号

向 dwmblocks 发信号可立即刷新对应模块：`kill -(34 + signal) $(pidof dwmblocks)`

| 模块 | 信号 | kill 命令示例 | 自动刷新间隔 |
|------|------|---------------|--------------|
| brightness | 3 | `kill -37 $(pidof dwmblocks)` | 5s |
| memory | 4 | `kill -38 ...` | 10s |
| cpu | 5 | `kill -39 ...` | 5s |
| bluetooth | 6 | `kill -40 ...` | 5s |
| fanspeed | 7 | `kill -41 ...` | 5s |
| internet | 8 | `kill -42 ...` | 5s |
| battery | 9 | `kill -43 ...` | 10s |
| clock | 10 | `kill -44 ...` | 30s |
| volume | 11 | `kill -45 ...` | 仅信号触发 |
| mic | 12 | `kill -46 ...` | 仅信号触发 |

音量、麦克风、亮度键已在 `config.h` 中绑定自动刷新。

### 状态栏点击操作

状态栏支持左键（1）、中键（2）、右键（3）、滚轮上（4）、滚轮下（5）。**Super + 右键**（button 6）可编辑对应脚本。

#### memory 内存

- **左键**：通知显示内存占用最高的进程
- **中键**：打开 `htop`
- **右键**：显示帮助

#### cpu

- **左键**：通知显示 CPU 占用最高的进程
- **中键**：打开 `htop`
- **右键**：显示帮助（含 CPU 温度说明）

#### fanspeed 风扇

- 只读显示，ThinkPad `/proc/acpi/ibm/fan` 转速；点击无操作

#### internet 网络

- **左键**：终端中打开 `nmtui`
- **右键**：图标说明（WiFi / 有线 / VPN）

#### bluetooth 蓝牙

- **左键**：打开 `blueman-manager` 或 `bluetoothctl`
- **右键**：图标说明
- 连接蓝牙音频时自动切换默认 sink

#### battery 电池

- **右键**：充电状态图标说明

#### clock 时钟

- **左键**：通知显示今天/昨天/明天日期与当前时间
- **中键**：打开 `calcurse`（若已安装）
- **右键**：帮助
- 显示格式：`图标 8:00 AM`（12 小时制）

#### volume 音量

- **左键**：打开 `pavucontrol` 或 `helvum`
- **中键**：静音切换
- **滚轮**：±5%
- **右键**：帮助

#### brightness 亮度

- **滚轮上/下**：亮度 ±10%

#### mic 麦克风

- **左键 / 中键**：静音切换
- **滚轮**：增益 ±5%
- **右键**：帮助

## 窗口规则

部分应用在启动时会自动应用规则（浮动、终端、标签等），详见 `config.h` 中 `rules[]`。常见示例：

- `kitty`：终端，可被 swallow
- `kitty-float`：浮动终端
- `LibreWolf` / `Firefox`：主窗口平铺，弹窗浮动
- `zoom`：按窗口标题区分会议/聊天/Breakout 等
- `copyq`、`Volume Control` 等：浮动

## 自定义

| 快捷键、布局、规则、颜色 | 编辑 `dwm/config.h` → `make && sudo make install` → Super+Shift+r 重启 |
| 彩虹 tag / 状态栏渐变 | 编辑 `selfgrainbow`、`statusgradfrom`、`statusgradto` 等 → 同上 |
| 状态栏模块 | 编辑 `dwmblocks/config.h` → `make && sudo make install` → 重启 dwmblocks |
| 状态栏脚本 / 间距 | 编辑 `dwmblocks/bin/*` 或 `dwmblocks-lib` → 复制到 PATH → `kill -(34+signal) $(pidof dwmblocks)` |
| 辅助脚本 | 编辑 `scripts/*` → `./scripts/install.sh` |
| 外观颜色（运行时） | 可通过 Xresources 覆盖（`dwm-xresources` patch） |

## 已应用的主要补丁

- 半透明状态栏 + 系统托盘（systray）
- vanitygaps 窗口间距、cfacts 可调窗口高度
- statuscmd（dwmblocks 点击与信号）
- pertag（每个 tag 独立布局 / mfact / nmaster）
- 状态栏文字渐变、标签彩虹色与下划线指示（本仓库自定义）
- scratchpad、swallow、selfrestart、togglefullscreen
- focusfollowmouse、dragmfact、placemouse、inplacerotate
- 多显示器 sortscreens、resizecorners、rulerefresher

完整补丁列表与上游说明见 [dwm/README](dwm/README)。
