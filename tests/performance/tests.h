/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:20:57 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/23 23:59:10 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
#define TESTS_HPP

//vector
void insert_1e5_integral_constant_at_begin();
void insert_1e7_integral_constant_at_end();
void insert_1e6_integral_constant_at_position();
void insert_1e4__with_count_eq_10_integral_constant_at_begin();
void insert_1e5_with_count_eq_10_integral_constant_at_end();
void insert_1e4_with_count_eq_10_integral_constant_at_position();
void insert_1e4_at_begin();
void insert_1e7_at_end();
void insert_1e4_at_position();
void insert_1e4__with_count_eq_10_at_begin();
void insert_1e6_with_count_eq_10_at_end();
void insert_1e4_with_count_eq_10_at_position();
void insert_1e8_integral_constant_with_range_II();
void insert_1e7_with_range_II();
void erase_1_element_in_the_middle_of_1e9_integral_constant();
void erase_1_element_in_the_middle_of_1e8();
void erase_range_element_in_the_middle_of_1e9_integral_constant();
void erase_range_element_in_the_middle_of_1e8();
void clear_1e8_integral_constant();
void clear_1e8();
void reserve_1e9_integral_constant();
void reserve_1e8();


//map
void insert_1e7_values();
void insert_1e7_values_string();
void insert_1e7_range();
void insert_1e7_range_string();
void erase_1_element_at_position();
void erase_key();
void erase_range();
void find_by_key();
void equal_range_key();
#endif // !TESTS_HPP
