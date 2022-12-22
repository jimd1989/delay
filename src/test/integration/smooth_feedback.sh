#!/bin/sh

make
mkfifo /tmp/fifo
./adelay <> /tmp/fifo &
ADELAY_PID=$!
echo 'V0;R0;w0.5;p0.5;t0.5' > /tmp/fifo
sleep 0.5
cat src/test/integration/ramp_feedback | xargs -I % sh -c 'sleep 0.1; echo %' > /tmp/fifo
kill -9 $ADELAY_PID
rm ./adelay
