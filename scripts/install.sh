#!/bin/sh
# Install dwm helper scripts to ~/.config/scripts/
set -e
dest="$HOME/.config/scripts"
src="${0%/*}"
mkdir -p "$dest"
for f in "$src"/*; do
	[ -f "$f" ] || continue
	case "$(basename "$f")" in
		install.sh|README.md) continue ;;
		emoji) cp -f "$f" "$dest/"; chmod 644 "$dest/emoji" ;;
		*) cp -f "$f" "$dest/"; chmod 755 "$dest/$(basename "$f")" ;;
	esac
done
echo "Installed scripts to $dest"
