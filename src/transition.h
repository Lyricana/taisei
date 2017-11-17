/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2017, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2017, Andrei Alexeyev <akari@alienslab.net>.
 */

#pragma once

#include <stdbool.h>

typedef struct Transition Transition;
typedef void (*TransitionRule)(double fade);
typedef void (*TransitionCallback)(void *a);

struct Transition {
    double fade;
	int dur1; // first half
	int dur2; // second half
    TransitionCallback callback;
    void *arg;

    enum {
        TRANS_IDLE,
        TRANS_FADE_IN,
        TRANS_FADE_OUT,
        TRANS_FADED_IN,
        TRANS_FADED_OUT,
    } state;

	TransitionRule rule;
    TransitionRule rule2;

    struct {
        int dur1;
        int dur2;
        TransitionRule rule;
        TransitionCallback callback;
        void *arg;
    } queued;
};

typedef enum TransUpdateMode {
    TRANS_UPDATE_FADE = (1 << 0),
    TRANS_UPDATE_PROGRESS = (1 << 1),
} TransUpdateMode;

extern Transition transition;

void TransFadeBlack(double fade);
void TransFadeWhite(double fade);
void TransLoader(double fade);
void TransMenu(double fade);
void TransMenuDark(double fade);
void TransEmpty(double fade);

void set_transition(TransitionRule rule, int dur1, int dur2);
void set_transition_callback(TransitionRule rule, int dur1, int dur2, TransitionCallback cb, void *arg);
void draw_transition(void);
void update_transition(void);
void update_transition_ex(TransUpdateMode mode);
void draw_and_update_transition(void);
