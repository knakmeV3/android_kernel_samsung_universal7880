/*
 * linux/drivers/video/fbdev/exynos/panel/dpui.h
 *
 * Header file for Samsung Common LCD Driver.
 *
 * Copyright (c) 2016 Samsung Electronics
 * Gwanghui Lee <gwanghui.lee@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __DPUI_H__
#define __DPUI_H__

#define MAX_DPUI_KEY_LEN	(20)
#define MAX_DPUI_VAL_LEN	(128)

enum {
	DPUI_AUTO_CLEAR_OFF,
	DPUI_AUTO_CLEAR_ON,
	MAX_DPUI_AUTO_CLEAR,
};

enum dpui_log_level {
	DPUI_LOG_LEVEL_DEBUG,
	DPUI_LOG_LEVEL_INFO,
	DPUI_LOG_LEVEL_ALL,
	MAX_DPUI_LOG_LEVEL,
};

enum dpui_type {
	DPUI_TYPE_NONE,
	DPUI_TYPE_MDNIE,
	DPUI_TYPE_PANEL,
	DPUI_TYPE_DISP,
	DPUI_TYPE_MIPI,
	MAX_DPUI_TYPE,
};

enum dpui_var_type {
	DPUI_VAR_BOOL,
	DPUI_VAR_S32,
	DPUI_VAR_S64,
	DPUI_VAR_U32,
	DPUI_VAR_U64,
	DPUI_VAR_STR,
	MAX_DPUI_VAR_TYPE,
};

#define DPUI_VALID_VAR_TYPE(_vtype_)	\
	(((_vtype_) >= DPUI_VAR_BOOL) && ((_vtype_) < MAX_DPUI_VAR_TYPE))

enum dpui_key {
	DPUI_KEY_NONE,
	DPUI_KEY_WCRD_X,	/* white color x-coordinate */
	DPUI_KEY_WCRD_Y,	/* white color y-coordinate */
	DPUI_KEY_WOFS_R,	/* mdnie whiteRGB red offset from user */
	DPUI_KEY_WOFS_G,	/* mdnie whiteRGB green offset from user */
	DPUI_KEY_WOFS_B,	/* mdnie whiteRGB blue offset from user */
	DPUI_KEY_LCDID1,	/* panel id 1 */
	DPUI_KEY_LCDID2,	/* panel id 2 */
	DPUI_KEY_LCDID3,	/* panel id 3 */
	DPUI_KEY_MAID_DATE,	/* panel manufacture date */
	DPUI_KEY_DISP_MODEL,	/* panel model name */
	DPUI_KEY_CHIPID,	/* display driver-ic chip id */
	DPUI_KEY_CELLID,	/* panel cell id */
	DPUI_KEY_PNDSIE,	/* panel dsi error count */
	DPUI_KEY_PNELVDE,	/* panel ELVDD error count */
	DPUI_KEY_PNVLI1E,	/* panel VLIN1 error count */
	DPUI_KEY_PNVLO3E,	/* panel VLOUT3 error count */
	DPUI_KEY_PNESDE,	/* panel ESD error count */
	DPUI_KEY_PNSDRE,	/* panel OTP loading error count */
	MAX_DPUI_KEY,
};

#define DPUI_VALID_KEY(_key_)	\
	(((_key_) > DPUI_KEY_NONE) && ((_key_) < MAX_DPUI_KEY))

struct dpui_field {
	enum dpui_type type;
	enum dpui_var_type var_type;
	bool auto_clear;
	bool initialized;
	enum dpui_key key;
	enum dpui_log_level level;
	char *default_value;
	char buf[MAX_DPUI_VAL_LEN];
};

#define DPUI_FIELD_INIT(_level_, _type_, _var_type_, _auto_clr_, _default_val_, _key_)	\
	[(_key_)] = {								\
		.type = (_type_),						\
		.var_type = (_var_type_),				\
		.auto_clear = (_auto_clr_),				\
		.initialized = (false),					\
		.key = (_key_),							\
		.level = (_level_),						\
		.default_value = (_default_val_),		\
		.buf[0] = ('\0'),						\
	}

struct dpui_info {
	void *pdata;
	struct dpui_field field[MAX_DPUI_KEY];
};

#ifdef CONFIG_DISPLAY_USE_INFO
void dpui_logging_notify(unsigned long, void *);
int dpui_logging_register(struct notifier_block *, enum dpui_type);
int dpui_logging_unregister(struct notifier_block *);
void update_dpui_log(enum dpui_log_level);
void clear_dpui_log(enum dpui_log_level);
int get_dpui_log(char *, enum dpui_log_level);
int set_dpui_field(enum dpui_key, char *, int);
int set_dpui_u32_field(enum dpui_key, u32);
int get_dpui_u32_field(enum dpui_key, u32 *);
int inc_dpui_u32_field(enum dpui_key, u32);
#else
static inline void dpui_logging_notify(unsigned long val, void *v) { return; }
static inline int dpui_logging_register(struct notifier_block *n, enum dpui_type type) { return 0; }
static inline int dpui_logging_unregister(struct notifier_block *n) { return 0; }
static inline void update_dpui_log(enum dpui_log_level level) { return; }
static inline void clear_dpui_log(enum dpui_log_level level) { return; }
static inline int get_dpui_log(char *buf, enum dpui_log_level level) { return 0; }
static inline int set_dpui_field(enum dpui_key key, char *buf, int size) { return 0; }
static inline int set_dpui_u32_field(enum dpui_key key, u32 value) { return 0; }
static inline int get_dpui_u32_field(enum dpui_key key, u32 *value) { return 0; }
static inline int inc_dpui_u32_field(enum dpui_key key, u32 value) { return 0; }
#endif /* CONFIG_DISPLAY_USE_INFO */
#endif /* __DPUI_H__ */
