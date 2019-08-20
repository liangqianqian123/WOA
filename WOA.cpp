// WOA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <time.h>
#include <ctype.h>
#include <memory>
#include <crtdbg.h>
#define dim 30 //变量数量
#define Max_iteration  500 //最大代数
#define SearchAgents_no 30 //个体的数量

#define maxmum 0xffff
#define PI 3.141592653
double position[dim];
double leader_pos[dim] = { 0 };
double leader_score;
double Convergence_curve[Max_iteration] = { 0 };//Convergence_curve收敛曲线
double lb = -100;
double ub = 100;
struct individual
{
	double position[dim];
	double fitness;
}ptcle[SearchAgents_no];

double function_fitness(double* position){
	int i;
	double sum = 0;
	for (i = 0; i < dim; i++) {
		sum += position[i] * position[i];
	}
	return sum;

}

//初始化
void initialization() {
	for (int i = 0; i < SearchAgents_no; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			double randx = (double)rand() / RAND_MAX;
			ptcle[i].position[j] = lb + (ub - lb) * randx;
		
		}
		
	}
}

double GetRand()
{
	return 2.0 * rand() / RAND_MAX - 1.0;
}

void function_WOA() {
	int i, j;
	leader_score = maxmum;
	int t = 0;
	while (t < Max_iteration) {
		for (i = 0; i < SearchAgents_no; i++) {
			for (j = 0; j < dim; j++)
			{
				if (ptcle[i].position[j] > ub) {
					ptcle[i].position[j] = ub;
				}
				if (ptcle[i].position[j] < lb) {
					ptcle[i].position[j] = lb;
				}
			}
			ptcle[i].fitness= function_fitness(ptcle[i].position);
			if (ptcle[i].fitness < leader_score) {
				leader_score = ptcle[i].fitness;
				memcpy(&leader_pos, &ptcle[i].position, sizeof(double) * dim);
			}
		}
		double a = 2 - t * (2 / Max_iteration);
		double a2 = -1+ t * ((-1) / Max_iteration);
		for (i = 0; i < SearchAgents_no; i++) {
			double r1= (double)rand() / RAND_MAX;
			double r2 = (double)rand() / RAND_MAX;
			double A = 2 * a * r1 - a;
			double C = 2 * r2;
			double b = 1;
			double l = (a2 - 1) * (double)rand() / RAND_MAX + 1;
			double p = (double)rand() / RAND_MAX;
			double x_rand[dim];
			double D_X_rand[dim]; 
			double D;
			for (j = 0; j < dim; j++) {
				if (p < 0.5) {
					if (abs(A) >= 1) {
						int	rand_leader_index = floor(SearchAgents_no * (double)rand() / RAND_MAX + 1);
						memcpy(&x_rand, &ptcle[rand_leader_index].position, sizeof(double) * dim);
						D_X_rand[j] = abs(C * x_rand[j] - ptcle[i].position[j]);
						ptcle[i].position[j] = x_rand[j] - A * D_X_rand[j];
					}
					else if(abs(A) < 1){
						double D_leader= abs(C * leader_pos[j] - ptcle[i].position[j]);
						ptcle[i].position[j] = leader_pos[j] - A * D_leader;
					}
				}
				else if (p > 0.5) {
					double distance2Leader= abs(leader_pos[j] - ptcle[i].position[j]);
					ptcle[i].position[j] = distance2Leader * exp(b*l)*cos(l*2*PI) + leader_pos[j];
					
				}
			}
		}
		t = t + 1;
		Convergence_curve[t] = leader_score;
		printf("%.12f\n", Convergence_curve[t]);
	}
	
}



int main()
{
	initialization();
	function_WOA();
	

}

