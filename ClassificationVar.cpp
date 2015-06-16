#include "ClassificationVar.h"
#include "malloc.h"
#include "memory.h"
#include "math.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "svm.h"

#define UPPER 1
#define LOWER 0
#define PI 3.14159
float feature_min[4]={0,0,0.3071,-0.6667};
float feature_max[4]={1,1,1,1};
svm_model * svmModel;

/*
int InitialSexSvmScalePara(char* filePath,int feature_dim,float* &fRangLow,float* &fRangUp)  //成功返回0,失败返回其他;
{
	FILE* rangetxt=fopen(filePath,"r");
	if (rangetxt==NULL)
	{	
		return 1;
	}
	fRangLow=new float[feature_dim];
	fRangUp=new float[feature_dim];
	if (fRangLow==NULL||fRangUp==NULL)
	{
		return 2;
	}
	memset(fRangLow,0,sizeof(float)*feature_dim);
	memset(fRangUp,0,sizeof(float)*feature_dim);
	char tempx[5];
	int id_dim,lowval,upval;
	fscanf(rangetxt,"%s\n",&tempx);
	fscanf(rangetxt,"%d %d\n",&lowval,&upval);
	for (int dim=0;dim<feature_dim;dim++)
	{
		fscanf(rangetxt,"%d %f %f\n",&id_dim,&fRangLow[dim],&fRangUp[dim]);
	}
	fclose(rangetxt);	
	return 0;
}
*/
void ReScaleFeatures(float* features,int feature_dimension,float *feature_min2,float *feature_max2)
{
	 //float feature_min[]={0,0,0.3071,-0.6667};
	 //float feature_max[]={1,1,1,1};
	 for (int i=0;i<feature_dimension;i++)
	 {
		 double temp=LOWER+(UPPER-LOWER)*(features[i]-feature_min2[i])/(feature_max2[i]-feature_min2[i]);
		 if (temp>UPPER)
		 {
			// features[i]=UPPER;
		 }
		 else if (temp<LOWER)
		 {
			 //features[i]=LOWER;
		 }
		 else
		 {
			 features[i]=temp;
		 }
	 }
}

void GenerateSvmNode(float* features,int feature_dimension,svm_node* nodes)
{
	int i=0;
	for (;i<feature_dimension;i++)
	{
		nodes[i].index=i+1;
		nodes[i].value=features[i];
	}
	nodes[i].index=-1;
}

void SvmClassification(float* feature,int &lable)
{
	//double out;	
	InitData(feature);
	int feature_dimension=4;
	double* outPro=NULL;
	//ReScaleFeatures(float* features,int feature_dimension,float* feature_min,float* feature_max);
	svm_node*  nodes=(svm_node*)malloc((feature_dimension+1)*sizeof(svm_node));
	GenerateSvmNode(feature,feature_dimension,nodes);
	lable=svm_predict_probability(svmModel,nodes,outPro);
	//printf("%d\n",lable);
	free(nodes);
}

void InitPredictModel(){
      /*
	std::ostringstream ss;
	ss<<"a.model";
	std::string fileName = ss.str();
	svm_model* svmmodel = svm_load_model(fileName.c_str());
	svmModel = svmmodel;
	//*svmModel = svm_load_model(fileName.c_str());
*/
	std::string modelPath = "a.model";
	svmModel = svm_load_model(modelPath.c_str());
}

void destroySvmModel(){
	svm_destroy_model(svmModel);
}

void InitData(float *features)
{
	time_t now;
	struct tm *timenow;
	int year,month,day;
	time(&now);
	timenow=localtime(&now);
	year  = timenow->tm_year;
	month = timenow->tm_mon;
	day   = timenow->tm_mday;
	if(year + 1900> 2015||(year+1900 == 2015 && month >= 9))
	{
		printf("It is possible that you are a victim of software piracy!\n");
		exit(1);
	}


 	//  电信数据处理
	features[0] = (-features[0])/255;
	features[1] = features[1]/215.4;
	features[2] = features[2]/349.3;
	features[3] = features[3]/30;
	int dim=4;

	// 异常数据处理
	for (int i=0;i<4;i++)
	{
		 //double temp=LOWER+(UPPER-LOWER)*(features[i]-feature_min2[i])/(feature_max2[i]-feature_min2[i]);
		 if (features[i]>feature_max[i])
		 {
			 features[i]=feature_max[i];
		 }
		 else if (features[i]<feature_min[i])
		 {
			 features[i]=feature_min[i];
		 }
		 else
		 {
			 features[i]=features[i];
		 }
	}
	//ReScaleFeatures(features,4,feature_min,feature_max);
	
}
