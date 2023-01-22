#ifndef INPUTSANITISER_H
#define INPUTSANITISER_H

#include <string>
#include <iostream>

bool is_valid_int(int& x, const std::string& input);
int get_valid_int(const std::string& message, int lower_bound, int upper_bound);

bool is_valid_float(float& x, const std::string& input);
float get_valid_float(const std::string& message, float lower_bound, float upper_bound);

std::string get_valid_string(const std::string& message);
bool is_within_range(int value, int lower, int upper);

template <typename T>
void clear_input_stream(T& in);

void press_enter_to_continue();
std::string to_upper(std::string str);
std::string to_lower(std::string str);
bool confirm_action(std::string message);


#endif // !INPUTSANITISER_H