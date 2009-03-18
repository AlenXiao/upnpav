/***************************************************************************
    begin                : Mon Mar 02 2009
    copyright            : (C) 2009 by Alper Akcan
    email                : alper.akcan@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef UPNP_H_
#define UPNP_H_

typedef struct ssdp_s ssdp_t;
typedef struct ssdp_device_s ssdp_device_t;
typedef struct gena_s gena_t;
typedef struct upnp_s upnp_t;

typedef enum {
	GENA_FILEMODE_READ  = 0x01,
	GENA_FILEMODE_WRITE = 0x02,
} gena_filemode_t;

typedef enum {
	GENA_SEEK_SET = 0x01,
	GENA_SEEK_CUR = 0x02,
	GENA_SEEK_END = 0x03,
} gena_seek_t;

typedef struct gena_fileinfo_s {
	unsigned long size;
	char *mimetype;
	unsigned long mtime;
} gena_fileinfo_t;

typedef struct gena_callbacks_s {
	int (*info) (void *cookie, char *path, gena_fileinfo_t *info);
	void * (*open) (void *cookie, char *path, gena_filemode_t mode);
	int (*read) (void *cookie, void *handle, char *buffer, unsigned int length);
	int (*write) (void *cookie, void *handle, char *buffer, unsigned int length);
	unsigned long (*seek)  (void *cookie, void *handle, long offset, gena_seek_t whence);
	int (*close) (void *cookie, void *handle);
	void *cookie;
} gena_callbacks_t;

int ssdp_advertise (ssdp_t *ssdp, char *description, char *location);
int ssdp_register (ssdp_t *ssdp, char *nt, char *usn, char *location, char *server, int age);
ssdp_t * ssdp_init (void);
int ssdp_uninit (ssdp_t *ssdp);

unsigned short gena_getport (gena_t *gena);
const char * gena_getaddress (gena_t *gena);
gena_t * gena_init (char *address, unsigned short port, gena_callbacks_t *callbacks);
int gena_uninit (gena_t *gena);

int upnp_advertise (upnp_t *upnp);
int upnp_register_device (upnp_t *upnp, const char *description);
char * upnp_getaddress (upnp_t *upnp);
unsigned short upnp_getport (upnp_t *upnp);
upnp_t * upnp_init (const char *host, const unsigned short port);
int upnp_uninit (upnp_t *upnp);

#endif /* UPNP_H_ */