#ifndef CKMAP_H
#define CKMAP_H

#include "ckfeature.h"
#include "ckrenderrule.h"
#include <vector>

using namespace std;

class CKMap {
public:
  CKMap();

  void loadSLD(const char *);

  void drawMap();

  void clear(); //清除Map对象中的数据，以准备加载新数据
  double *getEnvelop();

private:
  void loadGeoJSON(const char *path);

  void connectFeatSymb(); //把要素和符号关联起来

  CKFeature **pFeatures;
  int feature_size;
  vector<CKRenderRule *> pRules;
  double envelop[4];
};

#endif // CKMAP_H
