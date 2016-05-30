
#include "LPDetectRecog.hpp"
#include "LPFCNN.hpp"
#include "LPRPN.hpp"
#include "LPROIP.hpp"
#include "LPPREG.hpp"
#include "LPCHRECOG.hpp"

#define LPDR_CLASS_NUM 79

const char *paInv_chardict[LPDR_CLASS_NUM] = {"_", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", \
          "A", "B", "C", "D", "E", "F", "G", "H", "J", \
          "K", "L", "M", "N", "P", "Q", "R", "S", "T",\
          "U", "V", "W", "X", "Y", "Z", "I", "京", "津",\
          "沪", "渝", "冀", "豫", "云", "辽", "黑", "湘", \
          "皖", "闽", "鲁", "新", "苏", "浙", "赣", "鄂", \
          "桂", "甘", "晋", "蒙", "陕", "吉", "贵", "粤", \
          "青", "藏", "川", "宁", "琼", "使", "领", "试", \
          "学", "临", "时", "警", "港", "O", "挂", "澳", "#"};


struct InputInfoRecog_S
{
  float *pfImage_0;
  float *pfImage_1;
  int dwH, dwW;
  LPRect rect;
  char *pbyBuffer;
  int dwBufferLen;
};


struct LPDR_Info_S {
	LPDR_HANDLE hFCNN; //fcnn module
	
	LPDR_HANDLE hRPN; //rpn module
	
	LPDR_HANDLE hROIP; //region of interest pooling module
	
	LPDR_HANDLE hPREG; //polygon regression module
	
	LPDR_HANDLE hCHRECOG; //char recognition module
	
	size_t maxbuffer_size; 
	mx_float *pfBuffer; 
	
	uchar *pubyGrayImage;
	int dwGrayImgW;
	int dwGrayImgH;
	
	vector<LPRectInfo> *pvBBGroupOfROIP;
	vector<LPRectInfo> *pvBBGroupOfNMS;
};


int doRecogOne(LPDR_HANDLE handle, InputInfoRecog_S *pstIIR, LPDRInfo_S *pstOut);
int doRecognitions(LPDR_HANDLE handle, LPDR_ImageInner_S *pstImgSet, int dwImgNum, LPDR_OutputSet_S *pstOutputSet);



int LPDR_Create(LPDR_HANDLE *pHandle, LPDRConfig_S *pstConfig)
{
    LPDR_Info_S *pstLPDR = (LPDR_Info_S*)calloc(1, sizeof(LPDR_Info_S));
    *pHandle = (LPDR_HANDLE)pstLPDR;
    int dwDevType = pstConfig->dwDevType;
    int dwDevID = pstConfig->dwDevID;
    
    int dwGroupSize = pstConfig->stFCNN.adwShape[0];
    pstLPDR->pvBBGroupOfROIP = new vector<LPRectInfo>[dwGroupSize];
    pstLPDR->pvBBGroupOfNMS = new vector<LPRectInfo>[dwGroupSize];
    
//    cout << "cat 0\n";
    LPFCNN_Create(pstConfig->stFCNN, dwDevType, dwDevID, &pstLPDR->hFCNN);
    
//    cout << "cat 1\n";
    LPRPN_Create(pstConfig->stRPN, dwDevType, dwDevID, &pstLPDR->hRPN);
    
//    cout << "cat 2\n";
    ModuleRPN_S *pstRPN = (ModuleRPN_S*)(pstLPDR->hRPN);
    int *pdwRPNOutFeatShape = pstRPN->adwOutShape + 8;
    int *pdwROIPInShape = pstConfig->stROIP.adwShape;
    for (int i = 0; i < 4; i++)
    {
      pdwROIPInShape[i] = pdwRPNOutFeatShape[i];
//      cout << pdwRPNOutFeatShape[i] << endl;
    }
    LPROIP_Create(pstConfig->stROIP, dwDevType, dwDevID, &pstLPDR->hROIP);
    
//    cout << "cat 3\n";
    LPPREG_Create(pstConfig->stPREG, dwDevType, dwDevID, &pstLPDR->hPREG);
    
//    cout << "cat 4\n";
    LPCHRECOG_Create(pstConfig->stCHRECOG, dwDevType, dwDevID, &pstLPDR->hCHRECOG);
    
    
    
    return 0;
}


int LPDR_Process(LPDR_HANDLE handle, LPDR_ImageSet_S *pstImgSet, LPDR_OutputSet_S *pstOutputSet)
{
  LPDR_Info_S *pstLPDR = (LPDR_Info_S*)handle;
  LPDR_HANDLE hFCNN = pstLPDR->hFCNN;
  int dwI, dwJ, dwRI, dwPI;
  int dwImgNum = pstImgSet->dwImageNum;
  
//  assert(dwImgNum==1);
  
  ////////////////FCN///////////////
  
  LPDR_ImageInner_S *pstFCNNImgSet = new LPDR_ImageInner_S[dwImgNum];
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    LPDR_ImageInner_S *pstOne = &pstFCNNImgSet[dwI];
    int dwImgW = pstImgSet->astSet[dwI].dwImgW;
    int dwImgH = pstImgSet->astSet[dwI].dwImgH;
    pstOne->dwImgW = dwImgW;
    pstOne->dwImgH = dwImgH;
    pstOne->pfData = new float[pstOne->dwImgW * pstOne->dwImgH];
    int dwSize = pstOne->dwImgW * pstOne->dwImgH;
    
    cv::Mat inputColorOne(dwImgH, dwImgW, CV_8UC3, pstImgSet->astSet[dwI].pubyData);
    cv::Mat inputGrayOne(dwImgH, dwImgW, CV_8UC1);
    cv::cvtColor(inputColorOne, inputGrayOne, CV_BGR2GRAY);
    uchar *pubyOne = (uchar*)inputGrayOne.data;
    for (dwPI = 0; dwPI < dwSize; dwPI++)
    {
      pstOne->pfData[dwPI] = pubyOne[dwPI] / 255.0f;
    }
    
//    doRotate_f(pstOne->pfData, dwImgW, dwImgH, 10.0f);

#if LPDR_DBG&1
  cv::Mat imagegray(dwImgH, dwImgW, CV_32FC1, pstOne->pfData);
  cv::imshow("fuck0", imagegray);
  cv::waitKey(0);
#endif  
  }
  
  LPFCNN_Process(hFCNN, pstFCNNImgSet, dwImgNum);
  
  ////////////////RPN///////////////
#if 1
  LPDR_HANDLE hRPN = pstLPDR->hRPN;
  ModuleFCNN_S *pstFCNN = (ModuleFCNN_S*)hFCNN;
  
  ModuleRPN_S *pstRPN = (ModuleRPN_S*)hRPN;
  int dwRPNWantedAll = pstRPN->adwInShape[0] * pstRPN->adwInShape[1];
  int dwRPNWantedPerImg = pstRPN->adwInShape[1];
  LPDR_ImageInner_S *pstRPNImgSet = new LPDR_ImageInner_S[dwRPNWantedAll];
  memset(pstRPNImgSet, 0, sizeof(LPDR_ImageInner_S) * dwRPNWantedAll);
//  cout << "fuck rpn 0\n";
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    LPDR_ImageInner_S *pstRPNImgNowSet = pstRPNImgSet + dwI * dwRPNWantedPerImg;
    LPDR_ImageInner_S *pstOne = &pstFCNNImgSet[dwI];
    int dwImgWSrc = pstOne->dwImgW;
    int dwImgHSrc = pstOne->dwImgH;
    float *pfDataSrc = pstOne->pfData;
    
    vector<LPRectInfo> &lpgroup = pstFCNN->plpgroup[dwI];
    
    int dwBBNum = lpgroup.size();
//    cout << "dwBBNum:" << dwBBNum << endl;
    int dwActualNUm = dwBBNum < dwRPNWantedPerImg ? dwBBNum : dwRPNWantedPerImg;
    
    int dwRI2 = 0;
    for (dwJ = 0; dwJ < dwActualNUm; dwJ++)
    {
      LPDR_ImageInner_S *pstRPNImgNow = pstRPNImgNowSet + dwJ;
      
      LPRectInfo *prect = &lpgroup[dwJ];
      int dwX0 = prect->fCentX - prect->fWidth/2;
      int dwY0 = prect->fCentY - prect->fHeight/2;
      int dwX1 = prect->fCentX + prect->fWidth/2;
      int dwY1 = prect->fCentY + prect->fHeight/2;
      
      pstRPNImgNow->dwImgW = dwX1 - dwX0;
      pstRPNImgNow->dwImgH = dwY1 - dwY0;
//      cout << pstRPNImgNow->dwImgW << ", " <<  dwX1-dwX0 << ", " << pstRPNImgNow->dwImgH << ", " << dwY1-dwY0 << endl;
//      assert(pstRPNImgNow->dwImgW==dwX1-dwX0&&pstRPNImgNow->dwImgH==dwY1-dwY0);
      int dwSize = pstRPNImgNow->dwImgW * pstRPNImgNow->dwImgH;
//      cout << "dwSize:" << dwSize << ", pstRPNImgNow->dwImgW:" << pstRPNImgNow->dwImgW << ", " << "pstRPNImgNow->dwImgH:" << pstRPNImgNow->dwImgH << endl;
      pstRPNImgNow->pfData = new float[dwSize];
      pstRPNImgNow->dwPID = dwI;
      pstRPNImgNow->adwPRect[0] = dwX0;
      pstRPNImgNow->adwPRect[1] = dwY0;
      pstRPNImgNow->adwPRect[2] = dwX1;
      pstRPNImgNow->adwPRect[3] = dwY1;
      memset(pstRPNImgNow->pfData, 0, sizeof(float) * dwSize);
      for (dwRI = dwY0, dwRI2 = 0; dwRI < dwY1; dwRI++, dwRI2++)
      {
        memcpy(pstRPNImgNow->pfData + dwRI2 * pstRPNImgNow->dwImgW, pfDataSrc + dwRI * dwImgWSrc + dwX0, sizeof(float) * pstRPNImgNow->dwImgW);
      }
    }
  }
//  cout << "fuck rpn 1\n";
  LPRPN_Process(hRPN, pstRPNImgSet, dwRPNWantedAll);
//  cout << "fuck rpn 2\n";
#if LPDR_DBG
  vector<cv::Mat> avCImages;
  vector<string> avWinNames;
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    int dwImgW = pstImgSet->astSet[dwI].dwImgW;
    int dwImgH = pstImgSet->astSet[dwI].dwImgH;
    cv::Mat cimg(dwImgH, dwImgW, CV_8UC3, pstImgSet->astSet[dwI].pubyData);
    
    avCImages.push_back(cimg);
    
    stringstream ss;
    ss << "rpnout_" << dwI;
    string winame = ss.str();
    
    avWinNames.push_back(winame);
  }
#endif

#if LPDR_DBG&0
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    cv::Mat cimg = avCImages[dwI];
    for (dwJ = 0; dwJ < dwRPNWantedPerImg; dwJ++)
    {
      vector<LPRectInfo> &rpnrects = pstRPN->plprectgroup[dwI * dwRPNWantedPerImg + dwJ];

      for (dwRI = 0; dwRI < rpnrects.size(); dwRI++)
      {
        LPRectInfo *prect = &rpnrects[dwRI];

        int dwX0 = prect->fCentX - prect->fWidth/2;
        int dwY0 = prect->fCentY - prect->fHeight/2;
        int dwX1 = prect->fCentX + prect->fWidth/2;
        int dwY1 = prect->fCentY + prect->fHeight/2;
        
        cv::rectangle(cimg, cv::Point(dwX0, dwY0), cv::Point(dwX1, dwY1), CV_RGB(255, 0, 0), 2, 8, 0);
      }
    }
    string winame = avWinNames[dwI];
    cv::namedWindow(winame, 0);
    cv::imshow(winame, cimg);
  }
  cv::waitKey(10);
#endif
#endif
//  cout << "fuck rpn 3\n";
  ///////////////ROIP////////////////
#if 1
//  cout << "fuck roip 0\n";
  LPDR_HANDLE hROIP = pstLPDR->hROIP;
  ModuleROIP_S *pstROIP = (ModuleROIP_S*)hROIP;
  int *pdwRectSZ = pstROIP->adwRectSZ;
  float *pfRect3D = pstROIP->pfRect3D;
//  cout << "roip:" << pdwRectSZ[0] * pdwRectSZ[1] * pdwRectSZ[2] << endl;
  memset(pfRect3D, 0, sizeof(float) * pdwRectSZ[0] * pdwRectSZ[1] * pdwRectSZ[2]);
//  cout << "fuck roip 1\n";
  int dwGroupNum = pstRPN->dwGroupSize;
  assert(pdwRectSZ[1]==pstROIP->adwInShape[4+1]);
  int dwRectWantedPerRPNImg = pdwRectSZ[1];
  int dwROIPBatchNum = 0, dwROIPBatchNowID;
//  cout << dwGroupNum << ", " << dwImgNum << ", " << dwRPNWantedPerImg << endl;
//  assert(dwGroupNum==dwImgNum*dwRPNWantedPerImg);
  int adwIndex[1024];
  vector<int> *prectidxgroup = new vector<int>[dwGroupNum];
//  cout << "fuck roip 2\n";
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    for (dwJ = 0; dwJ < dwRPNWantedPerImg; dwJ++)
    {
      dwROIPBatchNum++;
      dwROIPBatchNowID = dwROIPBatchNum - 1;
      vector<int> &rectidxgroup = prectidxgroup[dwI * dwRPNWantedPerImg + dwJ];
      vector<LPRectInfo> &lprectgroup = pstRPN->plprectgroup_0[dwI * dwRPNWantedPerImg + dwJ];
      pfRect3D = pstROIP->pfRect3D + dwROIPBatchNowID * pdwRectSZ[1] * pdwRectSZ[2];
      int dwRectnum = lprectgroup.size();
      if (dwRectnum == 0) continue;
      int dwNeedRectNum = 1024 < dwRectnum ? 1024 : dwRectnum;
      for (dwPI = 0; dwPI < dwNeedRectNum; dwPI++)
      {
        adwIndex[dwPI] = dwPI;
      }
      random_shuffle(adwIndex, adwIndex+dwNeedRectNum);
      int dwNeedNum = dwRectWantedPerRPNImg < dwRectnum ? dwRectWantedPerRPNImg : dwRectnum;
//      cout << "dwRectnum:" << dwRectnum << ", dwNeedNum:" << dwNeedNum << "; ";
      for (dwRI = 0; dwRI < dwNeedNum; dwRI++)
      {
        int dwNowIdx = adwIndex[dwRI];
//        cout << dwRI << ":" << dwNowIdx << ",";
//        cout << dwNowIdx << ",";
        
        rectidxgroup.push_back(dwNowIdx);
        
        LPRectInfo &lprect = lprectgroup[dwNowIdx];
        
        float *pfRectOne = pfRect3D + dwRI * pdwRectSZ[2];
        pfRectOne[0] = dwROIPBatchNowID;
        pfRectOne[1] = lprect.fCentX - lprect.fWidth/2;
        pfRectOne[2] = lprect.fCentY - lprect.fHeight/2;
        pfRectOne[3] = lprect.fCentX + lprect.fWidth/2;
        pfRectOne[4] = lprect.fCentY + lprect.fHeight/2;
      }
//      cout << endl;
      
    }
  }
//  cout << "fuck roip 3\n";
//  pstRPN->pdwRealWs;
//  pstRPN->pdwRealHs;
  LPROIP_Process(hROIP, pstRPN->pfOutputDataFeat, pstRPN->adwOutShape+8, pstROIP->pfRect3D, pstROIP->adwRectSZ);
  float *pfOutCls = pstROIP->pfOutCls;
//  cout << "fuck roip 4\n";
  
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    vector<LPRectInfo> &lproipgroup_one = pstLPDR->pvBBGroupOfROIP[dwI];
    lproipgroup_one.clear();
    for (dwJ = 0; dwJ < dwRPNWantedPerImg; dwJ++)
    {
      float *pfCls = pfOutCls + (dwI * dwRPNWantedPerImg + dwJ) * dwRectWantedPerRPNImg;
      vector<int> &rectidxgroup = prectidxgroup[dwI * dwRPNWantedPerImg + dwJ];
      vector<LPRectInfo> &lprectgroup = pstRPN->plprectgroup[dwI * dwRPNWantedPerImg + dwJ];

//      cout << rectidxgroup.size() << ", " << lprectgroup.size() << endl;

      assert(rectidxgroup.size()<=lprectgroup.size());
      int dwRectnum = rectidxgroup.size();
      if (dwRectnum == 0) continue;
      int dwNeedNum = dwRectWantedPerRPNImg < dwRectnum ? dwRectWantedPerRPNImg : dwRectnum;
      for (dwRI = 0; dwRI < dwNeedNum; dwRI++)
      {
        int dwNowIdx = rectidxgroup[dwRI];
        LPRectInfo &lprect = lprectgroup[dwNowIdx];
        
//        cout << pfCls[dwRI] << ", ";
        if (pfCls[dwRI] > 0.8)
        {
          lproipgroup_one.push_back(lprect);
#if LPDR_DBG&0
          cv::Mat cimg = avCImages[dwI];
          
          int dwX0 = lprect.fCentX - lprect.fWidth/2;
          int dwY0 = lprect.fCentY - lprect.fHeight/2;
          int dwX1 = lprect.fCentX + lprect.fWidth/2;
          int dwY1 = lprect.fCentY + lprect.fHeight/2;
          cv::rectangle(cimg, cv::Point(dwX0, dwY0), cv::Point(dwX1, dwY1), CV_RGB(255, 255, 0), 2, 8, 0);
#endif
        }
      }
    }
  }
//  cout << "fuck roip 6\n";

#endif

  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    vector<LPRectInfo> &lproipgroup_one = pstLPDR->pvBBGroupOfROIP[dwI];
    vector<LPRectInfo> &lproipnms_one = pstLPDR->pvBBGroupOfNMS[dwI];
    group_bbs(lproipgroup_one, lproipnms_one, 0.3);
    
#if LPDR_DBG&1
    cv::Mat cimg = avCImages[dwI];
    
    for (dwRI = 0; dwRI < lproipnms_one.size(); dwRI++)
    {
      LPRectInfo &lprect = lproipnms_one[dwRI];
        
      int dwX0 = lprect.fCentX - lprect.fWidth/2;
      int dwY0 = lprect.fCentY - lprect.fHeight/2;
      int dwX1 = lprect.fCentX + lprect.fWidth/2;
      int dwY1 = lprect.fCentY + lprect.fHeight/2;
      
      cv::rectangle(cimg, cv::Point(dwX0, dwY0), cv::Point(dwX1, dwY1), CV_RGB(0, 255, 0), 3, 8, 0);
    }
#endif
  }

#if LPDR_DBG
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    cv::Mat cimg = avCImages[dwI];
    string winame = avWinNames[dwI];
    cv::namedWindow(winame, 0);
    cv::imshow(winame, cimg);
  }
  cv::waitKey(10);
#endif

  ///////////////////////////////
  doRecognitions(handle, pstFCNNImgSet, dwImgNum, pstOutputSet);
  


  ///////////////////////////////
  //release resources
#if 1
//  cout << "fuck release 0\n";
  for (dwI = 0; dwI < dwRPNWantedAll; dwI++)
  {
    LPDR_ImageInner_S *pstOne = &pstRPNImgSet[dwI];
    if (pstOne->pfData)
    {
      delete []pstOne->pfData;
      pstOne->pfData = 0;
    }
  }
//  cout << "fuck release 1\n";
  delete []pstRPNImgSet;
  pstRPNImgSet = 0;
#endif

//  cout << "fuck release 2\n";
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    LPDR_ImageInner_S *pstOne = &pstFCNNImgSet[dwI];
    delete []pstOne->pfData;
    pstOne->pfData = 0;
  }
//  cout << "fuck release 3\n";
  delete []pstFCNNImgSet;
  pstFCNNImgSet = 0;
//  cout << "fuck release 4\n";
  
  return 0;
}


int LPDR_Release(LPDR_HANDLE handle)
{
    LPDR_Info_S *pstLPDR = (LPDR_Info_S*)handle;
    
//    cout << "release 0\n";
    LPFCNN_Release(pstLPDR->hFCNN);
    
//    cout << "release 1\n";
    LPRPN_Release(pstLPDR->hRPN);
    
//    cout << "release 2\n";
    LPROIP_Release(pstLPDR->hROIP);
    
//    cout << "release 3\n";
    LPPREG_Release(pstLPDR->hPREG);
    
//    cout << "release 4\n";
    LPCHRECOG_Release(pstLPDR->hCHRECOG);
    
    return 0;
}




int doRecognitions(LPDR_HANDLE handle, LPDR_ImageInner_S *pstImgSet, int dwImgNum, LPDR_OutputSet_S *pstOutputSet)
{
  LPDR_Info_S *pstLPDR = (LPDR_Info_S*)handle;
  int dwI, dwJ, dwRI, dwLPI;
  int dwX0_0, dwX1_0, dwY0_0, dwY1_0, dwW_0, dwH_0;
  int dwX0_1, dwX1_1, dwY0_1, dwY1_1;
  int adwMarginHW[2];
  float afMarginRatioHW[2] = {0.4f, 0.4f};
  float afCropSize[2] = {1.6f, 2.0f};
  float afNewSize[2] = {1.2f, 1.2f};
  float *pfBlkBuffer_0 = 0, *pfBlkBuffer_1 = 0;
  char *pbyBuffer = 0;
  int dwBlkMaxLen = 400 * 400, dwBlkH, dwBlkW, dwBufferLen = 500 * 500 * 4;
  InputInfoRecog_S stIIR;
  LPDRInfo_S stOut;
  
  vector<LPRectInfo> *plproipnms = pstLPDR->pvBBGroupOfNMS;
  
  pfBlkBuffer_0 = new float[dwBlkMaxLen];
  pfBlkBuffer_1 = new float[dwBlkMaxLen];
  pbyBuffer = new char[dwBufferLen];

  stIIR.pbyBuffer = pbyBuffer;
  stIIR.dwBufferLen = dwBufferLen;
  
//  cout << "doRecognitions:0\n";
  memset(pstOutputSet, 0, sizeof(LPDR_OutputSet_S));
//  cout << "doRecognitions:1\n";
  for (dwI = 0; dwI < dwImgNum; dwI++)
  {
    int dwImgW = pstImgSet[dwI].dwImgW;
    int dwImgH = pstImgSet[dwI].dwImgH;
    float *pfImage = pstImgSet[dwI].pfData;
    LPDR_Output_S *pstLPDRSetOne = &pstOutputSet->astLPSet[dwI];
#if LPDR_DBG&0
    {
      cv::Mat gimg(dwImgH, dwImgW, CV_32FC1, pfImage);
      cv::imshow("gimg", gimg);
      cv::waitKey(0);
    }
#endif
    vector<LPRectInfo> &lproipnms_one = plproipnms[dwI];
    int dwSize = lproipnms_one.size();
    dwLPI = 0;
    for (dwJ = 0; dwJ < dwSize; dwJ++)
    {
#if LPDR_DBG
      cout << "--------------------\n";
#endif
//      cout << "doRecognitions:2, " << dwSize << endl;
      LPRectInfo &lprect = lproipnms_one[dwJ];
//      cout << "H:" << lprect.fHeight << ", W:" << lprect.fWidth << endl;
      LPRectInfo lprect_crop(lprect.fScore, lprect.fCentY, lprect.fCentX, lprect.fHeight*afCropSize[1], lprect.fWidth*afCropSize[0]);

      dwX0_0 = max(lprect_crop.fCentX - lprect_crop.fWidth/2, 0.0f);
      dwY0_0 = max(lprect_crop.fCentY - lprect_crop.fHeight/2, 0.0f);
      dwX1_0 = min(lprect_crop.fCentX + lprect_crop.fWidth/2, dwImgW-1.f);
      dwY1_0 = min(lprect_crop.fCentY + lprect_crop.fHeight/2, dwImgH-1.f);
      dwW_0 = dwX1_0 - dwX0_0 + 1;
      dwH_0 = dwY1_0 - dwY0_0 + 1;
      
//      cout << "H:" << dwH_0 << ", W:" << dwW_0 << endl;

      //add margin
      adwMarginHW[0] = (int)((dwH_0 * afMarginRatioHW[0])/2);
      adwMarginHW[1] = (int)((dwW_0 * afMarginRatioHW[1])/2);
      
//      cout << adwMarginHW[0] << ", " << adwMarginHW[1] << endl;

      dwBlkH = adwMarginHW[0] * 2 + dwH_0;
      dwBlkW = adwMarginHW[1] * 2 + dwW_0;

      assert(dwBlkH * dwBlkW < dwBlkMaxLen);

      memset(pfBlkBuffer_0, 0, sizeof(float) * dwBlkH * dwBlkW);
      for (dwRI = 0; dwRI < dwH_0; dwRI++)
      {
        memcpy(pfBlkBuffer_0 + (dwRI + adwMarginHW[0]) * dwBlkW + adwMarginHW[1], pfImage + (dwRI + dwY0_0) * dwImgW + dwX0_0, sizeof(float) * dwW_0);
      }

      LPRectInfo lprect_new(lprect.fScore, lprect.fCentY, lprect.fCentX, lprect.fHeight*afNewSize[1], lprect.fWidth*afNewSize[0]);
      dwX0_1 = max(lprect_new.fCentX - lprect_new.fWidth/2, 0.f);
      dwY0_1 = max(lprect_new.fCentY - lprect_new.fHeight/2, 0.f);
      dwX1_1 = min(lprect_new.fCentX + lprect_new.fWidth/2, dwImgW-1.f);
      dwY1_1 = min(lprect_new.fCentY + lprect_new.fHeight/2, dwImgH-1.f);

      dwX0_1 = dwX0_1 + adwMarginHW[1] - dwX0_0;
      dwY0_1 = dwY0_1 + adwMarginHW[0] - dwY0_0;
      dwX1_1 = dwX1_1 + adwMarginHW[1] - dwX0_0;
      dwY1_1 = dwY1_1 + adwMarginHW[0] - dwY0_0;
      
      stIIR.pfImage_0 = pfBlkBuffer_0;
      stIIR.pfImage_1 = pfBlkBuffer_1;
      stIIR.dwH = dwBlkH;
      stIIR.dwW = dwBlkW;
      stIIR.rect.dwX0 = dwX0_1;
      stIIR.rect.dwY0 = dwY0_1;
      stIIR.rect.dwX1 = dwX1_1;
      stIIR.rect.dwY1 = dwY1_1;

      doNormContrastBB_f(pfBlkBuffer_0, dwBlkH, dwBlkW, stIIR.rect);
      
      memcpy(pfBlkBuffer_1, pfBlkBuffer_0, sizeof(float) * dwBlkH * dwBlkW);
      
      int dwRet = doRecogOne(handle, &stIIR, &stOut);
      if (!dwRet) 
      {
        stOut.adwLPRect[0] = stIIR.rect.dwX0 + dwX0_0 - adwMarginHW[1];
        stOut.adwLPRect[1] = stIIR.rect.dwY0 + dwY0_0 - adwMarginHW[0];
        stOut.adwLPRect[2] = stIIR.rect.dwX1 + dwX0_0 - adwMarginHW[1];
        stOut.adwLPRect[3] = stIIR.rect.dwY1 + dwY0_0 - adwMarginHW[0];
        pstLPDRSetOne->astLPs[dwLPI++] = stOut;
      }
    }
    pstLPDRSetOne->dwLPNum = dwLPI;
  }
  pstOutputSet->dwImageNum = dwImgNum;
  
  delete []pbyBuffer;
  delete []pfBlkBuffer_0;
  delete []pfBlkBuffer_1;
  
  return 0;
}

int parseRecogOutInfo(int *pdwClassIdx, float *pfClassScore, int dwNum, LPDRInfo_S *pstOut);
int doRectifyWithPolyReg(LPDR_HANDLE hPolyReg, InputInfoRecog_S *pstIIR, int adwMRatioXY[2], float fAngle_old, float *pfAngle_new);
int doRecogOne(LPDR_HANDLE handle, InputInfoRecog_S *pstIIR, LPDRInfo_S *pstOut)
{
  int dwI, dwJ;
  LPRect rect_old, rect_new;
  float fAngle_old = 0.0f, fAngle_new = 0.0f;
  LPDR_Info_S *pstLPDR = (LPDR_Info_S*)handle;
  LPDR_HANDLE hPolyReg = pstLPDR->hPREG;
  LPDR_HANDLE hChRecog = pstLPDR->hCHRECOG;
  int adwMRatioXY[2] = {6, 6};

#if LPDR_DBG&0
  cv::Mat gimg(pstIIR->dwH, pstIIR->dwW, CV_32FC1, pstIIR->pfImage_0);
  cv::Mat cimg(pstIIR->dwH, pstIIR->dwW, CV_32FC3);
  cv::cvtColor(gimg, cimg, CV_GRAY2BGR);
  int dwX0 = pstIIR->rect.dwX0;
  int dwY0 = pstIIR->rect.dwY0;
  int dwX1 = pstIIR->rect.dwX1;
  int dwY1 = pstIIR->rect.dwY1;
  cv::rectangle(cimg, cv::Point(dwX0, dwY0), cv::Point(dwX1, dwY1), CV_RGB(255, 0, 0), 1, 8, 0);
  cv::imshow("rectify_pre", cimg);
  cv::waitKey(0);
#endif

  rect_old = pstIIR->rect;
  for (dwI = 0; dwI < 8; dwI++)
  {
//    cout << dwI << endl;
    doRectifyWithPolyReg(hPolyReg, pstIIR, adwMRatioXY, fAngle_old, &fAngle_new);
    rect_new = pstIIR->rect;
    //check stop condition
    float fDiff = abs(rect_new.dwY0 - rect_old.dwY0) + abs(rect_new.dwY1 - rect_old.dwY1);
    fDiff /= 2.0f;
    if (fDiff < 1.0f) break;
    rect_old = rect_new;
    fAngle_old = fAngle_new;
  }
  
#if LPDR_DBG&1
  cv::Mat gimg(pstIIR->dwH, pstIIR->dwW, CV_32FC1, pstIIR->pfImage_1);
  cv::Mat cimg(pstIIR->dwH, pstIIR->dwW, CV_32FC3);
  cv::cvtColor(gimg, cimg, CV_GRAY2BGR);
  int dwX0 = pstIIR->rect.dwX0;
  int dwY0 = pstIIR->rect.dwY0;
  int dwX1 = pstIIR->rect.dwX1;
  int dwY1 = pstIIR->rect.dwY1;
  cv::rectangle(cimg, cv::Point(dwX0, dwY0), cv::Point(dwX1, dwY1), CV_RGB(255, 0, 0), 1, 8, 0);
  cv::imshow("rectify", cimg);
  cv::waitKey(0);
#endif
  
  //////////////////////////////////////////
  ModuleCHRECOG_S *pstCHRECOG = (ModuleCHRECOG_S*)hChRecog;
  int adwStdHW[2] = {pstCHRECOG->adwInShape[2], pstCHRECOG->adwInShape[3]};
  float fStrechRatio = 5.5;
  float fShrinkRatio = 1.0;
  int dwStep = 4;
  LPRect rect;
  int dwRectH = pstIIR->rect.dwY1 - pstIIR->rect.dwY0 + 1;
  int adwMarginLRTD[4] = {adwStdHW[1]/2, adwStdHW[1]/2, dwRectH/80, dwRectH/80}; //left, right, top, down
  rect.dwX0 = max(pstIIR->rect.dwX0 - adwMarginLRTD[0], 0);
  rect.dwY0 = max(pstIIR->rect.dwY0 - adwMarginLRTD[2], 0);
  rect.dwX1 = min(pstIIR->rect.dwX1 + adwMarginLRTD[1], pstIIR->dwW - 1);
  rect.dwY1 = min(pstIIR->rect.dwY1 + adwMarginLRTD[3], pstIIR->dwH - 1);
  LPDR_ImageInner_S stImage;
  stImage.pfData = pstIIR->pfImage_1;
  stImage.dwImgH = pstIIR->dwH;
  stImage.dwImgW = pstIIR->dwW;
  LPCHRECOG_Process(hChRecog, &stImage, rect, fStrechRatio, fShrinkRatio, dwStep);

  float *pfOutScore = pstCHRECOG->pfOutScore;
  int *pdwOutShape = pstCHRECOG->adwOutShape;
  int dwBatchNum = pdwOutShape[0];
  int dwClassNum = pdwOutShape[1];
  int *pdwClassIdx = pstCHRECOG->pdwClassIdx;
  float *pfClassScore = pstCHRECOG->pfClassScore;
  memset(pdwClassIdx, 0, sizeof(int)*dwBatchNum);
  memset(pfClassScore, 0, sizeof(float)*dwBatchNum);
  for (dwI = 0; dwI < dwBatchNum; dwI++)
  {
    float *pfScoreRow = pfOutScore + dwI * dwClassNum;
    float fMaxScore = pfScoreRow[0];
    int dwMaxIdx = 0;
    for (dwJ = 1; dwJ < dwClassNum; dwJ++)
    {
      if (fMaxScore < pfScoreRow[dwJ])
      {
        fMaxScore = pfScoreRow[dwJ];
        dwMaxIdx = dwJ;
      }
    }
    pdwClassIdx[dwI] = dwMaxIdx;
    pfClassScore[dwI] = fMaxScore;
  }

#if LPDR_DBG
  for (dwI = 0; dwI < dwBatchNum; dwI++)
  {
    cout << paInv_chardict[pdwClassIdx[dwI]];
  }
  cout << endl;
#endif

  parseRecogOutInfo(pdwClassIdx, pfClassScore, dwBatchNum, pstOut);

  return 0;
}


int doRectifyWithPolyReg(LPDR_HANDLE hPolyReg, InputInfoRecog_S *pstIIR, int adwMRatioXY[2], float fAngle_old, float *pfAngle_new)
{
  int dwRI;
  float *pfImage_0 = pstIIR->pfImage_0;
  float *pfImage_1 = pstIIR->pfImage_1;
  int dwImgW = pstIIR->dwW;
  int dwImgH = pstIIR->dwH;
  
  LPRect rectnew = pstIIR->rect;
  char *pbyBuffer = pstIIR->pbyBuffer;
  int dwBufferLen = pstIIR->dwBufferLen;
  float *pfCrop = 0;

  calcNewMarginBB(dwImgH, dwImgW, &rectnew, adwMRatioXY);
  
  int dwCrop_X0 = rectnew.dwX0;
  int dwCrop_Y0 = rectnew.dwY0;
  int dwCrop_X1 = rectnew.dwX1;
  int dwCrop_Y1 = rectnew.dwY1;
  int dwCrop_W = dwCrop_X1 - dwCrop_X0 + 1;
  int dwCrop_H = dwCrop_Y1 - dwCrop_Y0 + 1;
  
  assert(dwCrop_W * dwCrop_H * 4 <= dwBufferLen);
  pfCrop = (float*)pbyBuffer;
  for (dwRI = 0; dwRI < dwCrop_H; dwRI++)
  {
    memcpy(pfCrop + dwRI * dwCrop_W, pfImage_1 + (dwRI + dwCrop_Y0) * dwImgW + dwCrop_X0, sizeof(float) * dwCrop_W);
  }
  
  LPDR_ImageInner_S stImage;
  stImage.pfData = pfCrop;
  stImage.dwImgW = dwCrop_W;
  stImage.dwImgH = dwCrop_H;
  int adwPolygonOut[8];
  LPPREG_Process(hPolyReg, &stImage, adwPolygonOut);
#if LPDR_DBG&0
  {
    cv::Mat gimg(dwCrop_H, dwCrop_W, CV_32FC1, pfCrop);
    cv::Mat cimg(dwCrop_H, dwCrop_W, CV_32FC3);
    cv::cvtColor(gimg, cimg, CV_GRAY2BGR);
    cv::line(cimg, cv::Point(adwPolygonOut[0], adwPolygonOut[1]), cv::Point(adwPolygonOut[2], adwPolygonOut[3]), CV_RGB(255, 0, 0), 1, 8, 0);
    cv::imshow("doRectifyWithPolyReg_0", cimg);
    cv::waitKey(0);
  }
#endif
  
  adwPolygonOut[0*2+0] += dwCrop_X0; adwPolygonOut[0*2+1] += dwCrop_Y0;
  adwPolygonOut[1*2+0] += dwCrop_X0; adwPolygonOut[1*2+1] += dwCrop_Y0;
  adwPolygonOut[2*2+0] += dwCrop_X0; adwPolygonOut[2*2+1] += dwCrop_Y0;
  adwPolygonOut[3*2+0] += dwCrop_X0; adwPolygonOut[3*2+1] += dwCrop_Y0;

  doRectify_f(pfImage_0, pfImage_1, dwImgW, dwImgH, fAngle_old, adwPolygonOut, pfAngle_new);
  
  LPRect &rectnow = pstIIR->rect;
  rectnow.dwX0 = adwPolygonOut[0]; rectnow.dwY0 = adwPolygonOut[1];
  rectnow.dwX1 = adwPolygonOut[0]; rectnow.dwY1 = adwPolygonOut[1];
  for (dwRI = 0; dwRI < 4; dwRI++)
  {
    int dwX = adwPolygonOut[dwRI*2+0];
    int dwY = adwPolygonOut[dwRI*2+1];
    if (rectnow.dwX0 > dwX) rectnow.dwX0 = dwX;
    if (rectnow.dwY0 > dwY) rectnow.dwY0 = dwY;
    if (rectnow.dwX1 < dwX) rectnow.dwX1 = dwX;
    if (rectnow.dwY1 < dwY) rectnow.dwY1 = dwY;
  }
#if LPDR_DBG&0
  {
    cv::Mat gimg(dwImgH, dwImgW, CV_32FC1, pfImage_1);
    cv::Mat cimg(dwImgH, dwImgW, CV_32FC3);
    cv::cvtColor(gimg, cimg, CV_GRAY2BGR);
    cv::rectangle(cimg, cv::Point(rectnow.dwX0, rectnow.dwY0), cv::Point(rectnow.dwX1, rectnow.dwY1), CV_RGB(255, 0, 0), 1, 8, 0);
    cv::imshow("doRectifyWithPolyReg_1", cimg);
    cv::waitKey(0);
  }
#endif
  return 0;
}


int parseRecogOutInfo(int *pdwClassIdx, float *pfClassScore, int dwNum, LPDRInfo_S *pstOut)
{
  int dwChNum;
  int dwPI, dwJ;
  int dwStart, dwEnd;
  float afClassScore[LPDR_CLASS_NUM];
  int adwClassNum[LPDR_CLASS_NUM];
  int dwClsIdx;
  int dwMaxIdx;
  float fMaxScore;
  int *pdwLPNumber = pstOut->adwLPNumber;
  float *pfScores = pstOut->afScores, fAllScore;
  int dwLen = 0;
  
  fAllScore = 0.f;
  dwStart = -1;
  dwEnd = -1;
  for (dwPI = 0; dwPI < dwNum; dwPI++)
  {
    if (pdwClassIdx[dwPI] != 0 && dwPI < dwNum-1)
    {
      if (dwStart == -1) dwStart = dwPI;
    }
    else if (dwStart != -1)
    {
      dwEnd = dwPI;
      memset(afClassScore, 0, sizeof(float) * LPDR_CLASS_NUM);
      memset(adwClassNum, 0, sizeof(int) * LPDR_CLASS_NUM);
      for (dwJ = dwStart; dwJ < dwEnd; dwJ++)
      {
        dwClsIdx = pdwClassIdx[dwJ];
        adwClassNum[dwClsIdx]++;
        afClassScore[dwClsIdx] += pfClassScore[dwJ];
      }
      
      fMaxScore = afClassScore[0];
      dwMaxIdx = 0;
      for (dwJ = 1; dwJ < LPDR_CLASS_NUM; dwJ++)
      {
        if (fMaxScore < afClassScore[dwJ])
        {
          fMaxScore = afClassScore[dwJ];
          dwMaxIdx = dwJ;
        }
      }
      pdwLPNumber[dwLen] = dwMaxIdx;
      pfScores[dwLen] = fMaxScore/adwClassNum[dwMaxIdx];
      fAllScore += fMaxScore;
      dwLen++;
      dwStart = -1;
      dwEnd = -1;
    }
  }
  
  if (fAllScore < 6.f) return 1;
  
  pstOut->dwLPLen = dwLen;
  pstOut->fAllScore = fAllScore;
  
  return 0;
}






