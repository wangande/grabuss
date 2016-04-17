/*
 * main.c
 *
 *  Created on: 2016-4-14
 *  Author: wangande
 */

#include <stdio.h>
#include "aircraft.h"

#define MODE_GET		1
#define MODE_FLITER  	2

/**
 * function: 解析用户输入
 * param:
 * return: 操作类型
 * */
int parse_input()
{
	int mode;
	int max_error = 3;

MODE_INPUT:
	printf("\n请选择你操作类型(1或者2)：\n");
	printf("1：输入样本，剔除异常样本数据，获取非异常数据的标准值（平均值）\n");
	printf("2：输入标准值（可以从1得到），输入样本，剔除异常样本数据\n");
	printf("请输入：");
	scanf("%d", &mode);

	if (mode == MODE_GET || mode == MODE_FLITER ) {
		return mode;
	}

	max_error -= 1;
	if (max_error > 0) {
		goto MODE_INPUT;
	} else {
		printf("错误输入超过3次，即将退出！\n");
	}

	return mode;
}

/**
 * function: 解析用户输入
 * param: 操作类型
 * return:
 * */
void run_grubbs(int mode)
{
	if (mode == MODE_GET){
		get_input();	//剔除异常样本数据，获取非异常数据的标准值（平均值）
	} else if (mode == MODE_FLITER) {
		fliter_input(); //输入标准值（可以从1得到），输入样本，剔除异常样本数据
	}
}

int main(int argc, char *argv[])
{
	int mode;
	printf("===============================================================\n");
	mode = parse_input();
	run_grubbs(mode);
	printf("===============================================================\n");
	return 0;
}

