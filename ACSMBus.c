//
//  ACSMBus.c
//  ACSMBus
//
//  Created by Andrew Cavanagh on 6/2/19.
//  Copyright © 2019 andrewjmc. All rights reserved.
//

#include "ACSMBus.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

#define I2C_SLAVE 0x0703

/* Uncomment this line to enable printing. */
//#define PRINT

#ifdef PRINT
#define _PRINT(prefix, buf, len)\
  uint8_t *_buf = (uint8_t *)buf;\
  printf("%s: ", prefix);\
  for (int i = 0; i < len; ++i) {\
    printf("%02x", _buf[i]);\
  }\
  printf("\n");
#else
#define _PRINT(prefix, buf, len)
#endif

static int ac_smbus_select(int fd, uint8_t dev)
{
  return ioctl(fd, I2C_SLAVE, dev & 0x7F);
}

int ac_smbus_open(const char *device)
{
  return open(device, O_RDWR);
}

int ac_smbus_close(int fd)
{
  return close(fd);
}

int ac_smbus_read(int fd, uint8_t dev, void *buf, size_t len)
{
  if (ac_smbus_select(fd, dev) < 0) {
    return -1;
  }

  int r = (int)read(fd, buf, len);
  _PRINT("R", buf, len)
  return r;
}

int ac_smbus_write(int fd, uint8_t dev, void *buf, size_t len)
{
  if (ac_smbus_select(fd, dev) < 0) {
    return -1;
  }

  _PRINT("W", buf, len)
  return (int)write(fd, buf, len);
}

int ac_smbus_read_from_reg(int fd, uint8_t dev, uint8_t reg, void *buf, size_t len)
{
  if (ac_smbus_write(fd, dev, &reg, 1) < 0) {
    return -1;
  }

  return ac_smbus_read(fd, dev, buf, len);
}

int ac_smbus_write_to_reg(int fd, uint8_t dev, uint8_t reg, void *buf, size_t len)
{
  void *out_buf = calloc(1, len + 1);
  memset(out_buf, reg, 1);
  memcpy(out_buf+1, buf, len);

  int r = ac_smbus_write(fd, dev, out_buf, len + 1);
  free(out_buf);
  return r;
}
