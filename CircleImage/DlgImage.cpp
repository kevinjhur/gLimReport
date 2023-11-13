// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "CircleImage.h"
#include "DlgImage.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;
#include <string>
#include<time.h> 
#include<stdlib.h>
#include<chrono>

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DLGIMAGE, pParent)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

BOOL CDlgImage::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    InitDlgImage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 여기에 메시지 처리기 코드를 추가합니다.
                       // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
    if (m_ImageField != NULL) {
        m_ImageField.Draw(dc, 0, 0);
    }
}

void CDlgImage::InitDlgImage()
{
    int nWidth = 640;
    int nHeight = 640;
    int nBpp = 8;

    MoveWindow(0, 0, nWidth, nHeight);

    if (m_ImageField == NULL) {
        m_ImageField.Create(nWidth, -nHeight, nBpp);
    }
    
    if (8 == nBpp) {
        static RGBQUAD rgb[256];
        for (int i = 0; i < 256; i++)
        {
            rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
        }
        m_ImageField.SetColorTable(0, 256, rgb);
    }
    
    unsigned char* fm = (unsigned char*)m_ImageField.GetBits();

    memset(fm, 0xFF, (nWidth * nHeight));
}

void CDlgImage::drawCircle(unsigned int nRadius)
{
    unsigned int nWidth = m_ImageField.GetWidth();
    unsigned int nHeight = m_ImageField.GetHeight();
    int nPitch = m_ImageField.GetPitch();

    int minX = 0 + nRadius;
    int maxX = nWidth - nRadius;
    if (minX > maxX) {
        AfxMessageBox(_T("Radius is to big!!"), MB_OK);
        return;
    }
    int minY = 0 + nRadius;
    int maxY = nWidth - nRadius;
    if (minY > maxY) {
        AfxMessageBox(_T("Radius is to big!!"), MB_OK);
        return;
    }

    srand((int)GetTickCount64());
    
    unsigned int nCenterX = getRandomPoint(minX, maxX);
    unsigned int nCenterY = getRandomPoint(minY, maxY);
    unsigned int nTopX    = nCenterX - nRadius;
    unsigned int nTopY    = nCenterY - nRadius;
    unsigned int nBottomX = nCenterX + nRadius;
    unsigned int nBottomY = nCenterY + nRadius;

    cout << "Radius = " << nRadius << "\t" << "Center X = " << nCenterX << "\t" << "Center Y = " << nCenterY << endl;

    CClientDC dc(this);
    CRect rect(nTopX, nTopY, nBottomX, nBottomY);;
    GetClientRect(&rect);

    dc.FillSolidRect(&rect, RGB(255, 255, 255));


    CPen  blackPen(PS_SOLID, 2, RGB(0x00, 0x00, 0x00)); //Black pen
    CPen* OldPen = dc.SelectObject(&blackPen); // backup black pen

    CPen yellowPen(PS_SOLID, 2, RGB(0xFF, 0xFF, 0x00)); //Yellow pen
    dc.SelectObject(yellowPen);

    dc.Ellipse(nTopX, nTopY, nBottomX, nBottomY);

    // Calculate center X & Y.
    unsigned int nSumX = 0;
    unsigned int nSumY = 0;
    unsigned int nCount = 0;

    for (int j = rect.top; j < rect.bottom; j++) {
        for (int i = rect.left; i < rect.right; i++) {
            if (TRUE == isInCircle(i, j, nCenterX, nCenterY, nRadius)) {
                nSumX += i;
                nSumY += j;
                nCount++;
            }
            else {
                //
            }
        }
    }

    cout << "nSumX = " << nSumX << "\t" << "nSumY = " << nSumY << "\t" << "nCount = " << nCount << endl;

    double dCenterX = (double)nSumX / nCount;
    double dCenterY = (double)nSumY / nCount;
    cout << "Calculated center X = " << dCenterX << "\t" << "Calculated center Y = " << dCenterY << endl;


    //Draw cross with black pen at calcualted center
    dc.SelectObject(OldPen); // restore black pen.

    unsigned int nCrossSize = nRadius / 5;
    dc.MoveTo(dCenterX - nCrossSize, dCenterY);
    dc.LineTo(dCenterX + nCrossSize +1, dCenterY);
    dc.MoveTo(dCenterX, dCenterY - nCrossSize);
    dc.LineTo(dCenterX, dCenterY + nCrossSize + 1);
}

unsigned int CDlgImage::getRandomPoint(unsigned int min, unsigned int max)
{
    return (rand() % (max - min + 1) + min);
}

bool CDlgImage::isInCircle(int i, int j, int nCenterX, int nCenterY, unsigned int nRadius)
{
    bool nReturn = FALSE;

    double dX = i - nCenterX;
    double dY = j - nCenterY;
    double dDist = dX * dX + dY * dY;

    if (dDist <= (nRadius * nRadius)) {
        nReturn = TRUE;
    }
    else {
        nReturn = FALSE;
    }

    return nReturn;
}

