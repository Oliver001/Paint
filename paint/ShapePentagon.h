// ShapePentagon.h: interface for the CShapePentagon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEPENTAGON_H__EDE4E918_3D03_45E2_9496_7232020E4D57__INCLUDED_)
#define AFX_SHAPEPENTAGON_H__EDE4E918_3D03_45E2_9496_7232020E4D57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CShapePentagon : public CShape  
{
public:
	virtual void Draw(CDC*pDC);
	CShapePentagon();
	virtual ~CShapePentagon();

};

#endif // !defined(AFX_SHAPEPENTAGON_H__EDE4E918_3D03_45E2_9496_7232020E4D57__INCLUDED_)
