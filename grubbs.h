/*
 * aircraft.h
 *
 *  Created on: 2016-4-14
 *  Author: wangande
 */

#ifndef __GRUBBS_H__
#define __GRUBBS_H__


void buble_sort(float data[], int length);

float get_grubbs_median(float data[], int start, int end);

float get_standard_deviation(float data[], int start, int end);

float get_grubbs_critical(int n);

#endif /* __GRUBBS_H__ */
