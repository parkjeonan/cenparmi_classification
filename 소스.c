/*

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

const int SIZE_CLASSES = 10;
const int SIZE_SAMPLES_train = 400;
const int SIZE_SAMPLES_test = 200;
const int SIZE_FEATURES = 100;
const int BATCH_SIZE = 100;
const int SIZE_SHUFFLE_1 = 4000;
const int SIZE_SHUFFLE_1_test = 2000;
const int SIZE_SHUFFLE_2 = 1000;
const double ALPHA = 0.1;

double V[101][21] = { 0, };
double W[21][10] = { 0, };

double ***datas = NULL;
double **batch_x = NULL;
double **batch_y = NULL;
int **batchs_index = NULL;


void readTrainFile(char *path, int SIZE_SAMPLES) {
FILE *file;

file = fopen(path, "r");

if (file == NULL) {
printf("No File exists.\n");
}

int label = 0;

datas = (double ***)calloc(SIZE_CLASSES, sizeof(double **));
batchs_index = (int **)calloc(SIZE_CLASSES, sizeof(int *));
for (int i = 0; i < SIZE_CLASSES; i++) {
datas[i] = (double **)calloc(SIZE_SAMPLES, sizeof(double *));
batchs_index[i] = (int *)calloc(SIZE_SAMPLES, sizeof(int));

for (int j = 0; j < SIZE_SAMPLES; j++) {
datas[i][j] = (double *)calloc(SIZE_FEATURES, sizeof(double));
batchs_index[i][j] = j;
}
}

int *cnts;
cnts = (int *)calloc(SIZE_CLASSES, sizeof(int));

for (int n = 0; n < SIZE_CLASSES * SIZE_SAMPLES; n++) {
fscanf(file, "%d\n", &label);

for (int i = 0; i < 100; i++) {
fscanf(file, "%lf", &datas[label][cnts[label]][i]);
}

cnts[label]++;
}

free(cnts);
fclose(file);
}

void shuffling(int SIZE_SHUFFLE, int SIZE_SAMPLES) {
for (int i = 0; i < SIZE_CLASSES; i++) {
for (int n = 0; n < SIZE_SHUFFLE; n++) {
int a = rand() % SIZE_SAMPLES;
int b = rand() % SIZE_SAMPLES;

int tmp = batchs_index[i][a];
batchs_index[i][a] = batchs_index[i][b];
batchs_index[i][b] = tmp;
}
}
}

void setBatchY() {
if (batch_y == NULL) {
batch_y = (double **)calloc(BATCH_SIZE, sizeof(double *));

for (int i = 0; i < BATCH_SIZE; i++) {
batch_y[i] = (double *)calloc(SIZE_CLASSES, sizeof(double));
batch_y[i][i / 10] = 1.0;
}
}

}

void setBatch(int iteration, int SIZE_SAMPLES) {
if (iteration > SIZE_CLASSES * SIZE_SAMPLES / BATCH_SIZE) {
printf("[ERROR] iteration is large!\n");

exit(1);
}

if (iteration == 1) {
shuffling(iteration * 100, SIZE_SAMPLES);
}

if (batch_x == NULL) {
batch_x = (double **)calloc(BATCH_SIZE, sizeof(double *));
}

for (int i = 0; i < BATCH_SIZE; i++) {
if (batch_x[i] == NULL) {
batch_x[i] = (double *)calloc(SIZE_FEATURES + 1, sizeof(double));
}

batch_x[i][0] = 1.0; //바이어스
memcpy(batch_x[i] + 1, datas[i / 10][batchs_index[i / 10][i % 10]], SIZE_FEATURES * sizeof(double));

int tmp_index = SIZE_SAMPLES - (iteration * (BATCH_SIZE / SIZE_CLASSES)) + (i % 10);

batchs_index[i / 10][i % 10] = batchs_index[i / 10][tmp_index];
}

setBatchY();
}
double randomF(void)
{
double rndno;

while ((rndno = (double)rand() / RAND_MAX) == 1.0);
rndno = rndno * 2 - 1;

return rndno;
}
void init(double V[101][21], double W[21][10])
{


for (int j = 0; j < 101; j++) {
for (int k = 0; k < 21; k++) {
V[j][k] = randomF();
//printf("%lf ", V[j][k]);
}
//printf("\n");
}
//printf("\n\n");
for (int j = 0; j < 21; j++) {
for (int k = 0; k < 10; k++) {
W[j][k] = randomF();
//printf("%lf ", W[j][k]);
}
//printf("\n");
}
//printf("\n\n");



}
double sigmoid(double u)
{
return 1.0 / (1.0 + exp(-u));
}
void forward()
{	// batch 당 100개의 인풋
int batchSize = 100;
for (int i = 0; i < batchSize; i++) {


}
}
void learn()
{

}
double accuracy(double Y[101][10], int i, double W[20][10])
{

}


int main(int argc, const char * argv[]) {

double input_accuracy = 0;



srand((unsigned int)time(NULL));

readTrainFile("C:\\Users\\210.117.128.200\\Desktop\\train.txt", SIZE_SAMPLES_train);

scanf("%lf", &input_accuracy);


int iter = SIZE_CLASSES * SIZE_SAMPLES_train / BATCH_SIZE;

int epoch = 1;

init(V, W);


while (1) {
int correct = 0;
int a = 0;
double acc;

if (epoch % 100 == 0) {
printf("training...\n", epoch);
}

for (int i = 1; i <= iter; i++) {
double Z_sigmoid[100][21] = { 0, };
double Y[100][10] = { 0, };
double Y_sigmoid[100][10] = { 0, };


int sum;
setBatch(i, SIZE_SAMPLES_train);


//while (1) {
for (int batch = 0; batch < 100; batch++) {

//forward
for (int k = 1; k < 21; k++) {
double Z = 0;
for (int j = 0; j < 101; j++) {
Z += batch_x[batch][j] * V[j][k];
}

Z_sigmoid[batch][k] = sigmoid(Z);
}
Z_sigmoid[batch][0] = 1;

for (int k = 0; k < 10; k++) {
for (int j = 0; j < 21; j++) {
Y[batch][k] += Z_sigmoid[batch][j] * W[j][k];
}
Y_sigmoid[batch][k] = sigmoid(Y[batch][k]);

}
}
for (int batch = 0; batch < 100; batch++) {
// backpropagation
double deriv_W[100][10] = { 0, };
double deriv_V[100][21] = { 0, };
double aver_deriv_W[21][10] = { 0, };
double aver_deriv_Z[101][21] = { 0, };


// out - target 오류율 계산
for (int m = 0; m < 10; m++) {
//printf("%d", m);
deriv_W[batch][m] = (batch_y[batch][m] - Y_sigmoid[batch][m]) * (1 - Y_sigmoid[batch][m]) * Y_sigmoid[batch][m];
//printf("%lf ", deriv_W[batch][m]);
//for (int q = 0; q < 21; q++) {
//	aver_deriv_W[q][m] += deriv_W[batch][m] * Z_sigmoid[batch][q];
//}
}

// hidden의 오류율 계산
//printf("\n");
for (int m = 0; m < 21; m++) {
for (int n = 0; n < 10; n++) {
deriv_V[batch][m] = deriv_W[batch][n] * (1 - Z_sigmoid[batch][m]) * Z_sigmoid[batch][m];
}

//for (int q = 0; q < 101; q++) {
//	aver_deriv_Z[q][m] += deriv_V * batch_x[batch][q];

//}

}

for (int q = 0; q < 21; q++) {
for (int m = 0; m < 10; m++) {
//aver_deriv_W[q][m] = (double)aver_deriv_W[q][m] / BATCH_SIZE;
W[q][m] += ALPHA * aver_deriv_W[q][m];
}

}

for (int q = 0; q < 101; q++) {
for (int m = 0; m < 21; m++) {
//aver_deriv_Z[q][m] = (double)aver_deriv_Z[q][m] / BATCH_SIZE;
V[q][m] += ALPHA * aver_deriv_Z[q][m];
}
}
//printf("\n");




//printf("\n");
//batch++;
/*
if (batch == 99) {
break;
}
else if (batch < 90) {
batch += 10;
}
else {
batch += (batch % 10)+1;
}
/



			}

		}

		correct = 0;
		for (int i = 0; i < iter; i++) {
			double Z_sigmoid[100][21] = { 0, };

			double Y[100][10] = { 0, };
			double Y_sigmoid[100][10] = { 0, };
			double compare_y[100][10] = { 0, };

			double max[100] = { 0, };

			for (int batch = 0; batch < BATCH_SIZE; batch++) {
				for (int k = 1; k < 21; k++) {
					double Z = 0;
					for (int j = 0; j < 101; j++) {
						Z += batch_x[batch][j] * V[j][k];
					}

					Z_sigmoid[batch][k] = sigmoid(Z);
				}
				Z_sigmoid[batch][0] = 1;

				for (int k = 0; k < 10; k++) {
					for (int j = 0; j < 21; j++) {
						Y[batch][k] += Z_sigmoid[batch][j] * W[j][k];
					}
					Y_sigmoid[batch][k] = sigmoid(Y[batch][k]);

				}


				// one hot encoding
				for (int k = 0; k < 10; k++) {

					if (k == 0) {
						max[batch] = Y_sigmoid[batch][k];
					}
					else {
						if (max[batch] < Y_sigmoid[batch][k]) {
							max[batch] = Y_sigmoid[batch][k];
						}
					}
				}

				// compare target - output(one hot encoding)
				for (int k = 0; k < 10; k++) {
					if (max[batch] == Y_sigmoid[batch][k]) {
						compare_y[batch][k] = 1;
					}
					else {
						compare_y[batch][k] = 0;
					}
				}

				//한 batch 정확도
				for (int label = 0; label < 10; label++) {
					if (batch_y[batch][label] == 1 && compare_y[batch][label] == 1) {
						correct++;
					}
				}
			}
		}

		double percent = (double)correct / 40;


		if (epoch % 100 == 0) {
			printf("[%d Epoch] %lf\n", epoch, percent);
		}

		if (percent >= input_accuracy) {
			printf("[Train Accuracy] %lf\n", percent);
			break;
		}
		epoch++;
	}


	readTrainFile("C:\\Users\\210.117.128.200\\Desktop\\test.txt", SIZE_SAMPLES_test);

	iter = SIZE_CLASSES * SIZE_SAMPLES_test / BATCH_SIZE;

	int correct = 0;
	for (int i = 1; i <= iter; i++) {
		double Z[100][21] = { 0, };
		double Z_sigmoid[100][21] = { 0, };
		double Y[100][10] = { 0, };
		double Y_sigmoid[100][10] = { 0, };
		double compare_y[100][10] = { 0, };
		double max[100] = { 0, };

		setBatch(i, SIZE_SAMPLES_test);



		//forward
		for (int batch = 0; batch < 100; batch++) {

			//forward
			for (int k = 1; k < 21; k++) {
				double Z = 0;
				for (int j = 0; j < 101; j++) {
					Z += batch_x[batch][j] * V[j][k];
				}

				Z_sigmoid[batch][k] = sigmoid(Z);
			}
			Z_sigmoid[batch][0] = 1;

			for (int k = 0; k < 10; k++) {
				for (int j = 0; j < 21; j++) {
					Y[batch][k] += Z_sigmoid[batch][j] * W[j][k];
				}
				Y_sigmoid[batch][k] = sigmoid(Y[batch][k]);

			}


			// one hot encoding
			for (int k = 0; k < 10; k++) {

				if (k == 0) {
					max[batch] = Y_sigmoid[batch][k];
				}
				else {
					if (max[batch] < Y_sigmoid[batch][k]) {
						max[batch] = Y_sigmoid[batch][k];
					}
				}
			}

			// compare target - output(one hot encoding)
			for (int k = 0; k < 10; k++) {
				if (max[batch] == Y_sigmoid[batch][k]) {
					compare_y[batch][k] = 1;
				}
				else {
					compare_y[batch][k] = 0;
				}
			}

			//한 batch 정확도
			for (int label = 0; label < 10; label++) {
				if (batch_y[batch][label] == 1 && compare_y[batch][label] == 1) {
					correct++;
				}
			}
		}

		if (i == iter) {
			double percent = (double)correct / 20;
			printf("%lf\n", percent);
		}
	}

	system("pause");
	return 0;
}
*/





