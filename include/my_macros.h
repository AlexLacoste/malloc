/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** my_macros
*/

#ifndef MY_MACROS_H_
#define MY_MACROS_H_

#define PTR(var, _ret_)     \
if (!var)                   \
    return _ret_;

#define CHECK(val, comp, _ret_) \
if (val == comp)                \
    return _ret_;

#endif /* !MY_MACROS_H_ */
