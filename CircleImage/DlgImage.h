#pragma once

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

private:
	//int lineWidth = 3;

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();
	CImage m_ImageField;
	void InitDlgImage();
	void drawCircle(unsigned int nRadius);
	unsigned int getRandomPoint(unsigned int min, unsigned int max);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, unsigned int nRadius);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
