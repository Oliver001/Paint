// Filter.cpp: implementation of the CFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "Filter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilter::CFilter()
{

}

CFilter::~CFilter()
{

}


void CFilter::Exposure(CDC *pDC, int x1, int y1, int x2, int y2)//曝光处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	
	int r,g,b;
	
//定义一个内存设备描述表对象（即后备缓冲区）  
CDC MemDC;   
//定义一个位图对象  
CBitmap MemBitmap;  
//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
MemDC.CreateCompatibleDC(NULL);  
//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
MemBitmap.CreateCompatibleBitmap(pDC,800,600);  
//将位图选入到内存设备描述表  
//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
//先用背景色将位图清除干净，这里我用的是白色作为背景  
//你也可以用自己应该用的颜色  
MemDC.FillSolidRect(0,0,800,600,RGB(255,255,255));  
//绘图  
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
			
			
			if (r<128)r=255-r;
			if(g<128)g=255-g;
			if(b<128)b=255-b;
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}

	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}
void CFilter::Backward(CDC *pDC, int x1, int y1, int x2, int y2)//逆反处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	
	int r,g,b;
	
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
			
			
			r=255-r;
			g=255-g;
			b=255-b;
			pDC->SetPixel(i,j,RGB(r,g,b));
		}
	}

}

void CFilter::Sleek(CDC *pDC, int x1, int y1, int x2, int y2)//平滑处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	
	
	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,x2-x1,y2-y1);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x2-x1,y2-y1,RGB(255,255,255));  
//绘图  

    int r,g,b;//,r1,g1,b1,r2,g2,b2,r3,g3,b3,r4,g4,b4,r5,g5,b5,r6,g6,b6,r7,g7,b7,r8,g8,b8;
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			COLORREF clr1=pDC->GetPixel(i-1,j-1);
			COLORREF clr2=pDC->GetPixel(i,j-1);
			COLORREF clr3=pDC->GetPixel(i+1,j-1);
			COLORREF clr4=pDC->GetPixel(i-1,j);
			COLORREF clr5=pDC->GetPixel(i+1,j);
			COLORREF clr6=pDC->GetPixel(i-1,j+1);
			COLORREF clr7=pDC->GetPixel(i,j+1);
			COLORREF clr8=pDC->GetPixel(i+1,j+1);
			int a[9]={clr,clr1,clr2,clr3,clr4,clr5,clr6,clr7,clr8};
			int m = 0,l = 0,n = 0;
			for(int k = 0;k < 9;k++)
			{
			
				m+=GetRValue(a[k]);
				l+=GetGValue(a[k]);
				n+=GetBValue(a[k]);				
			}
			r=m;g=l;b=n;
			r=r/9;g=g/9;b=b/9;
	        MemDC.SetPixel(i,j,RGB(r,g,b));
	/*   	r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
			r1=GetRValue(clr1);
			g1=GetGValue(clr1);
			b1=GetBValue(clr1);
			r2=GetRValue(clr2);
			g2=GetGValue(clr2);
			b2=GetBValue(clr2);
			r3=GetRValue(clr3);
			g3=GetGValue(clr3);
			b3=GetBValue(clr3);
			r4=GetRValue(clr4);
			g4=GetGValue(clr4);
			b4=GetBValue(clr4);
			r5=GetRValue(clr5);
			g5=GetGValue(clr5);
			b5=GetBValue(clr5);
			r6=GetRValue(clr6);
			g6=GetGValue(clr6);
			b6=GetBValue(clr6);
			r7=GetRValue(clr7);
			g7=GetGValue(clr7);
			b7=GetBValue(clr7);
			r8=GetRValue(clr8);
			g8=GetGValue(clr8);
			b8=GetBValue(clr8);
			
			r=(r+r1+r2+r3+r4+r5+r6+r7+r8)/9;
			g=(g+g1+g2+g3+g4+g5+g6+g7+g8)/9;
            b=(b+b1+b2+b3+b4+b5+b6+b7+b8)/9;
            9*/
	
		}
	}

	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Neonred(CDC *pDC, int x1, int y1, int x2, int y2)//霓虹处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;

	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,800,600);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,800,600,RGB(255,255,255));  
//绘图  

	
	int r,g,b,r1,g1,b1,r2,g2,b2;
	
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
  
			
			COLORREF clr1=pDC->GetPixel(i+1,j);
			COLORREF clr2=pDC->GetPixel(i,j+1);


			r1=GetRValue(clr1);
			g1=GetGValue(clr1);
			b1=GetBValue(clr1);
			
			
			r2=GetRValue(clr2);
			g2=GetGValue(clr2);
			b2=GetBValue(clr2);
			
			r=sqrt((r-r1)*(r-r1)+(r-r2)*(r-r2));
			g=sqrt((g-g1)*(g-g1)+(g-g2)*(g-g2));
            b=sqrt((b-b1)*(b-b1)+(b-b2)*(b-b2));
			
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
    if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Sharpen(CDC *pDC, int x1, int y1, int x2, int y2)//锐化处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	
	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,800,600);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,800,600,RGB(255,255,255));  
//绘图 

	int r,g,b,r1,g1,b1;
	
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
			

			COLORREF clr1=pDC->GetPixel(i-1,j-1);
			r1=GetRValue(clr1);
			g1=GetGValue(clr1);
			b1=GetBValue(clr1);
			
			r = r - abs(r - r1);
			g = g - abs(g - g1);
			b = b - abs(b - b1);
                        
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Relief(CDC *pDC, int x1, int y1, int x2, int y2)//浮雕处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	

	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,800,600);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,800,600,RGB(255,255,255));  
	//绘图 



	int r,g,b,r1,g1,b1;
	
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			r=GetRValue(clr);
			g=GetGValue(clr);
			b=GetBValue(clr);
	
			COLORREF clr1=pDC->GetPixel(i-1,j);
			r1=GetRValue(clr1);
			g1=GetGValue(clr1);
			b1=GetBValue(clr1);
			
			r=r-r1+128;
			g=g-g1+128;
            b=b-b1+128;
			
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Inlay(CDC *pDC, int x1, int y1, int x2, int y2)//镶嵌处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	

	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,x2-x1,y2-y1);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x2-x1,y2-y1,RGB(255,255,255));  
//绘图  


	int r=0,g=0,b=0;//,r1,g1,b1,r2,g2,b2,r3,g3,b3,r4,g4,b4,r5,g5,b5,r6,g6,b6,r7,g7,b7,r8,g8,b8;
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			COLORREF clr[25];
			 clr[0] = pDC->GetPixel(i,j);
// 			 clr[1]=pDC->GetPixel(i-2,j-2);
// 			 clr[2]=pDC->GetPixel(i-1,j-2);
// 			 clr[3]=pDC->GetPixel(i,j-2);
// 			 clr[4]=pDC->GetPixel(i+1,j-2);
// 			 clr[5]=pDC->GetPixel(i+2,j-2);
// 			 clr[6]=pDC->GetPixel(i-2,j-1);
			 clr[1]=pDC->GetPixel(i-1,j-1);
			 clr[2]=pDC->GetPixel(i,j-1);
			 clr[3]=pDC->GetPixel(i+1,j-1);
// 			 clr[10]=pDC->GetPixel(i+2,j-1);
//              clr[11]=pDC->GetPixel(i-2,j);
			 clr[4]=pDC->GetPixel(i-1,j);
			 clr[5]=pDC->GetPixel(i+1,j);
// 			 clr[14]=pDC->GetPixel(i+2,j);
// 			 clr[15]=pDC->GetPixel(i-2,j+1);
			 clr[6]=pDC->GetPixel(i-1,j+1);
			 clr[7]=pDC->GetPixel(i,j+1);
			 clr[8]=pDC->GetPixel(i+1,j+1);
// 			 clr[19]=pDC->GetPixel(i+2,j+1);
// 			 clr[20]=pDC->GetPixel(i-2,j+2);
// 			 clr[21]=pDC->GetPixel(i-1,j+2);
// 			 clr[22]=pDC->GetPixel(i,j+2);
// 			 clr[23]=pDC->GetPixel(i+1,j+2);
// 			 clr[24]=pDC->GetPixel(i+2,j+2);
		//	int a[25]={clr,clr1,clr2,clr3,clr4,clr5,clr6,clr7,clr8,clr9,clr10,clr11,clr12,clr13,clr14,clr15,clr16,clr17,clr18,clr19,clr20,clr21,clr22,clr23,clr24};
			
		//	int m = 0,l = 0,n = 0;	
			for(int k = 0;k < 9;k++)
			{
			
				r+=GetRValue(clr[k]);
				g+=GetGValue(clr[k]);
				b+=GetBValue(clr[k]);				
			}

			r/=9;g/=9;b/=9;
//       	r=m;g=l;b=n;
// 			r=GetRValue(clr);
// 			g=GetGValue(clr);
// 			b=GetBValue(clr);
// 			r1=GetRValue(clr1);
// 			g1=GetGValue(clr1);
// 			b1=GetBValue(clr1);
// 			r2=GetRValue(clr2);
// 			g2=GetGValue(clr2);
// 			b2=GetBValue(clr2);
// 			r3=GetRValue(clr3);
// 			g3=GetGValue(clr3);
// 			b3=GetBValue(clr3);
// 			r4=GetRValue(clr4);
// 			g4=GetGValue(clr4);
// 			b4=GetBValue(clr4);
// 			r5=GetRValue(clr5);
// 			g5=GetGValue(clr5);
// 			b5=GetBValue(clr5);
// 			r6=GetRValue(clr6);
// 			g6=GetGValue(clr6);
// 			b6=GetBValue(clr6);
// 			r7=GetRValue(clr7);
// 			g7=GetGValue(clr7);
// 			b7=GetBValue(clr7);
// 			r8=GetRValue(clr8);
// 			g8=GetGValue(clr8);
// 			b8=GetBValue(clr8);
// 			
// 			r=(r+r1+r2+r3+r4+r5+r6+r7+r8)/9;
// 			g=(g+g1+g2+g3+g4+g5+g6+g7+g8)/9;
//           b=(b+b1+b2+b3+b4+b5+b6+b7+b8)/9;

// 			MemDC.SetPixel(i-2,j-2,RGB(r,g,b));
// 			MemDC.SetPixel(i-1,j-2,RGB(r,g,b));
// 			MemDC.SetPixel(i,j-2,RGB(r,g,b));
// 			MemDC.SetPixel(i+1,j-2,RGB(r,g,b));
// 			MemDC.SetPixel(i+2,j-2,RGB(r,g,b));
// 			MemDC.SetPixel(i-2,j-1,RGB(r,g,b));
			MemDC.SetPixel(i-1,j-1,RGB(r,g,b));
			MemDC.SetPixel(i,j-1,RGB(r,g,b));
			MemDC.SetPixel(i+1,j-1,RGB(r,g,b));
// 			MemDC.SetPixel(i+2,j-1,RGB(r,g,b));
// 			MemDC.SetPixel(i-2,j,RGB(r,g,b));
			MemDC.SetPixel(i-1,j,RGB(r,g,b));
			MemDC.SetPixel(i,j,RGB(r,g,b));
			MemDC.SetPixel(i+1,j,RGB(r,g,b));
// 			MemDC.SetPixel(i+2,j,RGB(r,g,b));
// 			MemDC.SetPixel(i-2,j+1,RGB(r,g,b));
			MemDC.SetPixel(i-1,j+1,RGB(r,g,b));
			MemDC.SetPixel(i,j+1,RGB(r,g,b));
			MemDC.SetPixel(i+1,j+1,RGB(r,g,b));
// 			MemDC.SetPixel(i+2,j+1,RGB(r,g,b));
// 			MemDC.SetPixel(i-2,j+2,RGB(r,g,b));
// 			MemDC.SetPixel(i-1,j+2,RGB(r,g,b));
// 			MemDC.SetPixel(i,j+2,RGB(r,g,b));
// 			MemDC.SetPixel(i+1,j+2,RGB(r,g,b));
// 			MemDC.SetPixel(i+2,j+2,RGB(r,g,b));

		}
	}

	pDC->BitBlt(0,0,800,600,&MemDC,0,0,SRCCOPY);
	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Diffuse(CDC *pDC, int x1, int y1, int x2, int y2)//扩散处理
{
	if (x2<x1)
	{
		int temp = x1;
		x1=x2;
		x2=temp;
	}
	if (y2<y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	int x = x2-x1;
	int y = y2-y1;
	
	
	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC MemDC;   
	//定义一个位图对象  
	CBitmap MemBitmap;  
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图  
	MemBitmap.CreateCompatibleBitmap(pDC,800,600);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,800,600,RGB(255,255,255));  
	//绘图


	int r,g,b;
	
	for (int i = x1;i<x2;++i)
	{
		for (int j = y1;j<y2;++j)
		{
			int k=rand()%25;
			COLORREF clr[25];
			r=GetRValue(clr[k]);
			g=GetGValue(clr[k]);
			b=GetBValue(clr[k]);
			clr[0] = pDC->GetPixel(i,j);
			clr[1]=pDC->GetPixel(i-2,j-2);
			clr[2]=pDC->GetPixel(i-1,j-2);
			clr[3]=pDC->GetPixel(i,j-2);
			clr[4]=pDC->GetPixel(i+1,j-2);
			clr[5]=pDC->GetPixel(i+2,j-2);
			clr[6]=pDC->GetPixel(i-2,j-1);
			clr[1]=pDC->GetPixel(i-1,j-1);
			clr[2]=pDC->GetPixel(i,j-1);
			clr[3]=pDC->GetPixel(i+1,j-1);
			clr[10]=pDC->GetPixel(i+2,j-1);
			clr[11]=pDC->GetPixel(i-2,j);
			clr[4]=pDC->GetPixel(i-1,j);
			clr[5]=pDC->GetPixel(i+1,j);
			clr[14]=pDC->GetPixel(i+2,j);
			clr[15]=pDC->GetPixel(i-2,j+1);
			clr[6]=pDC->GetPixel(i-1,j+1);
			clr[7]=pDC->GetPixel(i,j+1);
			clr[8]=pDC->GetPixel(i+1,j+1);
			clr[19]=pDC->GetPixel(i+2,j+1);
			clr[20]=pDC->GetPixel(i-2,j+2);
			clr[21]=pDC->GetPixel(i-1,j+2);
			clr[22]=pDC->GetPixel(i,j+2);
			clr[23]=pDC->GetPixel(i+1,j+2);
			clr[24]=pDC->GetPixel(i+2,j+2);				
			
			
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
	if (pDC->BitBlt(x1,y1,x2,y2,&MemDC,x1,y1,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}
