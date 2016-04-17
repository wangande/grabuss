/*
 * aircraft.h
 *
 *  Created on: 2016-4-14
 *  Author: wangande
 */

#include <math.h>
#include "grubbs.h"

/*格拉布斯临界值表*/
float GRUBBS_CRITICAL_TABLE[101] = {1.15, 1.15, 1.15, 1.15, 											/*0-3*/
									1.46, 1.67, 1.82, 1.94, 2.03, 2.11, 2.18,  							/*4-10*/
									2.23, 2.29, 2.33, 2.37, 2.41, 2.44, 2.47, 2.50, 2.53, 2.56,  			/*11-20*/
									2.58, 2.60, 2.62, 2.64, 												/*20-24*/
									2.66, 2.66, 2.66, 2.66, 2.66,											/*25-29*/
									2.75, 2.75, 2.75, 2.75, 2.75, 										/*30-34*/
									2.81, 2.81, 2.81, 2.81, 2.81, 										/*35-39*/
									2.87,  2.87,  2.87,  2.87,  2.87,  2.87,  2.87,  2.87,  2.87,  2.87,  /*40-49*/
									2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97,  	/*50-60*/
									2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97,			/*61-70*/
									2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 			/*71-80*/
									2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 			/*81-90*/
									2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97, 2.97,  				/*91-99*/
									3.21};																/*100*/


/**
 * function: 冒泡排序发
 * param1(data[]):排序数据
 * param2(length):数据量
 * return:
 * */
void buble_sort(float data[], int length)
{
     int i, j;
     float k;
     for (j=0; j<length; j++) {
          for (i=0; i<length-j-1; i++) {
               if (data[i] > data[i+1]){
                    k = data[i];
                    data[i] = data[i+1];
                    data[i+1] = k;
               }
          }
     }
}

/**
 * function: 获取样本标准差
 * param1(data):输入样本数据
 * param2(start): 样本起始索引
 * param3(end): 样本末尾索引
 * return:
 * */
float get_standard_deviation(float data[], int start, int end)
{
	float sum = 0.0;
	float e = 0.0;
	float aver, s;
	int i = 0;
	int n = end - start  + 1;

	for (i=start; i <= end; i++) {
		sum += data[i];
	}

	aver = sum/n;
	for (i=start; i<=end; i++){
		e += (data[i] - aver) * (data[i] - aver);
		e /= n-1;
	 	s = sqrt(e);
	}

	return s;
}

/**
 * function: 获取样本中位数
 * param1(data[]):输入样本数据
 * param2(start): 样本起始索引
 * param3(end): 样本末尾索引
 * return:
 * */
float get_grubbs_median(float data[], int start, int end)
{
	int n = end - start  + 1;
	float median;

	int flag = 0;
	if ( n%2 != 0) {
		flag = 1;
	}

	if (flag == 1) {
		median = data[(n-1)/2];
	} else {
		median = (data[n/2] + data[n/2 -1])/2;
	}

	return median;
}

/**
 * function: 获取格拉布斯临界值
 * param1(n): 样本数量
 * return: n样本量下格拉布斯临界值
 * */
float get_grubbs_critical(int n){
	return GRUBBS_CRITICAL_TABLE[n];
}
