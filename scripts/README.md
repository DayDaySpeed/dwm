# dwm 快捷键脚本

由 `dwm/config.h` 中 `S_PATH`（`~/.config/scripts/`）引用。

## 安装

```bash
./scripts/install.sh
```

## 脚本与快捷键

| 脚本 | 快捷键 | 说明 |
|------|--------|------|
| `displayselect` | Alt+d | 多显示器布局（xrandr / arandr） |
| `set-fan` | Alt+f | ThinkPad 风扇（暗影精灵不可用） |
| `inactivity` | Alt+i | 周期性移动鼠标防休眠 |
| `screenlock` | Alt+l | slock 锁屏 |
| `dmenumount` | Alt+m | dmenu 挂载 U 盘 / 手机 |
| `screenrecord` | Alt+r | ffmpeg 录屏 |
| `toggletouchpad` | Alt+t | 开关触摸板（synclient） |
| `dmenuumount` | Alt+u | dmenu 卸载驱动器 |
| `randomwall-now` | Alt+w | 随机壁纸（hsetroot，需 `~/wallpapers`） |
| `safe-switch` | Alt+Shift+b | 安全模式（关网络/静音/降亮度/锁屏） |
| `dmenuunicode` | Alt+Shift+e | Emoji 选择（需 copyq、emoji 数据文件） |
| `launcher` | Alt+Shift+l | 脚本启动器 |
| `reminder` | Alt+Shift+r | 定时提醒 |
| `disk-usage` | Alt+Shift+u | 磁盘用量 |
| `downloader` | XF86Search | YouTube 转 MP3（yt-dlp / youtube-dl） |
| `killkittytag` | （无） | 关闭当前 tag 上所有 kitty 窗口；`~/.config/scripts/killkittytag` 或 `launcher` |

## 依赖

各脚本按需依赖：`dmenu`、`slock`、`ffmpeg`、`hsetroot`、`synclient`、`wpctl`、`notify-send`、`xwininfo`、`xkill`、`xrandr`、`yt-dlp` 等。缺失时对应脚本会报错或降级。
