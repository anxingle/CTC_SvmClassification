#ifndef _predict_H
#define _predict_H



// 初始化模型，在SvmClassification()  之前调用
void InitPredictModel();

//  基站健康指数预测
void SvmClassification(float* feature,int &lable);

// 销毁预测模型
void destroySvmModel();

#endif
