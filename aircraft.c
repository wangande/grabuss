/*
 * aircraft.c
 *
 *  Created on: 2016-4-14
 *  Author: wangande
 */

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "grubbs.h"
#include "aircraft.h"

/**
 * function: 打印数据
 * param1(data):数据
 * param2(length):数据量
 * return:
 * */
void show_data(float data[], int length)
{
	int i = 0;
	for (i=0; i<length; i++) {
		printf("%.3f ", data[i]);
	}
	printf("\n");
}

/**
 * function: 剔除异常样本数据，获取非异常数据的标准值（平均值）
 * param:
 * return:
 * */
int get_input()
{
	int n, i;
	float data[MAX_N];
	float new_data[MAX_N];
	float grubbs_standard;

	printf("\n===输入样本，剔除异常样本数据，获取非异常数据的标准值（平均值）===\n");
	printf("请输入样本量， 最少10个，最多100个: ");
	scanf("%d",&n);

	if (n < 10) {
		printf("样本量值必须大于10\n");
		goto ERROR_EXIT;
	} else if (n >100) {
		printf("样本量值最大100\n");
		goto ERROR_EXIT;
	}

	printf("请输入%d个样本：\n",n);
	for(i=0; i<n; i++) {
		printf("第%d个： ", i+1);
		scanf("%f", &data[i]);
		new_data[i] = data[i];
	 }

//	printf("原始数据：");
//	show_data(data, n);
//	printf("新数据：");
//	show_data(new_data, n);

	grubbs_standard = get_standard(new_data, n); 	//获取输入样本的标准值(平均值)
	save_grubbs_standard_count(data, new_data, grubbs_standard, n); //保存获取输入样本的标准值(平均值)的操作结果
	return n;

ERROR_EXIT:
	return 0;
}

/**
 * function: 根据标准值，剔除异常数据
 * param1(data): 输入样本数据
 * param2(grubbs_standard): 标准值
 * param3(length): 样本量
 * return:
 * */
void fliter_sample_data(float data[], float grubbs_standard, int length)
{
	int i;
	float e;
	for (i=0; i<length; i++) {
		e = (grubbs_standard - data[i]);
		if (e > 0.05 || e < -0.05)
			data[i] = 0;
	}
}

/**
 * function: 输入样本，剔除异常样本数据
 * param:
 * return:
 * */
int fliter_input()
{
	int n, i;
	float data[MAX_N];
	float new_data[MAX_N];
	float grubbs_standard;

	printf("\n===输入标准值（可以从1得到），输入样本，剔除异常样本数据===\n");
	printf("请输入标准值：");
	scanf("%f",&grubbs_standard);

	printf("请输入样本量，最多100个:");
	scanf("%d",&n);
	if (n <= 0) {
			printf("样本量值必须大于0\n");
			goto ERROR_EXIT;
		} else if (n >100) {
			printf("样本量值最大100\n");
			goto ERROR_EXIT;
		}
	printf("请输入%d个样本：\n", n);

	for(i=0; i<n; i++) {
		printf("第%d个： ", i+1);
		scanf("%f", &data[i]);
		new_data[i] = data[i];
	 }
	fliter_sample_data(new_data, grubbs_standard, n);	//根据标准值，剔除异常数据
	save_grubbs_standard_fliter(data, new_data, grubbs_standard, n); //保存剔除异常样本数据的结果
	return n;
ERROR_EXIT:
	return 0;
}

/**
 * function: 计算标准值
 * param1(data[]):输入样本数据
 * param2(start): 样本起始索引
 * param3(end): 样本末尾索引
 * return:
 * */
void count_standard(float data[], int start, int end){

	if (start >= end)
		return ;

	float min = data[start];	//获取样本最小值
	float max = data[end];		//获取样本最大值
	float median = get_grubbs_median(data, start, end);	//获取样本中位数
	float standard = get_standard_deviation(data, start, end); //获取样本标准差
	float grubbs_mix = (median - min)/standard;	//格拉布斯模拟异常最小值
	float grubbs_max = (max - median)/standard; //格拉布斯模拟异常最大值
	float grubbs_critical = get_grubbs_critical(end-start + 1); //获取格拉布斯临界值

	if ( grubbs_max > grubbs_critical ) {	//模拟异常最大值大于格拉布斯临界值
		data[end] = 0.0; 	//该数据最大值异常，剔除
		end -= 1;			//样本末尾向前移动
		count_standard(data, start, end);	//递归
	} else if (grubbs_mix < grubbs_critical) { //模拟异常最小值小于格拉布斯临界值
		data[start] = 0.0;	//该数据最小值异常，剔除
		start += 1;			//样本起始向后移动
		count_standard(data, start, end); //递归
	}

	return ;
}

/**
 * function: 获取输入样本的标准值(平均值)
 * param1(data[]):输入样本数据
 * param2(length):样本数量
 * return:
 * */
float get_standard(float data[], int length){
	int start = 0;
	int end = length - 1;
	int i = 0, n = 0;
	float aver, sum = 0.0;

	buble_sort(data, length);	//为了方便处理，将数据进行排序
//	printf("排序后数据：");
//	show_data(data, length);

	count_standard(data, start, end);
//	show_data(data, length);

	for (i=0; i<length; i++) {
		if (data[i] > 0) {
			sum += data[i];
			n ++;
		}
	}

	if (n > 0) {
		aver = sum/n;
	}

	return aver;
}

/**
 * function: 保存获取输入样本的标准值(平均值)的操作结果
 * param1(org_data):原始输入数据
 * param2(new_data):剔除异常后数据
 * param3(grubbs_standard):标准值
 * param4(length):样本数量
 * return:
 * */
void save_grubbs_standard_count(float org_data[], float new_data[], float grubbs_standard, int length)
{
	int i = 0;

	printf("原始数据:\n");
	for (i=0; i< length; i++) {
		printf("%.3f ", org_data[i]);
	}
	printf("\n");

	printf("正常数据:\n");
	for (i=0; i< length; i++) {
		if (new_data[i] > 0)
			printf("%.3f ", new_data[i]);
	}
	printf("\n");
	
	printf("异常数据:\n");
	for (i=0; i< length; i++) {
		if (new_data[i] <= 0)
			printf("%.3f ", org_data[i]);
	}
	printf("\n");

	printf("标准值:\n");
	printf("%.3f\n",  grubbs_standard);

	save_data_to_file(org_data, new_data, grubbs_standard, length, "./data_get_reacord.txt");	//保存到文件
}

/**
 * function: 保存剔除异常样本数据的结果
 * param1(org_data):原始输入数据
 * param2(new_data):剔除异常后数据
 * param3(grubbs_standard):标准值
 * param4(length):样本数量
 * return:
 * */
void save_grubbs_standard_fliter(float org_data[], float new_data[], float grubbs_standard, int length)
{
	int i = 0;

	printf("原始数据:\n");
	for (i=0; i< length; i++) {
		printf("%.3f ", org_data[i]);
	}
	printf("\n");

	printf("保存数据:\n");
	for (i=0; i< length; i++) {
		if (new_data[i] > 0)
			printf("%.3f ", new_data[i]);
	}
	printf("\n");
	
	printf("异常数据:\n");
	for (i=0; i< length; i++) {
		if (new_data[i] <= 0)
			printf("%.3f ", org_data[i]);
	}
	printf("\n");

	printf("标准值:\n");
	printf("%.3f\n",  grubbs_standard);

	save_data_to_file(org_data, new_data, grubbs_standard, length, "./data_fliter_reacord.txt");	//保存到文件
}

/**
 * function: 保存结果到文件
 * param1(org_data):原始输入数据
 * param2(new_data):剔除异常后数据
 * param3(grubbs_standard):标准值
 * param4(length):样本数量
 * param4(filename):保存文件名
 * return:
 * */
void save_data_to_file(float org_data[], float new_data[], float grubbs_standard, int length, char *filename)
{
	FILE *fp = NULL;
	int i;
	time_t rawtime;
	struct tm * timeinfo;

	fp = fopen(filename, "ab+");
	assert(fp);

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("保存结果到文件%s....\n", filename);

	fprintf(fp, "\r\n记录时间: %s", asctime(timeinfo));
	//fwrite("原始数据：", sizeof("原始数据："), 1, fp);
	fprintf(fp, "%s", "原始数据：");
	for (i=0; i<length; i++) {
		fprintf(fp, "%.3f ", org_data[i]);
	}

	//fwrite("\r\n正常数据：", sizeof("\r\n正常数据："), 1, fp);
	fprintf(fp, "%s", "\r\n正常数据：");
	for (i=0; i<length; i++) {
		if (new_data[i] > 0){
			fprintf(fp, "%.3f ", new_data[i]);
		}
	}
	
	//fwrite("\r\n异常数据：", sizeof("\r\n异常数据："), 1, fp);
	fprintf(fp, "%s", "\r\n异常数据：");
	for (i=0; i<length; i++) {
		if (new_data[i] <= 0){
			fprintf(fp, "%.3f ", org_data[i]);
		}
	}

	fprintf(fp, "\r\n标准值：%.3f\r\n", grubbs_standard);

	fclose(fp);
}
