#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

// global variables


void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

// helper functions
int calculateLevel(int index);
bool is_prime(int n);
int nearest_prime(int n);
bool is_knight_dead(int HP,int &phoenixdown, int & rescue, int & state);
std::string tolower(std::string s);
int has_merlin(std::string s);
// handle_event functions
void handle_event_1_to_5(int index,int event, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int &);
void handle_event_6(int index,int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int & state, int & state_end);
void handle_event_7(int index,int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int & state, int & state_end);
void handle_event_11(int &HP, int level, int phoenixdown);
void handle_event_12(int &HP);
void handle_event_13(int index, int event_code, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state, int &state_end, std::string filename);
void handle_event_15(int &HP, int &remedy, int&state);
void handle_event_16(int &level, int &maidenkiss, int&state);
void handle_event_18(int & HP, string filename);
void handle_event_19(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int & state, string filename);
void handle_event_99(int &level, int &rescue);
#endif // __KNIGHT_H__