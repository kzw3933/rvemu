#! /bin/bash
# 启用core dump文件生成
sudo sysctl -w kernel.core_pattern=core.%e.%p.%h.%t
sudo sysctl -w kernel.core_uses_pid=1
ulimit -c unlimited 