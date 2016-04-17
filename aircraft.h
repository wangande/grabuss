/*
 * aircraft.h
 *
 *  Created on: 2016-4-14
 *  Author: wangande
 */

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#define MAX_N 100


int get_input();

int fliter_input();

void count_standard(float data[], int start, int end);

float get_standard(float data[], int length);

void save_grubbs_standard_count(float org_data[], float new_data[], float grubbs_standard, int length);

void fliter_sample_data(float data[], float grubbs_standard, int length);

void save_grubbs_standard_fliter(float org_data[], float new_data[], float grubbs_standard, int length);

void save_data_to_file(float org_data[], float new_data[], float grubbs_standard, int length, char *filename);

#endif /* __AIRCRAFT_H__ */
