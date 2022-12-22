#!/bin/sh

make
mkfifo /tmp/fifo
./adelay <> /tmp/fifo &
ADELAY_PID=$!
echo 'V0;R0;w0;p0.5;v0' > /tmp/fifo
cat src/test/integration/ramp_volume | xargs -I % sh -c 'sleep 0.1; echo %' > /tmp/fifo
kill -9 $ADELAY_PID
rm ./adelay
