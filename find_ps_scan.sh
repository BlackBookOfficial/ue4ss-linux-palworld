#!/bin/bash
find /mnt/d/ue4ss-linux/build_linux -name "*.a" | while read f; do
    if nm "$f" 2>/dev/null | grep -q "T ps_scan"; then
        echo "FOUND: $f"
    fi
done
find /mnt/d/ue4ss-linux/build_linux -name "*.o" | while read f; do
    if nm "$f" 2>/dev/null | grep -q "T ps_scan"; then
        echo "FOUND: $f"
    fi
done
