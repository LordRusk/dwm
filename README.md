# Rusk's build of dwm

## FAQ

> What are the bindings?

This is suckless, mmmbud, the source code is the documentation! Check out `config.h`.

## Patches and features

- Clickable statusbar with my build of [dwmblocks](https://github.com/lordrusk/dwmblocks)
- Cycle through layouts with  (`super+shift+comma/period`)
- All layouts have gaps through `vanity gaps` (`super+z/x/a`)
- Borderpx can me adjusted on the fly. (`super+shift+z/x/a`)
- True fullscreen (`super+f`) and prevents focus shifting.
- Rule for fakefullscreen, forcing window to fullscreen into allocated area.
- Windows can be made sticky (`super+ctrl+s`)
- Selects the next window having the urgent flag regardless of the tag its on with (`super+shift+u`)
- Push windows up/down in stack (`super+shift+j/k`)
- Swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- All floating windows will appear in the center of the screen and floating windows after being forced into tiled mode will revert to their last  size when their previous floating size.
- Scratch pads with st, lf, pulsemixer, calculator, and surf defaults.
- Dwmc that works with all current patches. (pushup/pushdown/cyclelayouts/togglefullscr/togglesticky/togglescratch/etc...)
- NO DMENU

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.
