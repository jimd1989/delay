# adelay

Interactive stereo audio delay shell. Listens for standard audio input, and outputs delayed signals. Listens on stdio for parameter changes, which allows it to become a dynamic instrument itself if hooked up to a script/MIDI bridge/whatever.

## Building

Requires sndio. Operating systems other than OpenBSD have not and will not be considered.


```
make
make install
make uninstall
```

May have to be root for some operations.

## Usage

Invoking `adelay` drops the user into the shell. Audio playback begins immediately. The signal can be modulated with the following commands.

_Lowercase = left channel. Capital = right channel._

| Command            | Description                                                                                         |
|--------------------|-----------------------------------------------------------------------------------------------------|
| `f`/`F` [0.0, 1.0] | Amount of feedback applied to signal.                                                               |
| `p`/`P` [0.0, 1.0] | Pan signal. 0.0 is hard left and 1.0 is hard right. Left input can be panned right, and vice-versa. |
| `r`/`R` [0.0, 1.0] | Input volume.                                                                                       |
| `t`/`T` [0.0, ∞]   | Delay time. If over the limit, will wrap around with unexpected results.                            |
| `v`/`V` [0.0, 1.0] | Output volume.                                                                                      |
| `w`/`W` [0.0, 1.0] | Signal wetness. 0.0 is unmodulated input signal and 1.0 is only delayed output.                     |

## Examples

Commands can be `on;one;line`. An stereo shimmery reverb effect might be implemented as

```
p0.35;P0.65;t0.05;T0.2;w0.5;W0.5;f0.9;F0.8
```

A monophonic delay that syncopates nicely with the lowest BPM setting on a Korg Monotribe sequence.

```
V0;R0;p0.5;w0.5;t1.2;f0.6
```
