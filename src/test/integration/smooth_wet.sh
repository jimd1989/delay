#!/bin/sh

make
mkfifo /tmp/fifo
./adelay <> /tmp/fifo &
ADELAY_PID=$!
echo 'V0;R0;w0;p0.5;t0.5;f0.5' > /tmp/fifo
cat src/test/integration/ramp_wet | xargs -I % sh -c 'sleep 0.1; echo %' > /tmp/fifo
kill -9 $ADELAY_PID
rm ./adelay
