#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

// global variables


void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
int calculateLevel(int index);
void handle_event_1_to_5(int index,int event, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int &);
void handle_event_6(int index,int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int & state, int & state_end);
void handle_event_7(int index,int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int & state, int & state_end);


#endif // __KNIGHT_H__