/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef IOAPIC_H
#define IOAPIC_H

/*
 * IOAPIC_MAX_LINES is architecturally defined.
 * The usable RTEs may be a subset of the total on a per IO APIC basis.
 */
#define IOAPIC_MAX_LINES	120U
#define NR_LEGACY_IRQ		16U
#define NR_LEGACY_PIN		NR_LEGACY_IRQ
#define NR_MAX_GSI		(NR_IOAPICS * IOAPIC_MAX_LINES)

void setup_ioapic_irqs(void);

bool irq_is_gsi(uint32_t irq);
uint8_t irq_to_pin(uint32_t irq);

/**
 * @brief Get irq num from pin num
 *
 * @param[in]	pin The pin number
 */
uint32_t pin_to_irq(uint8_t pin);

/**
 * @brief Set the redirection table entry
 *
 * Set the redirection table entry of an interrupt
 *
 * @param[in]	irq The number of irq to set
 * @param[in]	rte Union of ioapic_rte to set
 */
void ioapic_set_rte(uint32_t irq, union ioapic_rte rte);

/**
 * @brief Get the redirection table entry
 *
 * Get the redirection table entry of an interrupt
 *
 * @param[in]	irq The number of irq to fetch RTE
 * @param[inout]	rte Pointer to union ioapic_rte to return result RTE
 *
 * @pre rte != NULL
 */
void ioapic_get_rte(uint32_t irq, union ioapic_rte *rte);

void suspend_ioapic(void);
void resume_ioapic(void);

void gsi_mask_irq(uint32_t irq);
void gsi_unmask_irq(uint32_t irq);

extern uint8_t pic_ioapic_pin_map[NR_LEGACY_PIN];

#ifdef HV_DEBUG
/**
 * @brief Get information of ioapic
 *
 * It's for debug only.
 *
 * @param[in]	str_max_len	The max size of the string containing
 * 				interrupt info
 * @param[inout]	str_arg	Pointer to the output information
 */
int get_ioapic_info(char *str_arg, size_t str_max_len);
#endif /* HV_DEBUG */

#endif /* IOAPIC_H */
