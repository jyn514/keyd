#ifndef MACRO_H
#define MACRO_H

#include <stdint.h>
#include <stdlib.h>

struct macro_entry {
	enum {
		MACRO_KEYSEQUENCE,
		MACRO_HOLD,
		MACRO_RELEASE,
		MACRO_UNICODE,
		MACRO_TIMEOUT
	} type;

	uint16_t data;
};

/*
 * A series of key sequences optionally punctuated by
 * timeouts
 */
struct macro {
	struct macro_entry entries[64];

	uint32_t sz;
};


void macro_execute(void (*output)(uint8_t, uint8_t),
		   const struct macro *macro,
		   size_t timeout);

int macro_parse(char *s, struct macro *macro);

#define MACRO_ADD_ENTRY(t, d) do { \
	if (macro->sz >= ARRAY_SIZE(macro->entries)) { \
		err("maximum macro size (%d) exceeded", ARRAY_SIZE(macro->entries)); \
		return -1; \
	} \
	macro->entries[macro->sz].type = t; \
	macro->entries[macro->sz].data = d; \
	macro->sz++; \
} while(0)

#endif
