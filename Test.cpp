#include <iostream>
#include <stdio.h>

#include "ClassificationVar.h"

int main()
{
	
	float data[4]={-200,0,22.6,19};

	int label;


	InitPredictModel();
	SvmClassification(data,label);
	printf("%d\n",label);
	destroySvmModel();

	return 0;
}
