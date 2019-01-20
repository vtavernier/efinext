#!/bin/bash
cp startup.nsh build/
qemu-system-x86_64 -nodefaults -vga std -machine q35,accel=kvm:tcg \
  -m 128M -drive if=pflash,format=raw,readonly,file=${PWD}/ovmf/OVMF_CODE.fd \
  -drive if=pflash,format=raw,file=${PWD}/ovmf/OVMF_VARS.fd \
  -drive format=raw,file=fat:rw:${PWD}/build -monitor vc:1024x768
