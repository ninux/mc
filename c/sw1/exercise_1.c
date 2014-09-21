#include <stdio.h>
#include <stdlib.h>

double far2cel(double far){
	return (far-32)/1.8;
}

int main(int args, char** argv){
	// check parameters
	if(args < 2){
		printf("no values given\n");
		return -1;
	}

	// prepare data structure
	int elements = args;
	double temp_f[elements];
	double temp_c[elements];

	// read temperature list and convert them
	int ctr = 0;
	for(ctr = 0; ctr < elements; ctr++){
		// convert the temperature
		temp_f[ctr] = atof(argv[ctr]);
		temp_c[ctr] = (temp_f[ctr] - 32)/1.8;
	}

	// print converted list
	printf("Temperatures in degree Celsius:\n\t");
	for(ctr = 1; ctr < elements; ctr++){
		printf("%f, ", temp_c[ctr]);
	}
	printf("\n");

	// exit
	return 0;
}
