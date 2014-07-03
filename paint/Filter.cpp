// Filter.cpp: implementation of the CFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "paint.h"
#include "Filter.h"
#include <math.h>
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
MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
//将位图选入到内存设备描述表  
//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
//先用背景色将位图清除干净，这里我用的是白色作为背景  
//你也可以用自己应该用的颜色  
MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//绘图  
for (int i = 0;i<x;++i)
{
	for (int j = 0;j<y;++j)
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

	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
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
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//绘图  

    int r,g,b;
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
		{
			COLORREF clr = pDC->GetPixel(i,j);
			COLORREF clr1=pDC->GetPixel(i-1,j-1);

			COLORREF clr2=pDC->GetPixel(i-1,j);

			int a[9]={clr,clr1,clr2};
			int m = 0,l = 0,n = 0;
			for(int k = 0;k < 3;k++)
			{
			
				m+=GetRValue(a[k]);
				l+=GetGValue(a[k]);
				n+=GetBValue(a[k]);				
			}
			r=m;g=l;b=n;
			r=r/3;g=g/3;b=b/3;
	        MemDC.SetPixel(i,j,RGB(r,g,b));

		}
	}

	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
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
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//绘图  

	
	int r,g,b,r1,g1,b1,r2,g2,b2;
	
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
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
			
 			r=(int)sqrt(float((r-r1)*(r-r1)+(r-r2)*(r-r2)));
 			g=(int)sqrt(float((g-g1)*(g-g1)+(g-g2)*(g-g2)));
			b=(int)sqrt(float((b-b1)*(b-b1)+(b-b2)*(b-b2)));
 			
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
    if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
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
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//绘图 

	int r,g,b,r1,g1,b1;
	
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
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
	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
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
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
	//绘图 



	int r,g,b,r1,g1,b1;
	
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
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
	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
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
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//将位图选入到内存设备描述表  
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//绘图  


	int r=0,g=0,b=0;
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
		{
			COLORREF clr[5];
			clr[0]=pDC->GetPixel(i,j);			
			clr[1]=pDC->GetPixel(i-1,j-1);			
			clr[2]=pDC->GetPixel(i-1,j+1);
			clr[3]=pDC->GetPixel(i+1,j-1);			
			clr[4]=pDC->GetPixel(i+1,j+1);

			for(int k = 0;k < 5;k++)
			{
			
				r+=GetRValue(clr[k]);
				g+=GetGValue(clr[k]);
				b+=GetBValue(clr[k]);				
			}
			r=r/5;g=g/5;b=b/5;
			MemDC.SetPixel(i-1,j-1,RGB(r,g,b));
			MemDC.SetPixel(i-1,j+1,RGB(r,g,b));
			MemDC.SetPixel(i,j,RGB(r,g,b));
			MemDC.SetPixel(i+1,j-1,RGB(r,g,b));
			MemDC.SetPixel(i+1,j+1,RGB(r,g,b));
		}
	}

	
	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY))
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
	
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的  
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图 
	CBitmap MemBitmap;   
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
 
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
	//绘图


	int r,g,b;
	
	for (int i = 0;i<x;++i)
	{
		for (int j = 0;j<y;++j)
		{
			int k=rand()%5;
			COLORREF clr[5];
			r=GetRValue(clr[k]);
			g=GetGValue(clr[k]);
			b=GetBValue(clr[k]);
			clr[0]=pDC->GetPixel(i,j);			
			clr[1]=pDC->GetPixel(i,j-1);			
			clr[2]=pDC->GetPixel(i-1,j);
			clr[3]=pDC->GetPixel(i+1,j);			
			clr[4]=pDC->GetPixel(i,j+1);
			
			MemDC.SetPixel(i,j,RGB(r,g,b));
		}
	}
	if (pDC->BitBlt(x1,y1,x,y,&MemDC,0,0,SRCCOPY) == 0)
		AfxMessageBox("错误！");
}

void CFilter::Grey(CDC *pDC, int x1, int y1, int x2, int y2)
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
            r=(r+g+b)/3;
            g=b=r;
			pDC->SetPixel(i,j,RGB(r,g,b));
		}
	}
}
