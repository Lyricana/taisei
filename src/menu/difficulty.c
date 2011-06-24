/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information. 
 * ---
 * Copyright (C) 2011, Lukas Weber <laochailan@web.de>
 */

#include "difficulty.h"
#include "mainmenu.h"
#include "global.h"

void set_difficulty(void *d) {
	global.diff = (Difficulty) d;
}

void create_difficulty_menu(MenuData *m) {
	create_menu(m);
	
	add_menu_entry(m, "Easy\nfor fearful fairies", set_difficulty, (void *)D_Easy);
	add_menu_entry(m, "Normal\nfor confident kappa", set_difficulty, (void *)D_Normal);
	add_menu_entry(m, "Hard\nfor omnipotent oni", set_difficulty, (void *)D_Hard);
	add_menu_entry(m, "Lunatic\nfor gods", set_difficulty, (void *)D_Lunatic);
	
}

void difficulty_menu_loop(MenuData *menu) {
	set_ortho();
	while(menu->quit != 2) {
		menu_logic(menu);
		menu_input(menu);
		
		draw_difficulty_menu(menu);
		SDL_GL_SwapBuffers();
		SDL_Delay(16);
	}
	destroy_menu(menu);
}

void draw_difficulty_menu(MenuData *menu) {
	draw_main_menu_bg(menu);
	draw_text(AL_Left, 10, 30, "Difficulty", _fonts.mainmenu);
	
	int i;
	for(i = 0; i < menu->ecount; i++) {
		glPushMatrix();
		glTranslatef(SCREEN_W/3 - 30*(i==menu->cursor), 200 + 70*i,0);
		
		glColor4f(1,1-0.1*i,1-0.1*i,0.7);
		glBegin(GL_QUADS);
		glVertex3f(-10,-30,0);
		glVertex3f(-10,30,0);
		glVertex3f(300,30,0);
		glVertex3f(300,-30,0);
		glEnd();
		
		glColor4f(0,0,0,1);
		
		if(i == menu->cursor)
			glColor3f(0.2,0,0.1);
		draw_text(AL_Left, 0, -15, menu->entries[i].name, _fonts.standard);
		glColor3f(1,1,1);
		glPopMatrix();
	}
	
	fade_out(menu->fade);
}
	