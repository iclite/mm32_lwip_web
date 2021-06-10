# MM32_LWIP_WEB

MindMotion MM32F3277 LwIP HTTP Server Web Demo.

## Target

- Chip: MM32F3277G9P
- Board: MindMotion MB-039
- IDE: IAR v7.80.4 or v8.50.9

## Cloning this repository

This repo uses Git Submodules to bring in dependent components.

- mm32_startup：[https://github.com/PYGC/mm32_startup.git](https://github.com/PYGC/mm32_startup.git)
- FreeRTOS-Kernel: [https://github.com/FreeRTOS/FreeRTOS-Kernel.git](https://github.com/FreeRTOS/FreeRTOS-Kernel.git)
- lwip: [https://git.savannah.gnu.org/git/lwip.git](https://git.savannah.gnu.org/git/lwip.git)

To clone using HTTPS:：

```bash
git clone https://www.github.com/PYGC/mm32_lwip_web.git --recurse-submodules
```

Using SSH:

```bash
git clone git@github.com:PYGC/mm32_lwip_web.git --recurse-submodules
```

If you have downloaded the repo without using the `--recurse-submodules` argument, you need to run:

```bash
git submodule update --init --recursive
```

## FreeRTOS

- Git Submodule Version: V10.4.3

## LwIP

- Git Submodule Version: STABLE-2_1_x
- DHCP: on
- HTTP Server Port: 80