//
//  ACSMBus.h
//  ACSMBus
//
//  Created by Andrew Cavanagh on 6/2/19.
//  Copyright © 2019 andrewjmc. All rights reserved.
//

#ifndef ACSMBus_h
#define ACSMBus_h

#include <stdio.h>
#include <stdint.h>

#define AC_SMBUS_DEFAULT_DEVICE "/dev/i2c-1"

/*
 Opens the specified I2C device file.
 */
int ac_smbus_open(const char *device);

/*
 Closes the given I2C device file.
 */
int ac_smbus_close(int fd);

/*
 Performs a raw read to I2C device file.
 */
int ac_smbus_read(int fd, uint8_t dev, void *buf, size_t len);

/*
 Performs a raw write to I2C device file.
 */
int ac_smbus_write(int fd, uint8_t dev, void *buf, size_t len);

/*
 Performs a read of the specific register of a the I2c device file.
 */
int ac_smbus_read_from_reg(int fd, uint8_t dev, uint8_t reg, void *buf, size_t len);

/*
 Performs a write of the specific register of a the I2c device file.
 */
int ac_smbus_write_to_reg(int fd, uint8_t dev, uint8_t reg, void *buf, size_t len);

#endif /* ACSMBus_h */
