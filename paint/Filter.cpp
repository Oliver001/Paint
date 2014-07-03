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


void CFilter::Exposure(CDC *pDC, int x1, int y1, int x2, int y2)//�ع⴦��
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
	
//����һ���ڴ��豸��������󣨼��󱸻�������  
CDC MemDC;   
//����һ��λͼ����  
CBitmap MemBitmap;  
//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
MemDC.CreateCompatibleDC(NULL);  
//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
//��λͼѡ�뵽�ڴ��豸������  
//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
//��Ҳ�������Լ�Ӧ���õ���ɫ  
MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//��ͼ  
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
		AfxMessageBox("����");
}
void CFilter::Backward(CDC *pDC, int x1, int y1, int x2, int y2)//�淴����
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

void CFilter::Sleek(CDC *pDC, int x1, int y1, int x2, int y2)//ƽ������
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
	
	
	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//��ͼ  

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
		AfxMessageBox("����");
}

void CFilter::Neonred(CDC *pDC, int x1, int y1, int x2, int y2)//�޺紦��
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

	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//��ͼ  

	
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
		AfxMessageBox("����");
}

void CFilter::Sharpen(CDC *pDC, int x1, int y1, int x2, int y2)//�񻯴���
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
	
	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//��ͼ 

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
		AfxMessageBox("����");
}

void CFilter::Relief(CDC *pDC, int x1, int y1, int x2, int y2)//������
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
	

	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
	//��ͼ 



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
		AfxMessageBox("����");
}

void CFilter::Inlay(CDC *pDC, int x1, int y1, int x2, int y2)//��Ƕ����
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
	

	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	CBitmap MemBitmap;  
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	//��λͼѡ�뵽�ڴ��豸������  
	//ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
//��ͼ  


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
		AfxMessageBox("����");
}

void CFilter::Diffuse(CDC *pDC, int x1, int y1, int x2, int y2)//��ɢ����
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
	
	
	//����һ���ڴ��豸��������󣨼��󱸻�������  
	CDC MemDC;   
	//����һ��λͼ����  
	
	//��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	//���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ 
	CBitmap MemBitmap;   
	MemBitmap.CreateCompatibleBitmap(pDC,x,y);  
	  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  
 
	MemDC.FillSolidRect(0,0,x,y,RGB(255,255,255));  
	//��ͼ


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
		AfxMessageBox("����");
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
