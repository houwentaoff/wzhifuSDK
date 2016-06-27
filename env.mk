
CROSS_COMPILE=$(TOP_DIR)/env/buildroot/output/host/usr/bin/arm-linux-
CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar

export CC AR
