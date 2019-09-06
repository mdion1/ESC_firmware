#ifndef _DMA_REG_H
#define _DMA_REG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute__((packed)) {
	volatile const void* volatile SADDR;
	int16_t SOFF;
	union {
		uint16_t ATTR;
		struct { uint8_t ATTR_DST; uint8_t ATTR_SRC; };
	};
	union {
		uint32_t NBYTES; uint32_t NBYTES_MLNO;
		uint32_t NBYTES_MLOFFNO; uint32_t NBYTES_MLOFFYES;
	};
	int32_t SLAST;
	volatile void* volatile DADDR;
	int16_t DOFF;
	union {
		volatile uint16_t CITER;
		volatile uint16_t CITER_ELINKYES; volatile uint16_t CITER_ELINKNO;
	};
	int32_t DLASTSGA;
	volatile uint16_t CSR;
	union {
		volatile uint16_t BITER;
		volatile uint16_t BITER_ELINKYES; volatile uint16_t BITER_ELINKNO;
	};
} TCD_t;

#ifdef __cplusplus
}
#endif

#endif
