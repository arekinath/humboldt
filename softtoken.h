/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017, Joyent Inc
 * Author: Alex Wilson <alex.wilson@joyent.com>
 */

#if !defined(_SOFTTOKEN_H)
#define _SOFTTOKEN_H

#include <zone.h>
#include <libnvpair.h>

enum slot_type {
	SLOT_ASYM_AUTH,
	SLOT_ASYM_CERT_SIGN,
	SLOT_SYM_HSM
};

enum slot_algo {
	ALGO_ED_25519,
	ALGO_RSA_2048,
	ALGO_AES_128
};

enum ctl_cmd_type {
	CMD_UNLOCK_KEY = 0xa0,
	CMD_LOCK_KEY,
	CMD_SHUTDOWN
};

struct ctl_cmd {
	uint8_t cc_type;
	uint8_t cc_p1;
	uint8_t cc_p2;
};

struct token_slot {
	enum slot_type ts_type;
	enum slot_algo ts_algo;
	char *ts_name;
	struct token_slot *ts_next;
	char *ts_data;
	nvlist_t *ts_nvl;
};

extern struct token_slot *token_slots;

void supervisor_main(zoneid_t zid, int ctlfd);
void agent_main(int listensock, int ctlfd);

#endif
