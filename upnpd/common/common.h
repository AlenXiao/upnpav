/***************************************************************************
    begin                : Sun Jun 01 2008
    copyright            : (C) 2008 by Alper Akcan
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

#ifndef COMMON_H_
#define COMMON_H_

typedef struct list_s list_t;
typedef struct file_s file_t;
typedef struct entry_s entry_t;
typedef struct client_s client_t;
typedef struct device_s device_t;
typedef struct icon_s icon_t;
typedef struct device_service_s device_service_t;
typedef struct service_action_s service_action_t;
typedef struct service_variable_s service_variable_t;

typedef enum {
	RENDER_STATE_UNKNOWN,
	RENDER_STATE_PLAYING,
	RENDER_STATE_STOPPED,
	RENDER_STATE_PAUSED,
	RENDER_STATE_WAITING,
	RENDER_STATE_STATES,
} render_state_t;

struct list_s {
	struct list_s *next;
	struct list_s *prev;
};

/**
  */
struct file_s {
	/** */
	int virtual;
	/** service info, show */
	device_service_t *service;
	/** file descriptor, only for real files */
	int fd;
	/** buffer size, only for virtual files */
	size_t size;
	/** buffer offset, only for virtual files */
	off_t offset;
	/** virtual buffer, only for virtual files */
	char *buf;
};

/**
  * http://dcmi.kc.tsukuba.ac.jp/dcregistry/navigateServlet
  */
typedef struct didl_dc_s {
	/** */
	char *title;
	/** */
	char *creator;
	/** */
	char *subject;
	/** */
	char *description;
	/** */
	char *publisher;
	/** */
	char *contributor;
	/** */
	char *date;
	/** */
	char *type;
	/** */
	char *format;
	/** */
	char *identifier;
	/** */
	char *source;
	/** */
	char *language;
	/** */
	char *relation;
	/** */
	char *coverage;
	/** */
	char *rights;
} didl_dc_t;

typedef enum {
	/** */
	DIDL_UPNP_OBJECT_TYPE_UNKNOWN,
	/** */
	DIDL_UPNP_OBJECT_TYPE_OBJECT,
	/** */
	DIDL_UPNP_OBJECT_TYPE_ITEM,
	/** */
	DIDL_UPNP_OBJECT_TYPE_AUDIOITEM,
	/** */
	DIDL_UPNP_OBJECT_TYPE_MUSICTRACK,
	/** */
	DIDL_UPNP_OBJECT_TYPE_VIDEOITEM,
	/** */
	DIDL_UPNP_OBJECT_TYPE_MOVIE,
	/** */
	DIDL_UPNP_OBJECT_TYPE_IMAGEITEM,
	/** */
	DIDL_UPNP_OBJECT_TYPE_PHOTO,
	/** */
	DIDL_UPNP_OBJECT_TYPE_CONTAINER,
	/** */
	DIDL_UPNP_OBJECT_TYPE_STORAGEFOLDER,
} didl_upnp_object_type_t;

typedef struct didl_upnp_object_s {
	/** */
	didl_upnp_object_type_t type;
	/** */
	char *class;
	/** */
	char *icon;
} didl_upnp_object_t;

typedef struct didl_upnp_item_s {
	/** */
	didl_upnp_object_t object;
} didl_upnp_item_t;

typedef struct didl_upnp_audioitem_s {
	/** */
	didl_upnp_item_t item;
	/** */
	char *genre;
	/** */
	char *longdescription;
} didl_upnp_audioitem_t;

typedef struct didl_upnp_musictrack_s {
	/** */
	didl_upnp_audioitem_t audioitem;
	/** */
	char *artist;
	/** */
	char *album;
	/** */
	uint32_t originaltracknumber;
	/** */
	char *playlist;
} didl_upnp_musictrack_t;

typedef struct didl_upnp_videoitem_s {
	/** */
	didl_upnp_item_t item;
	/** */
	char *genre;
	/** */
	char *longdescription;
	/** */
	char *producer;
	/** */
	char *rating;
	/** */
	char *actor;
	/** */
	char *director;
} didl_upnp_videoitem_t;

typedef struct didl_upnp_movie_s {
	/** */
	didl_upnp_videoitem_t videoitem;
} didl_upnp_movie_t;

typedef struct didl_upnp_imageitem_s {
	/** */
	didl_upnp_item_t item;
	/** */
	char *longdescription;
	/** */
	char *storagemedium;
	/** */
	char *rating;
} didl_upnp_imageitem_t;

typedef struct didl_upnp_photo_s {
	/** */
	didl_upnp_imageitem_t imageitem;
	/** */
	char *album;
} didl_upnp_photo_t;

typedef struct didl_upnp_container_s {
	/** */
	didl_upnp_object_t object;
} didl_upnp_container_t;

typedef struct didl_upnp_storagefolder_s {
	/** */
	didl_upnp_container_t container;
	/** */
	uint32_t storageused;
} didl_upnp_storagefolder_t;

typedef union didl_upnp_s {
	/** */
	didl_upnp_object_type_t type;
	/** */
	didl_upnp_object_t object;
	/** */
	didl_upnp_audioitem_t audioitem;
	/** */
	didl_upnp_musictrack_t musictrack;
	/** */
	didl_upnp_storagefolder_t storagefolder;
	/** */
	didl_upnp_videoitem_t videoitem;
	/** */
	didl_upnp_movie_t movie;
	/** */
	didl_upnp_imageitem_t imageitem;
	/** */
	didl_upnp_photo_t photo;
} didl_upnp_t;

/**
  */
typedef struct didl_res_s {
	char *protocolinfo;
	char *duration;
	uint32_t size;
	char *path;
} didl_res_t;

/**
  */
typedef struct didl_s {
	/** */
	char *entryid;
	/** */
	char *parentid;
	/** */
	uint32_t childcount;
	/** */
	int restricted;
	/** */
	didl_dc_t dc;
	/** */
	didl_upnp_t upnp;
	/** */
	didl_res_t res;
} didl_t;

/**
  */
struct entry_s {
	/** */
	didl_t didl;
	/** */
	char *path;
	/** */
	char *mime;
	/** */
	char *ext_info;
	/** */
	char *metadata;

	/** */
	entry_t *next;
	/** */
	entry_t *prev;
	/** */
	entry_t *child;
	/** */
	entry_t *parent;
};

/** icon struct
  */
struct icon_s {
        /** */
        int width;
        /** */
        int height;
        /** */
        int depth;
        /** */
        char *url;
        /** */
        char *mimetype;
        /** */
        int size;
        /** */
        unsigned char *buffer;
};

typedef enum {
	ARGUMENT_DIRECTION_IN,
	ARGUMENT_DIRECTION_OUT,
} argument_direction_t;

typedef struct action_argument_s {
	char *name;
	argument_direction_t direction;
	char *relatedstatevariable;
} action_argument_t;

/** service action struct
  */
struct service_action_s {
        /** */
	char *name;
	/** */
	action_argument_t **arguments;
        /** */
	int (*function) (device_service_t *service, upnp_event_action_t *request);
};

typedef enum {
	VARIABLE_SENDEVENT_NO,
	VARIABLE_SENDEVENT_YES,
} variable_sendevent_t;

typedef enum {
	VARIABLE_DATATYPE_STRING,
	VARIABLE_DATATYPE_I4,
	VARIABLE_DATATYPE_UI4,
} variable_datatype_t;

/** service variable struct
  */
struct service_variable_s {
        /** */
	char *name;
	/** */
	variable_datatype_t datatype;
	/** */
	variable_sendevent_t sendevent;
	/** */
	char **allowedvalues;
        /** */
	char *defaultvalue;
	/** */
	char *value;
};

/** client variable struct
  */
typedef struct client_variable_s {
	/** */
	list_t head;
	/** */
	char *name;
	/** */
	char *value;
} client_variable_t;

/** client service struct
  */
typedef struct client_service_s {
	/** */
	list_t head;
	/** */
	char *type;
	/** */
	char *id;
	/** */
	char *sid;
	/** */
	char *controlurl;
	/** */
	char *eventurl;
	/** */
	list_t variables;
} client_service_t;

/** client device struct
  */
typedef struct client_device_s {
	/** */
	list_t head;
	/** */
	char *name;
	/** */
	char *type;
	/** */
	char *uuid;
	/** */
	int expiretime;
	/** */
	list_t services;
} client_device_t;

/** client device desc struct
  */
typedef struct device_description_s {
	char *device;
	char **services;
} device_description_t;

/** client struct
  */
struct client_s {
	/** */
	char *name;
	/** */
	device_description_t **descriptions;
	/** */
	char *interface;

	/** */
	int running;
	/** */
	pthread_mutex_t mutex;
	/** */
	pthread_cond_t cond;
	/** */
	pthread_t timer_thread;
	/** */
	int timer_running;
	/** */
	char *ipaddress;
	/** */
	int port;
	/** */
	list_t devices;
};

/** device service struct
  */
struct device_service_s {
	/** */
	char *name;
	/** */
	char *id;
        /** */
	char *type;
        /** */
	char *scpdurl;
        /** */
	char *eventurl;
        /** */
	char *controlurl;
        /** */
	service_action_t **actions;
        /** */
	service_variable_t **variables;
	/** */
	gena_callback_vfs_t *vfscallbacks;
	/** */
	int (*uninit) (device_service_t *service);

        /** */
	pthread_mutex_t mutex;
	/** */
	char *description;
	/** */
	device_t *device;
};

/** device struct
  */
struct device_s {
	/** */
	char *name;
	/** */
	char *interface;
	/** */
	char *devicetype;
	/** */
	char *friendlyname;
	/** */
	char *manufacturer;
	/** */
	char *manufacturerurl;
	/** */
	char *modeldescription;
	/** */
	char *modelname;
	/** */
	char *modelnumber;
	/** */
	char *modelurl;
	/** */
	char *serialnumber;
	/** */
	char *upc;
	/** */
	char *presentationurl;

	/** */
	icon_t **icons;
	/** */
	device_service_t **services;

	/** */
	pthread_mutex_t mutex;
	/** */
	char *ipaddress;
	/** */
	int port;
	/** */
	char *uuid;
	/** */
	int expiretime;
	/** */
	char *description;
	/** */
	int daemonize;

	/** */
	upnp_t *upnp;
};

/* client.c */

int client_init (client_t *client);
int client_uninit (client_t *client);
int client_refresh (client_t *client, int remove);
IXML_Document * client_action (client_t *client, char *devicename, char *servicetype, char *actionname, char **param_name, char **param_val, int param_count);

/* controller.c */

client_t * controller_init (char *options);
int controller_uninit (client_t *controller);
entry_t * controller_browse_children (client_t *controller, const char *device, const char *object);
entry_t * controller_browse_metadata (client_t *controller, const char *device, const char *object);

/* device.c */

int device_init (device_t *device);
int device_uninit (device_t *device);
int device_service_add (device_t *device, device_service_t *service);
device_service_t * device_service_find (device_t *device, char *serviceid);

/* entry.c */

char * entryid_path_from_id (const char *id);
char * entryid_id_from_path (const char *path);
entry_t * entry_didl (const unsigned int magic, const char *path);
int entry_print (entry_t *file);
int entry_dump (entry_t *file);
int entry_normalize_parent (entry_t *entry);
int entry_normalize_root (entry_t *entry);
entry_t * entry_init (const char *path, int recursive);
int entry_uninit (entry_t *root);
entry_t * entry_id (entry_t *root, char *id);
entry_t * entry_from_result (char *result);
char * entry_to_result (device_service_t *service, entry_t *entry, int metadata, unsigned int offset, unsigned int count, unsigned int *numberreturned);

/* contentdir.c */

int contentdirectory_uninit (device_service_t *cotentdir);
device_service_t * contentdirectory_init (char *directory, int cached);

/* connection.c */

int connectionmanager_register_mimetype (device_service_t *service, const char *mime);
uint32_t connection_instance_new (void);
int connectionmanager_uninit (device_service_t *cotentdir);
device_service_t * connectionmanager_init (void);

/* inttool.c */

char * uint32tostr (char *out, uint32_t val);
uint32_t strtouint32 (const char *in);
int32_t strtoint32 (const char *in);

/* mediaserver.c */

device_t * mediaserver_init (char *options);
int mediaserver_uninit (device_t *mediaserver);
int mediaserver_refresh (device_t *mediaserver);

/* mediarender.c */

device_t * mediarender_init (char *options);
int mediarender_uninit (device_t *mediarender);

/* service.c */

int service_init (device_service_t *service);
int service_uninit (device_service_t *service);
service_variable_t * service_variable_find (device_service_t *service, char *name);
service_action_t * service_action_find (device_service_t *service, char *name);

/* upnp.c */

char * description_generate_from_device (device_t *device);
char * description_generate_from_service (device_service_t *service);
int upnp_add_response (upnp_event_action_t *request, char *servicetype, char *key, const char *value);

/* xml.c */

char * xml_escape (const char *str, int attribute);
char * xml_get_first_document_item (IXML_Document *doc, const char *item);
char * xml_get_first_element_item (IXML_Element *element, const char *item);
IXML_NodeList * xml_get_first_service_list (IXML_Document *doc);
char * xml_get_element_value (IXML_Element *element);
uint32_t xml_get_ui4 (IXML_Document *doc, const char *item);
char * xml_get_string (IXML_Document *doc, const char *item);

/* uri.c */

char * uri_escape (const char *str);

/* interface.c */

int interface_printall (void);
char * interface_getaddr (char *ifname);

/* list.c */

#define offsetof_(type, member) ((size_t) &((type *) 0)->member)

#define containerof_(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof_(type,member) );})

#define list_entry(ptr, type, member) \
	containerof_(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
	     n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

static inline int list_count (list_t *head)
{
	int count;
	list_t *entry;
	count = 0;
	list_for_each(entry, head) {
		count++;
	}
	return count;
}

static inline void list_add_actual (list_t *new, list_t *prev, list_t *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_del_actual (list_t *prev, list_t *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_add_tail (list_t *new, list_t *head)
{
	list_add_actual(new, head->prev, head);
}

static inline void list_add (list_t *new, list_t *head)
{
	list_add_actual(new, head, head->next);
}

static inline void list_del (list_t *entry)
{
	list_del_actual(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

static inline int list_is_first (list_t *list, list_t *head)
{
	return head->next == list;
}

static inline int list_is_last (list_t *list, list_t *head)
{
	return list->next == head;
}

static inline void list_init (list_t *head)
{
	head->next = head;
	head->prev = head;
}

#endif /*COMMON_H_*/
